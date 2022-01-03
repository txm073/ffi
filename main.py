import pathlib
from ctypes import *
import os, sys


os.system("g++ -shared -o lib.so src.cpp")
path = pathlib.Path().absolute() / "lib.so"
lib = CDLL(str(path))
print(lib.test())