:userdoc.
:title.Nice Enhancer

:h1.Font for text mode applications
:font facename=default size=12x12 codepage=866.

:artwork align='center' name='Images\VIOFont.bmp'.
:lines align=center.
If you still use full-screen text mode applications, you maybe want to change the
default font for text mode. There is a font for 866 (Cyrillic only) codepage, that
looks like System VIO.
:elines.

:p.
In OS/2 Warp text mode fonts are stored in the Viotbl.dcp file in the OS2 directory.

:p.
There is a string in the Config.sys file that refers to the font&colon.
.br
:font facename=Courier size=10x10 codepage=866.
 DEVINFO=SCR,VGA,C&colon.\OS2\BOOT\VIOTBL.DCP
.br
:font facename=default size=12x12 codepage=866.
You can change this string and make a reference to the new font&colon.
.br
:font facename=Courier size=10x10 codepage=866.
 DEVINFO=SCR,VGA,C&colon.\...\NICE.DCP
.br
:font facename=default size=12x12 codepage=866.
And reboot the system.

:p.
On any error this string will be skipped.

:p.

.*

:h1.Шрифт для текстовых приложений
:font facename=default size=12x12 codepage=866.

:artwork align='center' name='Images\VIOFont.bmp'.:lines align=center.
Если вы используете приложения, которые работают в текстовом режиме, вы можете установить
для них шрифт, похожий на оконный System VIO. Это будет полезно в случае, когда текстовые
приложения показывают вместо кириллицы латинские крокозябры.
:elines.

:p.
В OS/2 шрифты для текстового режима хранятся в файле Viotbl.dcp, который расположен в
каталоге C&colon.\OS2. Он занимает около 200 КB и содержит шрифты для разных языков и
режимов изображения - CGA, EGA, VGA.

:p.
Загляните в файл Config.sys - там есть строки, которые задают текущий шрифт&colon.
.br
:font facename=Courier size=10x10 codepage=866.
 DEVINFO=SCR,VGA,C&colon.\OS2\BOOT\VIOTBL.DCP
.br
 CODEPAGE=866,850
.br
:font facename=default size=12x12 codepage=866.
Исправьте их, чтобы они выглядели так&colon.
.br
:font facename=Courier size=10x10 codepage=866.
 DEVINFO=SCR,VGA,C&colon.\...\NICE.DCP
.br
 CODEPAGE=866
.br
:font facename=default size=12x12 codepage=866.
И перезагрузите систему.

:p.
В случае, если OS/2 не сможет взять шрифт из "NICE.DCP", вы увидите сообщение об этом и
слова, что "эта строка пропускается". Работе OS/2 это не помешает - будет использоваться
обычный шрифт.

:p.
Для того, чтобы отключить переключатель раскладок по "<Alt>+<Shift>" и пользоваться
другим переключателем, замените в Config.sys строку&colon.
.br
:font facename=Courier size=10x10 codepage=866.
 DEVINFO=KBD,RU...,C&colon.\OS2\KEYBOARD.DCP
.br
:font facename=default size=12x12 codepage=866.
На строку&colon.
.br
:font facename=Courier size=10x10 codepage=866.
 DEVINFO=KBD,US,C&colon.\OS2\KEYBOARD.DCP
.br
:font facename=default size=12x12 codepage=866.
И перезагрузите систему.

:p.

:euserdoc.
