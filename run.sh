#!/bin/bash
bison -d --report=all sin.y
flex lex.l
g++ sin.tab.c lex.yy.c symtable.h symtable.cpp codeGenerationQ.h codeGenerationQ.c -lfl

#cat ./tests/testif.txt | ./a.out
#cat ./tests/testloop.txt | ./a.out
#cat ./tests/testloop2.txt | ./a.out
#cat ./tests/testbreak.txt | ./a.out
#cat ./tests/testFunction.txt | ./a.out
#cat ./tests/testFunction2.txt | ./a.out
#cat ./tests/testGlobal.txt | ./a.out
#cat ./tests/testRecur.txt | ./a.out
cat ./tests/testfibbo.txt | ./a.out
#cat ./tests/testsuccessioncubes.txt | ./a.out
#cat ./tests/testPrint.txt | ./a.out

if [ $? == 0 ]
then
	./IQ codeQ.q.c
	rm symtable.h.gch
	rm codeGenerationQ.h.gch
	rm a.out
fi
