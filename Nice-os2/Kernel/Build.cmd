@CLS
@Del /F *.dll >NUL 2>NUL
@Del /F *.exe >NUL 2>NUL
@Icc.exe Build.cpp >NUL 2>NUL
@Build.exe
@Del /F Build.exe >NUL 2>NUL
@Del /F *.obj >NUL 2>NUL
@Del /F *.ini >NUL 2>NUL