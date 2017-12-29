////////////////////////////////////////////////////////////
//
// MIT License
//
// Copyright(c) 2017 Kurt Slagle - kurt_slagle@yahoo.com
// 
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files(the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and / or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions :
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
//
// The origin of this software must not be misrepresented; you must not claim
// that you wrote the original software.If you use this software in a product,
// an acknowledgment of the software used is required.
//
////////////////////////////////////////////////////////////

#include "Utils\String.h"

STRING::STRING()
{
  rawstring = (char *)malloc(1);
  rawstring[0] = '\0';

  refcount = (std::size_t *)malloc(sizeof(std::size_t));
  *refcount = 1;

  length = (std::size_t *)malloc(sizeof(std::size_t));
  *length = 0;
}

STRING::STRING(const STRING &str)
  : rawstring(str.rawstring), refcount(str.refcount), length(str.length)
{
  ++(*refcount);
}

STRING::STRING(const std::string &str)
{
  rawstring = (char *)malloc(str.length() + 1);
  memcpy(rawstring, str.c_str(), str.length());
  rawstring[*length] = '\0';

  length = (std::size_t *)malloc(sizeof(std::size_t));
  *length = str.length();

  refcount = (std::size_t *)malloc(sizeof(std::size_t));
  *refcount = 1;
}

STRING::STRING(const char *str)
{
  std::size_t len = strlen(str);

  rawstring = (char *)malloc(len + 1);
  memcpy(rawstring, str, len);
  rawstring[len] = '\0';

  refcount = (std::size_t *)malloc(sizeof(std::size_t));
  *refcount = 1;

  length = (std::size_t *)malloc(sizeof(std::size_t));
  *length = len;
}

STRING& STRING::operator=(const STRING &str)
{
  --(*refcount);
  if (*refcount == 0) {
    free(refcount);
    free(length);
    free(rawstring);
  }

  rawstring = str.rawstring;
  length = str.length;
  refcount = str.refcount;
  ++(*refcount);
  return *this;
}

STRING& STRING::operator=(const std::string &str)
{
  --(*refcount);
  if (*refcount == 0) {
    free(rawstring);
    free(refcount);
    free(length);
  }

  std::size_t len = str.length();

  rawstring = (char *)malloc(len + 1);
  memcpy(rawstring, str.c_str(), len);
  rawstring[len] = '\0';

  length = (std::size_t *)malloc(sizeof(std::size_t));
  *length = len;

  refcount = (std::size_t *)malloc(sizeof(std::size_t));
  *refcount = 1;

  return *this;
}

STRING& STRING::operator=(const char *str)
{
  --(*refcount);
  if (*refcount == 0) {
    free(refcount);
    free(length);
    free(rawstring);
  }

  std::size_t len = strlen(str);

  rawstring = (char *)malloc(len + 1);
  memcpy(rawstring, str, len);
  rawstring[len] = '\0';

  length = (std::size_t *)malloc(sizeof(std::size_t));
  *length = len;

  refcount = (std::size_t *)malloc(sizeof(std::size_t));
  *refcount = 1;

  return *this;
}

STRING::~STRING()
{
  if (*refcount > 1) {
    --(*refcount);
  }
  else {
    free(refcount);
    free(length);
    free(rawstring);
  }
}

std::size_t STRING::Length() const
{
  return (*length);
}

void STRING::Clear()
{
  delete[] rawstring;
  *length = 0;
}


std::ostream& operator<<(std::ostream &out, const STRING &str)
{
  char *f = str.rawstring;
  while (*f != '\0') {
    out << *f++;
  }

  return out;
}

std::istream& operator >> (std::istream &in, STRING &str)
{
  return in;
}

bool STRING::operator==(const STRING &str)
{
  if (!rawstring || !str.rawstring)
    return false;

  return (memcmp(rawstring, str.rawstring, *length) == 0);
}

bool STRING::operator==(const std::string &str)
{
  if (!length || !refcount || !rawstring)
    return false;

  if (*length != str.length())
    return false;

  char *f = rawstring;
  for (auto c : str) {
    if (*f != c)
      return false;
    f++;
  }
  return true;
}

bool STRING::operator==(const char *str)
{
  if (!rawstring || !length || !refcount)
    return false;

  return (strcmp(rawstring, str) == 0);
}

STRING::operator std::string()
{
  return std::string(rawstring);
}

STRING::operator bool()
{
  return (rawstring != nullptr);
}

const char* STRING::str() const
{
  return rawstring;
}
