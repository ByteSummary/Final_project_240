EXECS = simulation #testAnimator
OBJS = simulation.o Animator.o VehicleBase.o Road.o TrafficLight.o Random.o #testAnimator.o

#### use next two lines for Mac
CC = g++
CCFLAGS = -std=c++17

#### use next two lines for mathcs* machines:
#CC = g++
#CCFLAGS = -std=c++17

all: $(EXECS)

testAnimator: $(OBJS)
	$(CC) $(CCFLAGS) $^ -o $@

simulation: $(OBJS)
	$(CC) $(CCFLAGS) $^ -o $@

%.o: %.cpp *.h
	$(CC) $(CCFLAGS) -c $<

%.o: %.cpp
	$(CC) $(CCFLAGS) -c $<

clean:
	/bin/rm -f a.out $(OBJS) $(EXECS)
