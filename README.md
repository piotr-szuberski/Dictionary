# Dictionary
Program allowing to use unordered_map from C++ STL in C programs. Written on the 3rd semester of the studies together with K. A.

Compile:
g++ -c -Wall -Wextra -O2 -std=c++17 dict.cc -o dict.o;
g++ -c -Wall -Wextra -O2 -std=c++17 dictglobal.cc -o dictglobal.o;
gcc -c -Wall -Wextra -O2 dict_test1.c -o dict_test1.o;
gcc -c -Wall -Wextra -O2 -DTEST_NUM=<desired_test> dict_test.c -o dict_testC.o;
g++ -c -Wall -Wextra -O2 -std=c++17 dict_test2a.cc -o dict_test2a.o;
g++ -c -Wall -Wextra -O2 -std=c++17 dict_test2b.cc -o dict_test2b.o;
//the dict_test.cc should not compile for any test number
g++ -c -Wall -Wextra -O2 -std=c++17 -DTEST_NUM=<desired_test> dict_test.cc -o dict_testCC.o;
g++ dict_test1.o dict.o dictglobal.o -o dict_test1;
g++ dict_testC.o dict.o dictglobal.o -o dict_testC;
g++ dict_test2a.o dict.o dictglobal.o -o dict_test2a;
g++ dict_test2b.o dict.o dictglobal.o -o dict_test2b;


