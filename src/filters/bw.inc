// starting memory position for pixel
int idx = (y * w + x) * channels;

unsigned char r = raw_data[idx + 0];
unsigned char g = raw_data[idx + 1];
unsigned char b = raw_data[idx + 2];
unsigned char gray = static_cast<unsigned char>(0.2126 * r + 0.7152 * g + 0.0722 * b);

raw_data[idx + 0] = gray;
raw_data[idx + 1] = gray;
raw_data[idx + 2] = gray;
