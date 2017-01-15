DxlServo is a C++ object/library made for simplifying the use of Dynamixel AX-12a servomotors in C++ projects.  

This library aims at making the use of dynamixel servos more intuitive without loosing any of their wonderful features.  

For instance, instead of sending or requesting bytes to/from specific addresses, each feature and sensor has its own method.  
For giving commands such as speed or position, you can simply use a floating point number between -1 and 1 as a proportion  
of the maximum command, instead of bothering with commands such as "0 to 1023 in one direction and 1024 to 2048 for the  
other, both 0 and 1024 being zero speed".  

For more documentation, please see the comments above each function definition in src/DxlServo.cpp.  

It is released under a MIT licence so you are free to use it on commercial or non-commercial projects, open source or not.  

It works on top of the dxl_sdk provided by Dynamixel and thus should be crossplatform and work on Linux, Windows, usb2ax and  
usb2dynamixel.  

Though currently only usb2ax on Linux has been fully integrated and tested, very little efforts should be needed to make it  
work on other platforms as it just requires to compile it with a different version of the dxl_sdk.  
If you do implement that or have any improvement to share about this library, please send a pull request.  

To do (in random order):  
	- Implement scanning network for dynamixels  
	- test that dxl_terminate(); is called only upon destruction of the last servo instance on that device  
        - Integrate a build system for Windows users  
	- stop using dxl_sdk and implement a new, better and cross-platform one.  
        - Integrate Doxygen or other documentation generator.  
	- handle multiple serial devices (which current dxl_sdk does not handle) (if useful)  
	- Handle sync_read and sync_write (if useful)  

More documentation about the AX-12a:  

http://hackerspace.cs.rutgers.edu/library/Bioloid/doc/AX-12.pdf  
http://support.robotis.com/en/product/dynamixel/ax_series/dxl_ax_actuator.htm  

