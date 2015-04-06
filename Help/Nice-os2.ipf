:userdoc.
:title.Nice Enhancer

:h1.Using Nice Enhancer
:artwork align='center' name='Images\Nice-os2.bmp'.

:lines align=center.
This application adds new features to the OS/2 system. It works as a plug-in
for Presentation Manager (PM) and monitors system events. The full name of 
this tool is Nice Enhancer or just "Nice".
:elines.

:p.
Nice can be started manually from the Desktop. Click on icon that looks like 
a semaphore to start it in hidden mode.

:p.
This tool should be launched after WPS, so do not use the "Startup.cmd" file 
(or call SysWaitForShell function in the startup script before starting Nice).

:p.
You can tune it using icons in "Control Center" folder. Each icon opens settings
dialog and every dialog page has an "Apply" button. Press this button to activate 
settings for the selected page.

:p.

.*

:h1.Advanced scrolling
:artwork align='center' name='Images\Nice-os2.bmp'.
:p.
:color fc=yellow bc=default.:color fc=default bc=default.
Smooth scrolling.
:p.
This setting enables an extended scrolling. With this option window content
will follow the scroll bar immediately, without delay.

:p.
:color fc=green bc=default.:color fc=default bc=default.
Using arrow keys and "Scroll Lock".
:p.
With this option you can scroll window content using keys with arrows when
"Scroll Lock" is turned "ON".

:p.
:color fc=cyan bc=default.:color fc=default bc=default.
Using a mouse.
:p.
Drag'n'Drop actions are possible too (but only in some windows). You can scroll
window content using mouse when button is pressed and "Scroll Lock" or "Caps Lock"
is turned "ON".
:p.
By default this feature is disabled.

:p.

.*

:h1.Window frames
:artwork align='center' name='Images\Nice-os2.bmp'.
:p.
:color fc=green bc=default.:color fc=default bc=default.
New frames and controls.

:p.
Frames and control elements can be repainted for all windows. You can select "window
theme" to specify drawing methods and parts of frames to change.

:p.
Here is an example of this feature&colon.
.br
:artwork align='center' name='Images\Frames.bmp'.

:p.
:color fc=cyan bc=default.:color fc=default bc=default.
Neon and Glass titlebars
:p.
Nice Enhancer can use its own colors to draw window titles. They can be repainted
in colors like that&colon.

.br
:artwork align='center' name='Images\Warm_en.bmp'.
:artwork align='center' name='Images\Cold_en.bmp'.
:artwork align='center' name='Images\Parrot_en.bmp'.

:p.
These effects are known as "neon" or "glass" colors. Another names of these colors
are "warm", "cold" and "parrot". Too bright colors are not recommended.

:p.
Dark gray color is neutral. It is useful for menu and list selection.

:p.
:color fc=yellow bc=default.:color fc=default bc=default.
More about "warm", "cold" and "neon" colors.

:p.
The light is an electromagnetic wave, and color is dependent on the length of wave.
Here are visible colors from blue to red&colon.
.br
:artwork align='center' name='Images\Colors.bmp'.
:p.
As you can see, there is no violet color in this picture, and gray and white colors
are absent...

:p.
The reason is simple&colon. our eyes can see only three waves - red, green and blue.
With stereo vision there are enough&colon.
.br
:artwork align='center' name='Images\Eye.bmp'.
:p.
For our eyes, the yellow color is a mixture of red and green waves. The cyan color is
a mixture of green and blue, and violet - of blue and red waves. White and gray colors 
can be created from all three waves.

:p.
The computer shows these mixtures from the red, green and blue waves, but mixtures
are not notable, because we understand the "mixed yellow" and the "native yellow" as 
one "simple yellow" color.

:p.
So we see more colors than actually exists. Real colors are placed very simply -
they are dependent on the length of wave and formed in a straight line in only one
dimension. But for our eyes, each color is dependend on three variables and in order
to see their everything we need a three-dimensional space.
.br
:artwork align='center' name='Images\RGBCube.bmp'.
:p.
This is the so-called "RGB Cube". Red, green and blue intensities are placed in the
X, Y, and Z axises and all "available" colors are together.

:p.
So "warm", "cold" and "neon" colors are just sets of values in any cross section of
cube. Some color sets are related with nature and fire, so we call them "warm", some
looks like ice or water, and we call them "cold" etc.

:p.

.*

:h1.Rooms
:artwork align='center' name='Images\Nice-os2.bmp'.
:p.
:color fc=cyan bc=default.:color fc=default bc=default.
Create Rooms around the desktop.

:p.
Each room is a set of windows, it has its own wallpaper and color scheme. In the
room you can launch objects from the Desktop using eCenter or LaunchPad, and access 
running applications using the Window List.

:p.
Use numeric keys "2", "4", "5", "6" and "8" with "Shift" key to switch between
rooms. Another way is to use objects from the WarpCenter or eCenter&colon.
.br
:artwork align='center' name='Images\Rooms.bmp'.
:p.
To add them, drop icons from the "Rooms" folder to eCenter or WarpCenter surface.

:p.

.*

:h1.VIO Windows
:artwork align='center' name='Images\Nice-os2.bmp'.
:p.
:color fc=cyan bc=default.:color fc=default bc=default.
Change fonts in VIO windows.

:p.
There is possible to change font metrics in selected VIO windows. It will be useful
if you run two or more text-mode applications at the same time.

:p.
You can change the number of columns and rows in VIO window with "Mode" command, for
example, "Mode Co100,45" will expand VIO window to 100 x 45 cells. Then change font 
size for an application that created this window, and restart it.

:p.
:color fc=green bc=default.:color fc=default bc=default.
Add commands to SSH window menus

:p.
Menus in SSH windows can be complemented by string sequences like "ls -al" or "mysql
-u... -p..." that will be posted into the window. Different SSH windows can use different
commands depending on window title.

:p.
Commands and window titles should be stored in separate text files. For example, if you
maintain several Unix servers then Nice assumes that you will start one SSH window for
each server and each SSH window will display its own window title. So make a file with 
commands and window title (or many window titles) for each Unix server and place it with 
other data (documents, scripts etc.) in your work directory. Then add this file into the
list in Enhancer's settings dialog.

:p.
There is an example of file with commands and window titles named "SSH.txt" in Enahncer's
directory.

:p.
To launch SSH windows with different titles just create different objects on the desktop -
an icon text will become a window title. It is possible to launch SSH by typing "Start"
in FC/2 or OS/2 shell.

:p.

.*

:h1.Keyboard
:artwork align='center' name='Images\Nice-os2.bmp'.
:p.
:color fc=cyan bc=default.:color fc=default bc=default.
Keys and actions.

:p.
You can assign some actions for various keys. For example, pressing a key you can
launch the Window List, eCenter and ePager, or any other object from the workplace.

:p.
This feature has been designed for keyboards that has two WinKeys (also known as 
"Action" or "GUI" keys) and one TaskList key between Ctrl and Alt keys, and one 
"|\" key near Left Shift, and wide Backslash near big Enter&colon.

:lines align=center.
:artwork align='center' name='Images\Keyboard_Cherry.bmp'.
Cherry Business Line keyboard
:artwork align='center' name='Images\Keyboard_Compaq.bmp'.
Compaq KB-9963 keyboard
:elines.

:p.
If you have a keyboard with multimedia functions, you can use additional "multimedia"
keys to launch MP3 players and Web browsers. 

:p.
:color fc=green bc=default.:color fc=default bc=default.
Break keys.

:p.
There are some "break" key chords on the keyboard like Ctrl + Break or Ctrl + Alt + Delete.
They can be turned "off".

:p.
By default this feature is disabled.

:p.
:color fc=cyan bc=default.:color fc=default bc=default.
Hold Num Lock always ON or OFF and define numeric keys.

:p.
The Num Lock indicator can be holded in one state. Keys at the right side of the
keyboard will work as usual "1..9" keys.

:p.
:color fc=green bc=default.:color fc=default bc=default.
Define FireFox keys.

:p.
There is a key near left Shift often marked "|\" or "\/" that does nothing for the 
last 15 years. Now it can type dash and quotes. Another action is to close current 
browser window.

:p.
:color fc=yellow bc=default.:color fc=default bc=default.
Set keyboard rate

:p.
The value of keyboard repeat rate after delay, also known as "keyboard speed", can be 
changed up to (12 * 2) or (12 * 3) characters per second.

:p.
:color fc=cyan bc=default.:color fc=default bc=default.
Suppress line break in object titles

:p.
With this option, Nice will send "typing complete" message with Enter key for WPS
objects.

:p.
There is still possible to name files using several strings. You can type line break 
in object titles pressing Ctrl + Enter keys or adding "^" character into the name.

:p.
:color fc=yellow bc=default.:color fc=default bc=default.
Keyboard echo

:p.
A sound like "click! click! click!" will be played after any key with this option.

:p.

.*

:h1.Mouse actions
:artwork align='center' name='Images\Nice-os2.bmp'.
:p.
:color fc=green bc=default.:color fc=default bc=default.
Use right mouse button in scrollbars.

:p.
Right mouse buttons can be used with scroll bars and window titles. It is useful for 
ODIN applications and FireFox browser.

:p.
:color fc=cyan bc=default.:color fc=default bc=default.
Invert mouse buttons

:p.
Mouse buttons can be swapped when Caps Lock is turned "ON". Right button will send 
messages from left button and so on. This feature is useful for broken mouses with 
only one button available.

:p.
Drag'n'drop actions cannot be redefined using this way, only single or double clicks.

:p.
:color fc=green bc=default.:color fc=default bc=default.
Suppress double click in window system menus

:p.
With this option double clicking on the system menu (the picture in the upper left
corner of the window) will open the window menu.

:p.
:color fc=cyan bc=default.:color fc=default bc=default.
Clipboard actions in VIO windows.

:p.
Nice Enhancer allows you to mark blocks in text-mode windows using mouse and copy
them into Clipboard. 

:p.
Also, you can perform "Copy" and "Paste" actions pressing common Ctrl + Insert and 
Shift + Insert keys.

:p.
:color fc=yellow bc=default.:color fc=default bc=default.
Use middle button to copy and paste text

:p.
Middle mouse button (or roller) can be used to post Ctrl / Shift + Insert key messages
to the window under a mouse pointer. One click will copy text to the Clipboard and double
click will paste text from it.

:p.
:color fc=cyan bc=default.:color fc=default bc=default.
Move keyboard input focus under mouse pointer

:p.
Without AMouse, this feature will improve mouse scrolling. When scrolling event is occured,
the keyboard input will be redirected to the window under a mouse pointer.

:p.

.*

:h1.Change window placement
:artwork align='center' name='Images\Nice-os2.bmp'.
:p.
:color fc=yellow bc=default.:color fc=default bc=default.
Arrange windows

:p.
Text mode windows, WPS folders and some other windows can be arranged on the 
screen.

:p.

.*

:h1.Dialog boxes
:artwork align='center' name='Images\Nice-os2.bmp'.
:p.
:color fc=green bc=default.:color fc=default bc=default.
Run script after Logon.

:p.
You can specify an application or Rexx script to launch after typing login
and password into the selected Logon window. The script with values from that 
window will be started in background after a short delay.

:p.
To add Logon window to the list of known windows, just start the Logon 
process, but don't enter any values into the Logon window. Then launch Nice 
Enhancer and add this window to the list. Then specify an application/script 
and its parameters.

:p.
Script parameters should be named as %1, %2, %3, corresponding to the fields 
in a window&colon. The word %1 means "first value", the word %2 means "second 
value" and so on. Another parameters like "/P" or "--param" and quote symbols 
will be transferred "as is" to the script command line.

:p.
For example, if you want to connect to the FTP server after you entered to the
Novell network, just launch NWTools and add its Logon window into the list of
known Logon windows. Don't type your login and password at this time. Specify
a Rexx script like&colon. Script.cmd %1 %2, and it will receive two values
from the NWTools Logon.

:p.
Note than Nice Enhancer does *not* remember your login and password.

:p.
:color fc=yellow bc=default.:color fc=default bc=default.
Remember and restore field values.

:p.
If you want to keep text fields in some dialog windows in the permanent state,
open dialog window, type all values ito its fields and add it into the list of 
known windows. Nice Enhancer will remember and restore field values.

:p.
:color fc=cyan bc=default.:color fc=default bc=default.
Send 'Yes' to message boxes.

:p.
Nice Enhancer can close message boxes sending them "OK!" messages from their
buttons. To add message box into the list of known message boxes just launch 
it and add it into the list. Then select a button, and Nice will send a message 
from it to the window.

:p.

.*

:h1.Priority levels
:artwork align='center' name='Images\Nice-os2.bmp'.
:p.
:color fc=cyan bc=default.:color fc=default bc=default.
Normalize priority levels for some applications

:p.
Each application or thread gets a specific amount of CPU time that depends on 
its priority level. These values can be inspected using the WatchCat or other 
Task Manager.

:p.
Priority levels can be changed from 100 to 400. Common values are 200..210,
but some developers increases it to 300 or 400 "for better performance". In 
this case such application becomes dangerous, and any little error in it will 
enough to hang the system.

:p.
You can normalize priority levels for some applications, for example, it is good
for Java Applets.

:p.
:color fc=green bc=default.:color fc=default bc=default.
Calculate priority levels for all windows

:p.
With option, Nice will calculate and change priority levels for visible applications. 
Minimized and hidden applications gives the lowest priority level (100), visible 
applications gives middle level (100+), and active application gives regular (200) 
priority level.

:p.
Workplace Shell, Presentation Manager, invisible (not accessible from Window List) 
and detached (internal system) applications will work with their own levels.

:p.

.*

:h1.Window List
:artwork align='center' name='Images\Nice-os2.bmp'.
:p.
:color fc=green bc=default.:color fc=default bc=default.
Remove items from the Window List.

:p.
You can remove some items from the Window List and Alt + Esc round-robin. Common
items to hide are "LaunchPad", "eCenter" and so on.

:p.
This feature is compatible with lSwitcher and other window switchers.

:p.
The Window List cannot be empty (it is a limitation in Presentation Manager) so
Nice does not remove "Desktop" item from it.

:p.

.*

:h1.System patches
:artwork align='center' name='Images\Nice-os2.bmp'.
:p.
:color fc=yellow bc=default.:color fc=default bc=default.
Allow animation for Workplace Shell windows only.

:p.
An animation like flying frames is displayed for some windows. There is possible 
to allow it for Workplace Shell folders only.

:p.
:color fc=yellow bc=default.:color fc=default bc=default.
Restore windows before closing.

:p.
Nice Enhancer can restore minimized windows before they will be closed. This
feature is useful for applications like System Editor.

:p.
:color fc=cyan bc=default.:color fc=default bc=default.
Change background in WPS folders.

:p.
This feature is a little addition to the old-style Desktop Scheme Palette. You can
specify background image for folders that has no default background, and WPS will 
load this image and use it.

:p.

.*

:h1.�
:artwork align='center' name='Images\Nice-os2.bmp'.

:p.

.*

:h1.�ᯮ�짮����� Nice
:artwork align='center' name='Images\Nice-os2.bmp'.
:lines align=center.
�� �ਫ������ �������� ���� ���������� � OS/2. ��� ࠡ�⠥� �����६����
� ��㣨�� �ਫ�����ﬨ � ���㯠�� �� �६�, �᫨ �� �ॡ����. ��� 楫� -
������ ����� ���������⥩ ��⥬�, ���⮬� ��� ������� "����⥫��". ���
������ �������� "Nice Enhancer", ��� ���� "Nice".
:elines.

:p.
�� �६� ��⠭���� Nice �� ࠡ�祬 �⮫� ᮧ������ ���窨 ��� ���� � ��� �㪮����⢠.
���箪 � ���� ᥬ��� �������� �������� Nice � ���⮬ ����.

:p.
�����⥫� ������ ���� ����饭 ��᫥ �����窨 ࠡ�祣� �⮫� (WPS), ���⮬� ��� ��
᫥��� ��뢠�� � "Startup.cmd" (���� �� ��� �맮�� ���� �맢��� SysWaitForShell �
��������� ����㧪� �����窨 WPS).

:p.
��� ��������� ����஥� �� �६� ࠡ��� ���� ���窨 "����ன�� �� �६� ࠡ���". ��
������ ��࠭�� ����஥� ���� ������ � �������� "OK". ��� ⮣�, �⮡� ����ன�� ��
��࠭��� ��࠭�� �뫨 �ਬ�����, ᫥��� ������ �� ��� ������.

:p.

.*

:h1.��।������� ����ࠦ����
:artwork align='center' name='Images\Nice-os2.bmp'.
:p.
:color fc=yellow bc=default.:color fc=default bc=default.
������� ��।������� ����ࠦ����.

:p.
��ࠢ� � ����� �� ��� �������� ���� �ᯮ������ ����᪨ ��ᬮ��. �᫨
��墠��� ������ ����᪨, 㤥ন��� ����⮩ ������ ���, � ��।������ ����, 
� ����ࠦ���� �㤥� ������ ��������� � ����� ��஭�. ���筮 �� �믮������
�� ��� ��� �ਫ������ - ����� ᤥ���� ⠪, �⮡� ࠡ�⠫� ��� ���.

:p.
:color fc=green bc=default.:color fc=default bc=default.
�ᯮ�짮����� ������ � ��५����

:p.
� �����, �� ��� ������ �ᯮ������ ����᪨ ��ᬮ��, ����ࠦ���� �����
��।������ � ������� ������ � ��५����, �᫨ ����祭 "Scroll Lock". ��
�⮬ ����ࠦ���� ��।�������� �� ���� ��ப� ����� ��� ����.

:p.
�� ����������� ������� ��������� ᮢ६����� ��襩, ������ ����� ���
�ப��⪨ ����ࠦ����. ����� ��� ���뫠�� ����� ᮮ�饭�� � ����⨨ � ���
������ � ��५����, �� �� ᮮ�饭�� �� �ᥣ�� ��뢠�� ��।������� ��࠭���
� ����. ������ ��� ���� ࠡ���� �ࠢ��쭮 �� ��� �����.

:p.
:color fc=cyan bc=default.:color fc=default bc=default.
�ᯮ�짮����� ���

:p.
����� ����� ��।������ ����ࠦ���� � ������� ���, �᫨ ����� �ࠢ�� ������
� ����祭 "Scroll Lock" ��� "Caps Lock".

:p.
�� 㬮�砭�� �� ����������� �⪫�祭�.

:p.

.*

:h1.���譨� ��� ����
:artwork align='center' name='Images\Nice-os2.bmp'.
:p.
:color fc=green bc=default.:color fc=default bc=default.
���� ࠬ�� � ���������.

:p.
����� � ��������� ��� ���� ����� ����ᮢ뢠�� ⠪, �⮡� ����ભ��� �� ����.
�� �������� ������ ���譨� ��� ���� OS/2. �� ����� ����� "⥬�" ��� ���� �
������ �ࠢ��� ��� �ᮢ����.

:p.
��� �ਬ�� ���������⥩ Nice&colon.
.br
:artwork align='center' name='Images\Frames.bmp'.

:p.
:color fc=cyan bc=default.:color fc=default bc=default.
������� ���������.

:p.
�����⥫� �����窨 ����� �ᯮ�짮���� ᢮� ᮡ�⢥��� 梥� ��� �ᮢ���� ����������
���� (� ����, ��������� ���� ���� ����ᮢ��� � �ᯮ�짮������ 梥⮢ ����⥫�).

:p.
:color fc=yellow bc=default.:color fc=default bc=default.
�����騥 � ᬥ蠭�� 梥�

:p.
�� �� �����, �� ᢥ� - �� �����, � �� �����᪨�, � �� ������� &colon.-)
� 梥� ��� ������ �� ����� �����. �� ᨭ��� �� ��᭮�� �� 梥� �ᯮ������ ���
⠪&colon.
.br
:artwork align='center' name='Images\Colors.bmp'.
:p.
�����쭮 ��࠭��, �� �� �⮬ ��㭪� ��� 䨮��⮢��� 梥�, ����� ��� ����砥���
� ��த�. ������ 梥� ����� ⮦� ���...

:p.
���� � ⮬, �� ���� 祫����� ���ਭ����� ⮫쪮 �� 梥�: ����, ������ � ᨭ��.
����� � ��ꥬ�� �७��� �⮣� ��������� ������ �����筮&colon.
.br
:artwork align='center' name='Images\Eye.bmp'.
:p.
�� ���� �⢥� �� �����, ��� �� �����, ���ਬ��, ���� 梥� - �� ᬥ�� ��᭮�� � 
���񭮣�. ���㡮� 梥� ��� 祫����� - ᬥ�� ���񭮣� � ᨭ���, � 䨮��⮢� - ᨭ��� 
� ��᭮��. ���� � ��� ����� �������, �᫨ ᬥ��� �� 梥� �ࠧ�.

:p.
��������� ࠡ���� �筮 ⠪ ��. ����� ⮣�, �⮡� �����뢠�� �����騩 �࠭���� 梥�, 
��� ᬥ訢��� ���� � �����? ������� ��� ࠢ�� ����� �࠭����.

:p.
:color fc=green bc=default.:color fc=default bc=default.
���室�騥 梥�

:p.
��� ��� ����, � 梥� �� �����, � ���� ����� 梥⮢, 祬 ���� �� ᠬ�� ����. �����騥
梥� ������� �� ����� ����� � �ᯮ������ � ���� �����, � ����� ����७��. ����, ������
祫������, ������� �ࠧ� �� ���� ��⠢�����, � �⮡� �������� �� �� �ࠧ�, ����室���
���嬥୮� ����࠭�⢮&colon.
.br
:artwork align='center' name='Images\RGBCube.bmp'.
:p.
�� �⮬ ��㭪� 梥⮢� ��⠢���騥 �뫨 ࠧ��ᠭ� �� ��� X, Y � Z. ����稫�� 梥⭮�
��, ����� ᮤ�ন� �� 梥�, ����㯭� 祫�����. ���室�騥, ��� "�������" 梥�
�ᯮ�������� �� ��אַ� � �祭�� �㡠&colon.
.br
:artwork align='center' name='Images\Warm_ru.bmp'.
:artwork align='center' name='Images\Cold_ru.bmp'.
:artwork align='center' name='Images\Parrot_ru.bmp'.

:p.
���� � 梥� ���ᢥ⪨ ��ப ᯨ᪮� ���� ᤥ���� ⥬��-���. �� "����ࠫ��" 梥�, �
�� ࠢ��� ������⢮ ��᭮��, ���񭮣� � ᨭ���.

:p.
:color fc=yellow bc=default.:color fc=default bc=default.
������ � �ࠢ�� ���孥� 㣫� ����.

:p.
��� �������� ���� ����� �ᮢ��� ����襥 �᫮ ������, 祬 ���筮. �� ��������
�������� �������� �訡�� (� �᭮����, � �����窥 ࠡ�祣� �⮫�).

:p.

.*

:h1.�������
:artwork align='center' name='Images\Nice-os2.bmp'.
:p.
:color fc=cyan bc=default.:color fc=default bc=default.
�������� ������� � ࠡ�祬� �⮫�

:p.
������ ������ - �� ����� ����, ����� ����� ᢮� 梥⮢� ����ன�� � ����.
� ������ ����� ��뢠�� ��� �ਫ������ � ࠡ�祣� �⮫� �ᯮ���� eCenter
��� LaunchPad, � ⠪�� ��७���� � ��� ࠡ���騥 �ਫ������, �롨�� �� ��
ᯨ᪠ ����.

:p.
��� ��४��祭�� ����� �����⠬� �ᯮ������� ��஢� ������ "2", "4", "5",
"6" � "8", ����� ������ ���� ������ ����� � �����襩 "Shift". ����� �����
�ᯮ�짮���� ���窨 ������ �� �����孮�� eCenter ��� WarpCenter&colon.
.br
:artwork align='center' name='Images\Rooms.bmp'.
:p.
�����⥫� ��뢠�� � �����뢠�� � ����, � ������ ���� ������� "�������" 
(��� "Minimize") � ��⥬��� ����. ���� ��७����� � 䮫��� "������ ����".

:p.

.*

:h1.����⮢� ����
:artwork align='center' name='Images\Nice-os2.bmp'.
:p.
:color fc=cyan bc=default.:color fc=default bc=default.
��⠭����� ����� � ⥪�⮢�� �����.

:p.
������� ����������� ��⠭�������� ࠧ���� ����� � ࠧ��� ⥪�⮢�� �����. ��
�������, �᫨ �� ����᪠�� �����६���� ��᪮�쪮 ⥪�⮢�� �ਫ������.

:p.
� ������� ������� "Mode" ����� �������� �᫮ �⮫����� � ��ப � ⥪�⮢�� ����,
���ਬ��, "Mode Co100,45" 㢥���� ⥪�⮢�� ���� �� 100 x 45 ���⮪.

:p.
:color fc=green bc=default.:color fc=default bc=default.
�������� ������� � ���� SSH

:p.
� ���� ���� SSH ����� �������� ������� �த� "ls -al" ��� "mysql -u... -p...", �����
���� ��ࠢ���� � ���� �� �롮� ��ப� ����. ����� ����� SSH ����� �������� ࠧ��
������ ������ � ����ᨬ��� �� ��������� ����.

:p.
������� � ��������� ���� ������ ���� ����᫥�� � �⤥���� ⥪�⮢�� 䠩���. ���ਬ��,
�᫨ �� ࠡ�⠥� � ��᪮�쪨� �ନ�����, � Nice �।��������, �� ��� ������� �� ��� 
�㤥� ��뢠���� �⤥�쭮� ���� SSH � ᢮�� ����������, ���⮬� ��� ������� �� ��� ���� 
��⠢��� ⥪�⮢� 䠩� � ��������� � ���������� �⮣� ���� (��� ��᪮�쪨�� �������묨 
�����������). ����� ����⥫쭮 �ᯮ������ � ��⠫����, ��� ᮤ�ঠ��� �����, �ᯮ��㥬� 
� ࠡ�� (���㬥���, �ਯ�� � �.�.), � �� � ��⠫��� ����⥫�.

:p.
�⮡� ��뢠�� SSH � ࠧ�묨 �����������, ᮧ���� �� ࠡ�祬 �⮫� ࠧ�� ���窨 ���
�맮�� SSH - ������� ��� ���窮� �⠭�� ���������� ����. ����� �맢��� SSH � �������
����������, ���ࠢ "Start" � ���� FC/2 ��� OS/2 Shell.

:p.
�ਬ�� 䠩�� � ��������� � ����������� ���� ���� � ��⠫��� ����⥫�. �� ���뢠����
"SSH.txt".

:p.

.*

:h1.���������
:artwork align='center' name='Images\Nice-os2.bmp'.
:p.
:color fc=cyan bc=default.:color fc=default bc=default.
������ � ����⢨�.

:p.
��� �������� ������ ����� �������� ��।���� ����⢨�. �� ����� ��뢠��
ᯨ᮪ ����, ��४������� � ��㣮� ����, ��뢠�� ���窨 �� ࠡ�祬 �⮫� ���
�ਫ������ - ���ਬ��, "��ᬮ�� ������ ����", "����", "��⥢� ᮥ�������" �
⠪ �����.

:p.
�� ����������� �뫠 ࠧࠡ�⠭� ��� ����������, ���뢠���� "business line". ���
����� ��� ������ WinKey (��� "Action" ��� "GUI") � ���� ������� TaskList �����
�����蠬� Ctrl � Alt. �冷� � ����� �����襩 Shift ���� �������⥫쭠� ������
"|\". ������ � ���⭮� ��⮩ �ᯮ������ �冷� � �ப�� Backspace � ����让
Enter&colon.

:lines align=center.
:artwork align='center' name='Images\Keyboard_Cherry.bmp'.
��������� Cherry Business Line
:artwork align='center' name='Images\Keyboard_Compaq.bmp'.
��������� Compaq KB-9963
:elines.

:p.
�᫨ � ��� ���� ��������� � "multimedia"-��������, �� ����� �������� �� ��� �맮�
MP3-�ந��뢠⥫� ��� �⥢��� ����ॢ�⥫�. �᫨ �� ��������� ���� �� �� ���쬨 
������ "easy access", ࠧ������ ��� (3+2+3), �� ����� �ᯮ�짮���� ��� �맮�� FC/2, 
Mozilla � ⠪ �����.

:p.
�����⥫� �������� ��।����� ������ Ctrl + C / V ��� ⮣�, �⮡� ���������� �
��⠢���� ⥪�� � ������� �ਫ������� - ���� �᫨ ��� �� �����ন���� ��. �����-� 
�� ��⠭�� ������ �ᯮ�짮������ �� ��������� Apple, �� ����� ���� ������� � � 
OS/2. ��� ���������� �� ����� Ctrl / Shift + Insert.

:p.
:color fc=green bc=default.:color fc=default bc=default.
������ ���뢠���.

:p.
�����⥫� �������� �⪫���� ������ Ctrl + Break � Ctrl + Alt + Delete, �����
�ᯮ������� ��� �����襭�� �ਫ������ � ��१���㧪� OS/2.

:p.
�� 㬮�砭�� �� ����������� �⪫�祭�.

:p.
:color fc=yellow bc=default.:color fc=default bc=default.
���ন���� Num Lock ������� ��� �몫�祭��.

:p.
��� ��४���⥫� ����� 㤥ন���� � ��।��񭭮� ���ﭨ� �� �६�.
����� ����� ��८�।����� ��஢� ������ ��� ����� "1..9", �⮡� ���
�ᥣ�� ����ࠫ� ����. �� ������� ��� �������� �ਫ������, ��७����� �
Unix.

:p.
:color fc=green bc=default.:color fc=default bc=default.
FireFox-������.

:p.
�� �������� ���������� ���� ������, �� ���ன ���ᮢ��� �㪢� "|\". ���
����� ������� �� � ����窨, � ⠪�� ����뢠�� ���� �⥢��� ����ॢ�⥫�.

:p.
:color fc=cyan bc=default.:color fc=default bc=default.
������� ��७�� ��ப� ��� ���� ���窮�

:p.
� OS/2 ����� ������ 䠩��� � ���窠� �� ࠡ�祬 �⮫� ����� � ��᪮�쪮 ��ப.
��� �� ���, �� ��� �⮣� �ᯮ������ ������ "Enter". ��� ����������� �����
�⪫���� � ������� ��ॢ�� ��ப� � ��������� ���窠 ������� Ctrl + Enter ���
������ "^" � ����� 䠩��.

:p.
:color fc=green bc=default.:color fc=default bc=default.
��⠭����� ᪮���� ����������

:p.
������� ��᫥ ����প� ����� ���� 㢥��祭� �� (12 * 2) ��� (12 * 3) ����७��
� ᥪ㭤�.

:p.
:color fc=yellow bc=default.:color fc=default bc=default.
��� �� ����⨨.

:p.
�� ������ ����⨨ �� ������� �㤥� ࠧ�������� ���, ����� ����ᠭ � 䠩�� 
"Keyboard.wav" � ��⠫��� ����⥫�.

:p.

.*

:h1.����⢨� � �����
:artwork align='center' name='Images\Nice-os2.bmp'.
:p.
:color fc=green bc=default.:color fc=default bc=default.
������� �ࠢ�� ������ � ����᪠� ��ᬮ��

:p.
�ࠢ�� � �।��� ������ ��� ����� ���� �ᯮ�짮���� ��� ����⢨� � ����᪠�� 
��ᬮ�� � ����������� ����. �� ᤥ���� �०�� �ᥣ� ��� �⥢��� ����ॢ�⥫� 
Mozilla � �ਫ������, ࠡ����� � �।� ODIN.

:p.
:color fc=cyan bc=default.:color fc=default bc=default.
������ ������ ���

:p.
������ ��� ����� ��������� ��� ��㣠 �᫨ ����祭 Caps Lock. � �⮬ ��砥 �ࠢ��
������ ���뫠�� ᮮ�饭�� �� ����� � �������. �������, �᫨ �� �������� ࠧ��⮩
����� ��� � ��� ���� Apple ⮫쪮 � ����� �������.

:p.
��७�� ���窮� ("Drag and drop") ⠪�� ��ࠧ�� ��८�।����� �����, ⮫쪮 ������ 
�� ������.

:p.
:color fc=green bc=default.:color fc=default bc=default.
�⪫���� ������� ����⨥ � ��⥬��� ����

:p.
�᫨ ������� ��� ����ன��, ������� ����⨥ �� ��⥬��� ���� (��� �룫廊� ��� ���⨭�� 
� ����� ���孥� 㣫� ����) �㤥� ��뢠�� ���� ����� ������� ����.

:p.
:color fc=cyan bc=default.:color fc=default bc=default.
���������� ⥪�� � VIO-�����.

:p.
�����⥫� �������� �롨��� ��ப� � ⥪�⮢�� ����� � ������� ��� � �ࠧ� 
�� ���������� ��࠭�� ⥪��. �஬� ⮣�, �����ন������ ����⢨� "���������" � 
"��⠢���", �믮��塞� �� ����⨨ �� ������ Ctrl + Insert � Shift + Insert.

:p.
:color fc=yellow bc=default.:color fc=default bc=default.
�ᯮ�짮���� �।��� ������ ��� ��� ⮣�, �⮡� ���������� � ��⠢���� ⥪��

:p.
�।��� ������ (��� ����� ��� �ப��⪨) ����� ���ࠢ��� � ���� ��� 㪠��⥫�� ���
ᮮ�饭�� � ����⨨ ������ Ctrl / Shift + Insert. ���� ����⨥ �� �।��� ������
����頥� ⥪�� � Clipboard, ������� ����⨥ ��⠢��� ⥪�� �� ����.

:p.
:color fc=cyan bc=default.:color fc=default bc=default.
��७���� ���� �� ���������� ��� 㪠��⥫� ���

:p.
�� ����������� ����� ������ ᮢ६���� ��⮤� �ப��⪨ ����ࠦ���� � ����� � �������
���. ���� �� ���������� �㤥� ��७��� � ����, �ᯮ�������� ��� 㪠��⥫�� ���.

:p.

.*

:h1.��ࠢ������� ����
:artwork align='center' name='Images\Nice-os2.bmp'.
:p.
:color fc=yellow bc=default.:color fc=default bc=default.
��ࠢ������ ������� ����.

:p.
����⮢� ���� � ���� ࠡ�祣� �⮫� �ᯮ�������� �� ����⨨ �ந����쭮. ����
����������� ��ࠢ������ �� �� �।��� �࠭�, ������� ����� 㤮���� �ᯮ�������.

:p.

.*

:h1.���� ��������
:artwork align='center' name='Images\Nice-os2.bmp'.
:p.
:color fc=green bc=default.:color fc=default bc=default.
�믮����� �ਫ������ ��᫥ ����� ��஫�.

:p.
��᫥ ������� ���� ����� ��஫� � �����襭�� �ਫ������, ���ॡ����襣� �����
��஫�, ���࠭�� ���祭�� ����� ���ࠢ��� ��㣮�� �ਫ������, ���஥ �ᯮ����
�� �� ��襬� �ᬮ�७��. ��� �ࠢ���, �� �ਯ� �� �몥 Rexx.

:p.
�⮡� �������� ���� ����� ��஫� � ᯨ᮪ �������� ����⥫� ����, �맮���
���, �� ������ � �� ������� ���祭��. ��⥬ �맮��� ����ன�� ����⥫� �
������� � ᯨ᮪ �� ����. ��⥬ 㪠��� �ਯ� ��� �ਫ������, ���஥ ������
���� ����饭� ��᫥ ������� ���� ����� ��஫�.

:p.
��ࠬ���� ��� �⮣� �ਫ������ 㪠�뢠���� ��� %1, %2, %3 � ᮮ⢥������
���祭��, ���࠭�� � ����. �� ���� %1 �㤥� ����⠢���� ��ࢮ� ���祭��, �
�� ���� %2 ��஥. �� ����� 㪠���� �������⥫�� ��ࠬ����, ��� ��।�����
㪠������� ���� �ਯ�� ��� �ਫ������ ��� ���������.

:p.
���ਬ��, �᫨ �� ����᪥ OS/2 �� �����⢫�� �室 � ��� Novell � �⥫� 
�� ��।��� ��� � ��஫� ��襬� �ਯ�� �� Rexx, ����� �믮���� ������祭�� 
� ��㣨� �⥢� �㦡��, ��ன� ���� NWTools, �� ������ � �� ��� � ��஫�,
��⥬ ������� ��� � ᯨ᮪. ��᫥ �⮣� ������ ��� ���� ������� ����&colon.
Script.cmd %1 %2. ����� �ਯ� ������ ��� ���祭��, ���࠭�� � ����.

:p.
�����⥫� �� ���������� ���祭��, ����� �뫨 ���࠭� � ����� ����� ��஫�.

:p.
��� ࠧ, �� *�����* �� �࠭�� ��஫�.

:p.
:color fc=yellow bc=default.:color fc=default bc=default.
���������� � ����⠭�������� ���� �����.

:p.
�᫨ � �������� ���������� ����� �� �⥫� �� ������ �ᥣ�� ���� � � ��
���祭��, �맮��� ⠪�� ����, ������ �� ���祭�� � ������� ��� � ᯨ᮪.
�����⥫� �������� ���� � ���祭�� ����� ����� � ��, � �㤥� ����⠭��������
ᮤ�ন��� ����� ����� � �� ����� ࠧ �� ��� ������.

:p.
:color fc=cyan bc=default.:color fc=default bc=default.
����뢠�� ���� ᮮ�饭�� �� �� ������.

:p.
������� ���� ᮮ�饭�� ����� ����뢠�� �ࠧ� �� �� �� ������, ���ࠢ���
�� ���� �� ����� �� ������. ��� ⮣�, �⮡� ������ ����ன�� ��� ⠪��� ����,
�맮��� ��� � ������� � ᯨ᮪. ��⥬ �롥�� ������, �� ���ன ��� ����
���ࠢ��� ᮮ�饭��. �����⥫� �㤥� ���뫠�� ��� �� ������ ������ ����.

:p.

.*

:h1.�ਮ����
:artwork align='center' name='Images\Nice-os2.bmp'.
:p.
:color fc=cyan bc=default.:color fc=default bc=default.
��஢���� �ਮ���� ��� �������� �ਫ������.

:p.
�ਮ��� �ਫ������ ��� ��⮪� - �� �����஥ ���祭��, ���஥ ������, ᪮�쪮
�६��� �㤥� �뤠�� �����஬ �⮬� ��⮪�. ���祭�� �ਮ��⮢ 㬥�� �����뢠�� 
WatchCat, ��� �⮣� ���� �맢��� � �� ���� "Threads".

:p.
���祭�� �ਮ��⮢ �������� �� 100 �� 400. �।���� ���祭�� �� 200 �� 210 ���
����設�⢠ �ਫ������ ������ �����筮, ������ ������� ࠧࠡ��稪� �७��ॣ���
�⨬ � 㢥��稢��� �� ���祭��, "�⮡� ࠡ�⠫� ����॥". � �⮬ ��砥 �ਫ������
�⠭������ ����� - �����襩 �訡�� �����筮, �⮡� ������� ��⥬�.

:p.
�� ����� 㬥����� ���祭�� �ਮ��⮢ ��� �������� �ਫ������, ���ਬ��, ���
�����⮢ Java.

:p.
:color fc=green bc=default.:color fc=default bc=default.
������뢠�� �ਮ���� ��� ��� ������� �ਫ������

:p.
�᫨ ��࠭� �� ����ன��, ����⥫� �㤥� �����뢠�� ���祭�� �ਮ��⮢
��� ��� �ਫ������, ����㯭�� �� ᯨ᪠ ����. �����襭�� � ����� �ਫ������
������� ᠬ�� ������ ���祭�� �ਮ��� (100), ������ ������� �।��� ���祭��
(100+), � � �ਫ������, � ����� ࠡ�⠥� ���짮��⥫�, ����砥� ��᮪�� ���祭��
�ਮ��� (200).

:p.
�������� �ਫ������, � ���� ������㯭� � ᯨ᪥ ���� ��� �맢���� �� �������
"detach", ࠡ���� � �� ᮡ�⢥��� ���祭��� �ਮ���. �����窠 WPS �ᥣ��
ࠡ�⠥� � �� ᮡ�⢥��� �ਮ��⮬.

:p.
��� ����������� �� ᫥��� ������� ��� ����室�����. �� 㬮�砭�� ��� �⪫�祭�.

:p.

.*

:h1.���᮪ ����
:artwork align='center' name='Images\Nice-os2.bmp'.
:p.
:color fc=green bc=default.:color fc=default bc=default.
������� ��ப� �� ᯨ᪠ ����.

:p.
�᫨ �� �ᯮ���� �ਫ������, ��������� ����� ����易⥫쭮 �����뢠�� � ᯨ᪥ 
����, �� ����� 㤠���� �� ᯨ᪠ ���� ��᪮�쪮 ��ப.

:p.
���᮪ ���� �� ������ ���� ����� (��࠭�祭�� Presentation Manager), ���⮬� ����⥫�
�� 㤠��� �� ᯨ᪠ ���� ࠡ�祣� �⮫�.

:p.

.*

:h1.�����⪨ ��� WPS
:artwork align='center' name='Images\Nice-os2.bmp'.
:p.
:color fc=yellow bc=default.:color fc=default bc=default.
��ᮢ��� ���⠢�� ⮫쪮 ��� ���� ࠡ�祣� �⮫�.

:p.
�� ����⨨ �������� ���� �����뢠���� ���⠢��. ����� ᤥ���� ⠪, �⮡� ���⠢��
�����뢠���� ⮫쪮 ��� ���� ࠡ�祣� �⮫�, � ��� ���� �ਫ������ ��� �뫨 �⪫�祭�.

:p.
:color fc=yellow bc=default.:color fc=default bc=default.
����⠭�������� ���� ��। �����⨥�.

:p.
�᫨ �� ����ன�� ����祭�, ����⥫� �㤥� ����⠭�������� ����� � 㬥��襭�� 
���� ��। �� �����⨥�. �� ������� ��� �ਫ������, ����� ���������� �ᯮ������� 
� ���ﭨ� ᢮�� ���� � �� �����뢠�� �� �� ����᪥, �᫨ ��� ��⠢����� �������묨.

:p.
:color fc=cyan bc=default.:color fc=default bc=default.
������ ����ࠦ���� ��� ���� ࠡ�祣� �⮫�.

:p.
�� ����������� - ���������� � ���ॢ襩 "������ �奬" �����窨 WPS. ����� ������
����ࠦ���� ��� ���������� �� ���� ࠡ�祣� �⮫�, � ������ ��� ᢮��� ����ࠦ����,
� �� ����⨨ ⠪�� ���� �����窠 WPS �㤥� �ᯮ�짮���� ������� ��㭮�.

:p.
��� ��������� 梥� ⥪�� ��� ���窠�� � ����� ࠡ�祣� �⮫� �ᯮ���� "�������
���⮢" �����窨 WPS. ��७��� ��࠭�� 梥� � �� ����, ��ঠ �����묨 ������
Ctrl � Alt. ��᫥ �⮣� ���ன� �� ���� � ��ன� ��� ᭮��. ���� ���� ��������.

:p.

:euserdoc.
