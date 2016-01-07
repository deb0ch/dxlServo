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
