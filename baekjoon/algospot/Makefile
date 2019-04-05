SRCS		:= $(wildcard *.c)
OBJS		:= $(SRCS:.c=.o)
TARGET		:= algospot

CC		:= gcc
CFLAGS		:= -std=c99


all: $(TARGET)
	$(CC) -o $(TARGET) $(OBJS)

$(TARGET): $(SRCS)
	$(CC) -c $(SRCS)

clean:
	rm -f $(OBJS) $(TARGET)
