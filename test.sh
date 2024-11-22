#/bin/bash
gcc -c -o wcm.o wcm.c #Compile into library
gcc -o test test.c wcm.o #Compile test program
./test #Run test program