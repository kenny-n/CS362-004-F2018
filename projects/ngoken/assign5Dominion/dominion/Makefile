CFLAGS= -Wall -fpic -lm -std=c99 -g

rngs.o: rngs.h rngs.c
	gcc -c rngs.c -g  $(CFLAGS)

dominion.o: dominion.h dominion.c rngs.o
	gcc -c dominion.c $(CFLAGS)

playdom: dominion.o playdom.c
	gcc -o playdom playdom.c dominion.o rngs.o $(CFLAGS)
#To run playdom you need to entere: ./playdom <any integer number> like ./playdom 10*/

testDrawCard: testDrawCard.c dominion.o rngs.o
	gcc  -o testDrawCard testDrawCard.c dominion.o rngs.o $(CFLAGS)

badTestDrawCard: badTestDrawCard.c dominion.o rngs.o
	gcc -o badTestDrawCard badTestDrawCard.c dominion.o rngs.o $(CFLAGS)

testBuyCard: testDrawCard.c dominion.o rngs.o
	gcc -o testDrawCard testDrawCard.c dominion.o rngs.o $(CFLAGS)

testAll: dominion.o testSuite.c
	gcc -o testSuite testSuite.c dominion.o rngs.o $(CFLAGS)

unittest1:
	gcc -fprofile-arcs -ftest-coverage dominion.c tst/unittest1.c rngs.c -o unittest1 $(CFLAGS)

unittest2:
	gcc -fprofile-arcs -ftest-coverage dominion.c tst/unittest2.c rngs.c -o unittest2 $(CFLAGS)

unittest3:
	gcc -fprofile-arcs -ftest-coverage dominion.c tst/unittest3.c rngs.c -o unittest3 $(CFLAGS)

unittest4:
	gcc -fprofile-arcs -ftest-coverage dominion.c tst/unittest4.c rngs.c -o unittest4 $(CFLAGS)

cardtest1:
	gcc -fprofile-arcs -ftest-coverage dominion.c tst/cardtest1.c rngs.c -o cardtest1 $(CFLAGS)

cardtest2:
	gcc -fprofile-arcs -ftest-coverage dominion.c tst/cardtest2.c rngs.c -o cardtest2 $(CFLAGS)

cardtest3:
	gcc -fprofile-arcs -ftest-coverage dominion.c tst/cardtest3.c rngs.c -o cardtest3 $(CFLAGS)

cardtest4:
	gcc -fprofile-arcs -ftest-coverage dominion.c tst/cardtest4.c rngs.c -o cardtest4 $(CFLAGS)

unittestresults: unittest1 unittest2 unittest3 unittest4 cardtest1 cardtest2 cardtest3 cardtest4
	./unittest1 &> unittestresults.out
	./unittest2 >> unittestresults.out
	./unittest3 >> unittestresults.out
	./unittest4 >> unittestresults.out
	./cardtest1 >> unittestresults.out
	./cardtest2 >> unittestresults.out
	./cardtest3 >> unittestresults.out
	./cardtest4 >> unittestresults.out
	
	gcov -b unittest1.c >> unittestresults.out
	gcov -b unittest2.c >> unittestresults.out
	gcov -b unittest3.c >> unittestresults.out
	gcov -b unittest4.c >> unittestresults.out
	gcov -b cardtest1.c >> unittestresults.out
	gcov -b cardtest2.c >> unittestresults.out
	gcov -b cardtest3.c >> unittestresults.out
	gcov -b cardtest4.c >> unittestresults.out
	gcov -b dominion.c >> unittestresults.out

randomtestadventurer:
	gcc -fprofile-arcs -ftest-coverage dominion.c tst/randomtestadventurer.c rngs.c -o randomtestadventurer $(CFLAGS)

randomtestcard1:
	gcc -fprofile-arcs -ftest-coverage dominion.c tst/randomtestcard1.c rngs.c -o randomtestcard1 $(CFLAGS)

randomtestcard2:
	gcc -fprofile-arcs -ftest-coverage dominion.c tst/randomtestcard2.c rngs.c -o randomtestcard2 $(CFLAGS)

randomtestresults: randomtestadventurer randomtestcard1 randomtestcard2
	./randomtestadventurer &> randomtestadventurer.out
	./randomtestcard1 >> randomtestcard1.out
	./randomtestcard2 >> randomtestcard2.out

	gcov -b -c randomtestadventurer.c >> randomtestadventurer.out
	gcov -b -c randomtestcard1.c >> randomtestcard1.out
	gcov -b -c randomtestcard2.c >> randomtestcard2.out
	gcov -f -b -c dominion.c >> randomtestadventurer.out
	gcov -f -b -c dominion.c >> randomtestcard1.out
	gcov -f -b -c dominion.c >> randomtestcard2.out

interface.o: interface.h interface.c
	gcc -c interface.c -g  $(CFLAGS)

runtests: testDrawCard
	./testDrawCard &> unittestresult.out
	gcov dominion.c >> unittestresult.out
	cat dominion.c.gcov >> unittestresult.out

player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)

all: playdom player 

clean:
	rm -rf *.o playdom.exe playdom player player.exe  *.gcov *.gcda *.gcno *.so *.out testDrawCard testDrawCard.exe unittest* cardtest* randomtest*