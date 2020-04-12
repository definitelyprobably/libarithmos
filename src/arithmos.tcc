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


#ifndef LIBARITHMOS_TCC
#define LIBARITHMOS_TCC
  
namespace Arithmos {

inline
congruence_not_in_set::congruence_not_in_set()
  : out_of_range("element not in set") {}


// -- class Basic_Congruence --------------
template <typename TChar>
Basic_Congruence<TChar>::Basic_Congruence(const set& s, const char_type d)
  : set_{s}, default_{d}
{
  if ( set_.find(d) == set_.end() )
    throw congruence_not_in_set();
}

template <typename TChar>
bool Basic_Congruence<TChar>::operator==(const Basic_Congruence& b) const {
  return set_ == b.set_ && default_ == b.default_;
}

template <typename TChar>
bool Basic_Congruence<TChar>::operator!=(const Basic_Congruence& b) const {
  return !(*this == b);
}

template <typename TChar>
auto Basic_Congruence<TChar>::get_default() const -> char_type {
  return default_;
}

template <typename TChar>
auto Basic_Congruence<TChar>::normalize(const char_type t) const -> char_type {
  if ( has(t) )
    return default_;
  else
    return t;
}

template <typename TChar>
bool Basic_Congruence<TChar>::has(const char_type t) const {
  return set_.find(t) != set_.end();
}




// -- template function translate --------------
template <typename T>
std::basic_string<T>
translate(const std::basic_string<T>& input,
          const std::unordered_set<Basic_Congruence<T>>& translations) {
  std::basic_string<T> output;
  output.reserve( input.size() );
  for (auto string_char : input) {
    bool default_set = false;
    for (auto char_congruence : translations) {
      if ( char_congruence.has(string_char) ) {
        output += char_congruence.get_default();
        default_set = true;
        break;
      }
    }
    if (!default_set)
      output += string_char;
  }

  return output;
}



  
// -- class Basic_Digit --------------
// ctor: Basic_Digit(const char_type, const count_type)
template <typename T, typename U>
Basic_Digit<T,U>::Basic_Digit(const char_type name,
                              const count_type count_max)
  : name_{name}, count_max_{count_max} {}

// ctor: Basic_Digit(const char_type)
template <typename T, typename U>
Basic_Digit<T,U>::Basic_Digit(const char_type name)
  : Basic_Digit{name, static_cast<count_type>(-1)} {}

// operator==(const Basic_Digit&)
template <typename T, typename U>
bool Basic_Digit<T,U>::operator==(const Basic_Digit& d) const {
  return name_ == d.name_;
}

// operator==(const char_type)
template <typename T, typename U>
bool Basic_Digit<T,U>::operator==(const char_type d) const {
  return name_ == d;
}

// operator!=(const Basic_Digit&)
template <typename T, typename U>
bool Basic_Digit<T,U>::operator!=(const Basic_Digit& d) const {
  return !(*this == d);
}

// operator!=(const char_type)
template <typename T, typename U>
bool Basic_Digit<T,U>::operator!=(const char_type d) const {
  return !(*this == d);
}

// get name
template <typename T, typename U>
auto Basic_Digit<T,U>::name() const -> char_type {
  return name_;
}

// get count max
template <typename T, typename U>
auto Basic_Digit<T,U>::count_max() const -> count_type {
  return count_max_;
}





// -- struct Basic_Data --------------
// ctor: Basic_Data()
template <typename T>
Basic_Data<T>::Basic_Data()
  : is_number                     {false},
    is_integer                    {false},
    is_integer_literal            {true},
    has_decimal                   {false},
    has_decimal_literal           {false},
    is_fraction_by_exponent       {false},
    is_zero                       {false},
    is_positive                   {true},
    is_explicit_positive          {false},
    is_exponent_positive          {true},
    is_exponent_explicit_positive {false},
    whole_width                   {0},
    exponent_width                {0},
    mantissa                      {0},
    whole_string                  {},
    whole_string_normalized       {},
    exponent_position             {string::npos},
    exponent_string               {},
    exponent_string_normalized    {},
    normalized                    {}
  {}

// declare == operator
template <typename T>
bool Basic_Data<T>::operator==(const Basic_Data<T>& d) const {
  return is_number                     == d.is_number &&
         is_integer                    == d.is_integer &&
         is_integer_literal            == d.is_integer_literal &&
         has_decimal                   == d.has_decimal &&
         has_decimal_literal           == d.has_decimal_literal &&
         is_fraction_by_exponent       == d.is_fraction_by_exponent &&
         is_zero                       == d.is_zero &&
         is_positive                   == d.is_positive &&
         is_explicit_positive          == d.is_explicit_positive &&
         is_exponent_positive          == d.is_exponent_positive &&
         is_exponent_explicit_positive == d.is_exponent_explicit_positive &&
         whole_width                   == d.whole_width &&
         exponent_width                == d.exponent_width &&
         mantissa                      == d.mantissa &&
         whole_string                  == d.whole_string &&
         whole_string_normalized       == d.whole_string_normalized &&
         exponent_position             == d.exponent_position &&
         exponent_string               == d.exponent_string &&
         exponent_string_normalized    == d.exponent_string_normalized &&
         normalized                    == d.normalized;
}

// declare != operator
template <typename T>
bool Basic_Data<T>::operator!=(const Basic_Data<T>& d) const {
  return !(*this == d);
}

// print debug method
template <typename T>
void Basic_Data<T>::print(std::basic_ostream<char_type>& out) const {
  out << "is number: " << is_number
      << "\nwhole string: " << whole_string
      << "\nwhole string (normalized): " << whole_string_normalized
      << "\nexponent string: " << exponent_string
      << "\nexponent string (normalized): " << exponent_string_normalized
      << "\nnormalized: " << normalized
      << "\nis positive: " << is_positive
      << "\nis positive (explicit): " << is_explicit_positive
      << "\nis exponent positive: " << is_exponent_positive
      << "\nis exponent positive (explicit): "
      << is_exponent_explicit_positive
      << "\nis zero: " << is_zero
      << "\nis integer: " << is_integer
      << "\nis integer literal: " << is_integer_literal
      << "\nhas decimal: " << has_decimal
      << "\nhas decimal literal: " << has_decimal_literal
      << "\nis fraction by exponent: " << is_fraction_by_exponent
      << "\nwhole width: " << whole_width
      << "\nexponent width: " << exponent_width
      << "\nmantissa: " << mantissa
      << "\nexponent position: " << exponent_position
      << std::endl;
}





// -- struct Basic_Format::Split -------------
// ctor: Split()
template <typename T, typename U>
Basic_Format<T,U>::Split::Split()
  : whole_positive    {true},
    whole_part        {},
    decimal           {false},
    decimal_part      {},
    exponent          {false},
    exponent_positive {true},
    exponent_part     {}
{}

// print debug method
template <typename T, typename U>
void Basic_Format<T,U>::Split::print(std::basic_ostream<char_type>& out) const
{
  out << "whole positive: " << whole_positive
      << "\nwhole part: " << whole_part
      << "\ndecimal: " << decimal
      << "\ndecimal_part: " << decimal_part
      << "\nexponent: " << exponent
      << "\nexponent positive: " << exponent_positive
      << "\nexponent part: " << exponent_part
      << std::endl;
}


// -- struct Basic_Format::Count -------------
// ctor: Count(const count_type)
template <typename T, typename U>
Basic_Format<T,U>::Count::Count(const count_type max)
  : count_list_(max, count_type(0)) {}



// -- class Basic_Format --------------
// ctor: Basic_Format(<...>)
template <typename T, typename U>
Basic_Format<T,U>::Basic_Format(const string&       specifier,
                                const digits_type&  digits,
                                const string&       exp_string,
                                const digits_type&  exp_digits)
  : specifier_  {specifier},
    digits_     {digits},
    exp_        {exp_string},
    exp_digits_ {exp_digits}
{
  if ( digits.size() < 2 || exp_digits.size() < 2 )
    throw invalid_format();
  digits_.push_back(digit_type(char_type('.'),1)); // FIXME: better way?
}

// get: specifier_
template <typename T, typename U>
auto Basic_Format<T,U>::specifier() const -> const string& {
  return specifier_;
}

// get: digits_
template <typename T, typename U>
auto Basic_Format<T,U>::digits() const -> const digits_type& {
  return digits_;
}

// get: exp_
template <typename T, typename U>
auto Basic_Format<T,U>::exponent_specifier() const -> const string& {
  return exp_;
}

// get: exp_digits_
template <typename T, typename U>
auto Basic_Format<T,U>::exponent_digits() const -> const digits_type& {
  return exp_digits_;
}

// compare method:
//   Basic_Data<T> compare(const string& str)
//
// This member function will examine str to see whether it conforms to the
// number format described by the class and also record other properties of
// it concerning its interpretation as a number. It will function by moving
// sequentially through the string interpreting each character it meets by
// comparing it to what should be found at that point in the string as set
// out by the class's data members, who describe the format the number must
// conform to.
template <typename T, typename U>
Basic_Data<T> Basic_Format<T,U>::compare(const string& str) const {
  // first, we'll exit if the string is empty
  if (str.empty())
    return {};
  const str_size_type str_length = str.length();
  if (str_length==0 || str_length==string::npos)
    return {};

  // look for a pre-digit (+ or - sign)
  Basic_Data<T> data;
  str_size_type str_index = 0;
  if (str.at(str_index) == char_type('+')) {
    data.is_explicit_positive = true;
    ++str_index;
  }
  else if (str.at(str_index) == char_type('-')) {
    data.is_positive = false;
    data.whole_string_normalized += str.at(str_index);
    ++str_index;
  }

  // look for a type specifier if the class records one.
  if ( !specifier_.empty() ) {
    const str_size_type specifier_length = specifier_.length();
    if ( specifier_ != str.substr(str_index,specifier_length) )
      return {};
    str_index += specifier_length;
    data.whole_string_normalized += specifier_;
  }
  // at this point, whole_string_normalized is: [-][specifier]


  // look for an exponent string and then examine all the digits between
  // str_index and that exponent for conformity.
  data.exponent_position = str.find(exp_, str_index);
  bool start = true;
  Count digit_count{ digits_.size() };
  for (;
       str_index < (data.exponent_position == string::npos ?
                    str_length : data.exponent_position);
       ++str_index) {
    bool found = false;
    for (auto j = digits_.begin(); j != digits_.end(); ++j) {
      if ( *j == str.at(str_index) ) {
        found = true;
        if ( digit_count.count_list_.at(j - digits_.begin())
                >= j->count_max() )
          return {};
        // ignore all zeros that appear before any other digit:
        if ( j->name() != digits_.begin()->name() || !start ) {
          if ( j->name() == char_type('.') ) {
            data.has_decimal_literal = true;
            if (start)
              // a decimal at the start, ".",  is normalized to "0." and
              // then we continue...
              data.whole_string_normalized += digits_.begin()->name();
          }
          start = false;
          data.whole_string_normalized += j->name();
        }
        ++digit_count.count_list_.at(j - digits_.begin());
        break;
      }
    }
    if (!found)
      return {};
  }
  data.whole_string = str.substr(0,str_index);

  // First, let's deal with the decimals.
  // Let's begin by dealing with:
  //   [+-][specifier].[e...]  <-- whole string has no digits, only a
  //                               decimal point (excluding pre-digits and
  //                               the specifier.
  // This leaves:
  //   whole_string:  [+-][specifier].
  //   whole_string_normalized:  [-][specifier]0.
  // We need to deal with this case, and all other decimal variations will
  // be correctly handled by the code that follows. Note, the form of the
  // normalized whole string is reproduced by othe inputs, so check the form
  // of the raw whole string and NOT the form of the normalized whole string
  // to do the following check
  if (data.whole_string ==
       ((data.is_positive ?
            (data.is_explicit_positive ? string(1,char_type('+')) : string()) :
            string(1,char_type('-')))
        .append(specifier_)
        .append(1,char_type('.'))) )
    return {};

  // The only correction we've made is putting a zero before a decimal point
  // if there was not already one there, so let's begin normalizing the
  // whole string by removing any zeros from the end of the decimal part of
  // the normalized whole string, and the decimal point too if all the
  // decimal part was filled with zeros (this will also deal with the
  // scenario that the decimal part was empty, correctly removing the
  // decimal point):
  const str_size_type decimal_position = data.whole_string_normalized.find('.');
  if ( decimal_position != string::npos ) {
    data.is_integer_literal = false;
    for (auto i = data.whole_string_normalized.length()-1;
         i >= decimal_position; --i) {
      if ( data.whole_string_normalized.at(i) == digits_.begin()->name() )
        data.whole_string_normalized.erase(i);
      else
        break;
    }
    if ( data.whole_string_normalized.length() == decimal_position+1 ) {
      data.is_integer = true;
      data.whole_string_normalized.erase(decimal_position);
    }
  }
  // Note: whole_string_normalized may be "-[specifier]0" at this point, so
  // we're not finished yet; but this result will also be produced by
  // parsing some integer strings, so we'll deal with this after we've done
  // dealing with integer strings (coming up next...) and kill two birds
  // with one code.

  // Now let's deal with integers (strings that didn't have a decimal
  // point): basically, we only need to add a zero when the input was all
  // zeros, but before that we need to check for the case when no digits at
  // all were entered, returning not a number if there is no exponent, and
  // normalizing the whole string to 1 otherwise.
  //   [+-][specifier]
  //       whole_string: [+-][specifier]
  //       whole_string_normalized: [-][specifier]
  //       ACTION: return not a number
  //   [+-][specifier]e...
  //       whole_string: [+-][specifier]
  //       whole_string_normalized: [-][specifier]
  //       ACTION: whole_string_normalized turned to: [-][specifier]1
  //   [+-][specifier]0000...
  //       whole_string: [+-][specifier]
  //       whole_string_normalized: [-][specifier]
  //       ACTION: whole_string_normalized turned to: [-][specifier]0
  //   [+-][specifier]0000...e...
  //       whole_string: [+-][specifier]
  //       whole_string_normalized: [-][specifier]
  //       ACTION: whole_string_normalized turned to: [-][specifier]0
  if (data.whole_string ==
       ((data.is_positive ?
            (data.is_explicit_positive ? string(1,char_type('+')) : string()) :
            string(1,char_type('-')))
        + specifier_) ) {
    if (data.exponent_position == string::npos)
      return {};
    else
      data.whole_string_normalized += (digits_.begin()+1)->name();
  }
  //   [+-][specifier]0000...
  //       whole_string: [+-][specifier]
  //       whole_string_normalized: [-][specifier]
  if (data.whole_string_normalized ==
       ((data.is_positive ? string() : string(1,char_type('-')))
        + specifier_) )
    data.whole_string_normalized += digits_.begin()->name();

  // finally, we finish with the whole string by setting is_zero and finally
  // dealing with the case "-[specifier]0"
  if (data.whole_string_normalized == (specifier_ + digits_.begin()->name()))
    data.is_zero = true;
  else if (data.whole_string_normalized ==
            (string(1,char_type('-')) + specifier_
             + digits_.begin()->name()) ) {
    data.is_zero = true;
    data.whole_string_normalized = (specifier_ + digits_.begin()->name());
  }


  // next let's set the exponent data:
  if ( data.exponent_position != string::npos ) {
    str_index += exp_.length();
    const str_size_type exp_start = str_index;
    // if the exponent is empty, then exit not a number:
    if ( str.substr(str_index).empty() )
      return {};

    // look for an exponent pre-digit (+ or - sign)
    if (str.at(str_index) == char_type('+')) {
      data.is_exponent_explicit_positive = true;
      ++str_index;
    }
    else if (str.at(str_index) == char_type('-')) {
      data.is_exponent_positive = false;
      data.exponent_string_normalized += str.at(str_index);
      ++str_index;
    }

    // if the exponent (after a pre-digit) is empty, then exit not a number:
    if ( str.substr(str_index).empty() )
      return {};

    // examine all the digits in the exponent for conformity:
    start = true;
    Count exp_digit_count{ exp_digits_.size() };
    for (; str_index < str_length; ++str_index) {
      bool found = false;
      for (auto j = exp_digits_.begin(); j != exp_digits_.end(); ++j) {
        if ( *j == str.at(str_index) ) {
          found = true;
          if ( exp_digit_count.count_list_.at(j - exp_digits_.begin())
                  >= j->count_max() )
            return {};
          if ( j->name() != exp_digits_.begin()->name() || start==false ) {
            start = false;
            data.exponent_string_normalized += j->name();
          }
          ++exp_digit_count.count_list_.at(j - exp_digits_.begin());
          break;
        }
      }
      if (!found)
        return {};
    }
    data.exponent_string = str.substr(exp_start,str_length-exp_start);
  }

  // deal with the case that all the exponent digits were zero, so no digits
  // we captured into exponent_string_normalized:
  if ( data.exponent_string_normalized.empty() ||
       data.exponent_string_normalized == string(1,char_type('-')) )
    data.exponent_string_normalized = exp_digits_.begin()->name();

  data.normalized = data.whole_string_normalized;
  if ( (data.exponent_position != string::npos &&
        data.exponent_string_normalized !=
                          string(1, exp_digits_.begin()->name()))
       && !data.is_zero )
    data.normalized += exp_ + data.exponent_string_normalized;

  // finally, we need to determine if the number is an integer or not;
  // first, we'll calculate the whole width (zero if the number is zero, so
  // skip the code if data.is_zero == true)...
  const str_size_type norm_whole_string_decimal_pos =
      data.whole_string_normalized.find(string(1,char_type('.')));
  if ( norm_whole_string_decimal_pos != string::npos )
    data.has_decimal = true; // might as well set this here as were at it
  if ( !data.is_zero ) {
    const str_size_type norm_whole_string_length = 
      data.whole_string_normalized.length();
    if ( norm_whole_string_decimal_pos == string::npos )
      while (data.whole_string_normalized.at(norm_whole_string_length -
              data.whole_width-1) == digits_.begin()->name() )
        ++data.whole_width;
    else
      data.whole_width = norm_whole_string_decimal_pos -
                         norm_whole_string_length + 1;
  }
  // ...then we'll calculate the exponent width
  data.exponent_width =
          raw_str_to_int(data.exponent_string_normalized, false);
  if (!data.is_exponent_positive) {
    // only if the normalized exponent is not zero shall we set
    // is_fraction_by_exponent:
    if ( data.exponent_string_normalized !=
                                  string(1, exp_digits_.begin()->name()) )
      data.is_fraction_by_exponent = true;
    data.exponent_width *= -1;
  }

  // use the whole and exponent widths to set is_integer:
  if ( data.is_zero )
    data.is_integer = true;
  else if (data.whole_width + data.exponent_width < 0)
    data.is_integer = false;
  else
    data.is_integer = true;

  // if it is not an integer then it cannot be a literal integer:
  if (!data.is_integer)
    data.is_integer_literal = false;

  // let's set mantissa from the other data member data.
  if ( data.is_zero )
    data.mantissa = 1;
  else {
    if ( data.whole_width < 0 ) { // we have a fraction
      const str_size_type start = specifier_.length()
                                      + (data.is_positive ? 0 : 1);
      const str_size_type decimal_pos =
                  data.whole_string_normalized.find(string(1,char_type('.')));
      if ( decimal_pos == start + 1 ) {
        // we only have one digit before the decimal point.
        if (data.whole_string_normalized.at(start) == digits_.begin()->name()) {
          // the digit before the decimal point is zero. We need to find the
          // first non-zero digit after the decimal point:
          str_size_type zeros = 0;
          while ( data.whole_string_normalized.at(decimal_pos+1+zeros)
                    == digits_.begin()->name() )
            ++zeros;
          data.mantissa = -1*data.whole_width - zeros;
        }
        else
          data.mantissa = 1 - data.whole_width; //whole_width < 0 remember.
      }
      else
        // take all the digits before the decimal point and the digits after
        // it.
        data.mantissa = decimal_pos - start - data.whole_width;
    }
    else
      // take just the length of the string minus the zeros at the end and a
      // specifier and sign if they are present.
      data.mantissa = data.whole_string_normalized.length() - data.whole_width
                        - specifier_.length() - (data.is_positive ? 0 : 1);
  }
  
  data.is_number = true;
  return data;
}




template <typename T, typename U>
auto Basic_Format<T,U>::to (const Basic_Format<T,U>& dest,
                            const string& input) const -> string {
  const Basic_Data<T> d = compare(input);
  return (d.is_number && d.is_integer_literal) ? to(dest, d) : string{};
}

template <typename T, typename U>
auto Basic_Format<T,U>::to (const Basic_Format<T,U>& dest,
                            const Basic_Data<T>& data) const -> string {
  // [-][specifier][whole][.{decimal}][e[-]{exponent}]
  //
  const Split s = raw_split(data);
  const string whole_converted = raw_convert(dest, s.whole_part);
  const string exponent_converted = s.exponent ?
                               raw_convert(dest, s.exponent_part, false) :
                               string{};
  
  return (s.whole_positive ? string() : string(1,char_type('-')))
         + dest.specifier()
         + whole_converted
         + (s.exponent ?  dest.exponent_specifier()
                          + (s.exponent_positive ?
                             string() : string(1,char_type('-')))
                          + exponent_converted
                       : string());
}






template <typename T, typename U>
auto Basic_Format<T,U>::raw_str_to_int
    (const string& input, const bool digit_list) const -> width_type {
  width_type ret = 0;
  const str_size_type input_length = input.length();
  const typename digits_type::size_type base =
                            digit_list ? digits_.size()-1 : exp_digits_.size();
  for (str_size_type i=0; i<input_length; ++i) {
    for (typename digits_type::size_type j=0; j<base; ++j) {
      if ( (digit_list ? digits_ : exp_digits_).at(j) == input.at(i)) {
        ret += j*pow(base, (input_length-i-1));
        break;
      }
    }
  }
  return ret;
}



template <typename T, typename U>
auto Basic_Format<T,U>::raw_int_to_str
      (const Basic_Format<T,U>& dest, width_type input,
       const bool digit_list) const -> string {
  if (input==0)
    return string(1, dest.digits().begin()->name());
  const auto base = digit_list ? dest.digits().size() - 1 :
                                 dest.exponent_digits().size();
  if (input < 0 ||
      static_cast<std::make_unsigned<width_type>::type>(input) < base)
    return string(1, (digit_list ? dest.digits() : dest.exponent_digits())
                     .at(input).name());

  string ret;
  auto power = 0;
  while ( pow(base, power) <= input )
    ++power;
  while (--power, input > 0) {
    auto digit = 0;
    while ( digit*pow(base, power) <= input )
      ++digit;
    --digit;
    ret += (digit_list ? dest.digits() : dest.exponent_digits())
           .at(digit).name();
    input -= digit*pow(base, power);
  }
  for (; power >= 0; --power)
    ret += (digit_list ? dest.digits() : dest.exponent_digits())
           .begin()->name();
  return ret;
}



template <typename T, typename U>
auto Basic_Format<T,U>::raw_convert(const Basic_Format<T,U>& dest,
                                    const string& input,
                                    const bool digit_list) const -> string {
  const width_type internal_number
      = raw_str_to_int(input, digit_list);
  return raw_int_to_str(dest, internal_number, digit_list);
}




template <typename T, typename U>
auto Basic_Format<T,U>::raw_split(const Basic_Data<T>& data) const -> Split {
  Split s;
  // [-][specifier][whole][.{decimal}][e[-]{exponent}]

  str_size_type whole_start = specifier_.length();
  if (data.normalized.at(0) == char_type('-')) {
    s.whole_positive = data.is_positive;
    ++whole_start;
  }

  const str_size_type exp_pos = data.normalized.find(exp_);
  if (exp_pos != string::npos) {
    s.exponent = true;
    str_size_type exp_start = exp_pos + exp_.length();
    s.exponent_positive = data.is_exponent_positive;
    if (!s.exponent_positive)
      ++exp_start;
    s.exponent_part = data.normalized.substr(exp_start);
  }

  const str_size_type decimal_pos = data.normalized.find(char_type('.'));
  if (decimal_pos == string::npos) {
    if (exp_pos == string::npos)
      s.whole_part = data.normalized.substr(whole_start);
    else
      s.whole_part = data.normalized.substr(whole_start, exp_pos-whole_start);
  }
  else {
    s.decimal = true;
    if (exp_pos == string::npos) {
      s.whole_part = data.normalized.substr(whole_start,
                                            decimal_pos-whole_start);
      s.decimal_part = data.normalized.substr(decimal_pos+1);
    }
    else {
      s.whole_part = data.normalized.substr(whole_start, exp_pos-whole_start);
      s.decimal_part = data.normalized.substr(decimal_pos+1,
                                              exp_pos-decimal_pos-1);
    }
  }

  return s;
}


} // namespace Arithmos

#endif // LIBARITHMOS_TCC
