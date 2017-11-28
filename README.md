# STLTrust_StringFind
An example project as to why one should, at times, trust the STL over your own home-cut code, especially when boot strapping a new project.

# Build
Check out the repo, it is then recommended to create a subdirectory "mkdir build", change into this directory "cd build" perform "ccmake ../" and allow the configuration (c, followed by c, then generate with g).  And then perform "make" itself.

You will receive the output "STLTrust_StringFind" as a new executable.

Else to manually build the code, with g++...

g++ -std=c++17 main.cpp -pthread -o STLTrust_StringFind

