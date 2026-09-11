// starting memory position for pixel
int idx = (y * w + x) * channels;

double r = raw_data[idx + 0];
double g = raw_data[idx + 1];
double b = raw_data[idx + 2];

auto fade = [](double c)
{
    return c * 0.90 + 18;
};

r = r * 1.08 + 20;
g = g * 0.88 + 10;
b = b * 1.12 + 18;

r = r * 0.95 + 12;
g = g * 0.95 + 12;
b = b * 0.95 + 12;

double lum = (r + g + b) / 3.0;
if (lum > 190)
{
    r += 15;
    b += 10;
}

raw_data[idx + 0] = (int)fade(std::fmin(r * 1.2, 255.0));
raw_data[idx + 1] = (int)fade(g);
raw_data[idx + 2] = (int)fade(b);
