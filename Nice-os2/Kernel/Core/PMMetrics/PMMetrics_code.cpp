
// ��� ������ �ਭ� ࠬ�� ���� ���

// Frame_window - ���� ࠬ��. �����頥��� ���祭�� - �ਭ� ࠬ��.
INT PMMetrics_FrameWidth( HWND Frame_window )
{
 // ������, ��� �룫廊� ࠬ�� ����.
 LONG Frame_type = FrameType( Frame_window );

 // �᫨ ���� ����� ������ ࠬ��:
 if( Frame_type == FT_NORMAL )
  {
   // ������ ���� ࠡ�祣� �⮫�.
   HWND Desktop = QueryDesktopWindow();

   // ������ �ਭ� ࠬ�� �� 㬮�砭��.
   INT Normal_frame = Min( WinQuerySysValue( Desktop, SV_CXSIZEBORDER ), WinQuerySysValue( Desktop, SV_CYSIZEBORDER ) );

   // �����頥� �ਭ� ࠬ��.
   return Normal_frame;
  }

 // �᫨ ���� ����� ࠬ�� ����ﭭ��� ࠧ��� ��� �� ���᪮� ����:
 if( Frame_type == FT_CONST || Frame_type == FT_FLAT )
  {
   // ������ ���� ࠡ�祣� �⮫�.
   HWND Desktop = QueryDesktopWindow();

   // ������ �ਭ� ࠬ�� ����.
   INT Const_frame = Min( WinQuerySysValue( Desktop, SV_CXDLGFRAME ), WinQuerySysValue( Desktop, SV_CYDLGFRAME ) );

   // �����頥� �ਭ� ࠬ��.
   return Const_frame;
  }

 // � �᫨ ���� ����� ࠬ�� � 1 ���:
 if( Frame_type == FT_POINT )
  {
   // �����頥� �ਭ� ࠬ��.
   return 1;
  }

 // �᫨ � ���� ��� ࠬ�� - �����頥� ����.
 return 0;
}
