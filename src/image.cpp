#include "image.hpp"
#include "util.hpp"

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
  buffer_pixel_matrix();
}

void image::buffer_pixel_matrix() {
  // populate pixels
  int n_pixels = w*h;
  pixels = new pixel[n_pixels];
  for(int i = 0; i < n_pixels; i++) {
    pixels[i].r = raw_data[i*3+0];
    pixels[i].g = raw_data[i*3+1];
    pixels[i].b = raw_data[i*3+2];
  }
}

void image::apply_bw_filter() {
  for (int y = 0; y < h; y++) {
    for (int x = 0; x < w; x++) {
      #include "filters/bw.inc"
    }
  }

  buffer_pixel_matrix();
}

void image::apply_tritone_filter(int dark, int midtone, int light) {
  for (int y = 0; y < h; y++) {
    for (int x = 0; x < w; x++) {
      #include "filters/tritone.inc"
    }
  }

  buffer_pixel_matrix();
}
