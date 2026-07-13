#include "image.hpp"

pixel& image::at(int x, int y) {
  // assert(x >= 0);
  // assert(x < w);
  // assert(y >= 0);
  // assert(y < h);

  return pixels[y * w + x];
}

const pixel& image::at(int x, int y) const {
  // assert(x >= 0);
  // assert(x < w);
  // assert(y >= 0);
  // assert(y < h);

  return pixels[y * w + x];
}

void image::load(unsigned char* data) {
  raw_data = data;

  // populate pixels
  int n_pixels = w*h;
  pixels = new pixel[n_pixels];
  for(int i = 0; i < n_pixels; i++) {
    pixels[i].r = raw_data[i*3+0];
    pixels[i].g = raw_data[i*3+1];
    pixels[i].b = raw_data[i*3+2];
  }
}
