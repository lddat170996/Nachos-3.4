# use normal make for this Makefile
#
# Makefile for building user programs to run on top of Nachos
#
# Several things to be aware of:
#
#    Nachos assumes that the location of the program startup routine (the
# 	location the kernel jumps to when the program initially starts up)
#       is at location 0.  This means: start.o must be the first .o passed 
# 	to ld, in order for the routine "Start" to be loaded at location 0
#

# if you are cross-compiling, you need to point to the right executables
# and change the flags to ld and the build procedure for as

GCCDIR = ../../../cross-compiler/decstation-ultrix/bin/

LDFLAGS = -T script -N
ASFLAGS = -mips2
CPPFLAGS = $(INCDIR)

# if you aren't cross-compiling:
# GCCDIR =
# LDFLAGS = -N -T 0
# ASFLAGS =
# CPPFLAGS = -P $(INCDIR)

PATH = $(GCCDIR):/lib:/usr/bin:/bin

CC = $(GCCDIR)gcc -B../../../cross-compiler/
AS = $(GCCDIR)as
LD = $(GCCDIR)ld

CPP = gcc -E
INCDIR =-I../userprog -I../threads
CFLAGS = -G 0 -c $(INCDIR)

all: halt shell matmult sort sub create bubblesort help ascii writefile voinuoc_main sinhvien voinuoc

start.o: start.s ../userprog/syscall.h
	$(CPP) $(CPPFLAGS) start.c > strt.s
	$(AS) $(ASFLAGS) -o start.o strt.s
	rm strt.s

halt.o: halt.c
	$(CC) $(CFLAGS) -c halt.c
halt: halt.o start.o
	$(LD) $(LDFLAGS) start.o halt.o -o halt.coff
	../bin/coff2noff halt.coff halt

shell.o: shell.c
	$(CC) $(CFLAGS) -c shell.c
shell: shell.o start.o
	$(LD) $(LDFLAGS) start.o shell.o -o shell.coff
	../bin/coff2noff shell.coff shell

sort.o: sort.c
	$(CC) $(CFLAGS) -c sort.c
sort: sort.o start.o
	$(LD) $(LDFLAGS) start.o sort.o -o sort.coff
	../bin/coff2noff sort.coff sort

matmult.o: matmult.c
	$(CC) $(CFLAGS) -c matmult.c
matmult: matmult.o start.o
	$(LD) $(LDFLAGS) start.o matmult.o -o matmult.coff
	../bin/coff2noff matmult.coff matmult

sub.o: sub.c
	$(CC) $(CFLAGS) -c sub.c
sub: sub.o start.o
	$(LD) $(LDFLAGS) start.o sub.o -o sub.coff
	../bin/coff2noff sub.coff sub

create.o: create.c
	$(CC) $(CFLAGS) -c create.c
create: create.o start.o
	$(LD) $(LDFLAGS) start.o create.o -o create.coff
	../bin/coff2noff create.coff create

bubblesort.o: bubblesort.c
	$(CC) $(CFLAGS) -c bubblesort.c
bubblesort: bubblesort.o start.o
	$(LD) $(LDFLAGS) start.o bubblesort.o -o bubblesort.coff
	../bin/coff2noff bubblesort.coff bubblesort

help.o: help.c
	$(CC) $(CFLAGS) -c help.c
help: help.o start.o
	$(LD) $(LDFLAGS) start.o help.o -o help.coff
	../bin/coff2noff help.coff help

ascii.o: ascii.c
	$(CC) $(CFLAGS) -c ascii.c
ascii: ascii.o start.o
	$(LD) $(LDFLAGS) start.o ascii.o -o ascii.coff
	../bin/coff2noff ascii.coff ascii

writefile.o: writefile.c
	$(CC) $(CFLAGS) -c writefile.c
writefile: writefile.o start.o
	$(LD) $(LDFLAGS) start.o writefile.o -o writefile.coff
	../bin/coff2noff writefile.coff writefile

voinuoc_main.o: voinuoc_main.c
	$(CC) $(CFLAGS) -c voinuoc_main.c
voinuoc_main: voinuoc_main.o start.o
	$(LD) $(LDFLAGS) start.o voinuoc_main.o -o voinuoc_main.coff
	../bin/coff2noff voinuoc_main.coff voinuoc_main

voinuoc.o: voinuoc.c
	$(CC) $(CFLAGS) -c voinuoc.c
voinuoc: voinuoc.o start.o
	$(LD) $(LDFLAGS) start.o voinuoc.o -o voinuoc.coff
	../bin/coff2noff voinuoc.coff voinuoc

sinhvien.o: sinhvien.c
	$(CC) $(CFLAGS) -c sinhvien.c
sinhvien: sinhvien.o start.o
	$(LD) $(LDFLAGS) start.o sinhvien.o -o sinhvien.coff
	../bin/coff2noff sinhvien.coff sinhvien
