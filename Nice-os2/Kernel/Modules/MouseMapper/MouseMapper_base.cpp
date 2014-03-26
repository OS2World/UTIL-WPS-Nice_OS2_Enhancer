
// ��� ���������� ��� ��⠢��� ⥪�� �� ����⨨ �� ������ ��� ���

// Input_window - ����, � ����� ࠡ�⠥� ���짮��⥫�, Action - ����⢨�.
// Accelerator - ���祭�� ��� ᮮ�饭�� WM_COMMAND, �᫨ ��� �뫮 �������.
VOID MouseMapper_ClipboardMouseAction( HWND Input_window, LONG Action, LONG Accelerator )
{
 // �롨ࠥ� ����⢨�.
 BYTE Perform_copy = 0; BYTE Perform_paste = 0;

 if( Action == MOUSE_CLIPBOARD_COPY ) Perform_copy = 1;
 if( Action == MOUSE_CLIPBOARD_PASTE ) Perform_paste = 1;

 // ������ ���� ࠬ��.
 HWND Frame_window = QueryFrameWindow( Input_window );

 // �᫨ ���� ����� � ���� ࠡ�祩 ������:
 if( Input_window == WinWindowFromID( Frame_window, FID_CLIENT ) )
  {
   // �᫨ �� ���� VIO:
   if( IsVIOWindow( Frame_window ) )
    {
     // ���뫠�� ᮮ�饭�� � ��⮪.
     LONG Thread_message = SM_COPY_VIO_TEXT;
     if( Perform_paste ) Thread_message = SM_PASTE_VIO_TEXT;

     WinPostQueueMsg( Enhancer.Modules.Clipper->Message_queue, Thread_message, (MPARAM) Frame_window, 0 );

     // ����� ��祣� ������ �� ����, ������.
     return;
    }
  }

 // �᫨ ����� �᪮�⥫�:
 if( Accelerator != 0 )
  {
   // ���뫠�� �������� ���� �ਫ������ ᮮ�饭�� � ⮬, �� ������ ���� �믮����� ����⢨�, �易���� � �⨬ �᪮�⥫��.
   WinPostMsg( QueryMainWindow( Frame_window ), WM_COMMAND, (MPARAM) Accelerator, MPFROM2SHORT( CMDSRC_ACCELERATOR, 0 ) );
  }
 // � �᫨ �� �� �����:
 else
  {
   // ���⠢�塞 ᮮ�饭�� � ����⨨ ������.
   INT New_scan_code = SC_INSERT;
   INT Modifiers = KC_CTRL; if( Perform_paste ) Modifiers = KC_SHIFT;

   MPARAM First_parameter_1 = 0; MPARAM Second_parameter_1 = 0;
   MPARAM First_parameter_2 = 0; MPARAM Second_parameter_2 = 0;

   ComposeWMCharMessage( &First_parameter_1, &Second_parameter_1, &First_parameter_2, &Second_parameter_2, New_scan_code, 0, Modifiers );

   // ���塞 ���ﭨ� ���������� �� �६� ����⢨� ᮮ�饭��.
   QMSG Message = {0};
   ChangePMKeyboardState( &Message, New_scan_code, Modifiers, 0 );

   // ���뫠�� � ���� ᮮ�饭�� � ����⨨ ������.
   WinPostMsg( Input_window, WM_CHAR, First_parameter_1, Second_parameter_1 );

   // ���뫠�� � ��।� ���� ᮮ�饭�� WM_MARK. ����� ��� �㤥� ����祭�, ���ﭨ� ����� �㤥� ������ �����.
   HMQ Message_queue = WinQueryWindowULong( Input_window, QWL_HMQ );
   WinPostQueueMsg( Message_queue, WM_MARK, (MPARAM) MRK_KBD_MODIFIERS, 0 );

   // ���뫠�� � ���� ᮮ�饭�� �� �⦠⨨ ������.
   WinPostMsg( Input_window, WM_CHAR, First_parameter_2, Second_parameter_2 );
  }

 // ������.
 return;
}
