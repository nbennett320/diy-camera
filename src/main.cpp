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
      #ifdef DEBUG
      std::cout << "loading file: " << next << "\n";
      #endif
      
      // set file to load
      cam.set_input_filename(next);

      i++;
    }

    if (curr == "-a" || curr == "--amount") {
      if (i+1 > argc) {
        std::cout << "amount value not provided";
        break;
      }

      char* next = argv[i+1];
      #ifdef DEBUG
      std::cout << "amount value: " << next << "\n";
      #endif
      
      // set file to load
      cam.set_filter_amount(next);

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

  cam.img.apply_bw_filter();
  // cam.img.apply_tritone_filter(0xa4303f, 0xb4c794, 0xffeccc);
  // cam.img.apply_pinktone_filter(cam.get_filter_amount());
  // cam.img.apply_pink_yellow_dream_filter();
  // cam.img.apply_frutiger_filter();
  cam.img.apply_grain_filter(cam.get_filter_amount());
  cam.set_output_filename("output.jpg");
  cam.write_jpg();

  return 0;
}
