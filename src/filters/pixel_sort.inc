// sort each contiguous in-range run of `line`, in place, by brightness
for (std::pair<int, int> &run : runs)
{
  std::sort(line.begin() + run.first, line.begin() + run.second,
    [](const pixel &a, const pixel &b) {
      double ga = 0.2126 * a.r + 0.7152 * a.g + 0.0722 * a.b;
      double gb = 0.2126 * b.r + 0.7152 * b.g + 0.0722 * b.b;
      return ga < gb;
    });
}
