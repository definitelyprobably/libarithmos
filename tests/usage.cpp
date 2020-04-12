/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                                                                         *
 *  file: usage.cpp                                                        *
 *                                                                         *
 *  This file is a part of the libarithmos package.                        *
 *                                                                         *
 *  Copyright (c) 2020, Karta Kooner GNU GPL v3+                           *
 *                                                                         *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

//  This program is free software: you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published by
//  the Free Software Foundation, either version 3 of the License, or
//  (at your option) any later version.
//
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//
//  You should have received a copy of the GNU General Public License
//  along with this program.  If not, see <http://www.gnu.org/licenses/>.


#include <iostream>
#include <arithmos.h>
#ifdef HAVE_CONFIG_H
#  include "config.h"
#endif


void print_data(const Arithmos::Data& d) {
  std::cout << d.is_number << d.is_integer << d.is_integer_literal
            << d.has_decimal << d.has_decimal_literal
            << d.is_fraction_by_exponent
            << d.is_zero << d.is_positive << d.is_explicit_positive
            << d.is_exponent_positive << d.is_exponent_explicit_positive
            << ':' << d.whole_width << ':' << d.exponent_width
            << ':' << d.mantissa
            << ':' << (d.exponent_position == Arithmos::Data::position_type(-1)
                        ? static_cast<long long>(-1) :
                          static_cast<long long>(d.exponent_position))
            << ':' << d.whole_string << ':'
            << d.whole_string_normalized << ':'
            << d.exponent_string << ':'
            << d.exponent_string_normalized << ':'
            << d.normalized;
}


int main(int argc, char* argv[]) {
try {
  using Arithmos::translate;
  using Arithmos::hex_upper_to_lower;
  using Arithmos::binary;
  using Arithmos::octal;
  using Arithmos::decimal;
  using Arithmos::hexadecimal;
  using Arithmos::Data;
  Arithmos::Format custom1("START",
                                { 'a', 'v', 'r', 'l', 'g', 'n' },
                                "OVER",
                                { 'i', 'e' });

  if (argc < 3) {
    std::cerr << "failure: program usage incorrect.";
    return 1;
  }
  else {
    const std::string number_type(argv[1]);
    const std::string input(argv[2]);
    if (number_type == "binary") {
      const Data d = binary.compare(input);
      print_data(d);
      return 0;
    }
    else if (number_type == "octal") {
      const Data d = octal.compare(input);
      print_data(d);
      return 0;
    }
    else if (number_type == "decimal") {
      const Data d = decimal.compare(input);
      print_data(d);
      return 0;
    }
    else if (number_type == "hexadecimal") {
      const Data d = hexadecimal.compare(input);
      print_data(d);
      return 0;
    }
    else if (number_type == "Hexadecimal") {
      const Data d = hexadecimal.compare(translate<>(input,hex_upper_to_lower));
      print_data(d);
      return 0;
    }
    else if (number_type == "custom1") {
      const Data d = custom1.compare(input);
      print_data(d);
      return 0;
    }
    else if (number_type == "convert") {
      if (argc < 5) {
        std::cerr << "failure: program usage incorrect.";
        return 1;
      }
      const std::string from(argv[2]);
      const std::string to(argv[3]);
      const std::string input(argv[4]);
      if (from == "binary") {
        if (to == "binary")
          std::cout << binary.to(binary, input);
        else if (to == "octal")
          std::cout << binary.to(octal, input);
        else if (to == "decimal")
          std::cout << binary.to(decimal, input);
        else if (to == "hexadecimal")
          std::cout << binary.to(hexadecimal, input);
        else if (to == "custom1")
          std::cout << binary.to(custom1, input);
        else {
          std::cerr << "failure: convert to number type (" << to
                    << ") not recognized.";
          return 1;
        }
      }
      else if (from == "octal") {
        if (to == "binary")
          std::cout << octal.to(binary, input);
        else if (to == "octal")
          std::cout << octal.to(octal, input);
        else if (to == "decimal")
          std::cout << octal.to(decimal, input);
        else if (to == "hexadecimal")
          std::cout << octal.to(hexadecimal, input);
        else if (to == "custom1")
          std::cout << octal.to(custom1, input);
        else {
          std::cerr << "failure: convert to number type (" << to
                    << ") not recognized.";
          return 1;
        }
      }
      else if (from == "decimal") {
        if (to == "binary")
          std::cout << decimal.to(binary, input);
        else if (to == "octal")
          std::cout << decimal.to(octal, input);
        else if (to == "decimal")
          std::cout << decimal.to(decimal, input);
        else if (to == "hexadecimal")
          std::cout << decimal.to(hexadecimal, input);
        else if (to == "custom1")
          std::cout << decimal.to(custom1, input);
        else {
          std::cerr << "failure: convert to number type (" << to
                    << ") not recognized.";
          return 1;
        }
      }
      else if (from == "hexadecimal") {
        if (to == "binary")
          std::cout << hexadecimal.to(binary, input);
        else if (to == "octal")
          std::cout << hexadecimal.to(octal, input);
        else if (to == "decimal")
          std::cout << hexadecimal.to(decimal, input);
        else if (to == "hexadecimal")
          std::cout << hexadecimal.to(hexadecimal, input);
        else if (to == "custom1")
          std::cout << hexadecimal.to(custom1, input);
        else {
          std::cerr << "failure: convert to number type (" << to
                    << ") not recognized.";
          return 1;
        }
      }
      else if (from == "custom1") {
        if (to == "binary")
          std::cout << custom1.to(binary, input);
        else if (to == "octal")
          std::cout << custom1.to(octal, input);
        else if (to == "decimal")
          std::cout << custom1.to(decimal, input);
        else if (to == "hexadecimal")
          std::cout << custom1.to(hexadecimal, input);
        else if (to == "custom1")
          std::cout << custom1.to(custom1, input);
        else {
          std::cerr << "failure: convert to number type (" << to
                    << ") not recognized.";
          return 1;
        }
      }
      else {
        std::cerr << "failure: convert from number type (" << from
                  << ") not recognized.";
        return 1;
      }
      return 0;
    }
    else {
      std::cerr << "failure: number type (" << number_type
                << ") not recognized.";
      return 1;
    }
  }

  std::cerr << "failure: unexpected execution path.";
  return 2;

} catch (std::exception& exc) {
  std::cerr << "failure: caught exception: " << exc.what();
  return 2;
}}
