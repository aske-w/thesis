//
// Created by Aske Wachs on 03/02/2024.
//

#ifndef THESIS_SPATIALPARQUET_JAVA_PORT_HPP
#define THESIS_SPATIALPARQUET_JAVA_PORT_HPP

#include <vector>
#include "helpers/types.hpp"

namespace algorithms {

class spatialparquet_java_port {
public:
    static std::unique_ptr<byte_t*> encode(const std::vector<double_t>& in);
    static void decode(const std::vector<byte_t>& in, std::vector<double_t>& out);
};


} // algorithms
#endif //THESIS_SPATIALPARQUET_JAVA_PORT_HPP
