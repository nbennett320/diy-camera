#include <iostream>
#include <string>
#include "stb_image.hpp"
#include "stb_image_write.hpp"
#include "camera.hpp"

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

  return 0;
}
