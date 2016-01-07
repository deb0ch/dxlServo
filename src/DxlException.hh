
#ifndef DXL_EXCEPTION_H_
# define DXL_EXCEPTION_H_

# include <exception>
# include <iostream>
# include <map>

# ifndef _WIN32
#  include <cerrno>
#  include <cstdio>
#  include <cstring>
# endif

class DxlException : public std::exception
{
public:
  DxlException(const int error);
  DxlException(const std::string &error);
  ~DxlException() throw() {}

public:
  DxlException(const std::string &prefix, const int error);
  DxlException(const std::string &prefix, const std::string &error);

  const char* what() const throw();

private:
  void addError(const int error);
  std::string		_info;
};

#endif /* !DXL_EXCEPTION_H_ */
