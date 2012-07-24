
MRUBY_PREFIX = $(HOME)/opt/mruby

CC       = gcc
SOURCES  = sample.c
OBJS     = $(SOURCES:.c=.o)
INCLUDES = -I. -I$(MRUBY_PREFIX)/include
CFLAGS   = -Wall -Wwrite-strings -Werror
LDFLAGS  =
LIBS     = -lm $(MRUBY_PREFIX)/lib/libmruby.a
TARGET   = main

$(TARGET): $(OBJS)
	$(CC) $(LDFLAGS) -o $@ $(OBJS) $(LIBS)

.c.o:
	$(CC) $(INCLUDES) $(CFLAGS) -c $<

debug:
	make -f Makefile CFLAGS+="-g" LDFLAGS+="-g"

clean:
	rm -f $(TARGET) $(OBJS)

test:
	@./$(TARGET) hello.rb

