
#ifdef __linux__
# define _XOPEN_SOURCE 601
#endif

#include <sstream>
#include <cstring>
#include "DxlException.hh"

void DxlException::addError(const int error)
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

/*
 * Public Constructor
 */
DxlException::DxlException(const int error)
{
  _info = "DxlException : ";
  this->addError(error);
}

DxlException::DxlException(const std::string &info)
{
  _info = "DxlException : ";
  _info = info;
}

/*
 * Protected Constructor
 */
DxlException::DxlException(const std::string &prefix, const int error)
{
  _info = prefix;
  this->addError(error);
}

DxlException::DxlException(const std::string &prefix, const std::string &error)
{
  _info = prefix;
  _info += error;
}

/*
 * Methods
 */
const char*   DxlException::what() const throw()
{
  return (_info.c_str());
}
