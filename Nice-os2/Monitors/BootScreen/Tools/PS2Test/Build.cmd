@Echo OFF
Cls

Del /F *.exe >NUL 2>NUL
ICC DosMon.cpp
Del /F *.obj >NUL 2>NUL