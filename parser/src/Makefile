all: sdb3

sdb3.tab.c sdb3.tab.h:  sdb3.y
	bison -d sdb3.y

lex.yy.c: sdb3.l sdb3.tab.h
	flex sdb3.l

sdb3: lex.yy.c sdb3.tab.c sdb3.tab.h
	g++ -o sdb3 sdb3.tab.c lex.yy.c

clean:
	rm sdb3 sdb3.tab.c sdb3.tab.h lex.yy.c

