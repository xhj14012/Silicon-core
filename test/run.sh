echo normal case follows:
echo run test1
../core data-mod51-1.dat > data-mod51-1.out
echo finished
echo run test2
../core data-mod51-2.dat > data-mod51-2.out
echo finished
echo run test3
../core data-mod51-3.dat > data-mod51-3.out
echo finished
echo run test4
../core data-mod1.dat > data-mod1.out
echo finished
echo run test5
../core data-mod2.dat > data-mod2.out
echo finished
echo run test6
../core data-mod3.dat > data-mod3.out
echo finished
echo run test7
../core data-mod1-cut.dat > data-mod1-cut.out
echo finished
echo run test8
../core data-mod2-cut.dat > data-mod2-cut.out
echo finished
echo run test9
../core data-mod3-cut.dat > data-mod3-cut.out
echo finished
echo large case follows:
echo run test10
../core data-300.dat > data-300.out
echo finished
echo run test11
../core data-540.dat > data-540.out
echo finished
echo run test12
../core data-300-cut.dat > data-300-cut.out
echo finished
echo run test13
../core data-540-cut.dat > data-540-cut.out
echo finished