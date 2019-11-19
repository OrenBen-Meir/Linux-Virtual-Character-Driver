obj-m := char_dvr.o


KDIR = /lib/modules/$(shell uname -r)/build

all:
	$(MAKE) -C $(KDIR) M=$(PWD) modules

clean:       
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean

insert:
	insmod char_dvr.ko

remove:
	rmmod char_dvr