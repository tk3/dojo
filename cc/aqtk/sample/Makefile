CC       = gcc
SOURCES  = sample.c
OBJS     = $(SOURCES:.c=.o)
INCLUDES = -I$(HOME)/opt/AquestTalk/include
CFLAGS   = -Wall
LDFLAGS  = -L$(HOME)/opt/AquestTalk/lib
LIBS     = -lAquesTalk2
TARGET   = main

RUN_CMD := LD_LIBRARY_PATH=$(HOME)/opt/AquestTalk/lib ./$(TARGET)

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
