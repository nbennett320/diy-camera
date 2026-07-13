// starting memory position for pixel
int idx = (y * w + x) * channels;

std::array<unsigned char, 3> c1 = util::hex_to_rgb(dark);
std::array<unsigned char, 3> c2 = util::hex_to_rgb(midtone);
std::array<unsigned char, 3> c3 = util::hex_to_rgb(light);

// get rgb values
unsigned char r = raw_data[idx + 0];
unsigned char g = raw_data[idx + 1];
unsigned char b = raw_data[idx + 2];
unsigned char gray = static_cast<unsigned char>(0.2126 * r + 0.7152 * g + 0.0722 * b);

// modify rgb values
if(gray < 85) {
  raw_data[idx + 0] = c1[0];
  raw_data[idx + 1] = c1[1];
  raw_data[idx + 2] = c1[2];
}
else if(gray < 170) {
  raw_data[idx + 0] = c2[0];
  raw_data[idx + 1] = c2[1];
  raw_data[idx + 2] = c2[2];
}
else {
  raw_data[idx + 0] = c3[0];
  raw_data[idx + 1] = c3[1];
  raw_data[idx + 2] = c3[2];
}