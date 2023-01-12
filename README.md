# Introduction
This a quick way to learn Linux kernel development by writing a simple dummy driver. I am using Ubuntu 17.04 here, but any recent Ubuntu 
should work. Prerequisites:
- make
- gcc

The overall idea is that the driver returns some data when you try to read from it using the `dd` command. In order for the driver to be 
visible from the user, we also have to create character device file using the `mknod` command using the generated *major number* when you
load the driver into the kernel. 

## I) Build
```
make
```
This will produce `testdriver.ko` driver.

## II) Load
To test, open two terminals. In the first terminal to watch the driver's assigned major number:
```
sudo dmesg -w
```

In the second terminal, load the driver and create a character device file:
```
sudo insmod testdriver.ko 
sudo mknod /dev/johnny c 245 0 # this assumes that 245 is the major number shown in first terminal
```

## III) Test
Read data from the driver using the `dd` command:
```
dd if=/dev/johnny bs=13 count=3
```

You should receive the read data from the driver printed into the console. You will also see log messages in
the first terminal.
