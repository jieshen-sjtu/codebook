import os
import sys

SRC = Split('''
            codebook.cpp
            main.cpp
            ''')


INCLUDE_PATH = Split('''./include
                        /usr/include
                        /usr/local/include/
                        ''')

LIB_PATH = Split('''./lib
                    /usr/local/lib
                    /usr/lib
                    ''')

_LIBS = Split('''
                 libvl.so
                 libglog.so
                ''')


env = Environment(LIBPATH=LIB_PATH, LIBS=_LIBS, CPPPATH=INCLUDE_PATH, LINKFLAGS='-fopenmp',
                  CFLAGS='-O3', CXXFLAGS='-O3', CXX='g++');

env.StaticLibrary(target='codebook', source=SRC)
env.Program(target='codebook.bin', source=SRC)
