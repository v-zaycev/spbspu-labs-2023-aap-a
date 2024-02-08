#ifndef SHAPES_I_O_H
#define SHAPES_I_O_H
#include <ostream>
#include <cstddef>
#include "base-types.hpp"
#include "shape.hpp"

namespace zaitsev
{
  double readNextValue(char* param);
  Shape* readRectangle(char* param);
  Shape* readComplexquad(char* param);
  Shape* readParallelogram(char* param);
  void readScale(char* param, point_t& center, double& factor);
  std::ostream& shapesOutput(std::ostream& output, const Shape* const* shapes, size_t size);
}
#endif