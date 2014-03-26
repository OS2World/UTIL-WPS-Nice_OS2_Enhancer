
// ��� �������� �� ᮮ�饭�ﬨ ���

// �� ��६���� - ���譨�.
VOID VIOMenuManagerInputHook( HAB Application, PQMSG Message, PBYTE Discarding )
{
 // �����塞 ���� SSH �� ����⨨ ������ ��� � ���� ���⨭��.
 if( VIOMenuManager.Settings.SSH_Commands )
  {
   // �᫨ ���� ����砥� ᮮ�饭�� � ����⨨ ������ ���:
   if( Message->msg == WM_BUTTON1DOWN || Message->msg == WM_BUTTON2DOWN || Message->msg == WM_BUTTON3DOWN )
    {
     // �᫨ ���� ����� � ���� ���⨭�� � ���� VIO:
     if( IsMenuWindow( Message->hwnd ) )
      {
       HWND Frame_window = NULLHANDLE;
       HWND Parent_window = WinQueryWindow( Message->hwnd, QW_PARENT );
       if( IsFrameWindow( Parent_window ) ) Frame_window = Parent_window;

       if( Frame_window )
        {
         if( IsVIOWindow( Frame_window ) &&
             WinWindowFromID( Frame_window, FID_SYSMENU ) == Message->hwnd )
          {
           // �᫨ �� ���� SSH - ���� ����� ������� �� 䠩��� ����஥�,
           // � ⠪�� ����� ��������� ���짮��⥫�� 䠩��, �᫨ ��� ����.
           if( WindowIsCreatedBy( APP_SSH, Frame_window ) )
            {
             // ���뫠�� ᮮ�饭�� � ��⮪.
             // ����� ��� �㤥� ��ࠡ�⠭�, � ��।� ���� �ਤ�� ᮮ�饭�� WM_MARK.
             INT Markers_quantity = 1;
             WinPostQueueMsg( Enhancer.Modules.VIOMenuManager->Message_queue, SM_CHECK_ALL_COMMANDS, (MPARAM) Frame_window, (MPARAM) Markers_quantity );
            }
          }
        }
      }
    }

   // ������塞 � ���� ��ப� ��᫥ ⮣�, ��� ��� �뫨 ��⠭� ��⮪��.
   // �� ����⢨� ����� �믮����� ⮫쪮 � ��ࠡ��稪� ᮮ�饭�� ���� VIO.
   if( Message->msg == WM_MARK )
    {
     HWND Frame_window = (HWND) Message->mp2;
     if( Message->mp1 == (MPARAM) MRK_ADD_VIO_MENU_ITEMS ) VIOMenuManager_AddItems( Frame_window );
     if( Message->mp1 == (MPARAM) MRK_SHOW_VIO_MENU_ITEMS ) VIOMenuManager_ShowItems( Frame_window );
    }

   // ��ࠢ�塞 ��࠭��� ������� � ����.
   if( Message->msg == WM_SYSCOMMAND )
    {
     // ������ ���祭�� ID ��࠭��� ��ப�.
     ULONG Item_ID = (ULONG) Message->mp1;

     // �᫨ �� ���� �� ������:
     if( VIOMenuManager_IsSSHCommandMenuItem( Item_ID ) )
      {
       // ������ ���� ࠬ��.
       HWND Frame_window = QueryFrameWindow( Message->hwnd );

       // �᫨ �� ⥪�⮢�� ����:
       if( IsVIOWindow( Frame_window ) )
        {
         // �᫨ �� ���� SSH:
         if( WindowIsCreatedBy( APP_SSH, Frame_window ) )
          {
           // �᫨ ������� ������� ��� �⮣� ����:
           INT File_number = VIOMenuManager_GetCommandSubset( Frame_window );

           if( File_number != -1 )
            {
             // ����砥� ��࠭��� ��ப�.
             CHAR String[ SIZE_OF_ITEM_TEXT ] = ""; ULONG Length = SIZE_OF_ITEM_TEXT;
             VIOMenuManager_QueryCommandItemText( Frame_window, Item_ID, String, Length );

             // ��室�� �� � ᯨ᪥ ������.
             INT Position = VIOMenuManager_FindCommandInList( File_number, String );

             // �᫨ ��� �뫠 �������:
             if( Position != -1 )
              {
               // ���뫠�� ᮮ�饭�� � ��⮪.
               WinPostQueueMsg( Enhancer.Modules.VIOMenuManager->Message_queue, SM_POST_VIO_MENU_ITEM, (MPARAM) Frame_window, (MPARAM) Position );
              }
            }

           // ����饭�� ������ ���� ��襭�.
           *Discarding = 1;
          }
        }
      }
    }
  }

 // ������.
 return;
}

// ��� �������� �� ᮮ�饭�ﬨ ���

// �� ��६���� - ���譨�.
VOID VIOMenuManagerKbdInputHook( HAB Application, PQMSG Message, PBYTE Discarding )
{
 // �����塞 ���� SSH �� ����⨨ "Shift + Esc" � �����뢠�� ������� � ���� �� ����⨨ "Alt + ~".
 if( VIOMenuManager.Settings.SSH_Commands )
  {
   // �᫨ ���� ����砥� ᮮ�饭�� � ����⨨ �� �������:
   if( Message->msg == WM_CHAR )
    {
     // ����ਬ, ����� ������ �����.
     BYTE Scan_code = CHAR4FROMMP( Message->mp1 );
     SHORT State = SHORT1FROMMP( Message->mp1 );

     // �᫨ �� �, �� ��� �㦭�:
     ULONG Action = 0; ULONG Add_items = 1; ULONG Show_items = 2;
     if( Scan_code == SC_ESC ) if( State & KC_SHIFT ) Action = Add_items;
     if( Scan_code == SC_BACKQUOTE ) if( State & KC_ALT ) if( VIOMenuManager.Settings.Use_AltTilde ) Action = Show_items;

     if( Action )
      {
       // �᫨ �� ��ࢮ� ����⨥ �� �������:
       if( !( State & KC_KEYUP ) ) if( !( State & KC_PREVDOWN ) )
        {
         // ������ ���� ࠬ��.
         HWND Frame_window = QueryFrameWindow( Message->hwnd );

         // �᫨ �� ⥪�⮢�� ����:
         if( Frame_window ) if( IsVIOWindow( Frame_window ) )
          {
           // �᫨ �� ���� SSH - ���� ����� ������� �� 䠩��� ����஥�,
           // � ⠪�� ����� ��������� ���짮��⥫�� 䠩��, �᫨ ��� ����.
           if( WindowIsCreatedBy( APP_SSH, Frame_window ) )
            {
             // ���뫠�� ᮮ�饭�� � ��⮪.
             // ����� ��� �㤥� ��ࠡ�⠭�, � ��।� ���� �ਤ�� ᮮ�饭�� WM_MARK.
             INT Markers_quantity = 1; if( Action == Show_items ) Markers_quantity = 2;
             WinPostQueueMsg( Enhancer.Modules.VIOMenuManager->Message_queue, SM_CHECK_ALL_COMMANDS, (MPARAM) Frame_window, (MPARAM) Markers_quantity );
            }
          }
        }

       // ����饭�� �� ������ �맮�� ᯨ᪠ ����⢨� ������ ���� ��襭�.
       if( Action == Show_items ) *Discarding = 1;
      }
    }
  }

 // ������.
 return;
}

