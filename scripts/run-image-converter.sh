#!/bin/bash

set -e

cd "$(dirname "$0")"
cd ..
cmake --build build/

./build/image-converter

