CXX = g++
CXXFLAGS = -pthread -std=c++11 -Wall -Wextra

OBJS = main.o BoundedBuffer.o ConfigParser.o Producer.o Dispatcher.o CoEditor.o ScreenManager.o

ex4.out: $(OBJS)
	$(CXX) $(CXXFLAGS) -o ex4.out $(OBJS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $<

clean:
	rm -f *.o ex4.out
