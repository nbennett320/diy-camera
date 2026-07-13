#pragma once

#include <memory>
#include "pixel.hpp"

class image {
  public:

  pixel* pixels;
  unsigned char* raw_data;

  int w;
  int h;
  int channels = 3;
  int quality = 90;

  pixel& at(int x, int y);
  const pixel& at(int x, int y) const;

  bool in_bounds(int x, int y) const;

  void load(unsigned char* data);

  // ----- filters ----- 
  void apply_bw_filter();
  void apply_tritone_filter(int dark, int midtone, int light);

  private:

  void buffer_pixel_matrix();

};
