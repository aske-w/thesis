//
// Created by Aske Wachs on 08/02/2024.
//

#include <catch2/catch_test_macros.hpp>
#include <catch2/generators/catch_generators_adapters.hpp>
#include <catch2/generators/catch_generators_random.hpp>
#include <cstdint>
#include <random>
#include "helpers/bitstream.hpp"

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