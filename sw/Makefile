LDLIBS = -lwiiuse -lm -lbluetooth
ifneq (${KERNELRELEASE},)

# KERNELRELEASE defined: we are being compiled as part of the Kernel
        obj-m := ppu.o 

else

# We are being compiled as a module: use the Kernel build system

	KERNEL_SOURCE := /usr/src/linux-headers-$(shell uname -r)
        PWD := $(shell pwd)

EXTRA_CFLAGS = -I$(src)/game 
default: module duck_hunt 

duck_hunt.o: duck_hunt.c game/game.h sprites.h
	gcc -c duck_hunt.c -o duck_hunt.o -lm

duck_hunt_wii: duck_hunt_wii.o game/game.o sprites.o game/game.h sprites.h 

duck_hunt: duck_hunt.o game/game.o sprites.o 
	gcc -o duck_hunt duck_hunt.o game/game.o sprites.o -lm

driver_test: sprites.h ppu.h driver_test.o
	gcc -g driver_test.c -o driver_test -lm

module: 
	${MAKE} -C ${KERNEL_SOURCE} ${EXTRA_CFLAGS} SUBDIRS=${PWD}  modules 

clean:
	${MAKE} -C ${KERNEL_SOURCE} SUBDIRS=${PWD} clean
	${RM} *.ko sprites_test duck_hunt driver_test *.o

sprites.o: sprites.h sprites.c
	gcc -c sprites.c -g

sprites_test.o: sprites.h sprites.c sprites_test.c
	gcc -c sprites_test.c -g

sprites_test: sprites_test.o sprites.o 
	gcc -g sprites_test.o sprites.o -o sprites_test

sprites_san.o: sprites.h sprites.c
	gcc -c sprites.c -o sprites_san.o -fsanitize=address -static-libasan -g

sprites_test_san.o: sprites.h sprites.c
	gcc -c sprites_test.c -o sprites_test_san.o -fsanitize=address -static-libasan -g

sprites_test_san : sprites_test_san.o sprites_san.o
	gcc sprites_test_san.o sprites_san.o -o sprites_san -fsanitize=address -static-libasan -g
	./sprites_san


TARFILES = Makefile README vga_ball.h vga_ball.c hello.c
TARFILE = lab3-sw.tar.gz
.PHONY : tar
tar : $(TARFILE)

$(TARFILE) : $(TARFILES)
	tar zcfC $(TARFILE) .. $(TARFILES:%=lab3-sw/%)



endif 
