obj-m += testdriver.o
KDIR = /lib/modules/$(shell uname -r)/build

all:
	$(MAKE) -C $(KDIR) M=$(PWD) modules

bdf:
	@if [ -x "$(shell command -v cpptesttrace)" ]; then \
cpptesttrace --cpptesttraceOutputFile=`pwd`/testdriver.bdf make; \
else \
echo "Please set PATH for Parasoft C/C++test cpptesttrace executable"; \
fi

clean:
	rm -rf *.o *.ko *.mod *.mod.c *.order *.symvers .tmp_* .testdriver.* *.bdf
	git clean -fdx
