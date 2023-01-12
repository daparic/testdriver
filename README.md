# Introduction
This a quick way to learn Linux kernel development by writing a simple dummy driver. I am using Ubuntu 17.04 here, but any recent Ubuntu 
should work. Prerequisites:
- make
- gcc

## Build
```
make
```
This will produce `testdriver.ko` driver.

## Load
To test, open two terminals. In the first terminal to watch the driver's assigned major number:
```
sudo dmesg -w
```

In the second terminal, load the driver and create a character device file:
```
sudo insmod testdriver.ko 
sudo mknod /dev/johnny c 245 0 # this assumes that 245 is the major number shown in first terminal
```

## Test
Read data from the driver:
```
dd if=/dev/johnny bs=13 count=3
```

You should receive the read data from the driver printed into the console. You will also see log messages in
the first terminal.
