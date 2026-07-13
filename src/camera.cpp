#include "camera.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.hpp"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.hpp"

camera::camera() {};

camera::~camera() {
  stbi_image_free(img.raw_data);
};

bool camera::load_image() {
  int w, h, channels;
  unsigned char* raw_data = stbi_load(
    get_input_filename().c_str(),
    &w,
    &h,
    &channels,
    0
  );

  if (raw_data == nullptr) {
    std::cout << "welp :/\n";
    std::cout << stbi_failure_reason() << "\n";
    return false;
  }

  std::cout << "it was fine\n";

  img.w = w;
  img.h = h;
  img.channels = channels;
  img.load(raw_data);

  return true;
}

int camera::write_jpg() {
  std::cout << "writing file: " << get_output_filename() << "\n";
  int write_success = stbi_write_jpg(
    get_output_filename().c_str(), 
    img.w, 
    img.h, 
    img.channels, 
    img.raw_data, 
    img.quality
  );

  if (write_success == 0) {
    std::cout << "it failed :/ \n";
    return -1;
  }

  return write_success;
}
