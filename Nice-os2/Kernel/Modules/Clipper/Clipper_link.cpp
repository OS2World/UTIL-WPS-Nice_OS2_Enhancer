
// ��� ����頥�, ����祭� �� ����ன�� ��� ���� VIO ���

BYTE Clipper_CopyPasteKeysCanBeUsedInVIOWindows( VOID )
{
 // �஢��塞 ����ன��.
 if( Clipper.Settings.CopyPaste_keys_in_VIO ) return 1;

 // ������.
 return 0;
}
