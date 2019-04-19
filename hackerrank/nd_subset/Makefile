SRCS		:= $(wildcard *.c)
OBJS		:= $(SRCS:.c=.o)
TARGET		:= subset

CC		:= gcc
CFLAGS		:= -std=c99 -Wall


all: $(TARGET)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

$(TARGET): $(SRCS)
	$(CC) $(CFLAGS) -c $(SRCS)

clean:
	rm -f $(OBJS) $(TARGET)
