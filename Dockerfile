FROM ubuntu:24.04

RUN apt-get update && apt-get install -y \
# linux build dependencies
gcc g++ gcc-multilib g++-multilib \
# windows build dependencies
mingw-w64 \
# build system
python3 scons

WORKDIR /source