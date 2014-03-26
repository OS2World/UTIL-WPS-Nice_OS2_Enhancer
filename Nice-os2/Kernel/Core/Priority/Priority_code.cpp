
// ��� ������� ���祭�� �ਮ��� ��� �ਫ������ ���

// Frame_window - ���� �ਫ������, Class � Delta - ���祭�� �ਮ���.
VOID Priority_SetPriorityLevel( HWND Frame_window, LONG Class, LONG Delta )
{
 // ������ �ਫ������, ᮧ���襥 ����.
 PID Process_ID = QueryWindowRealProcessID( Frame_window );

 // �᫨ ��� �������⭮ - ������.
 if( Process_ID == 0 ) return;

 // �஡㥬 �������� �ਮ��� �� ����.
 APIRET Result = DosSetPriority( PRTYS_PROCESSTREE, Class, Delta, Process_ID );

 // �᫨ �� ᤥ���� �� 㤠����:
 if( Result != NO_ERROR )
  {
   // ���������� ���祭�� �ਮ��� ��� ����.
   SetProperty( Frame_window, PRP_PRIORITY_CLASS, &Class );
   SetProperty( Frame_window, PRP_PRIORITY_DELTA, &Delta );

   // ������ ���� ࠡ�祣� �⮫�.
   HWND Desktop = QueryDesktopWindow();

   // ���뫠�� � ��।� ���� ࠡ�祣� �⮫� ᮮ�饭�� WM_MARK. �ਮ��� ����� �㤥� �������� �� �६� ��� ����祭��.
   HMQ Desktop_queue = WinQueryWindowULong( Desktop, QWL_HMQ );
   WinPostQueueMsg( Desktop_queue, WM_MARK, (MPARAM) MRK_SET_PRIORITY, (MPARAM) Frame_window );

   // ���뫠�� ⠪�� �� ᮮ�饭�� � ��।� ����. ����⮢� ���� �ᯮ����� �� �� ��।�, �� � ���� ࠡ�祣� �⮫�, ���⮬� ��ன ࠧ ���뫠�� �� ᮮ�饭�� �� ����.
   HMQ Window_queue = WinQueryWindowULong( Frame_window, QWL_HMQ );
   if( Window_queue != Desktop_queue ) WinPostQueueMsg( Window_queue, WM_MARK, (MPARAM) MRK_SET_PRIORITY, (MPARAM) Frame_window );
  }

 // ������.
 return;
}
