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

// unsigned char* image::data() {
//   unsigned char* d = new unsigned char[w*h];

//   int idx = 0;
//   for(int i = 0; i < w*h; i++) {
//     for(int j = 0; j < 3; j++) {
//       d[idx] = pixels[i * w + j];
//     }
//   }

//   return d;
// }

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

// ----- filters ----- 
// void image::apply_filter() {

// }

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

void image::apply_pinktone_filter(int amt) {
  for (int y = 0; y < h; y++) {
    for (int x = 0; x < w; x++) {
      #include "filters/pinktone.inc"
    }
  }

  buffer_pixel_matrix();
}

void image::apply_pink_yellow_dream_filter() {
  for (int y = 0; y < h; y++) {
    for (int x = 0; x < w; x++) {
      #include "filters/pink_yellow_dream.inc"
    }
  }

  buffer_pixel_matrix();
}

void image::apply_frutiger_filter() {
  for (int y = 0; y < h; y++) {
    for (int x = 0; x < w; x++) {
      #include "filters/frutiger.inc"
    }
  }

  buffer_pixel_matrix();
}

void image::apply_grain_filter(int amt) {
  for (int y = 0; y < h; y++) {
    for (int x = 0; x < w; x++) {
      #include "filters/grain.inc"
    }
  }

  buffer_pixel_matrix();
}
