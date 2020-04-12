# libarithmos

This library can compare strings to a defined number format (think C strtol or C++ stringstream). It can also convert numbers from one format to another, and extract information about the number. It's not fast, but it does the job. The typical usage would be parsing command-line inputs to your program to catch malformed strings.

## Building

Clone the repo and configure, build and install as usual. See the INSTALL.md file for more details. A C++11 compiler is required, but there are no other external dependencies.

## Documentation

Haphazard. Example code follows. A man page has been written that contains more information. To read it without installation of the library, run the command:

```sh
groff -Tascii -man docs/manpages/libarithmos.3 | less
```

## Example

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
    // The object returned is an Arithmos::Data object.

    Arithmos::Data d = Arithmos::decimal.compare(input);

    // Arithmos::Data object contains the results of parsing 'input':
    if (!d.is_number) {
      std::cout << "  + not a number" << std::endl;
    }
    else {
      std::cout << std::boolalpha
                << "  + is positive: " << d.is_positive
                << "\n  + is integer: " << d.is_integer
                << "\n  + is zero: " << d.is_zero
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

