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

#ifdef _WIN32

# include "Timer.hh"

// Public:

Timer::Timer(unsigned long fps)
  : _fps(fps)
{
  _previousTime = this->getTime();
  _currentTime = this->getTime();
}

void	Timer::endFrame()
{
  if (!this->canTick())
    this->sleep((CLOCKS_PER_SEC / _fps) - (_currentTime - _previousTime));
  else
    _previousTime = _currentTime;
  _currentTime = this->getTime();
}

bool	Timer::canTick() const
{
  return (_currentTime - _previousTime >= CLOCKS_PER_SEC / _fps);
}

float	Timer::getDeltaTime() const
{
  return ((_currentTime - _previousTime) / 1000.f);
}

unsigned long	Timer::getFps() const
{
  return (_fps);
}

unsigned long	Timer::getCurrentFps() const
{
  return (CLOCKS_PER_SEC / (_currentTime - _previousTime));
}

void	Timer::setFps(unsigned long fps)
{
  _fps = fps;
}

unsigned long	Timer::getTime()
{
  if ((_time = clock()) == static_cast<clock_t>(-1))
    throw TimerException(GetLastError());
  return (_time);
}

void	Timer::sleep(unsigned long delay) const
{
  Sleep(delay); // No error return or exception
}

// Private:

#endif /* !_WIN32 */
