#include <iostream>
#include <string>
#include "camera.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.hpp"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.hpp"

void parse_args(int argc, char* argv[], camera &cam) {
  int i = 1;

  while (i < argc) {
    std::cout << "arg[" << i << "]: " << argv[i] << "\n";

    std::string curr = argv[i];
    if (curr == "-f" || curr == "--file") {
      if (i+1 > argc) {
        std::cout << "no file provided";
        break;
      }

      char* next = argv[i+1];
      std::cout << "loading file: " << next << "\n";
      
      // handle loading image
      cam.filename = next;

      i++;
    }

    i++;
  }
}

int main(int argc, char* argv[]) {
  camera cam = camera();

  parse_args(argc, argv, cam);

  #ifdef DEBUG
  std::cout << "camera file: " << cam.filename << "\n";
  #endif

  int w = 1440;
  int h = 1080;
  int channels = 3; // rgb
  unsigned char* img_data = stbi_load(cam.filename.c_str(), &w, &h, &channels, 0);

  if (img_data == nullptr) {
    std::cout << "welp :/\n";
    return 1;
  }

  std::cout <<"works\n";

  // iterate through image:
  for (int y = 0; y < h; y++) {
    for (int x = 0; x < w; x++) {
      // starting memory position for pixel
      int idx = (y * w + x) * channels;

      // 101 145 87
      unsigned char c1_r = 101;
      unsigned char c1_g = 145;
      unsigned char c1_b = 87;

      // 135 180 192
      unsigned char c2_r = 135;
      unsigned char c2_g = 180;
      unsigned char c2_b = 192;
      // 255 202 177
      unsigned char c3_r = 255;
      unsigned char c3_g = 202;
      unsigned char c3_b = 177;

      // get rgb values
      unsigned char r = img_data[idx + 0];
      unsigned char g = img_data[idx + 1];
      unsigned char b = img_data[idx + 2];

      // modify rgb values
      unsigned char gray = static_cast<unsigned char>(0.2126 * r + 0.7152 * g + 0.0722 * b);
      if(gray < 85) {
        img_data[idx + 0] = c1_r;
        img_data[idx + 1] = c1_g;
        img_data[idx + 2] = c1_b;
      }
      else if(gray < 170) {
        img_data[idx + 0] = c2_r;
        img_data[idx + 1] = c2_g;
        img_data[idx + 2] = c2_b;
      }
      else {
        img_data[idx + 0] = c3_r;
        img_data[idx + 1] = c3_g;
        img_data[idx + 2] = c3_b;
      }
    }
  }

  std::string output_filename = "output.jpg";
  int quality = 90;

  int write_success = stbi_write_jpg(
    output_filename.c_str(), 
    w, 
    h, 
    channels, 
    img_data, 
    quality
  );

  if (write_success == 0) {
    std::cout << "it failed :/ \n";
  }
  stbi_image_free(img_data);

  return 0;
}
