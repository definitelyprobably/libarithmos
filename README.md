# libarithmos

[![Build Status](https://travis-ci.com/definitelyprobably/libarithmos.svg?branch=master)](https://travis-ci.com/definitelyprobably/libarithmos)

This library can compare strings to a defined number format (think C strtol or C++ stringstream). It can also convert numbers from one format to another, and extract information about the number. It's not fast, but it does the job. The typical usage would be parsing command-line inputs to your program to catch malformed strings.

## Building

Clone the repo and configure, build and install as usual. See the INSTALL.md file for more details. A C++11 compiler is required and autotools will need to be installed if building from a clone of the repo, but there are no other external dependencies. If you want to just install the library, you can take a libarithmos tarball from the [releases page] and then autotools is not required, only a C++11 compiler is needed.

## Documentation

Haphazard. Example code follows. A man page has been written that contains more information. To read it without installation of the library, run the command:

```sh
groff -Tascii -man docs/manpages/libarithmos.3 | less
```

## Examples

### Parsing strings

```c++
#include <iostream>
#include <string>
#include <iomanip>
#include <arithmos.h>  // libarithmos header

int main() {

  std::string input;

  while ( std::cout << "input: ", !std::getline(std::cin, input).eof() ) {

    if (std::cin.fail() || std::cin.bad())
      return 1;
    if (input.empty())
      continue;
    if (input == "q" || input == "quit")
      return 0;

    // start of code that is pertinent...

    // This code assumes that 'input' should be a decimal number.
    // If expecting binary, octal or hexadecimal then call Arithmos::binary,
    // Arithmos::octal or Arithmos::hexadecimal respectively instead.
    // The object returned is an Arithmos::Data object, which contains the
    // results of the string parsing.

    Arithmos::Data d = Arithmos::decimal.compare(input);

    if (!d.is_number) {
      std::cout << "  + not a number" << std::endl;
    }
    else {
      std::cout << std::boolalpha
                << "  + is positive: "  << d.is_positive
                << "\n  + is integer: " << d.is_integer
                << "\n  + is zero: "    << d.is_zero
                << "\n  + normalized: " << d.normalized
                << std::endl;
    }
  }

  return 0;
}
```

Output:

```
input: abc123
  + not a number
input: 1241abc
  + not a number
input: 1234
  + is positive: true
  + is integer: true
  + is zero: false
  + normalized: 1234
input: -.01
  + is positive: false
  + is integer: false
  + is zero: false
  + normalized: -0.01
input: .050e+01
  + is positive: true
  + is integer: false
  + is zero: false
  + normalized: 0.05e1
input: e+5
  + is positive: true
  + is integer: true
  + is zero: false
  + normalized: 1e5
input: -.00
  + is positive: false
  + is integer: true
  + is zero: true
  + normalized: 0
input: -.00e-00
  + is positive: false
  + is integer: true
  + is zero: true
  + normalized: 0
input: -. 
  + not a number
```

### Converting strings

Library can also do some basic conversion of numbers from one format to another, but does not attempt conversion for non-integers.

```c++
#include <iostream>
#include <string>
#include <iomanip>
#include <arithmos.h>  // libarithmos header

int main() {

  std::string input;

  while ( std::cout << "input: ", !std::getline(std::cin, input).eof() ) {

    if (std::cin.fail() || std::cin.bad())
      return 1;
    if (input.empty())
      continue;
    if (input == "q" || input == "quit")
      return 0;

    // start of code that is pertinent...

    using Arithmos::octal;
    using Arithmos::hexadecimal;

    std::string output = hexadecimal.to(octal, input);

    if ( output.empty() ) {
      std::cout << "  + not a number" << std::endl;
    }
    else {
      std::cout << "  + to octal: " << output << std::endl;
    }
  }

  return 0;
}
```

Output:

```
input: -0x000
  + to octal: 00    # Note! Library does not attempt to contract to just '0'
input: +0x000p000
  + to octal: 00    # Note! Library does not attempt to contract to just '0'
input: 0x0ef1e0b
  + to octal: 073617013
input: 0xffp12
  + to octal: 0377e12
input: 0xffp-12
  + not a number    # Note! Only integers are converted
input: 0xff.ff
  + not a number    # Note! Only integers are converted
input: 0xff.ffp1234
  + not a number    # Note! Only integers are converted
```

### Creating a custom number format

```c++
#include <iostream>
#include <string>
#include <iomanip>
#include <clocale>
#include <cstdlib>
#include <arithmos.h>  // libarithmos header

int main() {

  // output to linux console, set locale and use std::wcstombs.
  std::setlocale(LC_ALL, "en_US.utf8");

  // use wide characters to represent Gurmukhi numerals; library has
  // corresponding wchar_t classes and objects (see man page):
  using Arithmos::WFormat;
  using Arithmos::WData;
  using Arithmos::wdecimal;

  WFormat ternary{
    L"g_",  // marker that identifies the number (like "0x" for hexadecimal numbers)
    { L'੦', L'੧', L'੨' }, // digits
    L"e", // exponent marker
    { L'੦', L'੧', L'੨', L'੩', L'੪', L'੫', L'੬', L'੭', L'੮', L'੯' } // digits in the exponent
  };

  std::vector<std::wstring> inputs{
    L"g_੦੦੧",
    L"g_੦੦੧੧e੪੭",
    L"g_੧੦੨.੦੨੦੦",
    L"g_੨੨e-੦੦",
    L"g_੨੧e੯੬",
    L"-g_੧੧੧"
  };

  for (const auto& i: inputs) {
    WData d = ternary.compare(i);

    char original[1024];
    std::wcstombs(original, i.c_str(), 1024);

    char normalized[1024];
    std::wcstombs(normalized, d.normalized.c_str(), 1024);

    char todecimal[1024];
    std::wcstombs(todecimal, ternary.to(wdecimal, i).c_str(), 1024);

    std::cout << std::boolalpha
              << "number: " << original
              << "\n  + is number: "  << d.is_number
              << "\n  + positive: "   << d.is_positive
              << "\n  + normalized: " << normalized
              << "\n  + to decimal: " << todecimal
              << std::endl;
  }

  return 0;
}
```

Output:

```
number: g_੦੦੧
  + is number: true
  + positive: true
  + normalized: g_੧
  + to decimal: 1
number: g_੦੦੧੧e੪੭
  + is number: true
  + positive: true
  + normalized: g_੧੧e੪੭
  + to decimal: 4e47
number: g_੧੦੨.੦੨੦੦
  + is number: true
  + positive: true
  + normalized: g_੧੦੨.੦੨
  + to decimal:     # Note! Non-integers are not converted
number: g_੨੨e-੦੦
  + is number: true
  + positive: true
  + normalized: g_੨੨
  + to decimal: 8
number: g_੨੧e੯੬
  + is number: true
  + positive: true
  + normalized: g_੨੧e੯੬
  + to decimal: 7e96
number: -g_੧੧੧
  + is number: true
  + positive: false
  + normalized: -g_੧੧੧
  + to decimal: -13
```

## Licence

GNU GPL v3+

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.

  [releases page]: https://github.com/definitelyprobably/libarithmos/releases
