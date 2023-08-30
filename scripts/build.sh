#!/bin/bash

set -e

cd "$(dirname "$0")"
cd ..
cmake . -B build/
cmake --build build/

