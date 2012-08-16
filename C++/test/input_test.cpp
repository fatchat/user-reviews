/*
 * input_test.cpp
 *
 *  Created on: 09-Aug-2012
 *      Author: rohit
 */

#include <iostream>
#include "input.h"

int main (int argc, char * argv[])
{
  using namespace Input;

  std::string long_string_1 = "sfdkjvnlasjfv,kjasdfjasd, jdsvkjasd adsjch , akjdnckjasd,,, adslkjc";
  std::string comma_regex_1 = "([^,]*,)+";

  std::cout << std::boolalpha << search_regex (long_string_1, comma_regex_1.c_str ()) << std::endl;;

  std::string long_string_2 = "\"sfdkjvnlasjfv\",\"kjasdfjasd\", \"jdsvkjasd adsjch\" ,,, \"akjdnckjasd\", \"adslkjc\"";
  std::string comma_regex_2 = "([^,]*,)+";

  std::cout << std::boolalpha << search_regex (long_string_2, comma_regex_2.c_str ()) << std::endl;;

  return 0;
}
