# Principles_of_Compiler
编译原理

## 编译boost_1_67_0
**Compiling with MSVC 2017 x64 (static linkage)**

> bootstrap.bat

> b2 -q  --toolset=msvc-14.1 address-model=64 variant=release link=static runtime-link=static include="C:\library\boost\include" library-path="C:\library\boost\lib" --prefix="C:\library\boost" --hash -j 8

> b2 -q  --toolset=msvc-14.1 address-model=64 variant=release link=static runtime-link=static include="C:\library\boost\include" library-path="C:\library\boost\lib" --prefix="C:\library\boost" --hash -j 8 install
