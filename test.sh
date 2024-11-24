#/bin/bash
mkdir -p build #Create build directory
gcc -c -o ./build/wcm.o wcm.c #Compile into library
gcc -o ./build/test test.c wcm.o #Compile test program
echo "=================================================="
echo "C output"
./build/test #Run test program
echo "=================================================="
echo "Python output"
python ./python_comp.py #Run python script
echo "=================================================="