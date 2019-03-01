CXX = g++
CXXFLAGS = -g -std=c++11 -lgmpxx -lgmp
INCS = -I./ -I../../include
OBJS = ../../build/*.o

all: sdb3

sdb3.tab.c sdb3.tab.h:  sdb3.y
	bison -d sdb3.y

lex.yy.c: sdb3.l sdb3.tab.h
	flex sdb3.l

sdb3: lex.yy.c sdb3.tab.c sdb3.tab.h
	$(CXX) $(CXXFLAGS) $(INCS) -o sdb3 sdb3.tab.c lex.yy.c $(OBJS)

clean:
	rm sdb3 sdb3.tab.c sdb3.tab.h lex.yy.c

