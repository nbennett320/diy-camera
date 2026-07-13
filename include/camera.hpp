#pragma once

#include <string>
#include <iostream>
#include "image.hpp"

class camera {
  public:

  camera();

  ~camera();

  bool load_image();
  int write_jpg();

  inline void set_input_filename(std::string str) { input_filename = str; };
  inline void set_input_filename(char* str) { input_filename = str; };
  inline std::string get_input_filename() { return input_filename; };

  inline void set_output_filename(std::string str) { output_filename = str; };
  inline void set_output_filename(char* str) { output_filename = str; };
  inline std::string get_output_filename() { return output_filename; };

  private:

  std::string input_filename;
  std::string output_filename = "output.jpg";
  image img;
};