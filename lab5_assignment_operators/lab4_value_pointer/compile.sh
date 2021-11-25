#!/bin/bash -x

set -o errexit
set -o nounset
set -o pipefail

mkdir -p build
(
  cd build
  cmake -G Ninja ..
#  cmake ..
#  make --jobs=$(grep -c ^processor /proc/cpuinfo)
  ninja -j $(grep -c ^processor /proc/cpuinfo)
)
rm -rf build
