CC = g++
CFLAGS = -O3 -c
LFLAGS = -O3
OBJS = main.o MeritFunction.o LM_Optimization.o

all: Test

Test: $(OBJS)
	$(CC) $(LFLAGS) $(OBJS) -o Test

MeritFunction.o: MeritFunction.cpp
	$(CC) $(CFLAGS) MeritFunction.cpp

LM_Optimization.o: LM_Optimization.cpp
	$(CC) $(CFLAGS) LM_Optimization.cpp

main.o: main.cpp
	$(CC) $(CFLAGS) main.cpp

clean:
	rm *.o Test
