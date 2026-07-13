// starting memory position for pixel
int idx = (y * w + x) * channels;
constexpr double strength = 0.18;

double r = raw_data[idx + 0];
double g = raw_data[idx + 1];
double b = raw_data[idx + 2];

r = r * 0.97 + 8;
g = g * 1.12 + 12;
b = b * 1.18 + 18;

r = r * (1.0 - strength) + 180 * strength;
g = g * (1.0 - strength) + 240 * strength;
b = b * (1.0 - strength) + 255 * strength;

double avg = (r + g + b) / 3.0;

r = avg + (r - avg) * 1.10;
g = avg + (g - avg) * 1.20;
b = avg + (b - avg) * 1.25;
r = r * 0.94 + 15;
g = g * 0.94 + 15;
b = b * 0.94 + 15;

raw_data[idx + 0] = std::clamp((int)std::round(r), 0, 255);
raw_data[idx + 1] = std::clamp((int)std::round(g), 0, 255);
raw_data[idx + 2] = std::clamp((int)std::round(b), 0, 255);
