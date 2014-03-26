@Echo OFF
Cls

Del /F *.exe >NUL 2>NUL
ICC USBKbd.cpp USBCalls/USBCalls.lib
Del /F *.obj >NUL 2>NUL