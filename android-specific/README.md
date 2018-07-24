**AudioEngine dependencies at android platform(Use android ndk standalone toolchain)**

#create standalone toolchain  
export PATH=$PATH:/opt/arm-standalone-toolchain/bin  

#openal-soft-1.18.2
https://github.com/kcat/openal-soft  
cd build  
export CMAKE_FIND_ROOT_PATH=/opt/arm-standalone-toolchain  
cmake .. -DCMAKE_TOOLCHAIN_FILE=../XCompile-Android.txt -DHOST=arm-linux-androideabi -DCMAKE_C_FLAGS="-mfloat-abi=softfp -mfpu=neon"
make -j4

#mpg123-1.25.10
download: http://www.mpg123.de/  
./configure --host=arm-linux-androideabi CC=arm-linux-androideabi-gcc CXX=arm-linux-androideabi-g++ --with-cpu=neon
make -j4

#libogg-1.3.3:
./configure --host=arm-linux-androideabi CC=arm-linux-androideabi-gcc CXX=arm-linux-androideabi-g++
make -j4

#libvorbis-1.3.6:
./configure --host=arm-linux-androideabi CC=arm-linux-androideabi-gcc CXX=arm-linux-androideabi-g++ --with-ogg-includes=/usr/local/src/libogg-1.3.3/include/ --with-ogg-libraries=/usr/local/src/libogg-1.3.3/src/.libs/
make -j4
