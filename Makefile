

Project1: main.o help.o mem_alloc.o mem_display.o mem_free.o mem_inv.o \
	mem_ver_pattern.o mem_write.o mem_write_pattern.o
	gcc -o Projec1 main.o help.o mem_alloc.o mem_display.o mem_free.o mem_inv.o \
	mem_ver_pattern.o mem_write.o mem_write_pattern.o

main.o: main.c command_interface.h help.h mem_alloc.h mem_display.h \
	mem_free.h mem_inv.h mem_ver_pattern.h mem_write.h mem_write_pattern.h
	gcc -c main.c
	
help.o: help.c help.h command_interface.h help.h mem_alloc.h mem_display.h \
	mem_free.h mem_inv.h mem_ver_pattern.h mem_write.h mem_write_pattern.h
	gcc -c help.c

mem_alloc.o: mem_alloc.h mem_alloc.c command_interface.h
	gcc -c mem_alloc.c

mem_display.o: mem_display.h mem_display.c command_interface.h
	gcc -c mem_display.c

mem_free.o: mem_free.h mem_free.c command_interface.h
	gcc -c mem_free.c

mem_inv.o: mem_inv.h mem_inv.c command_interface.h
	gcc -c mem_inv.c

mem_ver_pattern.o: mem_ver_pattern.h mem_ver_pattern.c command_interface.h
	gcc -c mem_ver_pattern.c

mem_write.o: mem_write.h mem_write.c command_interface.h
	gcc -c mem_write.c

mem_write_pattern.o: mem_write_pattern.h mem_write_pattern.c command_interface.h
	gcc -c mem_write_pattern.c


clean:
	rm main.o help.o mem_alloc.o mem_display.o mem_free.o mem_inv.o \
		mem_ver_pattern.o mem_write.o mem_write_pattern.o Projec1.exe


