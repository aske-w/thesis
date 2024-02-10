//
// Created by Aske Wachs on 10/02/2024.
//

#ifndef THESIS_GENERATORS_HPP
#define THESIS_GENERATORS_HPP

#include <vector>
#include "helpers/types.hpp"
#include <catch2/generators/catch_generators_all.hpp>

class DoubleVectorGenerator : Catch::Generators::IGenerator<std::vector<double_t>> {

};

#endif //THESIS_GENERATORS_HPP
