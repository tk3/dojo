MRUBY = $(HOME)/apps/mruby
CLEARSILVER = $(HOME)/apps/clearsilver-0.10.5

CC       = gcc
SOURCES  = sample.c
OBJS     = $(SOURCES:.c=.o)
INCLUDES = -I. -I$(MRUBY)/include  \
           -I$(CLEARSILVER)/include/ClearSilver
CFLAGS   = -Wall -Werror-implicit-function-declaration
LDFLAGS  = -L$(CLEARSILVER)/lib
LIBS     = $(MRUBY)/lib/libmruby.a -lm  \
           $(CLEARSILVER)/lib/libneo_cgi.a \
           $(CLEARSILVER)/lib/libneo_utl.a \
           $(CLEARSILVER)/lib/libneo_cs.a
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

