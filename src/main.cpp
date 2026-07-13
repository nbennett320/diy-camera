#include <iostream>
#include <string>
#include <array>

#include "camera.hpp"
#include "util.hpp"



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
      cam.set_input_filename(next);
      // cam.filename = next;

      i++;
    }

    i++;
  }
}

int main(int argc, char* argv[]) {
  camera cam = camera();

  parse_args(argc, argv, cam);

  #ifdef DEBUG
  std::cout << "camera file: " << cam.get_input_filename() << "\n";
  #endif

  if(!cam.load_image()) {
    // std::cout << "couldn't load image: " << stbi_failure_reason() << "\n";
    return 1;
  }
  
  std::cout <<"works\n";

  // // iterate through image:
  // for (int y = 0; y < h; y++) {
  //   for (int x = 0; x < w; x++) {
  //     // starting memory position for pixel
  //     int idx = (y * w + x) * channels;

  //     std::array<unsigned char, 3> c1 = util::hex_to_rgb(0xa4303f);
  //     std::array<unsigned char, 3> c2 = util::hex_to_rgb(0xb4c794);
  //     std::array<unsigned char, 3> c3 = util::hex_to_rgb(0xffeccc);

  //     // get rgb values
  //     unsigned char r = img_data[idx + 0];
  //     unsigned char g = img_data[idx + 1];
  //     unsigned char b = img_data[idx + 2];

  //     // modify rgb values
  //     unsigned char gray = static_cast<unsigned char>(0.2126 * r + 0.7152 * g + 0.0722 * b);
  //     if(gray < 85) {
  //       img_data[idx + 0] = c1[0];
  //       img_data[idx + 1] = c1[1];
  //       img_data[idx + 2] = c1[2];
  //     }
  //     else if(gray < 170) {
  //       img_data[idx + 0] = c2[0];
  //       img_data[idx + 1] = c2[1];
  //       img_data[idx + 2] = c2[2];
  //     }
  //     else {
  //       img_data[idx + 0] = c3[0];
  //       img_data[idx + 1] = c3[1];
  //       img_data[idx + 2] = c3[2];
  //     }
  //   }
  // }

  cam.set_output_filename("output.jpg");
  cam.write_jpg();

  return 0;
}
