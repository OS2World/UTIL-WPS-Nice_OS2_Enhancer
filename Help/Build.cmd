@Cls
@Del /F *.inf >NUL 2>NUL
@Del /F *.*~ >NUL 2>NUL
@Ipfc.exe -i -s Names.ipf
@Ipfc.exe -i -s Nice-os2.ipf
@Ipfc.exe -i -s VIOFont.ipf