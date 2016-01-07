
0  (0X00)	Model Number(L)			Lowest byte of model number				R	12 (0X0C)
1  (0X01)	Model Number(H)			Highest byte of model number				R	0 (0X00)
2  (0X02)	Version of Firmware		Information on the version of firmware			R	-
3  (0X03)	ID				ID of Dynamixel						RW	1 (0X01)
4  (0X04)	Baud Rate			Baud Rate of Dynamixel					RW	1 (0X01)
5  (0X05)	Return Delay Time		Return Delay Time					RW	250 (0XFA)
6  (0X06)	CW Angle Limit(L)		Lowest byte of clockwise Angle Limit			RW	0 (0X00)
7  (0X07)	CW Angle Limit(H)		Highest byte of clockwise Angle Limit			RW	0 (0X00)
8  (0X08)	CCW Angle Limit(L)		Lowest byte of counterclockwise Angle Limit		RW	255 (0XFF)
9  (0X09)	CCW Angle Limit(H)		Highest byte of counterclockwise Angle Limit		RW	3 (0X03)
11 (0X0B)	the Highest Limit Temperature	Internal Limit Temperature				RW	70 (0X46)
12 (0X0C)	the Lowest Limit Voltage	Lowest Limit Voltage					RW	60 (0X3C)
13 (0X0D)	the Highest Limit Voltage	Highest Limit Voltage					RW	140 (0XBE)
14 (0X0E)	Max Torque(L)			Lowest byte of Max. Torque				RW	255 (0XFF)
15 (0X0F)	Max Torque(H)			Highest byte of Max. Torque				RW	3 (0X03)
16 (0X10)	Status Return Level		Status Return Level					RW	2 (0X02)
17 (0X11)	Alarm LED			LED for Alarm						RW	36(0x24)
18 (0X12)	Alarm Shutdown			Shutdown for Alarm					RW	36(0x24)
24 (0X18)	Torque Enable			Torque On/Off						RW	0 (0X00)
25 (0X19)	LED				LED On/Off						RW	0 (0X00)
26 (0X1A)	CW Compliance Margin		CW Compliance margin					RW	1 (0X01)
27 (0X1B)	CCW Compliance Margin		CCW Compliance margin					RW	1 (0X01)
28 (0X1C)	CW Compliance Slope		CW Compliance slope					RW	32 (0X20)
29 (0X1D)	CCW Compliance Slope		CCW Compliance slope					RW	32 (0X20)
30 (0X1E)	Goal Position(L)		Lowest byte of Goal Position				RW	-
31 (0X1F)	Goal Position(H)		Highest byte of Goal Position				RW	-
32 (0X20)	Moving Speed(L)			Lowest byte of Moving Speed (Moving Velocity)		RW	-
33 (0X21)	Moving Speed(H)			Highest byte of Moving Speed (Moving Velocity)		RW	-
34 (0X22)	Torque Limit(L)			Lowest byte of Torque Limit (Goal Torque)		RW	ADD14
35 (0X23)	Torque Limit(H)			Highest byte of Torque Limit (Goal Torque)		RW	ADD15
36 (0X24)	Present Position(L)		Lowest byte of Current Position (Present Velocity)	R	-
37 (0X25)	Present Position(H)		Highest byte of Current Position (Present Velocity)	R	-
38 (0X26)	Present Speed(L)		Lowest byte of Current Speed				R	-
39 (0X27)	Present Speed(H)		Highest byte of Current Speed				R	-
40 (0X28)	Present Load(L)			Lowest byte of Current Load				R	-
41 (0X29)	Present Load(H)			Highest byte of Current Load				R	-
42 (0X2A)	Present Voltage			Current Voltage						R	-
43 (0X2B)	Present Temperature		Current Temperature					R	-
44 (0X2C)	Registered			Means if Instruction is registered			R	0 (0X00)
46 (0X2E)	Moving				Means if there is any movement				R	0 (0X00)
47 (0X2F)	Lock				Locking EEPROM						RW	0 (0X00)
48 (0X30)	Punch(L)			Lowest byte of Punch					RW	32 (0X20)
49 (0X31)	Punch(H)			Highest byte of Punch					RW	0 (0X00)

http://hackerspace.cs.rutgers.edu/library/Bioloid/doc/AX-12.pdf
http://support.robotis.com/en/product/dynamixel/ax_series/dxl_ax_actuator.htm

to do:
	- Params check and conversion:
	  * Check param range for every function. If out of range, bring it back to the
	    closest valid value.
	  * Convert "int 0 to 1023" range style to "float 0 to 1" (power-percentage style)
	    Example:
		for speed, instead of 0 to 1023 for one direction and 1024 to 2047 for the
		other direction, make it be -1 to 1, allowing 0.333 as 1/3 of max speed
	- Set of static methods for initialization / tasks to be done whithout an active instance:
	  * scan network for dynamixels
	  *
	- Initialize serial device only once even on several servo instanciations.
	- Handle sync_read and sync_write
	- test that dxl_terminate(); is called only upon destruction of the last servo
	  instance on that device
	- Create build system for the different versions of the dxl_sdk and integrate it to
	  the project. Leave option for using custom dxl_sdk.
	- stop using dxl_sdk
	- handle multiple serial devices (which current dxl_sdk does not handle)

notes:
	- maybe move serial device init to constructor ? => No, need to handle error cases
