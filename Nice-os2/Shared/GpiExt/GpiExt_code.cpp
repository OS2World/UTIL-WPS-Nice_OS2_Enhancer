
// ��� ����뢠�� ������� 梥⮢ � ���� ���

// Presentation_space - ����࠭�⢮ �⮡ࠦ����.
VOID GpiExt_ForceColorPaletteToRGB( HPS Presentation_space )
{
 // ��ॢ���� ����࠭�⢮ �⮡ࠦ���� � ���ﭨ�, ����� �� ���祭��, ��।������
 // ��⮤�� �ᮢ����, ���ਭ������� ��� RGB-梥�. ��᫥ �⮣� ���祭�� 梥⮢ ����
 // "CLR_*" ��� "SYSCLR_*" 㦥 �� ����� �ᯮ�짮������, � ��� �ᮢ���� ���� �ਬ�����
 // ���祭�� ���� "RGB_*". ��� ��� ������ 㦥 �� ����� ���� ����⠭������, � ������
 // ࠬ�� ��� ���� ⠪ ����㯠�� �����.
 GpiCreateLogColorTable( Presentation_space, 0, LCOLF_RGB, 0, 0, NULL );

 // ������.
 return;
}

