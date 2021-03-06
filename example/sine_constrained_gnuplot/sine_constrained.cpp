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

#include <cstdlib>
#include <math.h>
#include <iostream>

#include "gnuplot-iostream.h"

#include "DxlServo.hh"
#include "Timer.hh"

#define TIMER_FREQ_HZ	20
#define PLOT_MAX_S	30	// plot over 10s

float	limit_high = 0.5;
float	limit_low = 0.25;

void	printDxlError(DxlServo& servo)
{
  if (servo.errorComFailTx())
    std::cout << "COMM_TXFAIL: Failed transmit instruction packet!" << std::endl;
  if (servo.errorComInval())
    std::cout << "COMM_TXERROR: Incorrect instruction packet!" << std::endl;
  if (servo.errorComFailRx())
    std::cout << "COMM_RXFAIL: Failed get status packet from device!" << std::endl;
  if (servo.errorComWaiting())
    std::cout << "COMM_RXWAITING: Now recieving status packet!" << std::endl;
  if (servo.errorComTimeout())
    std::cout << "COMM_RXTIMEOUT: There is no status packet!" << std::endl;
  if (servo.errorComCorrupt())
    std::cout << "COMM_RXCORRUPT: Incorrect status packet!" << std::endl;
  if (servo.errorVoltage())
    std::cout << "Input voltage error!" << std::endl;
  if (servo.errorAngle())
    std::cout << "Angle limit error!" << std::endl;
  if (servo.errorOverheat())
    std::cout << "Overheat error!" << std::endl;
  if (servo.errorRange())
    std::cout << "Out of range error!" << std::endl;
  if (servo.errorChecksum())
    std::cout << "Checksum error!" << std::endl;
  if (servo.errorOverload())
    std::cout << "Overload error!" << std::endl;
  if (servo.errorInstruction())
    std::cout << "Instruction code error!" << std::endl;
}

void	plot_stats(Gnuplot & gp, int x, double y1, double y2, double y3, double y4, double y5, double y6)
{
  static double xmin = x;
  static double xmax = x + (PLOT_MAX_S * 1000);
  static double ymin = y1;
  static double ymax = y1;
  static std::list<boost::tuple<double, double> > y1Data;
  static std::list<boost::tuple<double, double> > y2Data;
  static std::list<boost::tuple<double, double> > y3Data;
  static std::list<boost::tuple<double, double> > y4Data;
  static std::list<boost::tuple<double, double> > y5Data;
  static std::list<boost::tuple<double, double> > y6Data;

  if (xmax - xmin > (PLOT_MAX_S * 1000))
    xmin = xmax - (PLOT_MAX_S * 1000);
  if (x >= xmax)
    xmax = x;

  if (y1 <= ymin)
    ymin = y1;
  if (y1 >= ymax)
    ymax = y1;
  if (y2 <= ymin)
    ymin = y2;
  if (y2 >= ymax)
    ymax = y2;
  if (y3 <= ymin)
    ymin = y3;
  if (y3 >= ymax)
    ymax = y3;
  if (y4 <= ymin)
    ymin = y4;
  if (y4 >= ymax)
    ymax = y4;
  if (y5 <= ymin)
    ymin = y5;
  if (y5 >= ymax)
    ymax = y5;
  if (y6 <= ymin)
    ymin = y6;
  if (y6 >= ymax)
    ymax = y6;

  while (y1Data.size() >= PLOT_MAX_S * TIMER_FREQ_HZ)
    y1Data.pop_front();
  while (y2Data.size() >= PLOT_MAX_S * TIMER_FREQ_HZ)
    y2Data.pop_front();
  while (y3Data.size() >= PLOT_MAX_S * TIMER_FREQ_HZ)
    y3Data.pop_front();
  while (y4Data.size() >= PLOT_MAX_S * TIMER_FREQ_HZ)
    y4Data.pop_front();
  while (y5Data.size() >= PLOT_MAX_S * TIMER_FREQ_HZ)
    y5Data.pop_front();
  while (y6Data.size() >= PLOT_MAX_S * TIMER_FREQ_HZ)
    y6Data.pop_front();

  y1Data.push_back(boost::make_tuple(x, y1));
  y2Data.push_back(boost::make_tuple(x, y2));
  y3Data.push_back(boost::make_tuple(x, y3));
  y4Data.push_back(boost::make_tuple(x, y4));
  y5Data.push_back(boost::make_tuple(x, y5));
  y6Data.push_back(boost::make_tuple(x, y6));

  gp << "set xrange [" << xmin << ":" << xmax << "]\n "
     << "set yrange [" << ymin << ":" << ymax << "]\n";

  gp << "plot "
     << "'-' with lines title 'position command'"
     << ", "
     << "'-' with lines title 'present speed'"
     << ", "
     << "'-' with lines title 'present position'"
     << ", "
     << "'-' with lines title 'temperature'"
     << ", "
     << "'-' with lines title 'torque'"
     << ", "
     << "'-' with lines title 'delta time (s) * 100'"
     << "\n";

  gp.send1d(y1Data);
  gp.send1d(y2Data);
  gp.send1d(y3Data);
  gp.send1d(y4Data);
  gp.send1d(y5Data);
  gp.send1d(y6Data);
}

int	do_sine(int servoId, float freq)
{
  DxlServo	servo(servoId);
  Gnuplot	gp;
  Timer		timer(TIMER_FREQ_HZ);

  if (!DxlServo::devInit(0))	// /dev/ttyACM0 or /dev/ttyUSB0 or other on windows
    {
      std::cout << "Failed to initialize serial device" << std::endl;
      return EXIT_FAILURE;
    }
  else
    std::cout << "Serial device successfully initialized" << std::endl;
  if (!servo.init())
    {
      std::cout << "Failed to initialize dxl servo " << servo.id() << std::endl;
      return EXIT_FAILURE;
    }
  else
    std::cout << "Dxl servo " << servo.id() << " sucessfully initialized" << std::endl;
  servo.setCWAngleLimit(limit_low);
  servo.setCCWAngleLimit(limit_high);	// Servo now set to joint mode
  while (42)
    {
      if (timer.canTick())
	{
	  float command = (sin(2 * M_PI * freq * (timer.getTime() / 1000000.f))
			   * ((limit_high - limit_low) / 2))
	    + ((limit_high - limit_low) / 2)
	    + limit_low;

	  command = 0.35 + (rand() % 1000) / 50000.f;
	  servo.setGoalPos(command);
	  plot_stats(gp,
		     timer.getTime() / 1000,
		     command,
		     servo.presentSpeed(),
		     servo.presentPos(),
		     servo.presentTemp() / 10.f,
		     servo.presentLoad(),
		     timer.getDeltaTime() * 100);
	}
      timer.endFrame();
    }
  return EXIT_SUCCESS;
}

int	main(int argc, char **argv)
{
  float freq = 1.f / 5.f;		// Frequency of the sinusoid in Hz
  int	servoId = 1;

  if (argc > 1)
    servoId = ::atoi(argv[1]);
  if (argc > 2)
    freq = ::atof(argv[2]);
  return do_sine(servoId, freq);
}
