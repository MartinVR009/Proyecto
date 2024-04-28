GCC = gcc
TARGET = sensor
SRCS = sensor.c
OBJS = $(SRCS:.c=.o)

s ?= 1
t ?= 1
f ?= datos
p ?= pipe1

all: $(TARGET)

$(TARGET): $(OBJS)
    $(GCC) $(CFLAGS) $(OBJS) -o $@

run_sensor: $(TARGET)
    ./$(TARGET) -s $(s) -t $(t) -f $(f) -p $(p)

clean:
    rm -f $(TARGET) $(OBJS)
