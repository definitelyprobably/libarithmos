/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                                                                         *
 *  This file is a part of the libarithmos package.                        *
 *                                                                         *
 *  Copyright (c) 2020, Karta Kooner, GNU GPL v3+                          *
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

// TODO: Digit count bound checks. Maybed static_assert for count_type
//       unsigned as well?


#ifndef LIBARITHMOS_H
#define LIBARITHMOS_H

#include <string>
#include <sstream>
#include <iostream>
#include <vector>
#include <exception>
#include <cmath>
#include <unordered_set>
#include <stdexcept>
#include <type_traits>


namespace Arithmos {



// create a typedef for count_type used by the Basic_Digit and Basic_Format
// classes.
typedef unsigned long long  count_type;

// create a typedef for count_type used by the Basic_Data and Basic_Format
// classes.
typedef long long int       width_type;



/** class congruence_not_in_set  (public std::out_of_range)
 *
 * thrown by the Basic_Congruence constructor if the default element is not
 * in the unordered set.
 *
 */
class congruence_not_in_set : public std::out_of_range {
public:
  congruence_not_in_set();
};



/** class Basic_Congruence
 *
 * This class defines a set of elements that are equal to one another (that
 * is, characters that are synonymous), and defines a default character that
 * any element in the congruence set should be translated to. For example,
 * 
 *   Basic_Congruence<char> a( {'a', 'A'}, 'a' );
 *
 * defines the characters 'a' and 'A' to be equal, and that either instance
 * is to be translated into 'a'.
 *
 */
template <typename TChar>
class Basic_Congruence {
public:
  typedef TChar                         char_type;
  typedef std::unordered_set<char_type> set;

private:
  set        set_;      // the set of elements to be equated
  char_type  default_;  // the character that any element in set_ is to be set
                        // to if translated. Note: default_ MUST be in set_
                        // or else the constructor will throw.

public:
  Basic_Congruence(const set&, const char_type);

  bool operator==(const Basic_Congruence&) const;
  bool operator!=(const Basic_Congruence&) const;

  char_type get_default() const;
    // return the default character of the set (i.e., default_).
  char_type normalize(const char_type) const;
    // return default_ if argument is in set_ or else the argument itself.
    // So, if we have:
    //    set_ = {'a', 'A'}    default_ = 'a'
    // then
    //    normalize('a')  -> returns 'a'
    //    normalize('A')  -> returns 'a'
    //    normalize('b')  -> returns 'b'
  bool       has(const char_type) const;
    // return true if argument is in set_ and false otherwise.
};



/** translate
 *
 * The translate (template) function translates an input string given a set
 * of congruences of characters in the string.
 *
 */
template <typename T = char>
std::basic_string<T>
translate(const std::basic_string<T>& input,
          const std::unordered_set<Basic_Congruence<T>>& translations);

} // namespace Arithmos


namespace std {
  // we'll partially specialize the (template) hash struct:
  template <typename T>
  struct hash<Arithmos::Basic_Congruence<T>> {
    typedef Arithmos::Basic_Congruence<T>  argument_type;
    typedef size_t  result_type;

    result_type operator() (const argument_type& t) const {
      return static_cast<result_type>(t.get_default());
    }
  };
}



//
// The number code proper //
//
namespace Arithmos {

/** class invalid_format  (public std::exception)
 *
 * thrown by the Basic_Format class ctor if not enough information has been
 * passed in order to construct a valid number format.
 *
 */
class invalid_format : public std::exception {
  std::string message_;
public:
  invalid_format();
  const char* what() noexcept;
};



/** class Basic_Digit
 *
 * class specifies a digit and a counter that can be set to how many times
 * it can be used. The count must manually be incremented: successful
 * comparison (operator==) will not automatically increment the count.
 *
 */
template <typename TChar, typename TCounter = count_type>
class Basic_Digit {
public:
  typedef TChar    char_type;
  typedef TCounter count_type;

private:
  char_type   name_;      // the character represented by the class
  count_type  count_max_; // the max number of times that the character
                          // can be used
public:
  // ctors
  Basic_Digit(const char_type, const count_type);
  Basic_Digit(const char_type);

  // some operator overloads
  bool operator==(const Basic_Digit&) const;
  bool operator==(const char_type) const;
  bool operator!=(const Basic_Digit&) const;
  bool operator!=(const char_type) const;

  char_type   name() const;      // get the digit symbol
  count_type  count_max() const; // get the max counter value
};



/** struct Basic_Data
 *
 * struct contains information on an input string that is checked for
 * conformity to the mother class's number format.
 *
 */
template <typename TChar>
struct Basic_Data {
  typedef TChar                         char_type;
  typedef std::basic_string<char_type>  string;
  typedef Arithmos::width_type          width_type;
  typedef typename string::size_type    position_type;

  // ctor
  Basic_Data();
  // overload == operator
  bool operator==(const Basic_Data&) const;
  // overload != operator
  bool operator!=(const Basic_Data&) const;

  // a print method, useful for debugging
  void print(std::basic_ostream<char_type>&) const;

  // data members:
  bool  is_number;
    // is the string a valid number
  bool  is_integer;
    // is the string an integer
  bool  is_integer_literal;
    // is the string a literal integer (so, 1.0 is an integer but not a
    // literal integer, whereas as 1 is both).
  bool has_decimal;
    // is there a decimal point in the normalized string
  bool has_decimal_literal;
    // is there a decimal point in the original string
  bool is_fraction_by_exponent;
    // is the number a fraction (not an integer) because of the exponent
    // width; that is, because the whole width plus the exponent width is
    // less than zero
  bool  is_zero;
    // is the number zero
  bool  is_positive;
    // is the number positive
  bool  is_explicit_positive;
    // is the number explicitly positive (containing a `+' sign)
  bool  is_exponent_positive;
    // is the exponent positive (yes in `1e2', no in `1e-2')
  bool  is_exponent_explicit_positive;
    // is the exponent explicitly positive (containing a `+' sign); so,
    // yes in `1e+2' and no in `1e2'
  width_type  whole_width;
    // if whole_string_normalized is an integer, then the power of ten
    // that can divide it without remainder (so 12500 has a whole_width of
    // 2, 1500080 has a whole_width of 1, and 140002 has a whole_width of
    // 0); otherwise (whole_string_normalized being a decimal), the
    // number of significant digits in the fractional part multiplied by
    // -1 (so 10.001 has a whole_width of -3, 4.010200 has a whole_width
    // of -4, and 5.1000 has a whole_width of -1)
  width_type  exponent_width;
    // the number value of the string exponent_string_normalized. So, if
    // exponent_string_normalized is "15", then the exponent_width is 15.
  width_type  mantissa;
    // When put into scientific form, the size of the mantissa. That is,
    // for 1200 (1.2e1) the mantissa is 2, for 0.00024 (2.4e-4) the
    // mantissa is 2, for 810.01400 (8.10014e2) the mantissa is 6.
  string  whole_string;
    // the [pre-digits][specifier][digits] part of the number format (the
    // portion of the number before the exponent). So, an input of +0.2e-4
    // has a whole_string of +0.2; and an input of -000.100e+0010 has a
    // whole_string of -000.100
  string  whole_string_normalized;
    // the whole_string with superfluous digits removed and a zero placed
    // infront of a decimal point if no digits are before it. So, +.230 is
    // normalized to 0.23, 0010.00 is normalized to 10, and -00.00 is
    // normalized to 0
  position_type  exponent_position;
    // the index position in the input string of the start of the exponent
    // string within the input string
  string  exponent_string;
    // the [exp. pre-digits][exp. digits] part of the number format (the
    // portion of the number after the exponent). So, an input of -.2e+04
    // has an exponent_string of +04, and .01e-01 has an exponent_string
    // of -01
  string  exponent_string_normalized;
    // the exponent_string with superfluous digits removed. So, +014200 is
    // normalized to 14200, and -00 is normalized to 0
  string  normalized;
    // if exponent_string_normalized is not empty, the string
    //   whole_string_normalized + exponent + exponent_string_normalized
    // otherwise just
    //   whole_string_normalized

}; // struct Basic_Data



/** class Basic_Format
 *
 * class records a number format; that is, information on what all numbers
 * of that type must conform to. The class also contains a member function
 * that checks conformance (`compare').
 *
 * The generic format is:
 *   [pre-digits][specifier][digits][exponent][pre-digits][exp. digits]
 * where
 *   pre-digits:      + -  (not user definable)
 *   specifier:       string that defines that number format
 *   digits:          the vector of digits allowed to appear in the number
 *                    (excluding the exponent). The decimal point must not
 *                    be included: it is automatically added.
 *   exponent:        string that signifies the exponent
 *   exponent digits: the vector of digits allowed to appear in the
 *                    exponent.
 * TODO: the first digit must be the additive identity (0) and the next
 *       digit must be the multiplicative identity (1). Add this info here!
 * TODO: digits must be in ascending order.
 * FIXME: when a zero or one is put into `compare', then which digits do we
 *        use: the ones in digits_ or in exp_digits_.
 *
 * For example, for a hexadecimal-format number:
 *   specifier:           0x
 *   digits:              0 1 2 3 4 5 6 7 8 9 a b c d e f
 *   exponent:            E
 *   exponent digits:     0 1 2 3 4 5 6 7 8 9 a b c d e f
 *
 *
 * TODO: maybe add conversion methods: convert decimal -> hex etc. If we do
 *       this, then we can use the * -> decimal converter in calculating
 *       data.exponent_width.
 *
 *
 * The following table will help identify certain classes of integers and
 * fractions:
 *
 *   A: 1       D: 1e-1, 100e-4  <-- whole part is integer literal
 *   B: 1.0     E: 10.0e-3       <-- whole is integer, but not literal
 *   C: 1.1     F: 10.1e-3       <-- whole is not an integer
 *
 *                               A  B  C  D  E  F
 *                            ---------------------
 * [1] is_integer                1  1  -  -  -  -
 * [2] is_integer_literal        1  -  -  -  -  -
 * [3] has_decimal               -  -  1  -  -  1
 * [4] has_decimal_literal       -  1  1  -  1  1
 * [5] is_fraction_by_exponent   -  -  -  1  1  1
 *
 *   2                           1  -  -  -  -  -
 *   1 & !2 , !(2 | 3 | 5)       -  1  -  -  -  -
 *   !(1 | 5)                    -  -  1  -  -  -
 *   !(1 | 4)                    -  -  -  1  -  -
 *   !(1 | 3 | !4)               -  -  -  -  1  -
 *   3 & 5                       -  -  -  -  -  1
 *
 */
template <typename TChar, typename TCounter = count_type>
class Basic_Format {
public:
  typedef TChar                             char_type;
  typedef TCounter                          count_type;
  typedef Basic_Digit<char_type,count_type> digit_type;
  typedef std::vector<digit_type>           digits_type;
  typedef std::basic_string<char_type>      string;
  typedef Arithmos::width_type              width_type;
protected:
  typedef typename string::size_type        str_size_type;

private:
  string       specifier_;
    // a string that marks a number being of a particular format. E.g., 0x
    // for a hexadecimal number and 0 for an octal number
  digits_type  digits_;
    // the digits of the number 0 1 2 3 etc.
  string       exp_;
    // the exponent string, like e in 1.34e4
  digits_type  exp_digits_;
    // the digits allowed in the exponent. Usually as digits_ excluding the
    // period symbol

protected:
  /** struct Split
   *
   * After a Basic_Data object has been populated, this struct splits
   * Basic_Data's `normalized' data member into its different parts
   * according to:
   *      [-][specifier][whole_part][.{decimal_part}][e[-]{exponent_part}]
   *       1                  2             3         4 5        6
   *
   * struct data members:
   *   whole_positive     (bool)   - is the whole part positive; that is, is
   *                                 there no negative sign at position 1,
   *                                 above.
   *   whole_part         (string) - the string representing the integer part
   *                                 of the number (position 2 above), as `14
   *                                 ' is in `14.7', and `8' in `-8.02'.
   *   decimal            (bool)   - is there a decimal portion of the
   *                                 string.
   *   decimal_part       (string) - the decimal part of the number (position
   *                                 3 above), as `24' is in `0.24', and `07'
   *                                 in `-9.07e-1'.
   *   exponent           (bool)   - is there an exponent part (existence of
   *                                 part 4 above).
   *   exponent_positive  (bool)   - the the exponent positive; that is, is
   *                                 there no negative sign at position 5,
   *                                 above.
   *   exponent_part      (string) - the exponent string (position 6 above),
   *                                 as in `4' in `-5.2e-4'.
   */
  struct Split {
    // ctors
    Split();

    // a print method, useful for debugging
    void print(std::basic_ostream<char_type>&) const;

    // data members
    bool   whole_positive;
    string whole_part;
    bool   decimal;
    string decimal_part;
    bool   exponent;
    bool   exponent_positive;
    string exponent_part;
  };


  /** struct Count
   *
   * this struct records how many times a digit has been used in the string
   * to compare. This count must be compared to the Basic_Digit's internal
   * max count to see if the string is conforming to the declared format.
   *
   */
  struct Count {
    // ctors
    Count(const count_type);

    // data members
    std::vector<count_type> count_list_;
  };


public:
  // ctor
  Basic_Format(const string&        specifier,
               const digits_type&   digits,
               const string&        exp_string,
               const digits_type&   exp_digits);

  // get methods (return specififc class data members)
  const string&       specifier() const;
  const digits_type&  digits() const;
  const string&       exponent_specifier() const;
  const digits_type&  exponent_digits() const;

  // the most important method of the class: this method returns data on the
  // input string as to that strings conformance and properties with respect
  // to the number format described by this class; that information being
  // recorded in the Basic_Data struct
  Basic_Data<char_type> compare(const string&) const;

  string to(const Basic_Format&, const string&) const;
  string to(const Basic_Format&, const Basic_Data<char_type>&) const;

protected:
  // conversion functions:
  width_type raw_str_to_int(const string&, const bool = true) const;

  string     raw_int_to_str(const Basic_Format&, width_type,
                            const bool = true) const;

  string     raw_convert(const Basic_Format& dest, const string& input,
                         const bool = true) const;

  Split      raw_split(const Basic_Data<char_type>&) const;
};


// typedef some useful templated classes
typedef  Basic_Congruence<char>                               Congruence;
typedef  std::unordered_set<Congruence>                       Translation;
typedef  Basic_Format<char, count_type>                       Format;
typedef  Basic_Data<Format::char_type>                        Data;
typedef  Basic_Digit<Format::char_type, Format::count_type>   Digit;

typedef  Basic_Congruence<wchar_t>                            WCongruence;
typedef  std::unordered_set<WCongruence>                      WTranslation;
typedef  Basic_Format<wchar_t, count_type>                    WFormat;
typedef  Basic_Data<WFormat::char_type>                       WData;
typedef  Basic_Digit<WFormat::char_type, WFormat::count_type> WDigit;

#ifdef __cpp_char8_t
typedef  Basic_Congruence<char8_t>                            U8Congruence;
typedef  std::unordered_set<U8Congruence>                     U8Translation;
typedef  Basic_Format<char8_t, count_type>                    U8Format;
typedef  Basic_Data<U8Format::char_type>                      U8Data;
typedef  Basic_Digit<U8Format::char_type, U8Format::count_type> U8Digit;
#endif // __cpp_char8_t

typedef  Basic_Congruence<char16_t>                           U16Congruence;
typedef  std::unordered_set<U16Congruence>                    U16Translation;
typedef  Basic_Format<char16_t, count_type>                   U16Format;
typedef  Basic_Data<U16Format::char_type>                     U16Data;
typedef  Basic_Digit<U16Format::char_type, U16Format::count_type> U16Digit;

typedef  Basic_Congruence<char32_t>                           U32Congruence;
typedef  std::unordered_set<U32Congruence>                    U32Translation;
typedef  Basic_Format<char32_t, count_type>                   U32Format;
typedef  Basic_Data<U32Format::char_type>                     U32Data;
typedef  Basic_Digit<U32Format::char_type, U32Format::count_type> U32Digit;

} // namespace Arithmos

// the implementation of the template methods are contained in the file
// arithmos.tcc so that the class interfaces can be easily discerned; we
// include them here:
#include "arithmos.tcc"


namespace Arithmos {

// some pre-defined translations
extern const Translation  hex_lower_to_upper;
extern const Translation  hex_upper_to_lower;

extern const WTranslation whex_lower_to_upper;
extern const WTranslation whex_upper_to_lower;

#ifdef __cpp_char8_t
extern const U8Translation  u8hex_lower_to_upper;
extern const U8Translation  u8hex_upper_to_lower;
#endif // __cpp_char8_t

extern const U16Translation  u16hex_lower_to_upper;
extern const U16Translation  u16hex_upper_to_lower;

extern const U32Translation  u32hex_lower_to_upper;
extern const U32Translation  u32hex_upper_to_lower;

// some pre-defined number formats
extern const std::vector<Digit> binary_digits;
extern const std::vector<Digit> octal_digits;
extern const std::vector<Digit> decimal_digits;
extern const std::vector<Digit> hexadecimal_digits;

extern const std::vector<WDigit> wbinary_digits;
extern const std::vector<WDigit> woctal_digits;
extern const std::vector<WDigit> wdecimal_digits;
extern const std::vector<WDigit> whexadecimal_digits;

#ifdef __cpp_char8_t
extern const std::vector<U8Digit> u8binary_digits;
extern const std::vector<U8Digit> u8octal_digits;
extern const std::vector<U8Digit> u8decimal_digits;
extern const std::vector<U8Digit> u8hexadecimal_digits;
#endif // __cpp_char8_t

extern const std::vector<U16Digit> u16binary_digits;
extern const std::vector<U16Digit> u16octal_digits;
extern const std::vector<U16Digit> u16decimal_digits;
extern const std::vector<U16Digit> u16hexadecimal_digits;

extern const std::vector<U32Digit> u32binary_digits;
extern const std::vector<U32Digit> u32octal_digits;
extern const std::vector<U32Digit> u32decimal_digits;
extern const std::vector<U32Digit> u32hexadecimal_digits;

extern const Format  binary;
extern const Format  octal;
extern const Format  decimal;
extern const Format  hexadecimal;

extern const WFormat  wbinary;
extern const WFormat  woctal;
extern const WFormat  wdecimal;
extern const WFormat  whexadecimal;

#ifdef __cpp_char8_t
extern const U8Format  u8binary;
extern const U8Format  u8octal;
extern const U8Format  u8decimal;
extern const U8Format  u8hexadecimal;
#endif // __cpp_char8_t

extern const U16Format  u16binary;
extern const U16Format  u16octal;
extern const U16Format  u16decimal;
extern const U16Format  u16hexadecimal;

extern const U32Format  u32binary;
extern const U32Format  u32octal;
extern const U32Format  u32decimal;
extern const U32Format  u32hexadecimal;


} // namespace Arithmos

#endif // LIBARITHMOS_H
