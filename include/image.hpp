#pragma once

#include <cmath>
#include <algorithm>
#include <iostream>
#include <vector>
#include <utility>
#include "pixel.hpp"

class image
{
public:
  pixel *pixels;
  unsigned char *raw_data;

  int w;
  int h;
  int channels = 3;
  int quality = 90;

  pixel &at(int x, int y);
  const pixel &at(int x, int y) const;

  bool in_bounds(int x, int y) const;

  void load(unsigned char *data);

  // unsigned char* data();

  // ----- filters -----
  void apply_bw_filter();
  void apply_tritone_filter(int dark, int midtone, int light);
  void apply_pinktone_filter(int amt);
  void apply_pink_yellow_dream_filter();
  void apply_frutiger_filter();
  void apply_grain_filter(int amt);
  void apply_saturation_filter();
  void apply_red_filter();
  void apply_halftone_filter(int dark, int light, int thresh);
  void apply_pixel_sort_filter(int lo, int hi, bool vertical);

  // ----- row/column processing engine -----
  // shared building blocks for any effect that operates on a whole
  // row or column at once instead of a single pixel. `vertical` selects
  // whether `index` names a column (true) or a row (false).
  std::vector<pixel> get_line(int index, bool vertical);
  void set_line(int index, bool vertical, const std::vector<pixel> &line);
  std::vector<std::pair<int, int>> find_runs(const std::vector<pixel> &line, int lo, int hi);

private:
  void buffer_pixel_matrix();
};
