/*
 * Copyright (c) 2016 Thomas Chauvot de Beauchene
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#ifdef __linux__
# define _XOPEN_SOURCE 601
#endif

#include <sstream>
#include <cstring>
#include "TimerException.hh"

void TimerException::addError(const int error)
{
  char buffer[512];
  std::string res;

  memset(buffer, 0, 512);
#ifdef _WIN32
  strerror_s(buffer, sizeof(buffer), error);
  _info += buffer;
#elif __linux__
  _info += strerror_r(error, buffer, sizeof(buffer));
#endif
}

/* Public Constructor */
TimerException::TimerException(const int error)
{
  _info = "TimerException : ";
  this->addError(error);
}

TimerException::TimerException(const std::string &info)
{
  _info = "TimerException : ";
  _info = info;
}

/* Protected Constructor */
TimerException::TimerException(const std::string &prefix, const int error)
{
  _info = prefix;
  this->addError(error);
}

TimerException::TimerException(const std::string &prefix, const std::string &error)
{
  _info = prefix;
  _info += error;
}

/* Methodes */
const char*   TimerException::what() const throw()
{
  return (_info.c_str());
}
