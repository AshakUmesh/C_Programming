CC = gcc
CFLAGS = -Wall -g

OBJS = main.o bookings.o operations.o
TARGET = bus_booking

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

main.o: main.c bookings.h operations.h
	$(CC) $(CFLAGS) -c main.c

bookings.o: bookings.c bookings.h
	$(CC) $(CFLAGS) -c bookings.c

operations.o: operations.c operations.h bookings.h
	$(CC) $(CFLAGS) -c operations.c

clean:
	rm -f $(OBJS) $(TARGET)
