obj-m += testdriver.o
KDIR = /lib/modules/$(shell uname -r)/build

all:
	$(MAKE) -C $(KDIR) M=$(PWD) modules

clean:
	rm -rf *.o *.ko *.mod *.mod.c *.order *.symvers .tmp_* .testdriver.*
