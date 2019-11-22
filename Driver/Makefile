obj-m := char_dvr.o


KDIR = /lib/modules/$(shell uname -r)/build

all:
	$(MAKE) -C $(KDIR) M=$(PWD) modules

clean:       
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean

insert:
	insmod char_dvr.ko

device-usable:
	chmod 777 /dev/myCharDevice

remdev:
	rm /dev/myCharDevice

remove:
	rmmod char_dvr
