
// ��� ����頥�, ����祭� �� ����ன�� ��� ���� VIO ���

BYTE VIOFontManager_FontsCanBeChangedInVIOWindows( VOID )
{
 // �஢��塞 ����ன��.
 if( VIOFontManager.Settings.Change_VIO_font_metrics ) return 1;

 // ������.
 return 0;
}
