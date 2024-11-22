gcc -c -o wcm.dll wcm.c #Compile into library
gcc -o test.exe test.c wcm.dll #Compile test program
./test.exe #Run test program