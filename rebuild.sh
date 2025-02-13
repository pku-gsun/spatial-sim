#!/bin/bash
if [ ! -d "build" ]; then
  mkdir build
fi
cd build
cmake -DPYTHON_EXECUTABLE=$(python3 -c "import sys; print(sys.executable)") ..
make -j

# cd src
# # build 
# make clean && make -j >/dev/null 2>&1
# rm libparser.a
# ar crf libparser.a lex.yy.o y.tab.o
# make clean && make -j