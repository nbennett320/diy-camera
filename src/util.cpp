#include "util.hpp"

std::array<unsigned char, 3> util::hex_to_rgb(unsigned int hex) {
  return {
    static_cast<unsigned char>((hex >> 16) & 0xFF),
    static_cast<unsigned char>((hex >> 8) & 0xFF),
    static_cast<unsigned char>(hex & 0xFF)
  };
}
