# Principles_of_Compiler
编译原理

## 用vs2017 x64编译boost_1_64_0
**Compiling with MSVC 2017 x64 (static linkage)**

从```C:\Program Files (x86)\Microsoft Visual Studio\2017\Enterprise\VC\Auxiliary\Build```

复制```vcvarsall.bat```到

```C:\Program Files (x86)\Microsoft Visual Studio\2017\Enterprise\VC\Tools\MSVC\14.10.25017\bin\HostX64```

运行
> %comspec% /k "C:\Program Files (x86)\Microsoft Visual Studio\2017\Enterprise\VC\Auxiliary\Build\vcvars64.bat"

> bootstrap.bat

> b2 -q  --toolset=msvc-14.1 address-model=64 variant=release link=static runtime-link=static include="C:\library\boost\include" library-path="C:\library\boost\lib" --prefix="C:\library\boost" --hash -j 8

> b2 -q  --toolset=msvc-14.1 address-model=64 variant=release link=static runtime-link=static include="C:\library\boost\include" library-path="C:\library\boost\lib" --prefix="C:\library\boost" --hash -j 8 install
