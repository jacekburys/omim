#include "string_utils.hpp"
#include "assert.hpp"

#include "../std/sstream.hpp"
#include "../std/iterator.hpp"

namespace strings
{

SimpleDelimiter::SimpleDelimiter(char const * delimChars)
{
  string const s(delimChars);
  string::const_iterator it = s.begin();
  while (it != s.end())
    m_delims.push_back(utf8::unchecked::next(it));
}

bool SimpleDelimiter::operator()(UniChar c) const
{
  for (UniString::const_iterator it = m_delims.begin(); it != m_delims.end(); ++it)
    if (*it == c)
      return true;
  return false;
}

UniChar LastUniChar(string const & s)
{
  if (s.empty())
    return 0;
  utf8::unchecked::iterator<string::const_iterator> iter(s.end());
  --iter;
  return *iter;
}

bool to_int(char const * s, int & i)
{
  char * stop;
  int x = strtol(s, &stop, 10);
  if (stop && *stop == 0)
  {
    i = x;
    return true;
  }
  return false;
}

bool to_uint64(char const * s, uint64_t & i)
{
  istringstream ss;
  ss.str(s);
  ss >> i;
  return !ss.fail();
}

bool to_int64(char const * s, int64_t & i)
{
  istringstream ss;
  ss.str(s);
  ss >> i;
  return !ss.fail();
}

bool to_double(char const * s, double & d)
{
  char * stop;
  double x = strtod(s, &stop);
  if (stop && *stop == 0)
  {
    d = x;
    return true;
  }
  return false;
}

UniString MakeLowerCase(UniString const & s)
{
  UniString result(s);
  MakeLowerCase(result);
  return result;
}

void MakeLowerCase(string & s)
{
  UniString uniStr;
  utf8::unchecked::utf8to32(s.begin(), s.end(), back_inserter(uniStr));
  MakeLowerCase(uniStr);
  s.clear();
  utf8::unchecked::utf32to8(uniStr.begin(), uniStr.end(), back_inserter(s));
}

string MakeLowerCase(string const & s)
{
  string result(s);
  MakeLowerCase(result);
  return result;
}

bool EqualNoCase(string const & s1, string const & s2)
{
  return MakeLowerCase(s1) == MakeLowerCase(s2);
}

}
