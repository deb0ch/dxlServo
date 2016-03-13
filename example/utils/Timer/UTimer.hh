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

#ifndef UTIMER_H_
# define UTIMER_H_

# define _XOPEN_SOURCE 700

# ifdef __linux__
#  include <cerrno>
#  include <exception>
#  include <unistd.h>
# endif /* !__linux__ */

# ifdef _win32

# endif /* !_WIN32 */

# include <string>
# include <ctime>

# include "ITimer.hh"
# include "TimerException.hh"

/**
 * All time units in this class are in microseconds
*/
class Timer : public ITimer
{
public:
  virtual void			endFrame();
  virtual bool			canTick() const;
  virtual float			getDeltaTime() const;

  virtual unsigned long		getFps() const;
  virtual unsigned long		getCurrentFps() const;
  virtual void			setFps(unsigned long fps);

  virtual unsigned long		getTime();
  virtual void			sleep(unsigned long delay) const;

public:
  Timer(unsigned long fps = 60);
  virtual ~Timer() {}

private:
  Timer(const Timer &) = delete;
  Timer &operator=(const Timer &) = delete;

private:
  inline unsigned long	bufToTime(const struct timespec & timebuff) const;

private:
  unsigned long		_fps;
  struct timespec	_timeBuff;
  unsigned long		_timeZero;
  unsigned long		_currentTime;
  unsigned long		_previousTime;
};

#endif /* !UTIMER_H_ */
