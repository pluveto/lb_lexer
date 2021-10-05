rm -rfd build/*
cd build
cmake .. -DCMAKE_TOOLCHAIN_FILE:FILEPATH=~/app/vcpkg/scripts/buildsystems/vcpkg.cmake