
// ��� ��ࠡ��稪 ᮡ�⨩, ��뢠���� �����窮� WPS �� ����祭�� ���⠢�� ���

// Application ��।���� �ਫ������, Lockup_frame - ���� ���⠢��.
ULONG EXPENTRY Hook_LockupHook (HAB Application, HWND Lockup_frame)
{
  // ����������, �� �맢��� ���⠢��.
  Krnl_Environment.RTSettings.System_is_locked = 1;
  Krnl_Environment.RTSettings.Lockup_frame = Lockup_frame;
  Krnl_Environment.RTSettings.Screen_Saver_can_be_closed = 1;

  // ������.
  return 0;
}

// ��� ������ �� ���ﭨ�� �����窨 OS/2 ���

// Message - ᮮ�饭��, ���஥ ��।����� ���� ࠡ�祣� �⮫�.
VOID LockupSendMsgHook (PSMHSTRUCT Message)
{
  // �᫨ �맢��� ���⠢�� � �ந�室�� ��४��祭�� � ��㣮� ����:
  if (Krnl_Environment.RTSettings.System_is_locked)
   if (Message->msg == WM_ACTIVATE) if (Message->mp1 == (MPARAM) 1)
   {
     // �᫨ ���� ���⠢�� ��� ��� ��� ���� - ���⠢�� �� �맢���.
     if (!WinIsWindow (WinQueryAnchorBlock (Krnl_Environment.RTSettings.Lockup_frame), Krnl_Environment.RTSettings.Lockup_frame) ||
         !WinIsWindowVisible (Krnl_Environment.RTSettings.Lockup_frame))
     {
       Krnl_Environment.RTSettings.System_is_locked = 0;
     }
     // ���� - �᫨ �뫮 �맢��� ���� �ࠢ�� �� F1, �࠭�⥫� �࠭� ����뢠�� �����.
     else
     {
       // �஢��塞 ����.
       if (FrameType (Message->hwnd) == FT_FLAT) Krnl_Environment.RTSettings.Screen_Saver_can_be_closed = 0;
     }
   }

  // ������.
  return;
}
