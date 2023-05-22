CC = gcc
CFLAGS = -g -MMD -I ./include

SRCS = $(wildcard src/*.c)
OBJS = $(patsubst src/%.c, obj/%.o, ${SRCS})

.PHONY: depend clean all

TARGET = server

$(TARGET): $(OBJS)
	$(CC) $^ -o $@ 

obj/%.o:src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm obj/*.o obj/*.d $(TARGET)
