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
	rm -rf ylnP2
	mkdir ylnP2
	cp Project2.cpp ylnP2
	cp LexicalAnalyzer.h ylnP2
	cp LexicalAnalyzer.save ylnP2
	cp SyntacticalAnalyzer.h ylnP2
	cp SyntacticalAnalyzer.cpp ylnP2
	cp makefile ylnP2
	cp README.txt ylnP2
	tar cfvz ylnP2.tgz ylnP2
	cp ylnP2.tgz ~tiayln/cs460drop
