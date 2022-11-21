
# Getting started
## Build & Install
```
git clone --branch ubuntu18.04 --recurse-submodules https://github.com/genkiiii/dbcppp.git
cd dbcppp
mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=Release ..
make -j
make RunTests
make install
ldconfig # on Unix-systems only
```

## Create Reflection available Structure from DBC file using RTTR libraries(https://www.rttr.org/)
```
dbcppp dbc2 --format=CPPStruct --dbc=yourfile.dbc > reflection_structure.hpp
```

The other information should be here:
https://github.com/xR3b0rn/dbcppp
