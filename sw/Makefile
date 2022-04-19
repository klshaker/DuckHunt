ifneq (${KERNELRELEASE},)

# KERNELRELEASE defined: we are being compiled as part of the Kernel
        obj-m := ppu.o 

else

# We are being compiled as a module: use the Kernel build system

	KERNEL_SOURCE := /usr/src/linux-headers-$(shell uname -r)
        PWD := $(shell pwd)

EXTRA_CFLAGS = -I$(src)/game
default: module hello 

hello: game/game.o sprites.o

module: 
	${MAKE} -C ${KERNEL_SOURCE} ${EXTRA_CFLAGS} SUBDIRS=${PWD}  modules

clean:
	${MAKE} -C ${KERNEL_SOURCE} SUBDIRS=${PWD} clean
	${RM} hello

sprites_test.o: sprites.h sprites.c
	gcc -c sprites_test.c 

sprites_test: sprites_test.o sprites.o 
	gcc sprites_test.o sprites.o -o sprites_test
	./sprites_test


TARFILES = Makefile README vga_ball.h vga_ball.c hello.c
TARFILE = lab3-sw.tar.gz
.PHONY : tar
tar : $(TARFILE)

$(TARFILE) : $(TARFILES)
	tar zcfC $(TARFILE) .. $(TARFILES:%=lab3-sw/%)



endif 
