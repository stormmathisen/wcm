New-Item -Path . -Name "build" -ItemType "directory" -Force | Out-Null #Make build directory even if it exists
gcc -c -o ./build/wcm.dll wcm.c #Compile into library
gcc -o ./build/test.exe test.c ./build/wcm.dll #Compile test program
Write-Output "======================================================================"
Write-Output "C output"
.\build\test.exe #Run test program
Write-Output "======================================================================"
Write-Output "Python output"
python ./python_comp.py #Run python script
Write-Output "======================================================================"