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

#ifndef ITIMER_H_
# define ITIMER_H_

# include "TimerException.hh"

/**
 * All time units in this class are in microseconds
*/
class ITimer
{
public:
  virtual void			endFrame() = 0;
  virtual bool			canTick() const = 0;
  virtual float			getDeltaTime() const = 0;

  virtual unsigned long		getFps() const = 0;
  virtual unsigned long		getCurrentFps() const = 0;
  virtual void			setFps(unsigned long fps) = 0;

  virtual unsigned long		getTime() = 0;
  virtual void			sleep(unsigned long delay) const = 0;

public:
  virtual ~ITimer() {}
};

#endif /* !ITIMER_H_ */
