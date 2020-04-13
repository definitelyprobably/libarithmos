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


#include "arithmos.h"

namespace Arithmos {


// useful translations
const Translation hex_lower_to_upper{
  Congruence{ {'a', 'A'}, 'A'}, Congruence{ {'b', 'B'}, 'B'},
  Congruence{ {'c', 'C'}, 'C'}, Congruence{ {'d', 'D'}, 'D'},
  Congruence{ {'e', 'E'}, 'E'}, Congruence{ {'f', 'F'}, 'F'} };

const Translation hex_upper_to_lower{
  Congruence{ {'a', 'A'}, 'a'}, Congruence{ {'b', 'B'}, 'b'},
  Congruence{ {'c', 'C'}, 'c'}, Congruence{ {'d', 'D'}, 'd'},
  Congruence{ {'e', 'E'}, 'e'}, Congruence{ {'f', 'F'}, 'f'} };

const WTranslation whex_lower_to_upper{
  WCongruence{ {L'a', L'A'}, L'A'}, WCongruence{ {L'b', L'B'}, L'B'},
  WCongruence{ {L'c', L'C'}, L'C'}, WCongruence{ {L'd', L'D'}, L'D'},
  WCongruence{ {L'e', L'E'}, L'E'}, WCongruence{ {L'f', L'F'}, L'F'} };

const WTranslation whex_upper_to_lower{
  WCongruence{ {L'a', L'A'}, L'a'}, WCongruence{ {L'b', L'B'}, L'b'},
  WCongruence{ {L'c', L'C'}, L'c'}, WCongruence{ {L'd', L'D'}, L'd'},
  WCongruence{ {L'e', L'E'}, L'e'}, WCongruence{ {L'f', L'F'}, L'f'} };

#ifdef __cpp_char8_t
const U8Translation u8hex_lower_to_upper{
  U8Congruence{ {u8'a', u8'A'}, u8'A'}, U8Congruence{ {u8'b', u8'B'}, u8'B'},
  U8Congruence{ {u8'c', u8'C'}, u8'C'}, U8Congruence{ {u8'd', u8'D'}, u8'D'},
  U8Congruence{ {u8'e', u8'E'}, u8'E'}, U8Congruence{ {u8'f', u8'F'}, u8'F'} };

const U8Translation u8hex_upper_to_lower{
  U8Congruence{ {u8'a', u8'A'}, u8'a'}, U8Congruence{ {u8'b', u8'B'}, u8'b'},
  U8Congruence{ {u8'c', u8'C'}, u8'c'}, U8Congruence{ {u8'd', u8'D'}, u8'd'},
  U8Congruence{ {u8'e', u8'E'}, u8'e'}, U8Congruence{ {u8'f', u8'F'}, u8'f'} };
#endif // __cpp_char8_t

const U16Translation u16hex_lower_to_upper{
  U16Congruence{ {u'a', u'A'}, u'A'}, U16Congruence{ {u'b', u'B'}, u'B'},
  U16Congruence{ {u'c', u'C'}, u'C'}, U16Congruence{ {u'd', u'D'}, u'D'},
  U16Congruence{ {u'e', u'E'}, u'E'}, U16Congruence{ {u'f', u'F'}, u'F'} };

const U16Translation u16hex_upper_to_lower{
  U16Congruence{ {u'a', u'A'}, u'a'}, U16Congruence{ {u'b', u'B'}, u'b'},
  U16Congruence{ {u'c', u'C'}, u'c'}, U16Congruence{ {u'd', u'D'}, u'd'},
  U16Congruence{ {u'e', u'E'}, u'e'}, U16Congruence{ {u'f', u'F'}, u'f'} };

const U32Translation u32hex_lower_to_upper{
  U32Congruence{ {U'a', U'A'}, U'A'}, U32Congruence{ {U'b', U'B'}, U'B'},
  U32Congruence{ {U'c', U'C'}, U'C'}, U32Congruence{ {U'd', U'D'}, U'D'},
  U32Congruence{ {U'e', U'E'}, U'E'}, U32Congruence{ {U'f', U'F'}, U'F'} };

const U32Translation u32hex_upper_to_lower{
  U32Congruence{ {U'a', U'A'}, U'a'}, U32Congruence{ {U'b', U'B'}, U'b'},
  U32Congruence{ {U'c', U'C'}, U'c'}, U32Congruence{ {U'd', U'D'}, U'd'},
  U32Congruence{ {U'e', U'E'}, U'e'}, U32Congruence{ {U'f', U'F'}, U'f'} };


// invalid_format class
invalid_format::invalid_format() : message_{"invalid format number"} {}
const char* invalid_format::what() const noexcept {
  return message_.c_str();
}


// useful lists for defining number Formats
const std::vector<Format::digit_type> binary_digits{
  Format::digit_type{'0'}, Format::digit_type{'1'} };

const std::vector<Format::digit_type> octal_digits{
  Format::digit_type{'0'}, Format::digit_type{'1'},
  Format::digit_type{'2'}, Format::digit_type{'3'},
  Format::digit_type{'4'}, Format::digit_type{'5'},
  Format::digit_type{'6'}, Format::digit_type{'7'} };

const std::vector<Format::digit_type> decimal_digits{
  Format::digit_type{'0'}, Format::digit_type{'1'},
  Format::digit_type{'2'}, Format::digit_type{'3'},
  Format::digit_type{'4'}, Format::digit_type{'5'},
  Format::digit_type{'6'}, Format::digit_type{'7'},
  Format::digit_type{'8'}, Format::digit_type{'9'} };

const std::vector<Format::digit_type> hexadecimal_digits{
  Format::digit_type{'0'}, Format::digit_type{'1'},
  Format::digit_type{'2'}, Format::digit_type{'3'},
  Format::digit_type{'4'}, Format::digit_type{'5'},
  Format::digit_type{'6'}, Format::digit_type{'7'},
  Format::digit_type{'8'}, Format::digit_type{'9'},
  Format::digit_type{'a'}, Format::digit_type{'b'},
  Format::digit_type{'c'}, Format::digit_type{'d'},
  Format::digit_type{'e'}, Format::digit_type{'f'} };


// declare a binary-format number.
const Format  binary{ "0b", binary_digits, "e", decimal_digits };


// declare an octal-format number.
const Format  octal{ "0", octal_digits, "e", decimal_digits };


// declare a decimal-format number.
const Format  decimal{ "", decimal_digits, "e", decimal_digits };


// declare a hexadecimal-format number.
const Format  hexadecimal{ "0x", hexadecimal_digits, "p", decimal_digits };



// wchar_t versions:
// useful lists for defining number Formats
const std::vector<WFormat::digit_type> wbinary_digits{
  WFormat::digit_type{L'0'}, WFormat::digit_type{L'1'} };

const std::vector<WFormat::digit_type> woctal_digits{
  WFormat::digit_type{L'0'}, WFormat::digit_type{L'1'},
  WFormat::digit_type{L'2'}, WFormat::digit_type{L'3'},
  WFormat::digit_type{L'4'}, WFormat::digit_type{L'5'},
  WFormat::digit_type{L'6'}, WFormat::digit_type{L'7'} };

const std::vector<WFormat::digit_type> wdecimal_digits{
  WFormat::digit_type{L'0'}, WFormat::digit_type{L'1'},
  WFormat::digit_type{L'2'}, WFormat::digit_type{L'3'},
  WFormat::digit_type{L'4'}, WFormat::digit_type{L'5'},
  WFormat::digit_type{L'6'}, WFormat::digit_type{L'7'},
  WFormat::digit_type{L'8'}, WFormat::digit_type{L'9'} };

const std::vector<WFormat::digit_type> whexadecimal_digits{
  WFormat::digit_type{L'0'}, WFormat::digit_type{L'1'},
  WFormat::digit_type{L'2'}, WFormat::digit_type{L'3'},
  WFormat::digit_type{L'4'}, WFormat::digit_type{L'5'},
  WFormat::digit_type{L'6'}, WFormat::digit_type{L'7'},
  WFormat::digit_type{L'8'}, WFormat::digit_type{L'9'},
  WFormat::digit_type{L'a'}, WFormat::digit_type{L'b'},
  WFormat::digit_type{L'c'}, WFormat::digit_type{L'd'},
  WFormat::digit_type{L'e'}, WFormat::digit_type{L'f'} };


// declare a binary-format number.
const WFormat  wbinary{ L"0b", wbinary_digits, L"e", wdecimal_digits };


// declare an octal-format number.
const WFormat  woctal{ L"0", woctal_digits, L"e", wdecimal_digits };


// declare a decimal-format number.
const WFormat  wdecimal{ L"", wdecimal_digits, L"e", wdecimal_digits };


// declare a hexadecimal-format number.
const WFormat  whexadecimal{ L"0x", whexadecimal_digits, L"p", wdecimal_digits };



#ifdef __cpp_char8_t
// char8_t versions:
// useful lists for defining number Formats
const std::vector<U8Format::digit_type> u8binary_digits{
  U8Format::digit_type{u8'0'}, U8Format::digit_type{u8'1'} };

const std::vector<Format::digit_type> u8octal_digits{
  U8Format::digit_type{u8'0'}, U8Format::digit_type{u8'1'},
  U8Format::digit_type{u8'2'}, U8Format::digit_type{u8'3'},
  U8Format::digit_type{u8'4'}, U8Format::digit_type{u8'5'},
  U8Format::digit_type{u8'6'}, U8Format::digit_type{u8'7'} };

const std::vector<Format::digit_type> u8decimal_digits{
  U8Format::digit_type{u8'0'}, U8Format::digit_type{u8'1'},
  U8Format::digit_type{u8'2'}, U8Format::digit_type{u8'3'},
  U8Format::digit_type{u8'4'}, U8Format::digit_type{u8'5'},
  U8Format::digit_type{u8'6'}, U8Format::digit_type{u8'7'},
  U8Format::digit_type{u8'8'}, U8Format::digit_type{u8'9'} };

const std::vector<Format::digit_type> u8hexadecimal_digits{
  U8Format::digit_type{u8'0'}, U8Format::digit_type{u8'1'},
  U8Format::digit_type{u8'2'}, U8Format::digit_type{u8'3'},
  U8Format::digit_type{u8'4'}, U8Format::digit_type{u8'5'},
  U8Format::digit_type{u8'6'}, U8Format::digit_type{u8'7'},
  U8Format::digit_type{u8'8'}, U8Format::digit_type{u8'9'},
  U8Format::digit_type{u8'a'}, U8Format::digit_type{u8'b'},
  U8Format::digit_type{u8'c'}, U8Format::digit_type{u8'd'},
  U8Format::digit_type{u8'e'}, U8Format::digit_type{u8'f'} };


// declare a binary-format number.
const U8Format  u8binary{ u8"0b", u8binary_digits, u8"e", u8decimal_digits };


// declare an octal-format number.
const U8Format  u8octal{ u8"0", u8octal_digits, u8"e", u8decimal_digits };


// declare a decimal-format number.
const U8Format  u8decimal{ u8"", u8decimal_digits, u8"e", u8decimal_digits };


// declare a hexadecimal-format number.
const U8Format  u8hexadecimal{ u8"0x", u8hexadecimal_digits, u8"p", u8decimal_digits };
#endif // __cpp_char16_t



// char16_t versions:
// useful lists for defining number Formats
const std::vector<U16Format::digit_type> u16binary_digits{
  U16Format::digit_type{u'0'}, U16Format::digit_type{u'1'} };

const std::vector<U16Format::digit_type> u16octal_digits{
  U16Format::digit_type{u'0'}, U16Format::digit_type{u'1'},
  U16Format::digit_type{u'2'}, U16Format::digit_type{u'3'},
  U16Format::digit_type{u'4'}, U16Format::digit_type{u'5'},
  U16Format::digit_type{u'6'}, U16Format::digit_type{u'7'} };

const std::vector<U16Format::digit_type> u16decimal_digits{
  U16Format::digit_type{u'0'}, U16Format::digit_type{u'1'},
  U16Format::digit_type{u'2'}, U16Format::digit_type{u'3'},
  U16Format::digit_type{u'4'}, U16Format::digit_type{u'5'},
  U16Format::digit_type{u'6'}, U16Format::digit_type{u'7'},
  U16Format::digit_type{u'8'}, U16Format::digit_type{u'9'} };

const std::vector<U16Format::digit_type> u16hexadecimal_digits{
  U16Format::digit_type{u'0'}, U16Format::digit_type{u'1'},
  U16Format::digit_type{u'2'}, U16Format::digit_type{u'3'},
  U16Format::digit_type{u'4'}, U16Format::digit_type{u'5'},
  U16Format::digit_type{u'6'}, U16Format::digit_type{u'7'},
  U16Format::digit_type{u'8'}, U16Format::digit_type{u'9'},
  U16Format::digit_type{u'a'}, U16Format::digit_type{u'b'},
  U16Format::digit_type{u'c'}, U16Format::digit_type{u'd'},
  U16Format::digit_type{u'e'}, U16Format::digit_type{u'f'} };


// declare a binary-format number.
const U16Format  u16binary{ u"0b", u16binary_digits, u"e", u16decimal_digits };


// declare an octal-format number.
const U16Format  u16octal{ u"0", u16octal_digits, u"e", u16decimal_digits };


// declare a decimal-format number.
const U16Format  u16decimal{ u"", u16decimal_digits, u"e", u16decimal_digits };


// declare a hexadecimal-format number.
const U16Format  u16hexadecimal{ u"0x", u16hexadecimal_digits, u"p", u16decimal_digits };



// char32_t versions:
// useful lists for defining number U32Formats
const std::vector<U32Format::digit_type> u32binary_digits{
  U32Format::digit_type{U'0'}, U32Format::digit_type{U'1'} };

const std::vector<U32Format::digit_type> u32octal_digits{
  U32Format::digit_type{U'0'}, U32Format::digit_type{U'1'},
  U32Format::digit_type{U'2'}, U32Format::digit_type{U'3'},
  U32Format::digit_type{U'4'}, U32Format::digit_type{U'5'},
  U32Format::digit_type{U'6'}, U32Format::digit_type{U'7'} };

const std::vector<U32Format::digit_type> u32decimal_digits{
  U32Format::digit_type{U'0'}, U32Format::digit_type{U'1'},
  U32Format::digit_type{U'2'}, U32Format::digit_type{U'3'},
  U32Format::digit_type{U'4'}, U32Format::digit_type{U'5'},
  U32Format::digit_type{U'6'}, U32Format::digit_type{U'7'},
  U32Format::digit_type{U'8'}, U32Format::digit_type{U'9'} };

const std::vector<U32Format::digit_type> u32hexadecimal_digits{
  U32Format::digit_type{U'0'}, U32Format::digit_type{U'1'},
  U32Format::digit_type{U'2'}, U32Format::digit_type{U'3'},
  U32Format::digit_type{U'4'}, U32Format::digit_type{U'5'},
  U32Format::digit_type{U'6'}, U32Format::digit_type{U'7'},
  U32Format::digit_type{U'8'}, U32Format::digit_type{U'9'},
  U32Format::digit_type{U'a'}, U32Format::digit_type{U'b'},
  U32Format::digit_type{U'c'}, U32Format::digit_type{U'd'},
  U32Format::digit_type{U'e'}, U32Format::digit_type{U'f'} };


// declare a binary-format number.
const U32Format  u32binary{ U"0b", u32binary_digits, U"e", u32decimal_digits };


// declare an octal-format number.
const U32Format  u32octal{ U"0", u32octal_digits, U"e", u32decimal_digits };


// declare a decimal-format number.
const U32Format  u32decimal{ U"", u32decimal_digits, U"e", u32decimal_digits };


// declare a hexadecimal-format number.
const U32Format  u32hexadecimal{ U"0x", u32hexadecimal_digits, U"p", u32decimal_digits };



// also, let's create some explicit instantiations of the templated classes:
template class  Basic_Congruence<char>;
template class  Basic_Digit<char, count_type>;
template class  Basic_Format<char, count_type>;
template struct Basic_Data<char>;

template class  Basic_Congruence<wchar_t>;
template class  Basic_Digit<wchar_t, count_type>;
template class  Basic_Format<wchar_t, count_type>;
template struct Basic_Data<wchar_t>;

#ifdef __cpp_char8_t
template class  Basic_Congruence<char8_t>;
template class  Basic_Digit<char8_t, count_type>;
template class  Basic_Format<char8_t, count_type>;
template struct Basic_Data<char8_t>;
#endif // __cpp_char8_t

template class  Basic_Congruence<char16_t>;
template class  Basic_Digit<char16_t, count_type>;
template class  Basic_Format<char16_t, count_type>;
template struct Basic_Data<char16_t>;

template class  Basic_Congruence<char32_t>;
template class  Basic_Digit<char32_t, count_type>;
template class  Basic_Format<char32_t, count_type>;
template struct Basic_Data<char32_t>;


template std::basic_string<char> translate(
    const std::basic_string<char>&,
    const std::unordered_set<Basic_Congruence<char>>&);

template std::basic_string<wchar_t> translate(
    const std::basic_string<wchar_t>&,
    const std::unordered_set<Basic_Congruence<wchar_t>>&);

#ifdef __cpp_char8_t
template std::basic_string<char8_t> translate(
    const std::basic_string<char8_t>&,
    const std::unordered_set<Basic_Congruence<char8_t>>&);
#endif // __cpp_char8_t

template std::basic_string<char16_t> translate(
    const std::basic_string<char16_t>&,
    const std::unordered_set<Basic_Congruence<char16_t>>&);

template std::basic_string<char32_t> translate(
    const std::basic_string<char32_t>&,
    const std::unordered_set<Basic_Congruence<char32_t>>&);

} // namespace Arithmos
