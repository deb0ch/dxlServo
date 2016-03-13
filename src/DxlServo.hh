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

#ifndef DXLSERVO_H_
# define DXLSERVO_H_

# include <vector>

class DxlServo
{
public:
  static bool			devInit(int devNum, int baudrate = 1000000);
  static std::vector<int>	scanNetwork();

  DxlServo(int id);
  ~DxlServo();

  // Misc
  bool	init();
  bool	ping();
  int	id() const;

  // EEPROM
  int	modelNumber();
  int	firmwareVersion();
  int	fetchId();
  int	baudRate();
  int	returnDelay();
  int	CWAngleLimit();
  int	CCWAngleLimit();
  int	getLimitTemp();
  int	lowLimitVoltage();
  int	highLimitVoltage();
  float	maxTorque();
  int	statusReturnLevel();
  int	getAlarmLed();
  int	getAlarmShutdown();

  bool	setId(unsigned char newId);
  bool	setBaudRate(int n);
  bool	setReturnDelayTime(int n);
  bool	setCWAngleLimit(float v);
  bool	setCCWAngleLimit(float v);
  bool	setLimitTemp(unsigned char n);
  bool	setLowLimitVoltage(int n);
  bool	setHighLimitVoltage(int n);
  bool	setMaxTorque(float n);
  bool	setStatusReturnLevel(int n);
  bool	setAlarmLed(bool v);
  bool	setAlarmShutdown(bool v);

  // RAM
  bool	torqueEnabled();
  bool	getLed();
  int	CWComplianceMargin();
  int	CCWComplianceMargin();
  int	CWComplianceSlope();
  int	CCWComplianceSlope();
  float	goalPos();
  float	movingSpeed();
  float	torqueLimit();
  float	presentPos();
  float	presentSpeed();
  float	presentLoad();
  int	presentVoltage();
  int	presentTemp();
  bool	instructionRegistered();
  bool	moving();
  bool	EEPROMLocked();
  int	punch();

  bool	enableTorque(bool v);
  bool	setLed(bool v);
  bool	setCWComplianceMargin(int n);
  bool	setCCWComplianceMargin(int n);
  bool	setCWComplianceSlope(int n);
  bool	setCCWComplianceSlope(int n);
  bool	setGoalPos(float v);
  bool	setMovingSpeed(float v);
  bool	setTorqueLimit(float v);
  bool	lockEEPROM();
  bool	unlockEEPROM();
  int	setPunch(int n);

  // Error handling
  bool	error();

  bool	comError() const;

  int	getComError() const;
  bool	errorComFailTx() const;
  bool	errorComInval() const;
  bool	errorComFailRx() const;
  bool	errorComWaiting() const;
  bool	errorComTimeout() const;
  bool	errorComCorrupt() const;

  bool		servoError();

  unsigned char	getServoError();
  bool		errorVoltage();
  bool		errorAngle();
  bool		errorOverheat();
  bool		errorRange();
  bool		errorChecksum();
  bool		errorOverload();
  bool		errorInstruction();

public:
  static const int ID_BROADCAST = 254;
  static const int ID_MAX = 252;
  static const int ANGLE_MAX = 1023;
  static const int SPEED_MAX = 1023;
  static const int TORQUE_MAX = 1023;

  enum dxlAddress
    {
					// Address	Name				Description						Access	Default value

      // EEPROM
      MODEL_NUMBER_L		= 0,	// (0X00)	Model Number(L)			Lowest byte of model number				R	12 (0X0C)
      MODEL_NUMBER_H		= 1,	// (0X01)	Model Number(H)			Highest byte of model number				R	0 (0X00)
      FIRMWARE_VERSION		= 2,	// (0X02)	Version of Firmware		Information on the version of firmware			R	-
      ID			= 3,	// (0X03)	ID				ID of Dynamixel, from 0 to 252, broadcast id = 254	RW	1 (0X01)
      BAUDRATE			= 4,	// (0X04)	Baud Rate			Baud Rate of Dynamixel					RW	1 (0X01)
      RETURN_DELAY		= 5,	// (0X05)	Return Delay Time		Return Delay Time					RW	250 (0XFA)
      CW_ANGLE_LIMIT_L		= 6,	// (0X06)	CW Angle Limit(L)		Lowest byte of clockwise Angle Limit			RW	0 (0X00)
      CW_ANGLE_LIMIT_H		= 7,	// (0X07)	CW Angle Limit(H)		Highest byte of clockwise Angle Limit			RW	0 (0X00)
      CCW_ANGLE_LIMIT_L		= 8,	// (0X08)	CCW Angle Limit(L)		Lowest byte of counterclockwise Angle Limit		RW	255 (0XFF)
      CCW_ANGLE_LIMIT_H		= 9,	// (0X09)	CCW Angle Limit(H)		Highest byte of counterclockwise Angle Limit		RW	3 (0X03)
      TEMP_LIMIT_HIGH		= 11,	// (0X0B)	the Highest Limit Temperature	Internal Limit Temperature				RW	70 (0X46)
      VOLT_LIMIT_LOW		= 12,	// (0X0C)	the Lowest Limit Voltage	Lowest Limit Voltage					RW	60 (0X3C)
      VOLT_LIMIT_HIGH		= 13,	// (0X0D)	the Highest Limit Voltage	Highest Limit Voltage					RW	140 (0XBE)
      MAX_TORQUE_L		= 14,	// (0X0E)	Max Torque(L)			Lowest byte of Max. Torque				RW	255 (0XFF)
      MAX_TORQUE_H		= 15,	// (0X0F)	Max Torque(H)			Highest byte of Max. Torque				RW	3 (0X03)
      STATUS_RET_LEVEL		= 16,	// (0X10)	Status Return Level		Status Return Level					RW	2 (0X02)
      ALARM_LED			= 17,	// (0X11)	Alarm LED			LED for Alarm						RW	36(0x24)
      ALARM_SHUTDOWN		= 18,	// (0X12)	Alarm Shutdown			Shutdown for Alarm					RW	36(0x24)

      // RAM
      TORQUE_ENABLE		= 24,	// (0X18)	Torque Enable			Torque On/Off						RW	0 (0X00)
      LED_ON_OFF		= 25,	// (0X19)	LED				LED On/Off						RW	0 (0X00)
      CW_COMPLIANCE_MARGIN	= 26,	// (0X1A)	CW Compliance Margin		CW Compliance margin					RW	1 (0X01)
      CCW_COMPLIANCE_MARGIN	= 27,	// (0X1B)	CCW Compliance Margin		CCW Compliance margin					RW	1 (0X01)
      CW_COMPLIANCE_SLOPE	= 28,	// (0X1C)	CW Compliance Slope		CW Compliance slope					RW	32 (0X20)
      CCW_COMPLIANCE_SLOPE	= 29,	// (0X1D)	CCW Compliance Slope		CCW Compliance slope					RW	32 (0X20)
      GOAL_POS_L		= 30,	// (0X1E)	Goal Position(L)		Lowest byte of Goal Position				RW	-
      GOAL_POS_H		= 31,	// (0X1F)	Goal Position(H)		Highest byte of Goal Position				RW	-
      MOVING_SPEED_L		= 32,	// (0X20)	Moving Speed(L)			Lowest byte of Moving Speed (Moving Velocity)		RW	-
      MOVING_SPEED_H		= 33,	// (0X21)	Moving Speed(H)			Highest byte of Moving Speed (Moving Velocity)		RW	-
      TORQUE_LIMIT_L		= 34,	// (0X22)	Torque Limit(L)			Lowest byte of Torque Limit (Goal Torque)		RW	ADD14
      TORQUE_LIMIT_H		= 35,	// (0X23)	Torque Limit(H)			Highest byte of Torque Limit (Goal Torque)		RW	ADD15
      PRESENT_POS_L		= 36,	// (0X24)	Present Position(L)		Lowest byte of Current Position (Present Velocity)	R	-
      PRESENT_POS_H		= 37,	// (0X25)	Present Position(H)		Highest byte of Current Position (Present Velocity)	R	-
      PRESENT_SPEED_L		= 38,	// (0X26)	Present Speed(L)		Lowest byte of Current Speed				R	-
      PRESENT_SPEED_H		= 39,	// (0X27)	Present Speed(H)		Highest byte of Current Speed				R	-
      PRESENT_LOAD_L		= 40,	// (0X28)	Present Load(L)			Lowest byte of Current Load				R	-
      PRESENT_LOAD_H		= 41,	// (0X29)	Present Load(H)			Highest byte of Current Load				R	-
      PRESENT_VOLT		= 42,	// (0X2A)	Present Voltage			Current Voltage						R	-
      PRESENT_TEMP		= 43,	// (0X2B)	Present Temperature		Current Temperature					R	-
      INSTRUCTION_REGISTERED	= 44,	// (0X2C)	Registered			Means if Instruction is registered			R	0 (0X00)
      MOVING			= 46,	// (0X2E)	Moving				Means if there is any movement				R	0 (0X00)
      LOCK			= 47,	// (0X2F)	Lock				Locking EEPROM						RW	0 (0X00)
      PUNCH_L			= 48,	// (0X30)	Punch(L)			Lowest byte of Punch					RW	32 (0X20)
      PUNCH_H			= 49	// (0X31)	Punch(H)			Highest byte of Punch					RW	0 (0X00)
    };

/*
 * b = 2000000 / (n + 1)
 * b * (n + 1) = 2000000
 * n = (2000000 / b) - 1
 */
# define BAUDNUM_TO_BAUDRATE(n) (2000000 / (n + 1))
# define BAUDRATE_TO_BAUDNUM(b) (2000000 / (b ? b : 1)) - 1

private:
  DxlServo();
  DxlServo(const DxlServo &);
  DxlServo &operator=(const DxlServo &);

private:
  static bool	_serialDevInitialized;
  static int	_numInstances;
  static int	_devNum;
  static int	_baudrate;
  static int	_comStatus;
  unsigned char	_id;
  bool		_healthy;
};

#endif /* !DXLSERVO_H_ */
