cmd_/home/pi/i2c_ds1307/Module.symvers := sed 's/ko$$/o/' /home/pi/i2c_ds1307/modules.order | scripts/mod/modpost -m -a   -o /home/pi/i2c_ds1307/Module.symvers -e -i Module.symvers   -T -
