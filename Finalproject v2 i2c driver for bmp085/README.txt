
*Build
------
$ make 
$ sudo make install 
$ sudo depmod -a

*Test:
-------
$ sudo modprobe bmp085 i2c_driver probe 

$ cat /sys/bus/i2c/drivers/bmp085/1-0077/temp0_input
$ cat /sys/bus/i2c/drivers/bmp085/1-0077/pressure0_input
