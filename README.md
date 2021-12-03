If you can do C++, you can do anything!!!

Python, JavaScript, ReactJS..... all a piece of cake if you can know the master languge known as C++.

Here is a very very handy code that will kill any process that has a Memory footprint above 250000 KB. This memory footprint is known as Workign Set.

According to https://docs.microsoft.com/en-us/windows/win32/api/psapi/ns-psapi-process_memory_counters, it says that WorkingSetSize is "The current working set size, in bytes"

This is a highly handy program that helps when you feel that there's some troublesome processes that's slowing down the computer.

What's beautiful about it is that it's using C++ & Win32 API for this. I am a giant stickler & massive fan of anything that has to do with Win32 API. It seems to me a difficult level vastly above anything abstract like Vue.JS & React.JS.

The size of the executable is 55 KB, so it's "snappy" and immediate. No more waiting for PowerShell scripts to run, no more waiting for Python to interpret the code. It just works, as it's using C++ and Win32 functions which are hover arount ntdll.dll & kernel at ntoskrnl.exe

![](images/large_memory_cpp.png)