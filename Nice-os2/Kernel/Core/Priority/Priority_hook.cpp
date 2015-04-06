
// ��� �������� �� ᮮ�饭�ﬨ ���

// �� ��६���� - ���譨�.
VOID PriorityInputHook( PQMSG Message )
{
 // ��⠭�������� �ਮ��� �ਫ������.
 // �� ᮮ�饭�� ���뫠���� ����⥫�� � ���� ࠡ�祣� �⮫�, ⠪ ��� �� ���� ����� ������ �ਮ���� ��� �ਫ������.
 if( Message->hwnd == NULLHANDLE ) if( Message->msg == WM_MARK )
  if( Message->mp1 == (MPARAM) MRK_SET_PRIORITY )
   {
    // ������ �ॡ㥬� ���祭�� �ਮ��⮢.
    HWND Frame_window = (HWND) Message->mp2;

    LONG Class = PRTYC_NOCHANGE; FindProperty( Frame_window, PRP_PRIORITY_CLASS, &Class );
    LONG Delta = PRTYD_NORMAL;   FindProperty( Frame_window, PRP_PRIORITY_DELTA, &Delta );

    // �᫨ ��� ������:
    if( Class != PRTYC_NOCHANGE )
     {
      // ������ �ਫ������, ᮧ���襥 ����.
      PID Process_ID = QueryWindowRealProcessID( Frame_window );

      // �᫨ ��� �����⭮ - �����塞 �ਮ���.
      if( Process_ID != 0 ) DosSetPriority( PRTYS_PROCESSTREE, Class, Delta, Process_ID );

      // ����뢠�� ���祭��.
      Class = PRTYC_NOCHANGE; SetProperty( Frame_window, PRP_PRIORITY_CLASS, &Class );
      Delta = PRTYD_NORMAL;   SetProperty( Frame_window, PRP_PRIORITY_DELTA, &Delta );
     }
   }

 // ������.
 return;
}
