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
      // starting memory position for pixel
      int idx = (y * w + x) * channels;

      std::array<unsigned char, 3> c1 = util::hex_to_rgb(0xa4303f);
      std::array<unsigned char, 3> c2 = util::hex_to_rgb(0xb4c794);
      std::array<unsigned char, 3> c3 = util::hex_to_rgb(0xffeccc);

      // get rgb values
      unsigned char r = raw_data[idx + 0];
      unsigned char g = raw_data[idx + 1];
      unsigned char b = raw_data[idx + 2];

      // modify rgb values
      unsigned char gray = static_cast<unsigned char>(0.2126 * r + 0.7152 * g + 0.0722 * b);
      // if(gray < 85) {
      //   img_data[idx + 0] = c1[0];
      //   img_data[idx + 1] = c1[1];
      //   img_data[idx + 2] = c1[2];
      // }
      // else if(gray < 170) {
      //   img_data[idx + 0] = c2[0];
      //   img_data[idx + 1] = c2[1];
      //   img_data[idx + 2] = c2[2];
      // }
      // else {
      //   img_data[idx + 0] = c3[0];
      //   img_data[idx + 1] = c3[1];
      //   img_data[idx + 2] = c3[2];
      // }
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
