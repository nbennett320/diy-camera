#include "image.hpp"
#include "util.hpp"

pixel &image::at(int x, int y)
{
  // assert(x >= 0);
  // assert(x < w);
  // assert(y >= 0);
  // assert(y < h);

  return pixels[y * w + x];
}

const pixel &image::at(int x, int y) const
{
  // assert(x >= 0);
  // assert(x < w);
  // assert(y >= 0);
  // assert(y < h);

  return pixels[y * w + x];
}

void image::load(unsigned char *data)
{
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

void image::buffer_pixel_matrix()
{
  // populate pixels
  int n_pixels = w * h;
  pixels = new pixel[n_pixels];
  for (int i = 0; i < n_pixels; i++)
  {
    pixels[i].r = raw_data[i * 3 + 0];
    pixels[i].g = raw_data[i * 3 + 1];
    pixels[i].b = raw_data[i * 3 + 2];
  }
}

// ----- filters -----
// void image::apply_filter() {

// }

void image::apply_bw_filter()
{
  for (int y = 0; y < h; y++)
  {
    for (int x = 0; x < w; x++)
    {
#include "filters/bw.inc"
    }
  }

  buffer_pixel_matrix();
}

void image::apply_tritone_filter(int dark, int midtone, int light)
{
  for (int y = 0; y < h; y++)
  {
    for (int x = 0; x < w; x++)
    {
#include "filters/tritone.inc"
    }
  }

  buffer_pixel_matrix();
}

void image::apply_pinktone_filter(int amt)
{
  for (int y = 0; y < h; y++)
  {
    for (int x = 0; x < w; x++)
    {
#include "filters/pinktone.inc"
    }
  }

  buffer_pixel_matrix();
}

void image::apply_pink_yellow_dream_filter()
{
  for (int y = 0; y < h; y++)
  {
    for (int x = 0; x < w; x++)
    {
#include "filters/pink_yellow_dream.inc"
    }
  }

  buffer_pixel_matrix();
}

void image::apply_frutiger_filter()
{
  for (int y = 0; y < h; y++)
  {
    for (int x = 0; x < w; x++)
    {
#include "filters/frutiger.inc"
    }
  }

  buffer_pixel_matrix();
}

void image::apply_grain_filter(int amt)
{
  for (int y = 0; y < h; y++)
  {
    for (int x = 0; x < w; x++)
    {
#include "filters/grain.inc"
    }
  }

  buffer_pixel_matrix();
}

void image::apply_saturation_filter()
{
  for (int y = 0; y < h; y++)
  {
    for (int x = 0; x < w; x++)
    {
#include "filters/saturation.inc"
    }
  }

  buffer_pixel_matrix();
}

void image::apply_red_filter()
{
  for (int y = 0; y < h; y++)
  {
    for (int x = 0; x < w; x++)
    {
#include "filters/red.inc"
    }
  }

  buffer_pixel_matrix();
}

void image::apply_halftone_filter(int dark, int light, int thresh)
{
  for (int y = 0; y < h; y++)
  {
    for (int x = 0; x < w; x++)
    {
#include "filters/halftone.inc"
    }
  }

  buffer_pixel_matrix();
}

// ----- row/column processing engine -----
// reusable read/write for a full row (vertical = false) or column
// (vertical = true) of raw_data, plus a generic brightness-range run
// finder. any row/column effect (pixel sort, row shift, channel offset,
// etc.) can be built from these three without re-deriving the indexing.

std::vector<pixel> image::get_line(int index, bool vertical)
{
  int len = vertical ? h : w;
  std::vector<pixel> line(len);

  for (int i = 0; i < len; i++)
  {
    int x = vertical ? index : i;
    int y = vertical ? i : index;
    int idx = (y * w + x) * channels;

    line[i].r = raw_data[idx + 0];
    line[i].g = raw_data[idx + 1];
    line[i].b = raw_data[idx + 2];
  }

  return line;
}

void image::set_line(int index, bool vertical, const std::vector<pixel> &line)
{
  int len = vertical ? h : w;

  for (int i = 0; i < len; i++)
  {
    int x = vertical ? index : i;
    int y = vertical ? i : index;
    int idx = (y * w + x) * channels;

    raw_data[idx + 0] = line[i].r;
    raw_data[idx + 1] = line[i].g;
    raw_data[idx + 2] = line[i].b;
  }
}

std::vector<std::pair<int, int>> image::find_runs(const std::vector<pixel> &line, int lo, int hi)
{
  std::vector<std::pair<int, int>> runs;

  int start = -1;
  for (int i = 0; i < (int)line.size(); i++)
  {
    double gray = 0.2126 * line[i].r + 0.7152 * line[i].g + 0.0722 * line[i].b;
    bool in_range = gray >= lo && gray <= hi;

    if (in_range && start == -1)
    {
      start = i;
    }
    else if (!in_range && start != -1)
    {
      runs.push_back({start, i});
      start = -1;
    }
  }

  if (start != -1)
  {
    runs.push_back({start, (int)line.size()});
  }

  return runs;
}

void image::apply_pixel_sort_filter(int lo, int hi, bool vertical)
{
  int lines = vertical ? w : h;

  for (int i = 0; i < lines; i++)
  {
    std::vector<pixel> line = get_line(i, vertical);
    std::vector<std::pair<int, int>> runs = find_runs(line, lo, hi);

#include "filters/pixel_sort.inc"

    set_line(i, vertical, line);
  }

  buffer_pixel_matrix();
}