ifneq (${KERNELRELEASE},)

# KERNELRELEASE defined: we are being compiled as part of the Kernel
        obj-m := ppu.o 

else

# We are being compiled as a module: use the Kernel build system

	KERNEL_SOURCE := /usr/src/linux-headers-$(shell uname -r)
        PWD := $(shell pwd)

EXTRA_CFLAGS = -I$(src)/game
default: module hello 

hello: game/game.o

module: 
	${MAKE} -C ${KERNEL_SOURCE} ${EXTRA_CFLAGS} SUBDIRS=${PWD}  modules

clean:
	${MAKE} -C ${KERNEL_SOURCE} SUBDIRS=${PWD} clean
	${RM} hello

#duck_hunt.o: duck_hunt.c duck_hunt.h 
#	gcc -c duck_hunt.c -o duck_hunt.o 

#duck_hunt: duck_hunt.o 
#	gcc -o duck_hunt duck_hunt.o 

TARFILES = Makefile README vga_ball.h vga_ball.c hello.c
TARFILE = lab3-sw.tar.gz
.PHONY : tar
tar : $(TARFILE)

$(TARFILE) : $(TARFILES)
	tar zcfC $(TARFILE) .. $(TARFILES:%=lab3-sw/%)



endif 
