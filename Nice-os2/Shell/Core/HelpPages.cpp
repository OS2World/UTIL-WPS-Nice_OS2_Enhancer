// ��⮤� ��� ࠡ��� � �ࠢ�筨����.
#define Help                  HelpPages_Help 
#define CloseExistingHelpPage HelpPages_CloseExistingHelpPage

// ��� ��⮤ ��� ������祭�� ����� ���

VOID HelpPages_Start( VOID )
{
 #ifdef HelpPages
 bzero( &HelpPages, sizeof( HelpPages ) );
 #endif

 // ������.
 return;
}
