//
// Created by Aske Wachs on 10/02/2024.
//

#include <vector>
#include <catch2/catch_test_macros.hpp>
#include <catch2/generators/catch_generators_all.hpp>
#include "algorithms/spatialparquet_java_port.hpp"

using std::vector;
using std::pair;
using thesis::algorithms::SpatialParquetJavaPort;
using thesis::helpers::byte_t;
using thesis::helpers::double_t;

vector<double_t> y {
    0.29153299448411635,
    0.2911873864580658,
    0.20677793021909396,
    0.23072017575808126,
    0.23719305448543823,
    0.29153299448411635,

    0.4851116025698806,
    0.5086904283730526,
    0.5260381071986735,
    0.4867658765008961,
    0.4857058897476151,
    0.43578904481572556,
    0.4468897747952226,
    0.4526046340329243,
    0.45862798234942403,
    0.4851116025698806,

    0.8262849560465205,
    0.8301569154256792,
    0.7382511412966556,
    0.7401851320126335,
    0.7629199108532835,
    0.8262849560465205
};
vector<byte_t> y_expected { 0x40,0x7f,0xa5,0x50,0xf4,0x02,0x81,0xd2,0x3a,0x00,0x00,0x0b,0x53,0x2b,0x95,0xa5,0xcb,0x00,0x10,0x56,0x3a,0xd7,0x18,0xd3,0x4d,0x00,0x06,0x21,0x14,0x39,0x95,0x2f,0x42,0x00,0x01,0xa8,0x34,0xe2,0x71,0xe9,0xb4,0x00,0x08,0x98,0x44,0xe6,0xa7,0x60,0x24,0x00,0x18,0xc7,0x2f,0x0f,0x77,0x7e,0xda,0x00,0x02,0x76,0x3f,0x3a,0x70,0x50,0x92,0x00,0x01,0x1c,0x39,0x70,0x4d,0xec,0x66,0x00,0x03,0x5c,0x43,0x9c,0x86,0xe6,0x27,0x00,0x00,0x22,0xbb,0xd0,0x38,0x42,0xaf,0x00,0x06,0x63,0xac,0xd8,0x40,0x40,0x83,0x00,0x01,0x6b,0xbf,0xac,0x1c,0xa1,0x1c,0x00,0x00,0xbb,0x43,0xb6,0xc3,0x7a,0x60,0x00,0x00,0xc5,0x5f,0x82,0x04,0x11,0x78,0x00,0x03,0x63,0xd0,0xb5,0x5c,0xff,0x70,0x00,0x16,0xc9,0xb7,0x39,0xe0,0x10,0xde,0x00,0x00,0x3f,0x70,0x2c,0xb9,0xea,0x52,0x00,0x05,0xe1,0xc8,0xc1,0x8c,0xa7,0x6d,0x00,0x00,0x1f,0xaf,0xbe,0xb8,0x0e,0xa0,0x00,0x01,0x74,0x7c,0x92,0xe6,0x8d,0x78,0x00,0x04,0x0e,0x2c,0x43,0x34,0x21,0x04 };
vector<byte_t> x_expected { 0x34,0xff,0xff,0xff,0xff,0xff,0xff,0xf7,0xfc,0x52,0xe0,0x6b,0x4c,0xbf,0x05,0xe1,0x78,0x8b,0xbd,0xbf,0x90,0xb5,0x30,0x20,0x2f,0x12,0xfe,0xa2,0x80,0xe1,0x91,0xfb,0xfb,0xcf,0x8a,0x01,0x2e,0x31,0xd4,0xf4,0x2b,0x82,0x7d,0xec,0x4c,0xbb,0x6b,0xb3,0xb5,0x2d,0x93,0x25,0x24,0xff,0xf1,0x72,0x26,0x5a,0x56,0x2f,0xbd,0x4b,0x5d,0x6d,0x90,0x3e,0xee,0x56,0x63,0x9b,0x19,0x00,0xb3,0xd5,0x00,0x73,0xa6,0x3a,0x95,0x86,0xf2,0x7c,0x02,0x31,0x89,0xd1,0xec,0x8f,0xe7,0x7f,0x14,0x27,0xe2,0xa0,0x74,0x32,0x5f,0x77,0xe3,0x5a,0x05,0x89,0xbe,0x56,0x02,0x09,0x20,0x4b,0x8a,0x48,0x5f,0xd6,0xe8,0x3e,0xe4,0x4b,0xb2,0x57,0x13,0xa0,0xac,0xc3,0xca,0x20,0x1e,0x57,0x2c,0xfb,0x73,0x5a,0x0b,0x49,0x11,0x3c,0xa9,0x28,0xa1,0xbb,0x0c,0x3a,0xaf,0x54,0xec,0x8c,0x7d,0x21,0x6b,0x23,0x77,0xa9,0xaf,0xf3 };
vector<double_t> x {
    0.5809342160789636,
    0.5579516804295914,
    0.6049494522023027,
    0.6187171677305706,
    0.6198699488572298,
    0.5809342160789636,

    0.45200127478460933,
    0.4407051988590682,
    0.40390590537482557,
    0.3539911760577602,
    0.3537705924635862,
    0.37318003363776153,
    0.44344579673228807,
    0.44699184071516307,
    0.44969597184133264,
    0.45200127478460933,

    0.48271015175681664,
    0.47743778838585094,
    0.4554738094416186,
    0.4651375294196905,
    0.49379226066367854,
    0.48271015175681664
};

TEST_CASE("x becomes same as java", "") {
    const auto data_tuple = GENERATE(pair(x, x_expected), pair(y, y_expected));
    const auto input = data_tuple.first;
    const auto expected = data_tuple.second;
    const auto result = SpatialParquetJavaPort::Encode(input);
    const auto result_bytes = *result;
    const auto size = expected.size();
    for(uint8_t i = 0; i < size; i++) {
        REQUIRE(expected.at(i) == result_bytes[i]);
    }
}

TEST_CASE("decoding encoded data is identity", "") {
    const auto data_tuple = GENERATE(pair(x, x_expected), pair(y, y_expected));
    const auto input = data_tuple.first;
    const auto expected = data_tuple.second;
    const auto encoded_input_ptr = SpatialParquetJavaPort::Encode(input);

    const auto encoded_input_ptr_bytes = *encoded_input_ptr;
    const auto size = expected.size();
    for(uint8_t i = 0; i < size; i++) {
        REQUIRE(expected.at(i) == encoded_input_ptr_bytes[i]);
    }

    vector<byte_t> encoded_input(*encoded_input_ptr, (*encoded_input_ptr) + expected.size());
    const auto decoded_encoded_input = SpatialParquetJavaPort::Decode(encoded_input);
    REQUIRE(input.size() == decoded_encoded_input->size());
}

TEST_CASE("encoding decoded data is identity", "") {
    const pair<vector<double_t>, vector<byte_t>> data_tuple = GENERATE(pair(x, x_expected), pair(y, y_expected));
    const auto input = data_tuple.second;
    const auto expected = data_tuple.first;

    const vector<double_t> decoded_input = *SpatialParquetJavaPort::Decode(input);
    const byte_t* encoded_input = *SpatialParquetJavaPort::Encode(decoded_input);


    const auto size = expected.size();
    for(uint8_t i = 0; i < size; i++) {
        REQUIRE(input.at(i) == encoded_input[i]);
    }
}
