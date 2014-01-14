obj-m := hello-1.o
obj-m := hello-2.o
obj-m := hello-3.o
obj-m := hello-4.o
obj-m := hello-5.o

KDIR := /lib/modules/$(shell uname -r)/build
PWD := $(shell pwd)

all:
	$(MAKE) -C $(KDIR) M=$(PWD) modules

clean:
	$(MAKE) -C $(KDIR) M=$(PWD)  clean
