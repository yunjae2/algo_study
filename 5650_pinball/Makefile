SRCS		:= $(wildcard *.c)
OBJS		:= $(SRCS:.c=.o)
TARGET		:= pinball

CC		:= gcc
CFLAGS		:= -Wall


all: $(TARGET)
	$(CC) -o $(TARGET) $(OBJS)

$(TARGET): $(SRCS)
	$(CC) -c $(SRCS)

clean:
	rm -f $(OBJS) $(TARGET)
