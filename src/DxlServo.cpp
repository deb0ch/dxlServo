//
// DxlServo.cpp for DxlServo
//
// Made by chauvo_t
// Login   <chauvo_t@epitech.net>
//
// Started on  Sun Dec  6 00:16:48 2015 chauvo_t
// Last update Tue Jan 12 15:41:03 2016 chauvo_t
//

#include <iostream>

#include "dynamixel.h"

#include "DxlServo.hh"
#include "DxlException.hh"

extern unsigned char           gbStatusPacket[MAXNUM_RXPARAM + 10];

bool	DxlServo::_serialDevInitialized = false;
int	DxlServo::_numInstances = 0;
int	DxlServo::_devNum = 0;
int	DxlServo::_baudrate = 0;
int	DxlServo::_comStatus = 0;

// Todo: terminate in separate static method
// Todo: static method to broadcast a fetchId request and list the connected servos

// Public

bool	DxlServo::devInit(int devNum, int baudrate)
{
  _devNum = devNum;
  _baudrate = baudrate;
  if (!_serialDevInitialized)
  {
    if (::dxl_initialize(_devNum, BAUDRATE_TO_BAUDNUM(_baudrate)) == 0)
      return false;
  }
  _serialDevInitialized = true;
  return true;
}

/*
 * Todo: devClose static member function
 */

std::vector<int>       DxlServo::scanNetwork() // Todo
{
  return std::vector<int>();
}

DxlServo::DxlServo(int id)
  : _id(id),
    _healthy(false)
{
  ++_numInstances;
}

/*
 * Todo: handle ::dxl_terminate errors
 * Todo: see if call to dxl_terminate is more relevant in static method
 */
DxlServo::~DxlServo()
{
  --_numInstances;
  if (_numInstances == 0)
    {
      ::dxl_terminate();
      _serialDevInitialized = false;
      std::cout << "Serial device closed." << std::endl;
    }
}

// Misc

/*
 * Todo: see if still useful
 */
bool	DxlServo::init()
{
  _healthy = false;
  if (!this->ping())
    return false;
  _healthy = true;
  return true;
}

/*
 * Check the existence of that servo
 */
bool	DxlServo::ping()	// Todo: debug. Not sure that dxl_ping() has ever been tested.
{
  return true;

  // dxl_ping(_id);
  // if (dxl_get_result() == COMM_RXSUCCESS)
  //   return true;
  // return false;
}

int	DxlServo::id() const
{
  return _id;
}

// EEPROM

int	DxlServo::modelNumber()
{
  int	val;

  val = ::dxl_read_byte(_id, DxlServo::MODEL_NUMBER_L);
  _comStatus = ::dxl_get_result();
  return val;
}

int	DxlServo::firmwareVersion()
{
  int	val;

  val = ::dxl_read_byte(_id, DxlServo::FIRMWARE_VERSION);
  _comStatus = ::dxl_get_result();
  return val;
}

int	DxlServo::fetchId()	// Todo: see if that method is really necessary
{
  int	val;

  val = ::dxl_read_byte(_id, DxlServo::ID);
  _comStatus = ::dxl_get_result();
  return val;
}

int	DxlServo::baudRate()
{
  int	val;

  val = ::dxl_read_byte(_id, DxlServo::BAUDRATE);
  _comStatus = ::dxl_get_result();
  return val;
}

int	DxlServo::returnDelay()
{
  int	val;

  val = ::dxl_read_byte(_id, DxlServo::RETURN_DELAY);
  _comStatus = ::dxl_get_result();
  return val;
}

int	DxlServo::CWAngleLimit()
{
  int	val;

  val = ::dxl_read_word(_id, DxlServo::CW_ANGLE_LIMIT_L);
  _comStatus = ::dxl_get_result();
  return val;
}

int	DxlServo::CCWAngleLimit()
{
  int	val;

  val = ::dxl_read_word(_id, DxlServo::CCW_ANGLE_LIMIT_L);
  _comStatus = ::dxl_get_result();
  return val;
}

int	DxlServo::getLimitTemp()
{
  int	val;

  val = ::dxl_read_byte(_id, DxlServo::TEMP_LIMIT_HIGH);
  _comStatus = ::dxl_get_result();
  return val;
}

int	DxlServo::lowLimitVoltage()
{
  int	val;

  val = ::dxl_read_byte(_id, DxlServo::VOLT_LIMIT_LOW);
  _comStatus = ::dxl_get_result();
  return val;
}

int	DxlServo::highLimitVoltage()
{
  int	val;

  val = ::dxl_read_byte(_id, DxlServo::VOLT_LIMIT_HIGH);
  _comStatus = ::dxl_get_result();
  return val;
}

/*
 * See setMaxTorque.
 */
float	DxlServo::maxTorque()
{
  int	val;

  val = ::dxl_read_word(_id, DxlServo::MAX_TORQUE_L);
  _comStatus = ::dxl_get_result();
  return (float)val / (float)DxlServo::TORQUE_MAX;
}

int	DxlServo::statusReturnLevel()
{
  int	val;

  val = ::dxl_read_byte(_id, DxlServo::STATUS_RET_LEVEL);
  _comStatus = ::dxl_get_result();
  return val;
}

int	DxlServo::getAlarmLed()
{
  int	val;

  val = ::dxl_read_byte(_id, DxlServo::ALARM_LED);
  _comStatus = ::dxl_get_result();
  return val;
}

int	DxlServo::getAlarmShutdown()
{
  int	val;

  val = ::dxl_read_byte(_id, DxlServo::ALARM_SHUTDOWN);
  _comStatus = ::dxl_get_result();
  return val;
}

/*
 * It is a unique number to identify Dynamixel.
 *
 * Range: from 0 to 252 (0xFC) can be used.
 *        254(0xFE) is used as the Broadcast ID.
 *
 * If the Broadcast ID is used to transmit Instruction Packet, we can
 * command to all Dynamixels.
 *
 * NB: when id of wxl servo is changed, you might have to unplug / replug
 *     it to make it work.
 *
 * Todo: check if id is not already used.
 */
bool	DxlServo::setId(unsigned char n)
{
  bool err;

  ::dxl_write_byte(_id, DxlServo::ID, n);
  _comStatus = ::dxl_get_result();
  err = this->error();
  if (!err)
    _id = n;
  return !err;
}

/*
 * It represents the communication speed, or baudrate.
 *
 * Range: from 7843 to 1000000 bps.
 *
 * Internally, the dxl servo uses one single byte to store the
 * baudrate. Therefore the actual data being sent to the servo
 * is a converted number according to the below formula:
 * baudrate (bps)  = 2000000 / (Data + 1)
 * or:
 * Data = (2000000 / baudrate) - 1
 *
 * Todo: test baudrate conversion
 */
bool	DxlServo::setBaudRate(int baudrate)
{
  int	baudnum = BAUDRATE_TO_BAUDNUM(baudrate);

  if (baudnum < 0)
    baudnum = 0;
  if (baudnum > 254)
    baudnum = 254;
  ::dxl_write_byte(_id, DxlServo::BAUDRATE, baudnum);
  _comStatus = ::dxl_get_result();
  return !this->error();
}

/*
 * It is the delay time per data value that takes from the transmission
 * of Instruction Packet until the return of Status Packet.
 *
 * Range: 0 to 254 (0xFE) can be used.
 *
 * The delay time per data value is 2 usec. That is to say, if the data
 * value is 10, 20 usec is delayed. The initial value is 250 (0xFA) (i.e.,
 * 0.5 msec).
 */
bool	DxlServo::setReturnDelayTime(int n)
{
  if (n < 0)
    n = 0;
  if (n > 254)
    n = 254;
  ::dxl_write_byte(_id, DxlServo::RETURN_DELAY, n);
  _comStatus = ::dxl_get_result();
  return !this->error();
}

/*
 * The angle limit allows the motion to be restrained.
 * The range and the unit of the value is the same as Goal Position:
 *     - CW Angle Limit: the minimum value of Goal Position (which is 0)
 *     - CCW Angle Limit: the maximum value of Goal Position (which is 1)
 * The following two modes can be set pursuant to the value of CW and CCW:
 *
 *	-------------------------------------------------
 *	|	Operation Type	|	CW / CCW	|
 *	|-----------------------------------------------|
 *	|	Wheel Mode	|	both are 0	|
 *	|-----------------------------------------------|
 *	|	Joint Mode	|	neither at 0	|
 *	-------------------------------------------------
 *
 * The wheel mode can be used to wheel-type operation robots since motors of
 * the robots spin infinitely.
 *
 * The joint mode can be used to multi-joints robot since the robots can be
 * controlled with specific angles.
 */
bool	DxlServo::setCWAngleLimit(float v)
{
  int angle;

  if (v < 0)
    v = 0;
  if (v > 1)
    v = 1;
  angle = v * DxlServo::ANGLE_MAX;
  ::dxl_write_word(_id, DxlServo::CW_ANGLE_LIMIT_L, angle);
  _comStatus = ::dxl_get_result();
  return !this->error();
}

/*
 * Cf. setCWAngleLimit
 */
bool	DxlServo::setCCWAngleLimit(float v)
{
  int angle;

  if (v < 0)
    v = 0;
  if (v > 1)
    v = 1;
  angle = v * DxlServo::ANGLE_MAX;
  ::dxl_write_word(_id, DxlServo::CCW_ANGLE_LIMIT_L, angle);
  _comStatus = ::dxl_get_result();
  return !this->error();
}

/*
 * Range: 0 to 255 (Range of a single unsigned byte)
 *
 * Caution : Do not set the temperature lower/higher than the default value.
 * -------   When the temperature alarm shutdown occurs, wait 20 minutes to
 *           cool the temperature before re-use. Using the product when the
 *           temperature is high may and can cause damage.
 */
bool	DxlServo::setLimitTemp(unsigned char n)
{
  ::dxl_write_byte(_id, DxlServo::TEMP_LIMIT_HIGH, n);
  _comStatus = ::dxl_get_result();
  return !this->error();
}

/*
 * Todo: params check
 */
bool	DxlServo::setLowLimitVoltage(int n)
{
  ::dxl_write_byte(_id, DxlServo::VOLT_LIMIT_LOW, n);
  _comStatus = ::dxl_get_result();
  return !this->error();
}

/*
 * Todo: params check
 */
bool	DxlServo::setHighLimitVoltage(int n)
{
  ::dxl_write_byte(_id, DxlServo::VOLT_LIMIT_HIGH, n);
  _comStatus = ::dxl_get_result();
  return !this->error();
}

/*
 * It is the torque value of maximum output.
 *
 * Range: 0 to 1 can be used, as a proportion of maximum torque.
 *
 * The precision (resolution of the command) is about 0.1%.
 * For example, 1 means that Dynamixel will use 100% of the maximum torque
 * it can produce while 0.5 means that Dynamixel will use 50% of the maximum
 * torque. When the power is turned on, torqueLimit and setTorqueLimit
 * use this value as the initial value.
 */
bool	DxlServo::setMaxTorque(float v)
{
  int	torque;

  if (v < 0)
    v = 0;
  if (v > 1)
    v = 1;
  torque = v * DxlServo::TORQUE_MAX;
  ::dxl_write_word(_id, DxlServo::MAX_TORQUE_L, torque);
  _comStatus = ::dxl_get_result();
  return !this->error();
}

/*
 * It decides how to return Status Packet.
 *
 * There are three ways like the below table:
 *
 *	---------------------------------------------------------------------------------
 *	|	Value	|	Return of Status Packet					|
 *	|-------------------------------------------------------------------------------|
 *	|	0	|	No return against all commands (Except PING Command)	|
 *	|-------------------------------------------------------------------------------|
 *	|	1	|	Return only for the READ command			|
 *	|-------------------------------------------------------------------------------|
 *	|	2	|	Return for all commands					|
 *	---------------------------------------------------------------------------------
 *
 * When Instruction Packet is Broadcast ID, Status Packet is not returned regardless of
 * Status Return Level.
 *
 * Todo: params check
 */
bool	DxlServo::setStatusReturnLevel(int n)
{
  if (n < 0)
    n = 0;
  if (n > 2)
    n = 2;
  ::dxl_write_byte(_id, DxlServo::STATUS_RET_LEVEL, n);
  _comStatus = ::dxl_get_result();
  return !this->error();
}

bool	DxlServo::setAlarmLed(bool v)
{
  ::dxl_write_byte(_id, DxlServo::ALARM_LED, v == true);
  _comStatus = ::dxl_get_result();
  return !this->error();
}

bool	DxlServo::setAlarmShutdown(bool v)
{
  ::dxl_write_byte(_id, DxlServo::ALARM_SHUTDOWN, v == true);
  _comStatus = ::dxl_get_result();
  return !this->error();
}

/////////////////////////////////////////////////////////
//
// RAM
//
/////////////////////////////////////////////////////////

bool	DxlServo::torqueEnabled()
{
  bool	val;

  val = ::dxl_read_byte(_id, DxlServo::TORQUE_ENABLE);
  _comStatus = ::dxl_get_result();
  return val;
}

bool	DxlServo::getLed()
{
  bool	val;

  val = ::dxl_read_byte(_id, DxlServo::LED_ON_OFF);
  _comStatus = ::dxl_get_result();
  return val;
}

/*
 * See http://support.robotis.com/en/product/dynamixel/ax_series/dxl_ax_actuator.htm#Actuator_Address_1A
 */
int	DxlServo::CWComplianceMargin()
{
  int	val;

  val = ::dxl_read_byte(_id, DxlServo::CW_COMPLIANCE_MARGIN);
  _comStatus = ::dxl_get_result();
  return val;
}

/*
 * See http://support.robotis.com/en/product/dynamixel/ax_series/dxl_ax_actuator.htm#Actuator_Address_1A
 */
int	DxlServo::CCWComplianceMargin()
{
  int	val;

  val = ::dxl_read_byte(_id, DxlServo::CCW_COMPLIANCE_MARGIN);
  _comStatus = ::dxl_get_result();
  return val;
}

/*
 * See http://support.robotis.com/en/product/dynamixel/ax_series/dxl_ax_actuator.htm#Actuator_Address_1A
 */
int	DxlServo::CWComplianceSlope()
{
  int	val;

  val = ::dxl_read_byte(_id, DxlServo::CW_COMPLIANCE_SLOPE);
  _comStatus = ::dxl_get_result();
  return val;
}

/*
 * See http://support.robotis.com/en/product/dynamixel/ax_series/dxl_ax_actuator.htm#Actuator_Address_1A
 */
int	DxlServo::CCWComplianceSlope()
{
  int	val;

  val = ::dxl_read_byte(_id, DxlServo::CCW_COMPLIANCE_SLOPE);
  _comStatus = ::dxl_get_result();
  return val;
}

/*
 * Cf. setGoalPos.
 */
float	DxlServo::goalPos()	// Todo: test if division returns floating point number
{
  int	val;

  val = ::dxl_read_word(_id, DxlServo::GOAL_POS_L);
  _comStatus = ::dxl_get_result();
  return (float)val / (float)DxlServo::ANGLE_MAX;
}

/*
 * Cf. setMovingSpeed.
 */
float	DxlServo::movingSpeed()	// Todo: test if division returns floating point number
{
  int	val;

  val = ::dxl_read_word(_id, DxlServo::MOVING_SPEED_L);
  if (val & 1024)
    {
      val = val & ~1024;
      val = -val;
    }
  _comStatus = ::dxl_get_result();
  return (float)val / (float)DxlServo::SPEED_MAX;
}

/*
 * See setTorqueLimit.
 */
float	DxlServo::torqueLimit()
{
  int	val;

  val = ::dxl_read_word(_id, DxlServo::TORQUE_LIMIT_L);
  _comStatus = ::dxl_get_result();
  return (float)val / (float)DxlServo::TORQUE_MAX;
}

/*
 * Cf. setGoalPos.
 */
float	DxlServo::presentPos()	// Todo: test if division returns floating point number
{
  float	val;

  val = ::dxl_read_word(_id, DxlServo::PRESENT_POS_L);
  _comStatus = ::dxl_get_result();
  return val / (float)DxlServo::ANGLE_MAX;
}

/*
 * Cf. setMovingSpeed.
 */
float	DxlServo::presentSpeed()	// Todo: test if division returns floating point number
{
  int	val;

  val = ::dxl_read_word(_id, DxlServo::PRESENT_SPEED_L);
  val &= 0x7FF; // clear irrelevant bits. value should be below 2047.
  if (val & 1024)
    {
      val = val & ~1024;
      val = -val;
    }
  _comStatus = ::dxl_get_result();
  return (float)val / (float)DxlServo::SPEED_MAX;
}

/*
 * See setTorqueLimit or setMaxTorque.
 *
 * Notes: Current load is inferred from the internal torque value, not
 *        from Torque sensor etc. For that reason, it cannot be used to
 *        measure weight or torque; however, it must be used only to
 *        detect which direction the force works.
 */
float	DxlServo::presentLoad()
{
  int	val;

  val = ::dxl_read_word(_id, DxlServo::PRESENT_LOAD_L);
  if (val & 1024)
    {
      val = val & ~1024;
      val = -val;
    }
  _comStatus = ::dxl_get_result();
  return (float)val / (float)DxlServo::TORQUE_MAX;
}

/*
 * It is the size of the current voltage supplied.
 *
 * This value is 10 times larger than the actual voltage. For example,
 * when 10V is supplied, the data value is 100 (0x64)
 */
int	DxlServo::presentVoltage()
{
  int	val;

  val = ::dxl_read_byte(_id, DxlServo::PRESENT_VOLT);
  _comStatus = ::dxl_get_result();
  return val;
}

int	DxlServo::presentTemp()
{
  int	val;

  val = ::dxl_read_byte(_id, DxlServo::PRESENT_TEMP);
  _comStatus = ::dxl_get_result();
  return val;
}

bool	DxlServo::instructionRegistered()
{
  bool	val;

  val = ::dxl_read_byte(_id, DxlServo::INSTRUCTION_REGISTERED);
  _comStatus = ::dxl_get_result();
  return val;
}

bool	DxlServo::moving()
{
  bool	val;

  val = ::dxl_read_byte(_id, DxlServo::MOVING) == 1;
  _comStatus = ::dxl_get_result();
  return val;
}

bool	DxlServo::EEPROMLocked()
{
  bool	val;

  val = ::dxl_read_byte(_id, DxlServo::LOCK);
  _comStatus = ::dxl_get_result();
  return val;
}

/*
 * See http://support.robotis.com/en/product/dynamixel/ax_series/dxl_ax_actuator.htm#Actuator_Address_1A
 */
int	DxlServo::punch()
{
  int	val;

  val = ::dxl_read_word(_id, DxlServo::PUNCH_L);
  _comStatus = ::dxl_get_result();
  return val;
}


bool	DxlServo::enableTorque(bool v)
{
  ::dxl_write_byte(_id, DxlServo::TORQUE_ENABLE, v == true);
  _comStatus = ::dxl_get_result();
  return !this->error();
}

bool	DxlServo::setLed(bool v)
{
  ::dxl_write_byte(_id, DxlServo::LED_ON_OFF, v == true);
  _comStatus = ::dxl_get_result();
  return !this->error();
}

/*
 * See http://support.robotis.com/en/product/dynamixel/ax_series/dxl_ax_actuator.htm#Actuator_Address_1A
 */
bool	DxlServo::setCWComplianceMargin(int n)
{
  ::dxl_write_byte(_id, DxlServo::CW_COMPLIANCE_MARGIN, n);
  _comStatus = ::dxl_get_result();
  return !this->error();
}

/*
 * See http://support.robotis.com/en/product/dynamixel/ax_series/dxl_ax_actuator.htm#Actuator_Address_1A
 */
bool	DxlServo::setCCWComplianceMargin(int n)
{
  ::dxl_write_byte(_id, DxlServo::CCW_COMPLIANCE_MARGIN, n);
  _comStatus = ::dxl_get_result();
  return !this->error();
}

/*
 * See http://support.robotis.com/en/product/dynamixel/ax_series/dxl_ax_actuator.htm#Actuator_Address_1A
 */
bool	DxlServo::setCWComplianceSlope(int n)
{
  ::dxl_write_byte(_id, DxlServo::CW_COMPLIANCE_SLOPE, n);
  _comStatus = ::dxl_get_result();
  return !this->error();
}

/*
 * See http://support.robotis.com/en/product/dynamixel/ax_series/dxl_ax_actuator.htm#Actuator_Address_1A
 */
bool	DxlServo::setCCWComplianceSlope(int n)
{
  ::dxl_write_byte(_id, DxlServo::CCW_COMPLIANCE_SLOPE, n);
  _comStatus = ::dxl_get_result();
  return !this->error();
}

/*
 * Position value of destination.
 *
 * Range: 0 to 1 is available, as a proportion of the max angle which is 300°.
 *
 * 0 will therefore be 0° and 1 is 300°, midpoint being at 0.5.
 * The resolution (precision) of the command is 0.29 degree.
 */
bool	DxlServo::setGoalPos(float v)
{
  int	angle;

  if (v < 0)
    v = 0;
  if (v > 1)
    v = 1;
  angle = v * DxlServo::ANGLE_MAX;
  ::dxl_write_word(_id, DxlServo::GOAL_POS_L, angle);
  _comStatus = ::dxl_get_result();
  return !this->error();
}

/*
 * It is a moving speed to Goal Position.
 *
 * Range: The range and the unit of the value may vary depending on the operation mode.
 *
 * Join Mode (CW and CCW limits != 0):
 *	0 to 1 can be used as a proportion of maximum rpm, with a precision (resolution)
 *	of about 0.111rpm. If it is 1, it is about 114rpm.
 *
 * Notes: Please check the maximum rpm of relevant model in Joint Mode. Even if
 *        the motor is set to more than maximum rpm, it cannot generate the
 *        torque more than the maximum rpm.
 *
 * Wheel Mode (CW and CCW limits are set to 0):
 *	-1 to 1 can be used. Negative values are for CCW, positive for CW rotation.
 *	The precision is about 0.1%.
 */
bool	DxlServo::setMovingSpeed(float v) // Todo: test
{
  int	angle = 0;

  if (v < -1)
    v = -1;
  if (v > 1)
    v = 1;
  if (v < 0)
    {
      angle = 1024;			// Set direction bit
      v = -v;
    }
  angle |= (int)(v * DxlServo::SPEED_MAX);	// Add value bits. Here, 0 < value < 1024
  ::dxl_write_word(_id, DxlServo::MOVING_SPEED_L, angle);
  _comStatus = ::dxl_get_result();
  return !this->error();
}

/*
 * It is the value of the maximum torque limit.
 *
 * Range: 0 to 1 is available, as a proportion of maximum torque.
 *
 * The precision (resolution of the command) is about 0.1%.
 * For example, if the value is 512, it is about 50%; that means only 50% of the
 * maximum torque will be used.
 * If the power is turned on, the value of Max Torque (Address 14, 15) is used
 * as the initial value.
 *
 * Notes: If the function of Alarm Shutdown is triggered, the motor loses its
 *        torque because the value becomes 0.  At this moment, if the value is
 *        changed to the value other than 0, the motor can be used again.
 */
bool	DxlServo::setTorqueLimit(float v)
{
  int	torque;

  if (v < 0)
    v = 0;
  if (v > 1)
    v = 1;
  torque = v * DxlServo::TORQUE_MAX;
  ::dxl_write_word(_id, DxlServo::TORQUE_LIMIT_L, torque);
  _comStatus = ::dxl_get_result();
  return !this->error();
}

bool	DxlServo::lockEEPROM()
{
  ::dxl_write_byte(_id, DxlServo::LOCK, true);
  _comStatus = ::dxl_get_result();
  return !this->error();
}

bool	DxlServo::unlockEEPROM()
{
  ::dxl_write_byte(_id, DxlServo::LOCK, false);
  _comStatus = ::dxl_get_result();
  return !this->error();
}

/*
 * See http://support.robotis.com/en/product/dynamixel/ax_series/dxl_ax_actuator.htm#Actuator_Address_1A
 */
int	DxlServo::setPunch(int n)
{
  ::dxl_write_word(_id, DxlServo::PUNCH_L, n);
  _comStatus = ::dxl_get_result();
  return !this->error();
}

// Error handling

/*
 * Check if an error occured
 */
bool	DxlServo::error()
{
  return (this->comError() || this->servoError());
}

bool	DxlServo::comError() const
{
  return _comStatus == COMM_RXSUCCESS;
}

/*
 * COMM_TXFAIL: Failed transmit instruction packet
 */
bool	DxlServo::errorComFailTx() const
{
  return _comStatus == COMM_TXFAIL;
}

/*
 * COMM_TXERROR: Incorrect instruction packet
 */
bool	DxlServo::errorComInval() const
{
  return _comStatus == COMM_TXERROR;
}

/*
 * COMM_RXFAIL: Failed get status packet from device
 */
bool	DxlServo::errorComFailRx() const
{
  return _comStatus == COMM_RXFAIL;
}

/*
 * COMM_RXWAITING: Now recieving status packet
 */
bool	DxlServo::errorComWaiting() const
{
  return _comStatus == COMM_RXWAITING;
}

/*
 * COMM_RXTIMEOUT: There is no status packet
 */
bool	DxlServo::errorComTimeout() const
{
  return _comStatus == COMM_RXTIMEOUT;
}

/*
 * COMM_RXCORRUPT: Incorrect status packet
 */
bool	DxlServo::errorComCorrupt() const
{
  return _comStatus == COMM_RXCORRUPT;
}

bool	DxlServo::servoError()
{
  return this->errorVoltage()
    || this->errorAngle()
    || this->errorOverheat()
    || this->errorRange()
    || this->errorChecksum()
    || this->errorOverload()
    || this->errorInstruction();
}

/*
 * Returns entire servoError status byte, containing all other servo errors.
 */
unsigned char	DxlServo::getServoError()
{
  return gbStatusPacket[4];
}

/*
 * Input voltage error
 */
bool	DxlServo::errorVoltage()
{
  if (dxl_get_rxpacket_error(ERRBIT_VOLTAGE))
    return true;
  return false;
}

/*
 * Angle limit error
 */
bool	DxlServo::errorAngle()
{
  if (::dxl_get_rxpacket_error(ERRBIT_ANGLE))
    return true;
  return false;
}

/*
 * Overheat error
 */
bool	DxlServo::errorOverheat()
{
  if (::dxl_get_rxpacket_error(ERRBIT_OVERHEAT))
    throw DxlException("overheating");
  return false;
}

/*
 * Out of range error
 */
bool	DxlServo::errorRange()
{
  if (::dxl_get_rxpacket_error(ERRBIT_RANGE))
    return true;
  return false;
}

/*
 * Checksum error
 */
bool	DxlServo::errorChecksum()
{
  if (::dxl_get_rxpacket_error(ERRBIT_CHECKSUM))
    return true;
  return false;
}

/*
 * Overload error
 */
bool	DxlServo::errorOverload()
{
  if (::dxl_get_rxpacket_error(ERRBIT_OVERLOAD))
    return true;
  return false;
}

/*
 * Instruction code error
 */
bool	DxlServo::errorInstruction()
{
  if (::dxl_get_rxpacket_error(ERRBIT_INSTRUCTION))
    return true;
  return false;
}
