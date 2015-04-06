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

:h1.�ᯮ�짮����� �ਫ������
:font facename=default size=12x12 codepage=866.
:artwork align='center' name='Images\Names.bmp'.
:lines align=center.
�� �ਫ������ �।�����祭� ��� �஢�ન 䠩���, �ᯮ�������� �� ��᪠� HPFS � JFS.
� ��� ������� ����� ��ॢ��� ����� 䠩��� � ����� 㤮��� ���, ��ࠢ��� ��宦�����
� ������ 䠩��� � �� ���窮� �� ࠡ�祬 �⮫�, � ⠪�� �������� ������� �� ᢮��⢠.
:elines.

:p.
:color fc=cyan bc=default.:color fc=default bc=default.
�ਢ��� ����� � ���� "�����.txt"

:p.
����� 䠩��� � 㪠������ ��⠫��� ����� ���� �ਢ����� � ���� "�����.txt" (��� "mixed
case"). ��� �ਫ������ OS/2 �� �� ����� ���祭��, �� ������� ������� Java ࠧ�����
�������� � ����� �㪢�.

:p.
�����, ����� 㦥 �ਢ����� � �⠥���� ����, ���ਬ��, "OS2Warp.html", �ய�᪠����.
����� �ய�᪠���� 䠩��, �ᯮ������� � ��⠫��� ࠡ�祣� �⮫�.

:p.
:color fc=green bc=default.:color fc=default bc=default.
��ࠢ��� ��宦����� � ������

:p.
� OS/2 ���� ��⠭�� � ������� 䠩���. �᫨ ᮧ���� 䠩� �� ࠡ�祬 �⮫� � ������� WPS, 
� �� �஬� �����饣� ����� ����砥� ��� ����, ���஥ �㤥� �ᯮ�짮���� ��� ��� ���窠 
��� ���������. �᫨ ��⥬ ��७��� ��� 䠩� �� ��� � ��२�������� ��� � ������� FM/2, 
File Commander, Larsen Commander ��� �������� "Rename", � ��������� ���窠 �� ���������. 
����� ��ࠧ��, ����� ������� 䠩�, ����� � WPS � File Manager �㤥� ���뢠���� ��-ࠧ����.

:p.
��஥ ���, ��������� ��� ���窠, ����ᠭ� � ���७��� ��ਡ�� ��� ��������� ".LONGNAME".
�� �ਫ������ 㤠��� ���, ��᫥ 祣� � 䠩�� ��⠥��� ⮫쪮 ���� ��� - �����饥, ���஥
����ᠭ� � 䠩����� ��⥬�.

:p.
:color fc=yellow bc=default.:color fc=default bc=default.
������ �������⥫�� ����ࠦ����

:p.
�� �� ᠬ��. ����� 䠩� ����� ����� ᢮� ���箪. ��� ���, �� ��� ����� �������� ⠪��
��� 䠩��� *.ico, � ⮣�� � ⠪��� 䠩�� �㤥� ��� ���窠 - �����騩, ����� � ��� ����ᠭ,
� �������⥫��, ����� �࠭���� � ���७��� ��ਡ���.

:p.
��襭� �� �筮 ⠪ ��. �᫨ ��ன ���箪 ����, �� ���뢠����, � WPS �ᯮ���� ⮫쪮
����ࠦ���� �� 䠩��.

:p.
:color fc=green bc=default.:color fc=default bc=default.
������ "���" �᫨ ���� ���७��

:p.
�� �� ᠬ��. ����뢠���� ���७�� ��ਡ�� "��� 䠩��", �᫨ � ���� ���� ���७��.
�᫨ � 䠩�� ���७�� ���, ᢥ����� � ��� ⨯� ��࠭�����.


:p.
:color fc=cyan bc=default.:color fc=default bc=default.
�⪫���� ᢮��⢮ "���쪮-�⥭��"

:p.
�⪫�砥��� ᢮��⢮ "���쪮 ��� �⥭��", ��⠭���������� �� ����஢���� 䠩��� � CD/DVD.

:euserdoc.
