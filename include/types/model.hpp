#pragma once

#include <string>
#include <vector>

#include <types.hpp>

struct Model {
  std::vector<Vertex> vertices;
  std::vector<uint16_t> indices;

  static Model load(std::string path);
};