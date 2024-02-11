#ifndef ALGORITHMS_SPATIALPARQUET_JAVA_PORT_HPP
#define ALGORITHMS_SPATIALPARQUET_JAVA_PORT_HPP

//
// Created by Aske Wachs on 03/02/2024.
//

#include <vector>
#include "helpers/types.hpp"


namespace thesis {
namespace algorithms {

using thesis::helpers::byte_t;
using thesis::helpers::double_t;

class SpatialParquetJavaPort {
public:
    static std::unique_ptr<byte_t *> Encode(const std::vector<double_t> &in);
    static std::unique_ptr<std::vector<double_t>> Decode(const std::vector<byte_t> &in);
};


} // algorithms
} // thesis
#endif //ALGORITHMS_SPATIALPARQUET_JAVA_PORT_HPP

