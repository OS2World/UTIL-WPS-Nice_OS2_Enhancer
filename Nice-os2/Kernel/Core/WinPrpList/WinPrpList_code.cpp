
// ��� ��뢠���� த�⥫�᪨� ����ᮬ �� �஢�થ ������ � ᯨ᪥ ���

// Position - ���� � ᯨ᪥, Frame_window - ���� ��� �஢�ન.
BYTE WinPrpList_IsItemEqualsTo( INT Position, LISTKEY Frame_window )
{
 // �஢��塞 ����.
 if( WinPrpList.Properties_list[ Position ].Frame_window == Frame_window ) return 1;

 // ������.
 return 0;
}

// ��� ��뢠���� த�⥫�᪨� ����ᮬ �� �஢�થ ������ � ᯨ᪥ ���

// Position - ���� � ᯨ᪥.
BYTE WinPrpList_IsItemEmpty( INT Position )
{
 // �஢��塞 ����.
 return WinPrpList_IsItemEqualsTo( Position, NULLHANDLE );
}

// ��� ��뢠���� த�⥫�᪨� ����ᮬ �� ���������� ������ � ᯨ᮪ ���

// Position - ���� � ᯨ᪥, Frame_window - ���� ࠬ�� � ᯨ᪥.
VOID WinPrpList_CreateNewItem( INT Position, LISTKEY Frame_window )
{
 // ������塞 ���� � ᯨ᮪.
 WinPrpList.Properties_list[ Position ].Frame_window = Frame_window;

 // ������ ᢮��⢠ �� 㬮�砭��.
 WinPrpList.Properties_list[ Position ].Room = NO_ROOM;

 // ������.
 return;
}

// ��� ��뢠���� த�⥫�᪨� ����ᮬ �� 㤠����� ������ �� ᯨ᪠ ���

// Position - ���� � ᯨ᪥.
VOID WinPrpList_DiscardItem( INT Position )
{
 // �᫨ ���箪 �� ����㦥� � ��᪠ - ���� �᢮������ ������.
 if( WinPrpList.Properties_list[ Position ].Icon_was_loaded )
 {
  // ���뫠�� ᮮ�饭�� � ��⮪.
  WinPostQueueMsg( Enhancer.Modules.Changer->Message_queue, SM_FREE_FILE_ICON, (MPARAM) WinPrpList.Properties_list[ Position ].Icon, 0 );
 }

 // ����塞 �� ᯨ᪠ ᢥ����� �� ����.
 bzero( &WinPrpList.Properties_list[ Position ], sizeof( WINDOWPROPERTY ) );

 // ������.
 return;
}

// ��� ��뢠���� த�⥫�᪨� ����ᮬ �� ��������� ������ � ᯨ᪥ ���

// Position - ���� � ᯨ᪥, Property - ᢮��⢮ ����.
PVOID WinPrpList_GetPointerForData( INT Position, LISTPRP Property )
{
 // �롨ࠥ� 㪠��⥫�.
 PVOID Pointer = NULL;

 switch( Property )
  {
   case PRP_TITLE:            Pointer = WinPrpList.Properties_list[ Position ].Title;                   break;
   case PRP_ICON:             Pointer = &WinPrpList.Properties_list[ Position ].Icon;                   break;
   case PRP_ICON_WAS_LOADED:  Pointer = &WinPrpList.Properties_list[ Position ].Icon_was_loaded;        break;
   case PRP_BORDER:           Pointer = &WinPrpList.Properties_list[ Position ].Frame_width;            break;
   case PRP_BUTTONS:          Pointer = &WinPrpList.Properties_list[ Position ].Buttons;                break;
   case PRP_ACTIONS:          Pointer = &WinPrpList.Properties_list[ Position ].Actions;                break;
   case PRP_CONTROLS:         Pointer = &WinPrpList.Properties_list[ Position ].Advanced_controls;      break;

   case PRP_RETARDS:          Pointer = &WinPrpList.Properties_list[ Position ].Retards_performed;      break;

   case PRP_TITLEBAR_PERF:    Pointer = &WinPrpList.Properties_list[ Position ].TitleBar_performer;     break;
   case PRP_MINMAX_PERF:      Pointer = &WinPrpList.Properties_list[ Position ].MinMax_performer;       break;
   case PRP_MENU_PERF:        Pointer = &WinPrpList.Properties_list[ Position ].Menu_performer;         break;

   case PRP_ACTIVATED:        Pointer = &WinPrpList.Properties_list[ Position ].Activated;              break;
   case PRP_MAXIMIZED:        Pointer = &WinPrpList.Properties_list[ Position ].Maximized;              break;
   case PRP_ROOM:             Pointer = &WinPrpList.Properties_list[ Position ].Room;                   break;

   case PRP_PERFORMED_ACTION: Pointer = &WinPrpList.Properties_list[ Position ].Performed_action;       break;
   case PRP_PREVIOUS_WIDTH:   Pointer = &WinPrpList.Properties_list[ Position ].Previous_width;         break;
   case PRP_PREVIOUS_HEIGHT:  Pointer = &WinPrpList.Properties_list[ Position ].Previous_height;        break;

   case PRP_CLOSE_RECEIVED:   Pointer = &WinPrpList.Properties_list[ Position ].Close_message_received; break;

   case PRP_TIME_OF_ARRANGE:  Pointer = &WinPrpList.Properties_list[ Position ].Time_of_arrange;        break;
   case PRP_VIO_FONT_DIALOG:  Pointer = &WinPrpList.Properties_list[ Position ].VIO_font_dialog;        break;

   case PRP_PRIORITY_CLASS:   Pointer = &WinPrpList.Properties_list[ Position ].Priority_class;         break;
   case PRP_PRIORITY_DELTA:   Pointer = &WinPrpList.Properties_list[ Position ].Priority_delta;         break;

   case PRP_EXENAME:          Pointer = WinPrpList.Properties_list[ Position ].Exe_name;                break;
   case PRP_EXEPATH:          Pointer = WinPrpList.Properties_list[ Position ].Exe_path;                break;
  }

 // �����頥� 㪠��⥫�.
 return Pointer;
}

// ��� ��뢠���� த�⥫�᪨� ����ᮬ �� ��������� ������ � ᯨ᪥ ���

// Property - ᢮��⢮ ����.
ULONG WinPrpList_GetSizeOfData( LISTPRP Property )
{
 // ������ ࠧ��� ������.
 ULONG Size_of_data = 0;

 switch( Property )
  {
   case PRP_TITLE:            Size_of_data = SIZE_OF_TITLE;                                                    break;
   case PRP_ICON:             Size_of_data = sizeof( WinPrpList.Properties_list[ 0 ].Icon );                   break;
   case PRP_ICON_WAS_LOADED:  Size_of_data = sizeof( WinPrpList.Properties_list[ 0 ].Icon_was_loaded );        break;
   case PRP_BORDER:           Size_of_data = sizeof( WinPrpList.Properties_list[ 0 ].Frame_width );            break;
   case PRP_BUTTONS:          Size_of_data = sizeof( WinPrpList.Properties_list[ 0 ].Buttons );                break;
   case PRP_ACTIONS:          Size_of_data = sizeof( WinPrpList.Properties_list[ 0 ].Actions );                break;
   case PRP_CONTROLS:         Size_of_data = sizeof( WinPrpList.Properties_list[ 0 ].Advanced_controls );      break;

   case PRP_RETARDS:          Size_of_data = sizeof( WinPrpList.Properties_list[ 0 ].Retards_performed );      break;

   case PRP_TITLEBAR_PERF:    Size_of_data = sizeof( WinPrpList.Properties_list[ 0 ].TitleBar_performer );     break;
   case PRP_MINMAX_PERF:      Size_of_data = sizeof( WinPrpList.Properties_list[ 0 ].MinMax_performer );       break;
   case PRP_MENU_PERF:        Size_of_data = sizeof( WinPrpList.Properties_list[ 0 ].Menu_performer );         break;

   case PRP_ACTIVATED:        Size_of_data = sizeof( WinPrpList.Properties_list[ 0 ].Activated );              break;
   case PRP_MAXIMIZED:        Size_of_data = sizeof( WinPrpList.Properties_list[ 0 ].Maximized );              break;
   case PRP_ROOM:             Size_of_data = sizeof( WinPrpList.Properties_list[ 0 ].Room );                   break;

   case PRP_PERFORMED_ACTION: Size_of_data = sizeof( WinPrpList.Properties_list[ 0 ].Performed_action );       break;
   case PRP_PREVIOUS_WIDTH:   Size_of_data = sizeof( WinPrpList.Properties_list[ 0 ].Previous_width );         break;
   case PRP_PREVIOUS_HEIGHT:  Size_of_data = sizeof( WinPrpList.Properties_list[ 0 ].Previous_height );        break;

   case PRP_CLOSE_RECEIVED:   Size_of_data = sizeof( WinPrpList.Properties_list[ 0 ].Close_message_received ); break;

   case PRP_TIME_OF_ARRANGE:  Size_of_data = sizeof( WinPrpList.Properties_list[ 0 ].Time_of_arrange );        break;
   case PRP_VIO_FONT_DIALOG:  Size_of_data = sizeof( WinPrpList.Properties_list[ 0 ].VIO_font_dialog );        break;

   case PRP_PRIORITY_CLASS:   Size_of_data = sizeof( WinPrpList.Properties_list[ 0 ].Priority_class );         break;
   case PRP_PRIORITY_DELTA:   Size_of_data = sizeof( WinPrpList.Properties_list[ 0 ].Priority_delta );         break;

   case PRP_EXENAME:          Size_of_data = SIZE_OF_NAME;                                                     break;
   case PRP_EXEPATH:          Size_of_data = SIZE_OF_PATH;                                                     break;
  }

 // �����頥� ࠧ��� ������.
 return Size_of_data;
}

// ��� �������� � ᯨ᮪ ᢮��⢠ ��� ���� ࠬ�� ���

// Frame_window - ���� ࠬ��, Property - ᢮��⢮, Data - ����� ��� ����.
VOID WinPrpList_SetProperty( HWND Frame_window, LONG Property, PVOID Data )
{
 // ��室�� ����.
 PrpList_SetProperty( &WinPrpList.Descendant, Frame_window, Property, Data );

 // ������.
 return;
}

// ��� ��室�� ���� � ᯨ᪥ ���

// Frame_window - ���� ࠬ��, Property - ᢮��⢮, Data - ����� ��� ����.
VOID WinPrpList_FindProperty( HWND Frame_window, LONG Property, PVOID Data )
{
 // ��室�� ����.
 PrpList_FindProperty( &WinPrpList.Descendant, Frame_window, Property, Data );

 // ������.
 return;
}

// ��� ����뢠�� ᢮��⢠ ����������� ���� ���

// Frame_window - ���� ࠬ��.
VOID WinPrpList_DiscardUnusedProperties( HWND Frame_window )
{
 // ��ᬠ�ਢ��� ᯨ᮪.
 for( INT Count = PrpList_GetTopItemPosition( &WinPrpList.Descendant ); Count >= 0; Count -- )
  {
   // �஢��塞 ����.
   if( WinPrpList_IsItemEmpty( Count ) ) continue;

   BYTE Discard_properties = 0;
   HWND Window = WinPrpList.Properties_list[ Count ].Frame_window;

   if( Window == Frame_window ) Discard_properties = 1;
   else if( !WinIsWindow( WinQueryAnchorBlock( Window ), Window ) ) Discard_properties = 1;

   // ����塞 ��� �� ᯨ᪠, �᫨ �� �ॡ����.
   if( Discard_properties ) WinPrpList_DiscardItem( Count );
  }

 // ������.
 return;
}

// ��� �஢����, ���� �� ���� ࠬ�� � ᯨ᪥ ���

// Frame_window - ���� ��� ���᪠.
// �����頥��� ���祭�� - 1, �᫨ ���� �������, ���� 0.
BYTE WinPrpList_PropertiesForDrawingAreDetected( HWND Frame_window )
{
 // �饬 ���� � ᯨ᪥.
 HPOINTER Icon = NULLHANDLE; WinPrpList_FindProperty( Frame_window, PRP_ICON, &Icon );
 if( Icon != NULLHANDLE ) return 1;

 CHAR Title[ SIZE_OF_TITLE ] = ""; WinPrpList_FindProperty( Frame_window, PRP_TITLE, Title );
 if( Title[ 0 ] != 0 ) return 1;

 LONG Buttons = NO_ACTION; WinPrpList_FindProperty( Frame_window, PRP_BUTTONS, &Buttons );
 if( Buttons != NO_ACTION ) return 1;

 // ������.
 return 0;
}

