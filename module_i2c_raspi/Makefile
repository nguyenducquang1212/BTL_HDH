KDIR = /lib/modules/`uname -r`/build
#KDIR=/usr/src/kernel/ # FPGA
all:
	make -C $(KDIR) M=`pwd`
 
clean:
	make -C $(KDIR) M=`pwd` clean
