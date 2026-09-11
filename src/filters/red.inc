// starting memory position for pixel
int idx = (y * w + x) * channels;

unsigned char r = raw_data[idx + 0];
unsigned char g = raw_data[idx + 1];
unsigned char b = raw_data[idx + 2];

raw_data[idx + 0] = r * 2;
raw_data[idx + 1] = g;
raw_data[idx + 2] = b;
