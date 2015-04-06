:userdoc.
:title.Nice Enhancer

:h1.Using the tool
:font facename=default size=12x12 codepage=866.
:artwork align='center' name='Images\Names.bmp'.
:lines align=center.
This application checks files on HPFS and JFS drives. It changes case of names
and some file attributes.
:elines.

:p.
:color fc=cyan bc=default.:color fc=default bc=default.
Convert file names to Mixed Case

:p.
File names will be converted to mixed case like "Text.txt". Files with capital letters
like "OS2Warp.html" will not be processed. Files placed in the Desktop directory will be 
ignored.

:p.
:color fc=green bc=default.:color fc=default bc=default.
Revise differences between real names and object names

:p.
There is little maze with file and WPS object names. If user creates a file on the
Desktop using WPS templates then file will use two names - "real" name from file
system and "object" name, the caption of WPS object. Then user can rename this file -
and obtain a file that will be named differently in WPS and File Manager.

:p.
The object name is stored in the ".LONGNAME" extended attribute (EA). This tool discards
this attribute, so only one name will be used for the file.

:p.
:color fc=yellow bc=default.:color fc=default bc=default.
Remove file images for icons and pictures

:p.
The same problem. Any image can be joined to any file as its extended attribute. 
Everything well, but it can be joined to "*.ico" and "*.ptr" files too. Then icon 
file will have two different icons - real, recorded in it, and another, stored in 
its extended attributes.

:p.
The solution is the same. This tool discards ".ICON" attribute for icon files.

:p.
:color fc=green bc=default.:color fc=default bc=default.
Remove "Type" attribute for files with extensions

:p.
The same problem. This tool discards ".TYPE" property if file name has an extension.

:p.
:color fc=cyan bc=default.:color fc=default bc=default.
Turn off "Read-only" property

:p.
This tool discards "read-only" attribute that comes from CD/DVD drives.

.*

:h1.Использование приложения
:font facename=default size=12x12 codepage=866.
:artwork align='center' name='Images\Names.bmp'.
:lines align=center.
Это приложение предназначено для проверки файлов, расположенных на дисках HPFS и JFS.
С его помощью можно перевести имена файлов в более удобный вид, исправить расхождения
в именах файлов и их значков на рабочем столе, а также поменять некоторые их свойства.
:elines.

:p.
:color fc=cyan bc=default.:color fc=default bc=default.
Привести имена к виду "Текст.txt"

:p.
Имена файлов в указанном каталоге могут быть приведены к виду "Текст.txt" (или "mixed
case"). Для приложений OS/2 это не имеет значения, но некоторые апплеты Java различают
заглавные и строчные буквы.

:p.
Файлы, которые уже приведены к читаемому виду, например, "OS2Warp.html", пропускаются.
Также пропускаются файлы, расположенные в каталоге рабочего стола.

:p.
:color fc=green bc=default.:color fc=default bc=default.
Исправить расхождения в именах

:p.
В OS/2 есть путаница с именами файлов. Если создать файл на рабочем столе с помощью WPS, 
то он кроме настоящего имени получает ещё одно, которое будет использовано для его значка 
как заголовок. Если затем перенести этот файл на диск и переименовать его с помощью FM/2, 
File Commander, Larsen Commander или командой "Rename", то заголовок значка не изменяется. 
Таким образом, можно получить файл, который в WPS и File Manager будет называться по-разному.

:p.
Второе имя, заголовок для значка, записано в расширенном атрибуте под названием ".LONGNAME".
Это приложение удаляет его, после чего у файла остается только одно имя - настоящее, которое
записано в файловой системе.

:p.
:color fc=yellow bc=default.:color fc=default bc=default.
Сбросить дополнительные изображения

:p.
То же самое. Каждый файл может иметь свой значок. Всё хорошо, но его можно изменить также
для файлов *.ico, и тогда у такого файла будет два значка - настоящий, который в нем записан,
и дополнительный, который хранится в расширенных атрибутах.

:p.
Решено это точно так же. Если второй значок есть, он сбрасывается, и WPS использует только
изображение из файла.

:p.
:color fc=green bc=default.:color fc=default bc=default.
Сбросить "Тип" если есть расширение

:p.
То же самое. Сбрасывается расширенный атрибут "Тип файла", если у него есть расширение.
Если у файла расширения нет, сведения о его типе сохраняются.


:p.
:color fc=cyan bc=default.:color fc=default bc=default.
Отключить свойство "Только-чтение"

:p.
Отключается свойство "Только для чтения", устанавливаемое при копировании файлов с CD/DVD.

:euserdoc.
