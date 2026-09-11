// starting memory position for pixel
int idx = (y * w + x) * channels;

std::array<unsigned char, 3> c1 = util::hex_to_rgb(dark);
std::array<unsigned char, 3> c3 = util::hex_to_rgb(light);

// thresh doubles as the dot grid pitch (cell size in px)
int cell = std::max(thresh, 2);

// this pixel's cell center, in image coords
int cx = std::min((x / cell) * cell + cell / 2, w - 1);
int cy = std::min((y / cell) * cell + cell / 2, h - 1);

// sample brightness once per cell, from the untouched source pixels
pixel &anchor = pixels[cy * w + cx];
double gray = 0.2126 * anchor.r + 0.7152 * anchor.g + 0.0722 * anchor.b;

// darker cells get bigger dots
double radius = (1.0 - gray / 255.0) * (cell / 2.0);

double dx = x - cx;
double dy = y - cy;
double dist = std::sqrt(dx * dx + dy * dy);

if (dist <= radius) {
  raw_data[idx + 0] = c1[0];
  raw_data[idx + 1] = c1[1];
  raw_data[idx + 2] = c1[2];
} else {
  raw_data[idx + 0] = c3[0];
  raw_data[idx + 1] = c3[1];
  raw_data[idx + 2] = c3[2];
}
