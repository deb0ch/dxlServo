//
// sine.cpp for DxlServo
//
// Made by chauvo_t
// Login   <chauvo_t@epitech.net>
//
// Started on  Mon Dec  7 00:25:05 2015 chauvo_t
// Last update Tue Jan  5 12:04:14 2016 chauvo_t
//

#include <cstdlib>
#include <math.h>
#include <iostream>

#include "DxlServo.hh"
#include "Timer.hh"

#define TIMER_FREQ_HZ	60

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

int	do_sine(int servoId, float freq)
{
  DxlServo	servo(servoId);
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
  servo.setCWAngleLimit(0);
  servo.setCCWAngleLimit(0);	// Servo now set to wheel mode
  while (42)
    {
      if (timer.canTick())
	{
	  float command = ::sin(2 * M_PI * freq * (timer.getTime() / 1000000.f));

	  servo.setMovingSpeed(command);
	}
      timer.endFrame();
    }
  return EXIT_SUCCESS;
}

int	main(int argc, char **argv)
{
  float freq = 1.f / 3.f;		// Frequency of the sinusoid in Hz
  int	servoId = 1;

  if (argc > 1)
    servoId = ::atoi(argv[1]);
  if (argc > 2)
    freq = ::atof(argv[2]);
  return do_sine(servoId, freq);
}
