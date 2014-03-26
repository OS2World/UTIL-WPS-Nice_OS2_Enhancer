
// ��� �������� �� ᮮ�饭�ﬨ ���

// �� ��६���� - ���譨�.
VOID ClipperInputHook( HAB Application, PQMSG Message, PBYTE Discarding )
{
 // ����砥� � �몫�砥� �뤥����� ��ப � ⥪�⮢�� ����� � ������� ���.
 if( Clipper.Settings.Mouse_in_VIO )
  {
   // �᫨ � ���� ����� ��� �⦠� ������ ���:
   if( ( Message->msg == WM_BUTTON1DOWN ) ||
       ( Message->msg == WM_BUTTON1UP && Clipper.Settings.Mouse_in_VIO_sends_Copy ) )
    {
     // ������ ���� ࠬ��.
     HWND Frame_window = QueryFrameWindow( Message->hwnd );

     // �᫨ ���� ����� � ���� ࠡ�祩 ������:
     if( Message->hwnd == WinWindowFromID( Frame_window, FID_CLIENT ) )
      {
       // �᫨ �� ���� VIO:
       if( IsVIOWindow( Frame_window ) )
        {
         // �஢��塞, ����� �� ������ "Shift", �᫨ �� �ॡ����.
         BYTE Perform_action = 1;

         if( Message->msg == WM_BUTTON1DOWN )
          if( Clipper.Settings.Mouse_in_VIO_requires_Shift )
           if( !ShiftIsPressed() )
            Perform_action = 0;

         if( Perform_action )
          {
           // �롨ࠥ� ����⢨�.
           LONG Action = 0;
           if( Message->msg == WM_BUTTON1DOWN ) Action = SM_BEGIN_VIO_MARKING;
           if( Message->msg == WM_BUTTON1UP ) Action = SM_END_VIO_MARKING;

           // ����砥� �뤥�����. �� ���� ������ �� �� ⮣�, ��� ᮮ�饭�� �㤥�
           // ��ࠢ���� � ����, ��⮬� �� ��� ��砫� �����饣� �뤥����� ����
           // ������ ������� ᮮ�饭�� � �롮� ��ப� ���� � ᮮ�饭�� �� ���.
           if( Action == SM_BEGIN_VIO_MARKING ) Clipper_BeginVIOMarking( Frame_window );

           // �몫�砥� �뤥�����. ���뫠�� ᮮ�饭�� � ��⮪.
           if( Action == SM_END_VIO_MARKING ) WinPostQueueMsg( Enhancer.Modules.Clipper->Message_queue, SM_END_VIO_MARKING, (MPARAM) Frame_window, 0 );
          }
        }
      }
    }
  }

 // ���뫠�� � ���� ������ "Ctrl + V".
 if( Message->msg == WM_MARK )
  if( Message->mp1 == (MPARAM) MRK_POST_CTRL_V )
   Clipper_PostCtrlV( (HWND) Message->mp2 );

 // ����⠭�������� ᮤ�ন��� Clipboard.
 if( Message->msg == WM_MARK )
  if( Message->mp1 == (MPARAM) MRK_RESTORE_CLIPBOARD )
   WinPostQueueMsg( Enhancer.Modules.Clipper->Message_queue, SM_RESTORE_CLIPBOARD, 0, 0 );

 // ������.
 return;
}

// ��� �������� �� ᮮ�饭�ﬨ �� ���������� ���

// �� ��६���� - ���譨�.
VOID ClipperKbdInputHook( HAB Application, PQMSG Message, PBYTE Discarding )
{
 // ����砥� � �몫�砥� �뤥����� ��ப � ⥪�⮢�� ����� � ������� ����������.
 // �� ���� ������ ��᫥ ��ࠡ�⪨ ������ "^C/V", �⮡� �ᯮ�짮���� �� ⮦�,
 // � �� ��७����祭�� ������ 0..9 �� ��஢�� ���������.
 if( Clipper.Settings.CopyPaste_keys_in_VIO )
  {
   // ������ �� �����ﬨ �� ������.
   if( Message->msg == WM_CHAR )
    {
     // ����ਬ, ����� ������ �����.
     BYTE Scan_code = CHAR4FROMMP( Message->mp1 );
     SHORT State = SHORT1FROMMP( Message->mp1 );

     // �᫨ �� ������ "Insert":
     if( Scan_code == SC_INSERT || Scan_code == SC_NUM_0 ) if( !( State & KC_ALT ) )
      {
       // ������ ���� ࠬ��.
       HWND Frame_window = QueryFrameWindow( Message->hwnd );

       // �᫨ ������ ����� � ���� ࠡ�祩 ������:
       if( Message->hwnd == WinWindowFromID( Frame_window, FID_CLIENT ) )
        {
         // �᫨ �� ���� VIO � � ��� ����� �믮����� �뤥�����:
         if( IsVIOWindow( Frame_window ) ) if( Clipper_PermissionForMarking( Frame_window ) )
          {
           // �롨ࠥ� ����⢨�.
           LONG Thread_message = 0; BYTE Post = 0;

           if( State & KC_CTRL ) Thread_message = SM_COPY_VIO_TEXT;
           if( State & KC_SHIFT ) Thread_message = SM_PASTE_VIO_TEXT;

           // ����⢨� ���� �믮����� ⮫쪮 ��� ������, � ���뢠�� ᮮ�饭�� - �ᥣ��.
           if( !( State & KC_KEYUP ) ) Post = 1;

           // �᫨ ����⢨� ������ � ����� ���� �믮�����:
           if( Thread_message ) if( Post )
            {
             // ���뫠�� ᮮ�饭�� � ��⮪.
             WinPostQueueMsg( Enhancer.Modules.Clipper->Message_queue, Thread_message, (MPARAM) Frame_window, 0 );
            }

           // �᫨ ����⢨� ������ - ᮮ�饭�� ������ ���� ��襭�.
           if( Thread_message ) *Discarding = 1;
          }
        }
      }
    }
  }

 // ����⠭�������� ���ﭨ� ����������, �᫨ ��� �뫮 �������� �� �६� ��८�।������ ������.
 if( Message->msg == WM_CHAR )
  {
   SHORT State = SHORT1FROMMP( Message->mp1 );
   if( State & KC_KEYUP ) if( PMKeyboardStateIsChanged() ) RestorePMKeyboardState();
  }

 // ������.
 return;
}
