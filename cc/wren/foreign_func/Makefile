CC       = gcc
SOURCES  = sample.c
OBJS     = $(SOURCES:.c=.o)
INCLUDES = -I$(HOME)/opt/wren/include
CFLAGS   = -Wall
LDFLAGS  = -L$(HOME)/opt/wren/lib -lwren
LIBS     =
TARGET   = main

RUN_CMD := DYLD_LIBRARY_PATH=$(HOME)/opt/wren/lib ./$(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(LDFLAGS) -o $@ $(OBJS) $(LIBS)

.c.o:
	$(CC) $(INCLUDES) $(CFLAGS) -c $<

debug:
	make -f Makefile CFLAGS="-g $(CFLAGS)" LDFLAGS="-g $(LDFLAGS)"

run:
	@ $(RUN_CMD)

clean:
	rm -f $(TARGET) $(OBJS)
