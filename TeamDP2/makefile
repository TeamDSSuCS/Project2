P2.out : Project2.o SetLimits.o LexicalAnalyzer.o SyntacticalAnalyzer.o
	g++ -std=c++11 -g -o P2.out Project2.o SetLimits.o LexicalAnalyzer.o SyntacticalAnalyzer.o

Project2.o : Project2.cpp SetLimits.h SyntacticalAnalyzer.h
	g++ -std=c++11 -g -c Project2.cpp

SetLimits.o : SetLimits.cpp SetLimits.h
	g++ -std=c++11 -g -c SetLimits.cpp

LexicalAnalyzer.o : LexicalAnalyzer.save
	cp LexicalAnalyzer.save LexicalAnalyzer.o

SyntacticalAnalyzer.o : SyntacticalAnalyzer.cpp SyntacticalAnalyzer.h LexicalAnalyzer.h
	g++ -std=c++11 -g -c SyntacticalAnalyzer.cpp

clean : 
	rm *.o P2.out *.gch

run: P2.out
	./P2.out test.ss

submit : Project2.cpp LexicalAnalyzer.h LexicalAnalyzer.save SyntacticalAnalyzer.h SyntacticalAnalyzer.cpp makefile README.txt
	rm -rf TeamDP2
	mkdir TeamDP2
	cp Project2.cpp TeamDP2
	cp LexicalAnalyzer.h TeamDP2
	cp LexicalAnalyzer.save TeamDP2
	cp SyntacticalAnalyzer.h TeamDP2
	cp SyntacticalAnalyzer.cpp TeamDP2
	cp makefile TeamDP2
	cp README.txt TeamDP2
	tar cfvz TeamDP2.tgz TeamDP2
	cp TeamDP2.tgz ~tiawatts/cs460drop
