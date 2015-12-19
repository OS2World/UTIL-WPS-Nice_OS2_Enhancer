@Echo off
Cls

Del /F XTest.exe >NUL 2>NUL
Del /F _log.txt >NUL 2>NUL
Del /F *.ini >NUL 2>NUL

Copy XTest.cpp .. >NUL 2>NUL
Cd ..

Del /F XTest.exe >NUL 2>NUL
Del /F Nice-os2.dll >NUL 2>NUL
Del _log.txt >NUL 2>NUL
Del /F *.ini >NUL 2>NUL

Cmd /C Gcc Xtest.cpp Xtest\\Xtest.def
Copy XTest.exe XTest >NUL 2>NUL

Del /F XTest.cpp >NUL 2>NUL
Del /F XTest.exe >NUL 2>NUL
Cd XTest
