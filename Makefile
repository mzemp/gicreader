# Makefile for gic_reader functions

NAME	= gic_reader
SOURCES = gic_reader.c
VERSION = 1.0

CC	= gcc
CFLAGS	= -O3 -mcmodel=medium -Wall -pedantic
LIBS	=

# Rules

gic_reader: $(SOURCES:.c=.o) $(SOURCES:.c=.h) Makefile
	ar rcs lib$(NAME).a $(SOURCES:.c=.o) $(LIBS)

clean:
	-rm -f *~ *.o *.a

install:
	cd ../include; ln -sf ../$(NAME)/$(NAME).h .
	cd ../lib; ln -sf ../$(NAME)/lib$(NAME).a .

tar:
	cd ..; tar cvf - $(NAME)/*.c $(NAME)/*.h $(NAME)/Makefile > $(NAME)-$(VERSION).tar
