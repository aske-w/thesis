//
// Created by Aske Wachs on 08/02/2024.
//

#include <catch2/catch_test_macros.hpp>
#include <catch2/generators/catch_generators_adapters.hpp>
#include <catch2/generators/catch_generators_random.hpp>
#include <cstdint>
#include <random>
#include "helpers/bitstream.hpp"

using std::pair;

TEST_CASE("write single uint64_t on aligned byte boundary", "[bitstream]") {
    auto x = GENERATE(take(50, random(0ull, UINT64_MAX)));
    bitstream b;
    const auto size = 8ull;
    byte_t dest[size];
    b.open_write(dest, size);
    b.write(x, 64);
    auto result = *reinterpret_cast<uint64_t*>(dest);
    REQUIRE(x == result);
}

TEST_CASE("write multiple uint64_t on aligned byte boundary", "[bitstream]") {
    auto count = GENERATE(take(50, random(2,50)));
    auto rng = GENERATE_COPY(RandomIntegerGenerator(0ull, UINT64_MAX, count));

    std::vector<uint64_t> numbers;
    const auto size = sizeof(uint64_t) * count;
    byte_t dest[size];
    bitstream b;
    b.open_write(dest, size);
    for (int i = 0; i < count; i++) {
        auto n = rng.get(); rng.next();
        numbers.push_back(n);
        b.write(n, sizeof(uint64_t) * 8);
    }
    auto dest_ints = reinterpret_cast<uint64_t*>(dest);
    for (int i = 0; i < count; i++) {
        REQUIRE(numbers.at(i) == dest_ints[i]);
    }
}

TEST_CASE("write single uint64 with unaligned bits", "[bitstream]") {
    auto x = GENERATE(take(50, random(0ull, UINT64_MAX)));
    auto bits = GENERATE(filter([](uint32_t x) { return (x + 1) % 8 != 0; }, take(50, random(0u, 63u))));

    bitstream b;
    const auto size = sizeof(uint64_t);
    byte_t dest[size];
    b.open_write(dest, size);
    b.write(x, bits);
    auto result = *reinterpret_cast<uint64_t*>(dest);
    auto mask = ~(-1ull << bits);
    REQUIRE((x & mask) == result);
}

TEST_CASE("write multiple uint64 with unaligned bits", "") {
    std::vector<std::pair<uint64_t, uint32_t>> val_and_bits {
        pair(0b111ull, 3u),
        pair(0b100001ull, 6u),
        pair(0b111ull, 3u),
        pair(0b000ull, 3u),
        pair(0b10101010101010101010ull, 21u),
    };

    const auto total_bits = 3 + 6 + 3 + 3 + 21;
    const auto zeroing_mask = ~(-1ull << total_bits);
    uint64_t expected = 0b10101010101010101010'000'111'100001'111ull & zeroing_mask;

    const uint32_t size = total_bits / 8 + 1;
    bitstream b;
    byte_t dest[size];
    b.open_write(dest, size);

    for (auto pair : val_and_bits) {
        b.write(pair.first, pair.second);
    }

    uint64_t result = (*reinterpret_cast<uint64_t*>(dest)) & zeroing_mask;
    REQUIRE(expected == result);
}

TEST_CASE("write different types", "") {

    const uint32_t size =  19;
//    const auto zeroing_mask = ~(-1ull << total_bits);
    bitstream b;
    byte_t dest[size];
    auto result = reinterpret_cast<uint64_t*>(dest);
    b.open_write(dest, size);

    b.write('f', 8u);
    b.write('o', 8u);
    b.write('o', 8u);
    CHECK(((*result) & ~(-1ull << 24)) == 0x6F6F66);

    b.write('b', 8u);
    b.write('a', 8u);
    b.write('r', 8u);
    b.write('\0', 8u);
    CHECK(((*result) & ~(-1ull << (24 + 32))) == 0x007261626F6F66);

    b.write(0b1011'1001ull, 8u);
    CHECK((*result) == 0xB9007261626F6F66);

    // end of first 8 bytes
    result++;

    b.write(-1ull, 64u);
    CHECK((*result) == -1ull);

    // end of second 8 bytes
    result++;

    struct foo {
        char a;
        char b;
        char c;
    };

    b.write<foo>({'a', 'b', 'c'}, 24u);
    auto foo_result = std::make_unique<char*>(new char[]{'a', 'b', 'c'});
    CHECK((*reinterpret_cast<char*>(result)) == **foo_result);

//    REQUIRE(expected == ((*result) & zeroing_mask));
}