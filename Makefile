#DEBUG  = -g
CFLAGS = -Wall -pedantic $(DEBUG) 
LFLAGS = -Wall -lm $(DEBUG)
# for Windows use del for UNIX use \rm -f
RM = del
INCS = poly.h
SRCS = poly.cpp \
	tester.cpp
OBJS = $(SRCS:.cpp=.o)
EXEC = tester

all: $(SRCS) $(EXEC)

# To make an object from source
#.cpp.o: 
%.o:%.cpp $(INCS)
	$(CXX) $(CFLAGS) -c $< -o $@

$(EXEC): $(OBJS) 
	$(CXX) $(LFLAGS) $(OBJS) -o $@

clean:
	del   *.o  $(EXEC)
	echo clean done


