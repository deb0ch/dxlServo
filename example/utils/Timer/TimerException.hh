
#ifndef TIMER_EXCEPTION_H_
# define TIMER_EXCEPTION_H_

# include <exception>
# include <iostream>
# include <map>

# ifndef _WIN32
#  include <cerrno>
#  include <cstdio>
#  include <cstring>
# endif

class TimerException : public std::exception
{
public:
  TimerException(const int error);
  TimerException(const std::string &error);
  ~TimerException() throw() {}

public:
  TimerException(const std::string &prefix, const int error);
  TimerException(const std::string &prefix, const std::string &error);

  const char* what() const throw();

private:
  void addError(const int error);
  std::string		_info;
};

#endif /* !TIMER_EXCEPTION_H_ */
