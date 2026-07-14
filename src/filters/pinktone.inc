// starting memory position for pixel
int idx = (y * w + x) * channels;
double strength = (double)amt / 100.0;

double r = raw_data[idx + 0];
double g = raw_data[idx + 1];
double b = raw_data[idx + 2];

const int pink_r = 255;
const int pink_g = 170;
const int pink_b = 210;

r = r * (1.0 - strength) + pink_r * strength;
g = g * (1.0 - strength) + pink_g * strength;
b = b * (1.0 - strength) + pink_b * strength;

auto fade = [](double c) {
  return c * 0.90 + 18;
};

double lum = (r + g + b) / 3.0;
if (lum > 190) {
  r += 15;
  b += 10;
}

raw_data[idx + 0] = (int)fade(std::fmin(r * 1.2, 255.0));
raw_data[idx + 1] = (int)fade(g);
raw_data[idx + 2] = (int)fade(b);
