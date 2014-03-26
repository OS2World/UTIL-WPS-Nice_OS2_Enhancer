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

:h1.���� ��� ⥪�⮢�� �ਫ������
:font facename=default size=12x12 codepage=866.

:artwork align='center' name='Images\VIOFont.bmp'.:lines align=center.
�᫨ �� �ᯮ���� �ਫ������, ����� ࠡ���� � ⥪�⮢�� ०���, �� ����� ��⠭�����
��� ��� ����, ��宦�� �� ������ System VIO. �� �㤥� ������� � ��砥, ����� ⥪�⮢�
�ਫ������ �����뢠�� ����� ��ਫ���� ��⨭᪨� �ப�����.
:elines.

:p.
� OS/2 ����� ��� ⥪�⮢��� ०��� �࠭���� � 䠩�� Viotbl.dcp, ����� �ᯮ����� �
��⠫��� C&colon.\OS2. �� �������� ����� 200 �B � ᮤ�ন� ����� ��� ࠧ��� �몮� �
०���� ����ࠦ���� - CGA, EGA, VGA.

:p.
����ﭨ� � 䠩� Config.sys - ⠬ ���� ��ப�, ����� ������ ⥪�騩 ����&colon.
.br
:font facename=Courier size=10x10 codepage=866.
 DEVINFO=SCR,VGA,C&colon.\OS2\BOOT\VIOTBL.DCP
.br
 CODEPAGE=866,850
.br
:font facename=default size=12x12 codepage=866.
��ࠢ�� ��, �⮡� ��� �룫拉�� ⠪&colon.
.br
:font facename=Courier size=10x10 codepage=866.
 DEVINFO=SCR,VGA,C&colon.\...\NICE.DCP
.br
 CODEPAGE=866
.br
:font facename=default size=12x12 codepage=866.
� ��१���㧨� ��⥬�.

:p.
� ��砥, �᫨ OS/2 �� ᬮ��� ����� ���� �� "NICE.DCP", �� 㢨��� ᮮ�饭�� �� �⮬ �
᫮��, �� "�� ��ப� �ய�᪠����". ����� OS/2 �� �� ����蠥� - �㤥� �ᯮ�짮������
����� ����.

:p.
��� ⮣�, �⮡� �⪫���� ��४���⥫� �᪫���� �� "<Alt>+<Shift>" � ���짮������
��㣨� ��४���⥫��, ������� � Config.sys ��ப�&colon.
.br
:font facename=Courier size=10x10 codepage=866.
 DEVINFO=KBD,RU...,C&colon.\OS2\KEYBOARD.DCP
.br
:font facename=default size=12x12 codepage=866.
�� ��ப�&colon.
.br
:font facename=Courier size=10x10 codepage=866.
 DEVINFO=KBD,US,C&colon.\OS2\KEYBOARD.DCP
.br
:font facename=default size=12x12 codepage=866.
� ��१���㧨� ��⥬�.

:p.

:euserdoc.
