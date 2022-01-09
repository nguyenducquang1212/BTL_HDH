cmd_/home/pi/i2c_ds1307/modules.order := {   echo /home/pi/i2c_ds1307/ds1307.ko;   echo /home/pi/i2c_ds1307/ssh1106.ko; :; } | awk '!x[$$0]++' - > /home/pi/i2c_ds1307/modules.order
