#include "util.hpp"

std::array<unsigned char, 3> util::hex_to_rgb(unsigned int hex) {
  return {
    static_cast<unsigned char>((hex >> 16) & 0xFF),
    static_cast<unsigned char>((hex >> 8) & 0xFF),
    static_cast<unsigned char>(hex & 0xFF)
  };
}

unsigned int util::fast_rand() {
  unsigned int state = 4431;
  state += 0xa0761d6478bd642fULL;
  __uint128_t m = (__uint128_t)state * (state ^ 0xe7037ed1a0b428dbULL);
  return (m >> 64) ^ m;
}
