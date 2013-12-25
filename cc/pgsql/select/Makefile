CC       = gcc
SOURCES  = sample.c
OBJS     = $(SOURCES:.c=.o)
INCLUDES =
CFLAGS   = -Wall `pkg-config --cflags libpq`
LDFLAGS  = `pkg-config --libs libpq`
LIBS     =
TARGET   = main

$(TARGET): $(OBJS)
	$(CC) $(LDFLAGS) -o $@ $(OBJS) $(LIBS)

.c.o:
	$(CC) $(INCLUDES) $(CFLAGS) -c $<

debug:
	make -f Makefile CFLAGS="-g $(CFLAGS)" LDFLAGS="-g $(LDFLAGS)"

clean:
	rm -f $(TARGET) $(OBJS)

run:
	@LD_LIBRARY_PATH=$(HOME)/opt/postgresql-9.3.2/lib ./main
