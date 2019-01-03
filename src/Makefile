CXX = g++
CXXFLAGS = -g -std=c++11
INCS = -I./
OBJS = KetMap.o Ket.o Superposition.o Functions.o Sequence.o

main: main.cpp $(OBJS)
	$(CXX) $(CXXFLAGS) -o main main.cpp $(OBJS)

.cpp.o:
	$(CXX) $(CXXFLAGS) -c $< -o $@ $(INCS)

clean:
	rm *.o main

