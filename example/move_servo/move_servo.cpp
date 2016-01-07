//
// move_servo.cpp for DxlServo
//
// Made by chauvo_t
// Login   <chauvo_t@epitech.net>
//
// Started on  Mon Dec  7 00:25:05 2015 chauvo_t
// Last update Mon Dec 28 16:57:48 2015 chauvo_t
//

#include <cstdlib>
#include <math.h>
#include <iostream>

#include <unistd.h>
#include "DxlServo.hh"

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

void	waitAndPrint(DxlServo &servo)
{
  int	presentPos = 0;
  int	prevPos = 0;

  while (servo.moving())
    {
      if (servo.error())
	printDxlError(servo);
      presentPos = servo.presentPos();
      if (servo.error())
	printDxlError(servo);
      if (presentPos != prevPos)
	{
	  std::cout << "Present pos: " << presentPos << std::endl;
	  prevPos = presentPos;
	}
    }
}

int	main(int argc, char **argv)
{
  int servoId = 1;

  if (!DxlServo::devInit(0))
    {
      std::cout << "Failed to initialize serial device" << std::endl;
      return EXIT_FAILURE;
    }
  else
    std::cout << "serial device successfully initialized" << std::endl;

  if (argc > 1)
    servoId = ::atoi(argv[1]);

  DxlServo	servo(servoId);

  if (!servo.init())
    {
      std::cout << "Failed to initialize dxl servo " << servo.id() << std::endl;
      return EXIT_FAILURE;
    }
  else
    std::cout << "Dxl servo " << servo.id() << " successfully initialized" << std::endl;
  servo.setCWAngleLimit(0);
  servo.setCCWAngleLimit(1);
  servo.setMovingSpeed(0.25);
  while (42)
    {
      servo.setGoalPos(0);
      if (servo.error())
	printDxlError(servo);
      waitAndPrint(servo);
      servo.setGoalPos(1);
      if (servo.error())
	printDxlError(servo);
      waitAndPrint(servo);
    }
  return 0;
}
