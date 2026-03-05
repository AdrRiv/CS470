CC = gcc
CFLAGS = -Wall -Wextra -std=c99
TARGET = Adrian_testFS
SRCS = Adrian_testFS.c Adrian_libFS.c
OBJS = $(SRCS:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
		$(CC) $(OBJS) -o $(TARGET)

%.o: %.c Adrian_libFS.h
	$(CC) $(CFLAGS) -c $< -o $@
run: Adrian_testFS
	./Adrian_testFS

clean:
	rm -f $(TARGET) $(OBJS) $(FILENAME)
