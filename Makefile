#
# Makefile for Back Block Info project
#


CROSS_COMPILE ?= /opt/crosstool-ng-arm/bin/arm-unknown-linux-gnueabi-
CC     := $(CROSS_COMPILE)gcc

SRCS   := main.c
OBJS   := $(SRCS:.c=.o)
TARGET := bbinfo

CFLAGS += -Wall -Werror



default: all
all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)


clean:
	rm -rf $(TARGET) $(OBJS)


.PHONY: default all clean
