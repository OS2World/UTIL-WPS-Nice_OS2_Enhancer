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

:h1. 
:artwork align='center' name='Images\Nice-os2.bmp'.

:p.

.*

:h1.Использование Nice
:artwork align='center' name='Images\Nice-os2.bmp'.
:lines align=center.
Это приложение добавляет новые возможности к OS/2. Оно работает одновременно
с другими приложениями и уступает им время, если это требуется. Его цель -
расширить набор возможностей системы, поэтому оно названо "расширителем". Его
полное название "Nice Enhancer", или просто "Nice".
:elines.

:p.
Во время установки Nice на рабочем столе создаются значки для него и для руководства.
Значок в виде семафора позволяет запустить Nice в скрытом виде.

:p.
Расширитель должен быть запущен после оболочки рабочего стола (WPS), поэтому его не
следует вызывать в "Startup.cmd" (либо до его вызова надо вызвать SysWaitForShell и
дождаться загрузки оболочки WPS).

:p.
Для изменения настроек во время работы есть значки "Настройка во время работы". На
каждой странице настроек есть кнопка с надписью "OK". Для того, чтобы настройки на
выбранной странице были применены, следует нажать на эту кнопку.

:p.

.*

:h1.Передвижение изображения
:artwork align='center' name='Images\Nice-os2.bmp'.
:p.
:color fc=yellow bc=default.:color fc=default bc=default.
Плавное передвижение изображения.

:p.
Справа и внизу по краям некоторых окон расположены полоски просмотра. Если
захватить движок полоски, удерживая нажатой кнопку мыши, и передвинуть мышь, 
то изображение будет плавно двигаться в другую сторону. Обычно это выполняется
не для всех приложений - можно сделать так, чтобы работало для всех.

:p.
:color fc=green bc=default.:color fc=default bc=default.
Использование клавиш со стрелками

:p.
В окнах, по краям которых расположены полоски просмотра, изображение можно
передвигать с помощью клавиш со стрелками, если включен "Scroll Lock". При
этом изображение передвигается на одну строку вверх или вниз.

:p.
Эта возможность изменяет поведение современных мышей, имеющих колесо для
прокрутки изображения. Такие мыши посылают окнам сообщения о нажатии в них
клавиш со стрелками, но эти сообщения не всегда вызывают передвижение страницы
в окне. Теперь мыши будут работать правильно во всех случаях.

:p.
:color fc=cyan bc=default.:color fc=default bc=default.
Использование мыши

:p.
Также можно передвигать изображение с помощью мыши, если нажата правая кнопка
и включен "Scroll Lock" или "Caps Lock".

:p.
По умолчанию эта возможность отключена.

:p.

.*

:h1.Внешний вид окон
:artwork align='center' name='Images\Nice-os2.bmp'.
:p.
:color fc=green bc=default.:color fc=default bc=default.
Новые рамки и заголовки.

:p.
Рамки и заголовки всех окон можно перерисовывать так, чтобы подчеркнуть их объём.
Это позволяет улучшить внешний вид окон OS/2. Вы можете выбрать "тему" для окон и
задать правила для рисования.

:p.
Вот пример возможностей Nice&colon.
.br
:artwork align='center' name='Images\Frames.bmp'.

:p.
:color fc=cyan bc=default.:color fc=default bc=default.
Неоновые заголовки.

:p.
Расширитель оболочки может использовать свои собственные цвета для рисования заголовков
окон (то есть, заголовки окон будут перерисованы с использованием цветов расширителя).

:p.
:color fc=yellow bc=default.:color fc=default bc=default.
Настоящие и смешанные цвета

:p.
Мы все знаем, что свет - это волны, то ли электрические, то ли магнитные &colon.-)
и цвет луча зависит от длины волны. От синего до красного все цвета расположены вот
так&colon.
.br
:artwork align='center' name='Images\Colors.bmp'.
:p.
Довольно странно, что на этом рисунке нет фиолетового цвета, который часто встречается
в природе. Белого цвета здесь тоже нет...

:p.
Дело в том, что глаз человека воспринимает только три цвета: красный, зеленый и синий.
Вместе с объемным зрением этого оказалось вполне достаточно&colon.
.br
:artwork align='center' name='Images\Eye.bmp'.
:p.
Это даёт ответ на вопрос, как мы видим, например, жёлтый цвет - это смесь красного и 
зелёного. Голубой цвет для человека - смесь зелёного и синего, а фиолетовый - синего 
и красного. Белый и серый можно получить, если смешать все цвета сразу.

:p.
Компьютеры работают точно так же. Вместо того, чтобы показывать настоящий оранжевый цвет, 
они смешивают красный и зелёный? Человек всё равно видит оранжевый.

:p.
:color fc=green bc=default.:color fc=default bc=default.
Переходящие цвета

:p.
Так или иначе, а цвета мы видим, и даже больше цветов, чем есть на самом деле. Настоящие
цвета зависят от длины волны и расположены в виде линии, в одном измерении. Цвета, видимые
человеком, зависят сразу от трёх составляющих, и чтобы показать их все сразу, необходимо
трёхмерное пространство&colon.
.br
:artwork align='center' name='Images\RGBCube.bmp'.
:p.
На этом рисунке цветовые составляющие были разбросаны по осям X, Y и Z. Получился цветной
куб, который содержит все цвета, доступные человеку. Переходящие, или "неоновые" цвета
располагаются на прямой в сечении куба&colon.
.br
:artwork align='center' name='Images\Warm_ru.bmp'.
:artwork align='center' name='Images\Cold_ru.bmp'.
:artwork align='center' name='Images\Parrot_ru.bmp'.

:p.
Меню и цвет подсветки строк списков лучше сделать темно-серым. Это "нейтральный" цвет, в
нём равное количество красного, зелёного и синего.

:p.
:color fc=yellow bc=default.:color fc=default bc=default.
Кнопки в правом верхнем углу окна.

:p.
Для некоторых окон можно рисовать меньшее число кнопок, чем обычно. Это позволяет
избежать некоторых ошибок (в основном, в оболочке рабочего стола).

:p.

.*

:h1.Комнаты
:artwork align='center' name='Images\Nice-os2.bmp'.
:p.
:color fc=cyan bc=default.:color fc=default bc=default.
Добавить комнаты к рабочему столу

:p.
Каждая комната - это набор окон, который имеет свои цветовые настройки и обои.
В комнате можно вызывать любые приложения с рабочего стола используя eCenter
или LaunchPad, а также переносить в неё работающие приложения, выбирая их из
списка окон.

:p.
Для переключения между комнатами используются цифровые клавиши "2", "4", "5",
"6" и "8", которые должны быть нажаты вместе с клавишей "Shift". Также можно
использовать значки комнат на поверхности eCenter или WarpCenter&colon.
.br
:artwork align='center' name='Images\Rooms.bmp'.
:p.
Расширитель скрывает и показывает те окна, у которых есть команда "Свернуть" 
(или "Minimize") в системном меню. Окно переносится в фолдер "Скрытые окна".

:p.

.*

:h1.Текстовые окна
:artwork align='center' name='Images\Nice-os2.bmp'.
:p.
:color fc=cyan bc=default.:color fc=default bc=default.
Установить шрифты в текстовых окнах.

:p.
Существует возможность устанавливать различные шрифты в разных текстовых окнах. Это
полезно, если вы запускаете одновременно несколько текстовых приложений.

:p.
С помощью команды "Mode" можно изменить число столбиков и строк в текстовом окне,
например, "Mode Co100,45" увеличит текстовое окно до 100 x 45 клеток.

:p.
:color fc=green bc=default.:color fc=default bc=default.
Добавить команды в меню SSH

:p.
В меню окон SSH можно добавить команды вроде "ls -al" или "mysql -u... -p...", которые
будут отправлены в окно при выборе строки меню. Разным окнам SSH можно назначить разные
наборы команд в зависимости от заголовка окна.

:p.
Команды и заголовки окон должны быть перечислены в отдельных текстовых файлах. Например,
если вы работаете в нескольких терминалах, то Nice предполагает, что для каждого из них 
будет вызываться отдельное окно SSH со своим заголовком, поэтому для каждого из них надо 
составить текстовый файл с командами и заголовком этого окна (или несколькими возможными 
заголовками). Файлы желательно располагать в каталогах, где содержатся данные, используемые 
в работе (документы, скрипты и т.д.), а не в каталоге расширителя.

:p.
Чтобы вызывать SSH с разными заголовками, создайте на рабочем столе разные значки для
вызова SSH - подпись под значком станет заголовком окна. Можно вызвать SSH с заданным
заголовком, набрав "Start" в окне FC/2 или OS/2 Shell.

:p.
Пример файла с командами и заголовками окон есть в каталоге расширителя. Он называется
"SSH.txt".

:p.

.*

:h1.Клавиатура
:artwork align='center' name='Images\Nice-os2.bmp'.
:p.
:color fc=cyan bc=default.:color fc=default bc=default.
Клавиши и действия.

:p.
Для некоторых клавиш можно назначить определённые действия. Вы можете вызывать
список окон, переключаться в другое окно, вызывать значки на рабочем столе или
приложения - например, "Просмотр скрытых окон", "Часы", "Сетевые соединения" и
так далее.

:p.
Эта возможность была разработана для клавиатуры, называемой "business line". Она
имеет две клавиши WinKey (или "Action" или "GUI") и одну клавишу TaskList между
клавишами Ctrl и Alt. Рядом с левой клавишей Shift есть дополнительная клавиша
"|\". Клавиша с обратной чертой расположена рядом с широкой Backspace и большой
Enter&colon.

:lines align=center.
:artwork align='center' name='Images\Keyboard_Cherry.bmp'.
Клавиатура Cherry Business Line
:artwork align='center' name='Images\Keyboard_Compaq.bmp'.
Клавиатура Compaq KB-9963
:elines.

:p.
Если у вас есть клавиатура с "multimedia"-кнопками, вы можете назначить на них вызов
MP3-проигрывателя или сетевого обозревателя. Если на клавиатуре есть ряд из восьми 
кнопок "easy access", разделённых как (3+2+3), их можно использовать для вызова FC/2, 
Mozilla и так далее.

:p.
Расширитель позволяет определить клавиши Ctrl + C / V для того, чтобы запоминать и
вставлять текст в оконных приложениях - даже если они не поддерживают их. Когда-то 
эти сочетания клавиш использовались на компьютерах Apple, но могут быть полезны и в 
OS/2. Они заменяются на обычные Ctrl / Shift + Insert.

:p.
:color fc=green bc=default.:color fc=default bc=default.
Клавиши прерывания.

:p.
Расширитель позволяет отключить клавиши Ctrl + Break и Ctrl + Alt + Delete, которые
используются для завершения приложений и перезагрузки OS/2.

:p.
По умолчанию эта возможность отключена.

:p.
:color fc=yellow bc=default.:color fc=default bc=default.
Удерживать Num Lock включённым или выключенным.

:p.
Этот переключатель можно удерживать в определённом состоянии все время.
Также можно переопределить цифровые клавиши как обычные "1..9", чтобы они
всегда набирали цифры. Это полезно для некоторых приложений, перенесённых с
Unix.

:p.
:color fc=green bc=default.:color fc=default bc=default.
FireFox-клавиши.

:p.
На некоторых клавиатурах есть клавиша, на которой нарисованы буквы "|\". Она
может набирать тире и кавычки, а также закрывать окно сетевого обозревателя.

:p.
:color fc=cyan bc=default.:color fc=default bc=default.
Запретить перенос строки для имен значков

:p.
В OS/2 можно давать файлам и значкам на рабочем столе имена в несколько строк.
Всё бы хорошо, но для этого используется клавиша "Enter". Эту возможность можно
отключить и вводить перевод строки в заголовке значка нажимая Ctrl + Enter или
набирая "^" в имени файла.

:p.
:color fc=green bc=default.:color fc=default bc=default.
Установить скорость клавиатуры

:p.
Скорость после задержки может быть увеличена до (12 * 2) или (12 * 3) повторений
в секунду.

:p.
:color fc=yellow bc=default.:color fc=default bc=default.
Звук при нажатии.

:p.
При каждом нажатии на клавишу будет раздаваться звук, который записан в файле 
"Keyboard.wav" в каталоге расширителя.

:p.

.*

:h1.Действия с мышью
:artwork align='center' name='Images\Nice-os2.bmp'.
:p.
:color fc=green bc=default.:color fc=default bc=default.
Включить правую кнопку в полосках просмотра

:p.
Правая и средняя кнопки мыши могут быть использованы для действий с полосками 
просмотра и заголовками окон. Это сделано прежде всего для сетевого обозревателя 
Mozilla и приложений, работающих в среде ODIN.

:p.
:color fc=cyan bc=default.:color fc=default bc=default.
Менять кнопки мыши

:p.
Кнопки мыши могут подменять друг друга если включен Caps Lock. В этом случае правая
кнопка посылает сообщения от левой и наоборот. Полезно, если вы пользуетесь разбитой
мышью или у вас мышь Apple только с одной кнопкой.

:p.
Перенос значков ("Drag and drop") таким образом переопределить нельзя, только нажатия 
на кнопки.

:p.
:color fc=green bc=default.:color fc=default bc=default.
Отключить двойное нажатие в системном меню

:p.
Если включить эту настройку, двойное нажатие на системное меню (оно выглядит как картинка 
в левом верхнем углу окна) будет вызывать меню вместо закрытия окна.

:p.
:color fc=cyan bc=default.:color fc=default bc=default.
Запоминать текст в VIO-окнах.

:p.
Расширитель позволяет выбирать строки в текстовых окнах с помощью мыши и сразу 
же запоминать выбранный текст. Кроме того, поддерживаются действия "запомнить" и 
"вставить", выполняемые при нажатии на клавиши Ctrl + Insert и Shift + Insert.

:p.
:color fc=yellow bc=default.:color fc=default bc=default.
Использовать среднюю кнопку мыши для того, чтобы запоминать и вставлять текст

:p.
Средняя кнопка (или колесо для прокрутки) может направить в окно под указателем мыши
сообщения о нажатии клавиш Ctrl / Shift + Insert. Одно нажатие на среднюю кнопку
помещает текст в Clipboard, двойное нажатие вставляет текст из него.

:p.
:color fc=cyan bc=default.:color fc=default bc=default.
Переносить ввод от клавиатуры под указатель мыши

:p.
Эта возможность может улучшить современные методы прокрутки изображения в окнах с помощью
мыши. Ввод от клавиатуры будет перенесён в окно, расположенное под указателем мыши.

:p.

.*

:h1.Выравнивание окон
:artwork align='center' name='Images\Nice-os2.bmp'.
:p.
:color fc=yellow bc=default.:color fc=default bc=default.
Выравнивать некоторые окна.

:p.
Текстовые окна и окна рабочего стола располагаются при открытии произвольно. Есть
возможность выравнивать их по середине экрана, задавая более удобное расположение.

:p.

.*

:h1.Окна диалогов
:artwork align='center' name='Images\Nice-os2.bmp'.
:p.
:color fc=green bc=default.:color fc=default bc=default.
Выполнять приложение после ввода пароля.

:p.
После закрытия окна ввода пароля и завершения приложения, потребовавшего ввести
пароль, набранные значения можно направить другому приложению, которое использует
их по вашему усмотрению. Как правило, это скрипт на языке Rexx.

:p.
Чтобы добавить окно ввода пароля в список известных расширителю окон, вызовите
его, не набирая в нём никаких значений. Затем вызовите настройки расширителя и
добавьте в список это окно. Затем укажите скрипт или приложение, которое должно
быть запущено после закрытия окна ввода пароля.

:p.
Параметры для этого приложения указываются как %1, %2, %3 и соответствуют
значениям, набранным в окне. На место %1 будет подставлено первое значение, а
на место %2 второе. Вы можете указать дополнительные параметры, они передаются
указанному вами скрипту или приложению без изменений.

:p.
Например, если при запуске OS/2 вы осуществляете вход в сеть Novell и хотели 
бы передать имя и пароль вашему скрипту на Rexx, который выполнит подключение 
к другим сетевым службам, откройте окно NWTools, не набирая в нём имя и пароль,
затем добавьте его в список. После этого задайте для него команду вида&colon.
Script.cmd %1 %2. Тогда скрипт получит оба значения, набранные в окне.

:p.
Расширитель не запоминает значения, которые были набраны в окнах ввода пароля.

:p.
Ещё раз, он *нигде* не хранит пароли.

:p.
:color fc=yellow bc=default.:color fc=default bc=default.
Запоминать и восстанавливать поля ввода.

:p.
Если в некоторых диалоговых окнах вы хотели бы видеть всегда одни и те же
значения, вызовите такое окно, наберите эти значения и добавьте его в список.
Расширитель запомнит окно и значения полей ввода в нём, и будет восстанавливать
содержимое полей ввода в нём каждый раз при его появлении.

:p.
:color fc=cyan bc=default.:color fc=default bc=default.
Закрывать окна сообщений при их появлении.

:p.
Некоторые окна сообщений можно закрывать сразу же при их появлении, направляя
им ввод от одной из кнопок. Для того, чтобы задать настройку для такого окна,
вызовите его и добавьте в список. Затем выберите кнопку, от которой ему надо
направить сообщение. Расширитель будет посылать его при каждом появлении окна.

:p.

.*

:h1.Приоритеты
:artwork align='center' name='Images\Nice-os2.bmp'.
:p.
:color fc=cyan bc=default.:color fc=default bc=default.
Выровнять приоритеты для некоторых приложений.

:p.
Приоритет приложения или потока - это некоторое значение, которое задаёт, сколько
времени будет выдано процессором этому потоку. Значения приоритетов умеет показывать 
WatchCat, для этого надо вызвать в нём окно "Threads".

:p.
Значения приоритетов меняются от 100 до 400. Среднего значения от 200 до 210 для
большинства приложений вполне достаточно, однако некоторые разработчики пренебрегают
этим и увеличивают эти значения, "чтобы работало быстрее". В этом случае приложение
становится опасным - малейшей ошибки достаточно, чтобы завесить систему.

:p.
Вы можете уменьшить значения приоритетов для некоторых приложений, например, для
апплетов Java.

:p.
:color fc=green bc=default.:color fc=default bc=default.
Рассчитывать приоритеты для всех видимых приложений

:p.
Если выбрана эта настройка, расширитель будет рассчитывать значения приоритетов
для всех приложений, доступных из списка окон. Уменьшенные и скрытые приложения
получают самое низкое значение приоритета (100), видимые получают среднее значение
(100+), а то приложение, с которым работает пользователь, получает высокое значение
приоритета (200).

:p.
Невидимые приложения, то есть недоступные в списке окон или вызванные по команде
"detach", работают с их собственным значением приоритета. Оболочка WPS всегда
работает с её собственным приоритетом.

:p.
Эту возможность не следует включать без необходимости. По умолчанию она отключена.

:p.

.*

:h1.Список окон
:artwork align='center' name='Images\Nice-os2.bmp'.
:p.
:color fc=green bc=default.:color fc=default bc=default.
Удалить строки из списка окон.

:p.
Если вы используете приложения, заголовки которые необязательно показывать в списке 
окон, вы можете удалить из списка окон несколько строк.

:p.
Список окон не должен быть пустым (ограничение Presentation Manager), поэтому расширитель
не удаляет из списка окно рабочего стола.

:p.

.*

:h1.Заплатки для WPS
:artwork align='center' name='Images\Nice-os2.bmp'.
:p.
:color fc=yellow bc=default.:color fc=default bc=default.
Рисовать заставки только для окон рабочего стола.

:p.
При открытии некоторых окон показывается заставка. Можно сделать так, чтобы заставки
показывались только для окон рабочего стола, а для окон приложений они были отключены.

:p.
:color fc=yellow bc=default.:color fc=default bc=default.
Восстанавливать окна перед закрытием.

:p.
Если эта настройка включена, расширитель будет восстанавливать скрытые и уменьшенные 
окна перед их закрытием. Это полезно для приложений, которые запоминают расположение 
и состояние своих окон и не показывают их при запуске, если они оставались невидимыми.

:p.
:color fc=cyan bc=default.:color fc=default bc=default.
Задать изображения для окон рабочего стола.

:p.
Эта возможность - дополнение к устаревшей "Палитре Схем" оболочки WPS. Можно задать
изображение для заполнения тех окон рабочего стола, у которых нет своего изображения,
и при открытии таких окон оболочка WPS будет использовать заданный рисунок.

:p.
Для изменения цвета текста под значками в окнах рабочего стола используйте "Палитру
Цветов" оболочки WPS. Перенесите выбранный цвет в любое окно, держа нажатыми клавиши
Ctrl и Alt. После этого закройте это окно и откройте его снова. Цвета будут изменены.

:p.

:euserdoc.
