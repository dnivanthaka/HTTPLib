#!/bin/bash
g++ -c HTTPResponse.cpp
g++ -c HTTPRequest.cpp
ar cr libhttplib.a *.o
rm *.o
echo "Include the HTTPLib.h file in your project and compile as g++ <source file>.cpp -o <dest program name>.cgi -L. -lhttplib"
