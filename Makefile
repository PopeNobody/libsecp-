MAKEFLAGS:=-rR -j

LD=g++
CXX=g++

CPPFLAGS :=
LDFLAGS :=
CFLAGS :=

allsrc:=$(wildcard *.cc *.c)

exeexe:= upload-server

all: $(exeexe)

.PHONY: install
install:
	cp upload-server /var/cell411/cell411-empty/
	cp upload-server /var/cell411/cell411-parse/

exesrc:= $(patsubst %,%.cc,$(exeexe))
exeobj:= $(patsubst %.cc,%.oo,$(exesrc))
execpp:= $(patsubst %.cc,%.ii,$(exesrc))
exeall:= $(exesrc) $(exeobj) $(execpp)

libsrc:= $(filter-out $(exesrc), $(allsrc))
libobj:= $(patsubst %.c,%.o,$(patsubst %.cc,%.oo,$(libsrc)))
libcpp:= $(patsubst %.cc,%.ii,$(libsrc))
liball:= $(libsrc) $(libobj) $(libcpp)
all: $(exeexe)

#$(warning libsrc:=$(libsrc))

libsimp.a: $(libobj)
	ar -r $@ $?

.PRECIOUS: $(liball) $(exeall)

$(exeexe): %: %.oo libsimp.a ldflags
	g++ -o $@ $< $(shell cat ldflags)


%.i: %.cc checkret.hh fixed_buf.hh cppflags cflags
	g++ -o $@ $< -E $(shell cat cppflags)

%.oo: %.ii cppflags
	g++ -o $@ $< -c $(shell cat cppflags)

%.ii: %.cc $(wildcard *.hh) cppflags
	g++ -o $@ $< -E $(shell cat cppflags)


clean:
	rm -f *.oo *.a recv send
	rm -fr log

include /dev/null $(wildcard *.d)
