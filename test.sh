#/bin/bash
mkdir -p build #Create build directory
gcc -c -o ./build/wcm.o wcm.c --std=c99 #Compile into library
gcc -o ./build/test test.c ./build/wcm.o --std=c99 #Compile test program
echo "=================================================="
echo "C output"
./build/test #Run test program
echo "=================================================="
echo "Python output"
python3 ./python_comp.py #Run python script
echo "=================================================="