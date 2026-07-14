if (!amt && amt != 0) {
  std::cout << "error\n";
}

int idx = (y * w + x) * channels;

double r = raw_data[idx + 0];
double g = raw_data[idx + 1];
double b = raw_data[idx + 2];

// random value between -amount and +amount
// int noise = ((util::fast_rand() % 21 / 10) % (amt * 2 + 1)) - amt;
// to do: optimize using rand()
int noise = (rand() % (amt * 2 + 1)) - amt;


raw_data[idx + 0] = std::clamp((int)r + noise, 0, 255);
raw_data[idx + 1] = std::clamp((int)g + noise, 0, 255);
raw_data[idx + 2] = std::clamp((int)b + noise, 0, 255);
