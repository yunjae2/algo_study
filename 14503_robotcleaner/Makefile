SRCS		:= $(wildcard *.c)
OBJS		:= $(SRCS:.c=.o)
TARGET		:= robotcleaner

CC		:= gcc
CFLAGS		:= -std=c99 -Wall


all: $(TARGET)
	$(CC) -o $(TARGET) $(OBJS)

$(TARGET): $(SRCS)
	$(CC) -c $(SRCS)

clean:
	rm -f $(OBJS) $(TARGET)
