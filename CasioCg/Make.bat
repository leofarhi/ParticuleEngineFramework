rm -rf build
rm -rf ../bin
rm -rf bin
mkdir build
mkdir bin
wsl -e bash -lic "fxsdk build-cg -c -B build;make -C build"
mv build/libparticule.a bin/
mv bin ../
pause