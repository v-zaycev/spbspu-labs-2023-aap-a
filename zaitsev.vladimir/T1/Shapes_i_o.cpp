#include "Shapes_i_o.h"
#include <string>
#include <cstdlib>
#include <cstring>
#include <stdexcept>
#include <cstddef>
#include "base-types.hpp"
#include "shape.hpp"
#include "rectangle.hpp"
#include "complexquad.hpp"
#include "parallelogram.hpp"
#include "Geom_functions.h"

double zaitsev::readNextValue(char* param)
{
  static char* strtok_context = nullptr;
  char* pos = strtok_r(param, " ", std::addressof(strtok_context));
  char* ptr = nullptr;
  double val = std::strtod(pos, std::addressof(ptr));
  if (val == 0 && ptr == pos)
  {
    throw std::invalid_argument("Read value is not a number");
  }
  return val;
}

zaitsev::Shape* zaitsev::readRectangle(char* param)
{
  point_t left = { 0,0 };
  point_t right = { 0,0 };
  Shape* res = nullptr;
  try
  {
    left.x = readNextValue(param);
    left.y = readNextValue(nullptr);
    right.x = readNextValue(nullptr);
    right.y = readNextValue(nullptr);
    res = new Rectangle(left, right);
  }
  catch (std::invalid_argument&)
  {
    return nullptr;
  }

  return res;
}

zaitsev::Shape* zaitsev::readComplexquad(char* param)
{
  point_t vertices[4] = {};
  Shape* res = nullptr;
  try
  {
    for (size_t i = 0; i < 4; ++i)
    {
      vertices[i].x = readNextValue(i == 0 ? param : nullptr);
      vertices[i].y = readNextValue(nullptr);
    }
    res = new Complexquad(vertices);
  }
  catch (std::invalid_argument&)
  {
    return nullptr;
  }

  return res;
}

zaitsev::Shape* zaitsev::readParallelogram(char* param)
{
  point_t vertices[3] = {};
  Shape* res = nullptr;
  try
  {
    for (size_t i = 0; i < 3; ++i)
    {
      vertices[i].x = readNextValue(i == 0 ? param : nullptr);
      vertices[i].y = readNextValue(nullptr);
    }
    res = new Parallelogram(vertices);
  }
  catch (std::invalid_argument&)
  {
    return nullptr;
  }

  return res;
}

void zaitsev::readScale(char* param, point_t& center, double& factor)
{
  double x = readNextValue(param);
  double y = readNextValue(nullptr);
  double read_factor = readNextValue(nullptr);

  factor = read_factor;
  center.x = x;
  center.y = y;
}

std::ostream& zaitsev::shapesOutput(std::ostream& output, const Shape* const* shapes, size_t size)
{
  std::ios format_holder(nullptr);
  format_holder.copyfmt(output);
  output.precision(1);
  output.setf(std::ios::fixed);

  double area = 0;
  for (size_t i = 0; i < size; ++i)
  {
    area+=shapes[i]->getArea();
  }

  output << area;

  for (size_t i = 0; i < size; ++i)
  {
    rectangle_t frame = shapes[i]->getFrameRect();
    output << " " << frame.pos.x - frame.width / 2 << " " << frame.pos.y - frame.height / 2;
    output << " " << frame.pos.x + frame.width / 2 << " " << frame.pos.y + frame.height / 2;
  }
  output << "\n";
  output.copyfmt(format_holder);
  return output;
}