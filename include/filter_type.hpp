#pragma once

#include <iostream>
#include <string>

enum class filter_type {
  bw,
  tritone,
  pinktone,
  pink_yellow_dream,
  frutiger,
  grain,
};

constexpr inline filter_type match_filter_type(std::string str) {
  if (str == "bw")   return filter_type::bw;
  if (str == "tritone") return filter_type::tritone;
  if (str == "pinktone")  return filter_type::pinktone;
  if (str == "pink_yellow_dream")  return filter_type::pink_yellow_dream;
  if (str == "frutiger")  return filter_type::frutiger;
  if (str == "grain")  return filter_type::grain;
  
  throw std::invalid_argument("unknown filter type");
}