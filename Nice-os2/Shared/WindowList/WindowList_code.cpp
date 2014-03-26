
// ��� ��ࠢ��� ��������� ���� ���

// Window_title - ���������, Required_length - �ॡ㥬�� �����.
VOID WindowList_CorrectWindowTitle( HWND Frame_window, PCHAR Window_title, INT Required_length )
{
 // ������ ����� ��ப�.
 INT String_length = strlen( Window_title );

 // ����塞 � ��������� �㪢� ࠧ�뢠 ��ப� � ᫮�� "Applet Viewer".
 {
  INT Step;

  for( Step = 0; Step < 4; Step ++ )
   {
    // ������ ᫮�� ��� 㤠�����.
    CHAR Word_for_removing[ 25 ] = ""; INT Length = 1;
    if( Step == 0 ) { Word_for_removing[ 0 ] = 0x0D; Word_for_removing[ 1 ] = 0;   }
    if( Step == 1 ) { Word_for_removing[ 0 ] = 0x0A; Word_for_removing[ 1 ] = 0;   }
    if( Step == 2 ) { strcpy( Word_for_removing, "Applet Viewer: " ); Length = 15; }
    if( Step == 3 ) { strcpy( Word_for_removing, ".class" );          Length = 6;  }

    // ��ᬠ�ਢ��� ��ப�.
    {
     INT Count = 0;

     while( Window_title[ Count ] != 0 )
      {
       // �஢��塞, ���� �� ᮢ�������.
       BYTE Words_is_equally = 1; INT Position = 0;
       while( Word_for_removing[ Position ] != 0 )
        {
         if( Window_title[ Count + Position ] != Word_for_removing[ Position ] )
          { Words_is_equally = 0; break; }

         Position ++;
        }

       // �᫨ ��� ���� - 㤠�塞 ᫮��.
       if( Words_is_equally )
        {
         // ����� ࠧ�뢠 ��ப� ���� ���⠢��� �஡��.
         if( Window_title[ Count ] == 0x0A && Window_title[ Count - 1 ] != ' ' )
          {
           Window_title[ Count ] = ' ';
          }
         // ����塞 ᫮��.
         else
          {
           strcpy( &Window_title[ Count ], &Window_title[ Count + Length ] );
          }
        }

       // �����稢��� ���稪.
       Count ++;
      }
    }
   }
 }

 // �᫨ ��������� ᫨誮� ������ - ������塞 � ���� ������稥.
 if( String_length >= Required_length - 1 )
  {
   // ��ப� ������ �����稢����� �㪢��.
   INT Points_length = 3; INT Position = Required_length - 1 - Points_length;

   INT Count = 0;

   while( Count < 100000 )
    {
     CHAR Letter = Window_title[ Position - 1 ];
     if( Letter < 48 || ( Letter > 57 && Letter < 61 ) ) Position --;
     else break;
    }

   // ������塞 ������稥.
   strncpy( &Window_title[ Position ], "...", Points_length );
   Window_title[ Position + Points_length ] = 0;
  }

 // �᫨ ��������� ᮤ�ন� ��� �ᯮ��塞��� 䠩�� - �ਢ���� ��� � ���� "���.exe"
 if( String_length > 4 )
  if( Window_title[ String_length - 4 ] == '.' )
   if( !strfind( " ", Window_title ) )
    if( ( Window_title[ String_length - 3 ] == 'E' &&
          Window_title[ String_length - 2 ] == 'X' &&
          Window_title[ String_length - 1 ] == 'E' ) ||
        ( Window_title[ String_length - 3 ] == 'e' &&
          Window_title[ String_length - 2 ] == 'x' &&
          Window_title[ String_length - 1 ] == 'e' ) ||
        ( Window_title[ String_length - 3 ] == 'C' &&
          Window_title[ String_length - 2 ] == 'O' &&
          Window_title[ String_length - 1 ] == 'M' ) ||
        ( Window_title[ String_length - 3 ] == 'c' &&
          Window_title[ String_length - 2 ] == 'o' &&
          Window_title[ String_length - 1 ] == 'm' ) )
     {
      MixedCase( Window_title );
     }

 // ���� Larsen Commander ���� ������ ���⮩ ��������� ����� "C:\..."
 if( Window_title[ 1 ] == ':' )
  if( WindowIsCreatedBy( APP_LCMD, Frame_window ) )
   {
    CHAR New_title[ SIZE_OF_TITLE ] = "";
    strcpy( New_title, "Larsen Commander - " );
    strcat( New_title, Window_title );

    strcpy( Window_title, New_title );
   }

 // � ��������� ����ॢ�⥫� Mozilla �� ���� �����뢠�� ���� ��� ᡮન.
 PCHAR Brace = strfind( " {", Window_title );
 if( Brace )
  if( WindowIsCreatedBy( APP_MOZILLA, Frame_window ) )
   *Brace = 0;

 // ������.
 return;
}

// ��� ������ ��������� ���� ���

// �� ��६���� - ���譨�.
VOID WindowList_QueryWindowTitle( HWND Frame_window, HWND TitleBar_window, PCHAR Window_title, BYTE Update_frame_if_required = 0 )
{
 // �᫨ �� �� ᯨ᮪ ���� - 㧭���, ���� �� ���� � ᯨ᪥.
 HSWITCH Switch_handle = NULLHANDLE;
 if( !IsWinListWindow( Frame_window ) ) Switch_handle = WinQuerySwitchHandle( Frame_window, NULLHANDLE );

 // �᫨ ���� ��������� �� ������ - 㧭��� ���.
 if( TitleBar_window == NULLHANDLE ) TitleBar_window = WinWindowFromID( Frame_window, FID_TITLEBAR );

 // ������ ��������� ����.
 Window_title[ 0 ] = NULL;

 if( Switch_handle != NULLHANDLE ) if( WinWindowFromID( Frame_window, FID_SYSMENU ) != NULLHANDLE )
  {
   SWCNTRL Task = {0}; WinQuerySwitchEntry( Switch_handle, &Task );

   strncpy( Window_title, Task.szSwtitle, SIZE_OF_TITLE );
   Window_title[ SIZE_OF_TITLE - 1 ] = NULL;

   if( strfind( "% ", Window_title ) ) Window_title[ 0 ] = NULL;
   if( Window_title[ strlen( Window_title ) - 1 ] == '%' ) Window_title[ 0 ] = NULL;
  }

 if( Window_title[ 0 ] == NULL )
  {
   WinQueryWindowText( TitleBar_window, SIZE_OF_TITLE, Window_title );
  }

 #ifndef INCLUDED_BY_SHELL

 // �᫨ �� ���᪮� ���� ᮮ�饭�� - 㧭��� ⥪�� � ��� ��ࢮ� ��ப�.
 if( Window_title[ 0 ] == NULL )
  if( TitleBar_window == NULLHANDLE )
   if( Switch_handle == NULLHANDLE )
    if( FrameType( Frame_window ) == FT_FLAT )
     {
      HWND Button = WinWindowFromID( Frame_window, MSGBOX_OK_BUTTON );
      if( Button != NULLHANDLE ) if( IsButtonWindow( Button ) )
       {
        HWND Message = WinWindowFromID( Frame_window, MSGBOX_MESSAGE_TEXT );
        if( Message != NULLHANDLE )
         {
          HWND Title_window = WinWindowFromID( Frame_window, MSGBOX_TITLE_TEXT );
          if( Title_window != NULLHANDLE )
           WinQueryWindowText( Title_window, SIZE_OF_TITLE, Window_title );
         }
       }
     }

 // ������� ���� �� ����� ���������.
 if( Window_title[ 0 ] == NULL )
  {
   BYTE Window_code_page = QueryCodePage( Frame_window ); BYTE Change_real_title = 0;

   // �᫨ �� �ࠢ�筨� ��� ��⥬��� ᮮ�饭�� - ��⠭�������� ᢮� ���������.
   if( WindowIsCreatedBy( APP_VIEWDOC, Frame_window ) )
    {
     if( Window_code_page == RUSSIAN ) strcpy( Window_title, "��ࠢ�筨�" );
     else strcpy( Window_title, "Help" );
    }

   if( IsSysMsgWindow( Frame_window ) )
    {
     if( Window_code_page == RUSSIAN ) strcpy( Window_title, "�訡��" );
     else strcpy( Window_title, "Error" );

     Change_real_title = 1;
    }

   // ��⠭�������� �����騩 ���������, �᫨ �� �ॡ����.
   if( Change_real_title == 1 ) WinSetWindowText( TitleBar_window, Window_title );

   // �᫨ ��������� ���:
   if( Window_title[ 0 ] == NULL )
    {
     // ��⠭�������� ���祭�� �� 㬮�砭��.
     if( Window_code_page == RUSSIAN ) strcpy( Window_title, "����" );
     else strcpy( Window_title, "Window" );

     // �����塞 ��������� ����, �᫨ �� �ॡ����.
     if( Update_frame_if_required ) WinSetWindowText( TitleBar_window, Window_title );
    }
  }

 #endif

 // ��ࠢ�塞 ��������� ����.
 WindowList_CorrectWindowTitle( Frame_window, Window_title, SIZE_OF_TITLE );

 // ������.
 return;
}

#ifndef INCLUDED_BY_SHELL

// ��� �����頥� ��������� ��� ���� ࠡ�祣� �⮫� ���

// Window_title - ��������� ����.
VOID WindowList_GetDefaultShellTitle( PCHAR Window_title )
{
 // �����頥� ���������.
 BYTE Desktop_code_page = QueryCodePage( QueryDesktopWindow() );

 if( Desktop_code_page == RUSSIAN ) strcpy( Window_title, "����稩 �⮫" );
 else strcpy( Window_title, "Desktop" );

 // *********************************************************************** //
 // "Desktop",                                                              //
 // "����稩 �⮫",                                                         //
 // "\x83\x66\x83\x58\x83\x4E\x83\x67\x83\x62\x83\x76",                     //
 // "Escritorio",                                                           //
 // "Werkplek",                                                             //
 // "\x41\x72\x62\x65\x69\x74\x73\x6f\x62\x65\x72\x66\x6c\x84\x63\x68\x65", //
 // "Area di lavoro",                                                       //
 // "Scrivania",                                                            //
 // *********************************************************************** //

 // ������.
 return;
}

#endif

// ��� ����砥� ᯨ᮪ ���� ���

// SWBlock � Corrected_SWBlock - ����� 㪠��⥫�.
VOID WindowList_QuerySWBlocks( PSWBLOCK* SWBlock, PSWBLOCK* Corrected_SWBlock )
{
 INT Number_of_items; INT SWBlock_length;

 // ������, ᪮�쪮 ����� ���ॡ���� ��� ᯨ᪠.
 HAB Application = ActiveApplication();

 Number_of_items = WinQuerySwitchList( Application, NULL, 0 );
 SWBlock_length = ( Number_of_items * sizeof( SWENTRY ) ) + sizeof( HSWITCH );

 // �뤥�塞 ������.
 DosAllocMem( (PPVOID) SWBlock, SWBlock_length, PAG_ALLOCATE );
 DosAllocMem( (PPVOID) Corrected_SWBlock, SWBlock_length, PAG_ALLOCATE );

 // ������ ᯨ᮪ ����.
 WinQuerySwitchList( Application, *SWBlock, SWBlock_length );
 memcpy( *Corrected_SWBlock, *SWBlock, SWBlock_length );

 // ��ࠢ�塞 ���.
 {
  INT Count;

  for( Count = 0; Count < ( *Corrected_SWBlock )->cswentry; Count ++ )
   {
    PSWCNTRL Task = &( ( *Corrected_SWBlock )->aswentry[ Count ].swctl );
    WindowList_CorrectWindowTitle( Task->hwnd, Task->szSwtitle, SIZE_OF_NAME );
   }
 }

 // ������.
 return;
}

// ��� �᢮������� ������ ���

// SWBlock � Corrected_SWBlock - 㪠��⥫� �� ������ �����.
VOID WindowList_FreeSWBlockMemory( PSWBLOCK SWBlock, PSWBLOCK Corrected_SWBlock )
{
 // �᢮������� ������.
 if( SWBlock ) DosFreeMem( SWBlock );
 if( Corrected_SWBlock ) DosFreeMem( Corrected_SWBlock );

 // ������.
 return;
}

// ��� ������ ᯨ᮪ ���� ���

// SWBlock - ���⮩ 㪠��⥫�.
VOID WindowList_QuerySwitchList( PSWBLOCK* SWBlock )
{
 // ����砥� ᯨ᮪ ����.
 PSWBLOCK Temporary_SWBlock = NULL;
 WindowList_QuerySWBlocks( &Temporary_SWBlock, SWBlock );
 WindowList_FreeSWBlockMemory( Temporary_SWBlock, NULL );

 // ������.
 return;
}

// ��� �᢮������� ������ ���

// SWBlock - 㪠��⥫� �� ������� �����.
VOID WindowList_FreeSwitchListMemory( PSWBLOCK SWBlock )
{
 // �᢮������� ������.
 WindowList_FreeSWBlockMemory( NULL, SWBlock );

 // ������.
 return;
}

// ��� �����뢠�� ��� ��뢠�� ��ப� � ᯨ᪥ ���� ���

// Switch_handle, Task - ��ப�, Show_item - �� ���� ᤥ����.
VOID WindowList_ShowItemInSwitchList( HSWITCH Switch_handle, SWCNTRL Task, BYTE Show_item )
{
 // ���뢠�� ��� �����뢠�� ��ப�.
 if( Show_item )
  {
   Task.uchVisibility = SWL_VISIBLE;
   Task.fbJump = SWL_JUMPABLE;
  }
 else
  {
   Task.uchVisibility = SWL_INVISIBLE;
   Task.fbJump = SWL_NOTJUMPABLE;
  }

 WinChangeSwitchEntry( Switch_handle, &Task );

 // ������.
 return;
}

// ��� �����뢠�� ��� ��뢠�� ��ப� � ᯨ᪥ ���� ���

// Item_name - ��ப�, Show_item - �� ���� ᤥ����.
VOID WindowList_ShowItemInSwitchList( PCHAR Item_name, BYTE Show_item )
{
 // ������ ᯨ᮪ ����.
 PSWBLOCK SWBlock = NULL; PSWBLOCK Corrected_SWBlock = NULL;
 WindowList_QuerySWBlocks( &SWBlock, &Corrected_SWBlock );

 // �����뢠�� ��� ��뢠�� ��ப�.
 {
  INT Count;

  for( Count = 0; Count < Corrected_SWBlock->cswentry; Count ++ )
   {
    HSWITCH Switch_handle = SWBlock->aswentry[ Count ].hswitch;
    SWCNTRL Task = Corrected_SWBlock->aswentry[ Count ].swctl;
    PCHAR Title = Corrected_SWBlock->aswentry[ Count ].swctl.szSwtitle;

    if( strcmp( Title, Item_name ) == EQUALLY ) WindowList_ShowItemInSwitchList( Switch_handle, Task, Show_item );
   }
 }

 // �᢮������� ������.
 WindowList_FreeSWBlockMemory( SWBlock, Corrected_SWBlock ); SWBlock = Corrected_SWBlock = NULL;

 // ������.
 return;
}

