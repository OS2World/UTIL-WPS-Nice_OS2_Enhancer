
// ��� ����ࠥ� ᢥ����� � ����� ����� � ���� ���

// Window - ���� ࠬ�� ��� ࠡ�祩 ������, Data - 㪠��⥫� �� �����.
// Condition - ����� ���祭�� ���������� � � ����� �᫮���� �ந�室�� �맮�.
// �� �६� ࠡ��� �������� ������ �맮�, �� �⮬ Recursive_calling != 0.
VOID Krnl_DlgBox_ScanDialogWindow( HWND Window, PDLGBOX Data, BYTE Condition = SCAN_ALL_FIELDS, BYTE Recursive_calling = 0 )
{
 // ����뢠�� ���譨� ᯨ᮪.
 Data->Frame_type = FT_UNKNOWN;
 Data->Quantity = 0;
 Data->Enabled = 0;
 Data->Exe_name[ 0 ] = 0;
 Data->Window_title[ 0 ] = 0;

 // �᫨ ���� ���� ࠡ�祩 ������ - �஢���� ���� � ���.
 HWND Client_window = WinWindowFromID( Window, FID_CLIENT );
 if( Client_window != NULLHANDLE ) Window = Client_window;

 // ��᫮ ����� �����.
 INT Quantity = 0;

 // ���ᨢ� ��� ᡮ� ������.
 DLGFIELD Fields[ DLG_MAX_FIELDS ]; SWP Placements[ DLG_MAX_FIELDS ];
 bzero( Fields, sizeof( DLGFIELD ) * DLG_MAX_FIELDS );

 {
  // ��ॡ�ࠥ� ���� ����� � 㪠������ ����.
  HENUM Enumeration = WinBeginEnumWindows( Window ); HWND Field = NULLHANDLE;
  while( ( Field = WinGetNextWindow( Enumeration ) ) != NULLHANDLE )
   {
    // �᫨ ���� ����� ������㯭� - �த������ ��ॡ�� ����.
    if( !WindowIsPresent( Field ) ) continue;

    // ������, �� �� �� ���� �����. �롮� ������ �� ���譨� �᫮���.
    LONG Field_type = 0;

    if( Condition == SCAN_ALL_FIELDS || Condition & SCAN_INPUT_FIELDS )
     {
      if( !Field_type ) if( IsInputFieldWindow( Field ) ) Field_type = DLG_INPUT_FIELD;
      if( !Field_type ) if( IsEntryFieldWindow( Field ) ) Field_type = DLG_ENTRY_FIELD;
     }

    if( Condition == SCAN_ALL_FIELDS )
     {
      if( !Field_type ) if( IsComboBoxWindow( Field ) ) Field_type = DLG_COMBO_BOX;
      if( !Field_type ) if( IsListBoxWindow( Field ) ) Field_type = DLG_LIST_BOX;
     }

    if( Condition == SCAN_ALL_FIELDS )
     {
      if( !Field_type ) if( IsSpinButtonWindow( Field ) ) Field_type = DLG_SPIN_BUTTON;
      if( !Field_type ) if( IsCheckBoxButtonWindow( Field ) ) Field_type = DLG_CHECKBOX_BUTTON;
      if( !Field_type ) if( IsRadioButtonWindow( Field ) ) Field_type = DLG_RADIO_BUTTON;
     }

    if( Condition == SCAN_ALL_FIELDS )
     {
      if( !Field_type ) if( IsButtonWindow( Field ) ) Field_type = DLG_PUSH_BUTTON;
     }

    if( Condition == SCAN_ALL_FIELDS )
     {
      if( !Field_type ) if( IsSliderWindow( Field ) ) Field_type = DLG_SLIDER;
     }

    // ��ᯮ����� �������� ��אַ㣮�쭨��, ����� ����� ᮤ�ঠ�� ��㣨� ����.
    if( !Field_type ) if( IsStaticWindow( Field ) ) Field_type = DLG_STATIC;

    // �᫨ �� �� ������ � �� ��אַ㣮�쭨� � ���� �몫�祭� - �த������ ��ॡ�� ����.
    if( Field_type != DLG_PUSH_BUTTON )
     if( Field_type != DLG_STATIC )
      if( !WinIsWindowEnabled( Field ) ) continue;

    // �᫨ ���� ����� ���� ���������:
    if( Field_type )
     {
      // ���������� ����.
      Fields[ Quantity ].Window = Field;

      // ����������, �� �� �� ���� �����.
      Fields[ Quantity ].Type = Field_type;

      // ����뢠�� �६���� ��६����.
      Krnl_DlgBox.RTSettings.Item_index = LIT_NONE; Krnl_DlgBox.RTSettings.Item_text[ 0 ] = 0;

      // ���������� ᮤ�ন��� ���� �����.
      Fields[ Quantity ].Value[ 0 ] = 0;

      if( Field_type == DLG_INPUT_FIELD || Field_type == DLG_ENTRY_FIELD )
       {
        WinQueryWindowText( Field, SIZE_OF_DIALOG_FIELD, Fields[ Quantity ].Value );
        if( Fields[ Quantity ].Value[ 0 ] != 0 ) Fields[ Quantity ].Useful = 1;
       }

      if( Field_type == DLG_COMBO_BOX || Field_type == DLG_LIST_BOX )
       {
        LONG Index = (LONG) WinSendMsg( Field, LM_QUERYSELECTION, (MPARAM) LIT_CURSOR, 0 );
        if( Index != LIT_NONE )
         {
          WinSendMsg( Field, LM_QUERYITEMTEXT, MPFROM2SHORT( Index, SIZE_OF_DIALOG_FIELD ), Krnl_DlgBox.RTSettings.Item_text );
          strcpy( Fields[ Quantity ].Value, Krnl_DlgBox.RTSettings.Item_text );
          if( Fields[ Quantity ].Value[ 0 ] != 0 ) Fields[ Quantity ].Useful = 1;
         }
       }

      if( Field_type == DLG_SPIN_BUTTON )
       {
        WinSendMsg( Field, SPBM_QUERYVALUE, &Krnl_DlgBox.RTSettings.Item_index, MPFROM2SHORT( 0, SPBQ_ALWAYSUPDATE ) );

        if( Krnl_DlgBox.RTSettings.Item_index != LIT_NONE )
         {
          itoa( Krnl_DlgBox.RTSettings.Item_index, Fields[ Quantity ].Value, 10 );
          strcat( Fields[ Quantity ].Value, ":" );

          WinSendMsg( Field, SPBM_QUERYVALUE, Krnl_DlgBox.RTSettings.Item_text, MPFROM2SHORT( SIZE_OF_DIALOG_FIELD, SPBQ_ALWAYSUPDATE ) );
          strcat( Fields[ Quantity ].Value, Krnl_DlgBox.RTSettings.Item_text );

          if( Fields[ Quantity ].Value[ 0 ] != 0 ) Fields[ Quantity ].Useful = 1;
         }
       }

      if( Field_type == DLG_CHECKBOX_BUTTON || Field_type == DLG_RADIO_BUTTON )
       {
        LONG Checked = (LONG) WinSendMsg( Field, BM_QUERYCHECK, 0, 0 );
        switch( Checked )
         {
          case 0: strcpy( Fields[ Quantity ].Value, "-" ); break;
          case 1: strcpy( Fields[ Quantity ].Value, "+" ); break;
          case 2: strcpy( Fields[ Quantity ].Value, "*" ); break;
         }
       }

      if( Field_type == DLG_PUSH_BUTTON )
       {
        WinQueryWindowText( Field, SIZE_OF_DIALOG_FIELD, Fields[ Quantity ].Value );
        if( Fields[ Quantity ].Value[ 0 ] == 0 ) strcpy( Fields[ Quantity ].Value, ">>" );
       }

      if( Field_type == DLG_SLIDER )
       {
        ULONG Position = (ULONG) WinSendMsg( Field, SLM_QUERYSLIDERINFO, MPFROM2SHORT( SMA_SLIDERARMPOSITION, SMA_INCREMENTVALUE ), 0 );
        itoa( Position, Fields[ Quantity ].Value, 10 );
        if( Fields[ Quantity ].Value[ 0 ] != 0 ) Fields[ Quantity ].Useful = 1;
       }

      if( Field_type == DLG_STATIC ) strcpy( Fields[ Quantity ].Value, "::" );

      // ���������� �ᯮ������� ����.
      WinQueryWindowPos( Field, &Placements[ Quantity ] );

      // �����稢��� ���稪.
      Quantity ++; if( Quantity == DLG_MAX_FIELDS ) break;
     }
   }
  WinEndEnumWindows( Enumeration );
 }

 // �᫨ ������� ��� �� ���� ����:
 if( Quantity > 0 )
  {
   // �ࠢ������ �ᯮ������� ����� ����� � ��७�ᨬ �� �� ���譨� ᯨ᮪.
   for( INT Main_count = 0; Main_count < Quantity; Main_count ++ )
    {
     // ���������� ���� �����, ���஥ �ᯮ������ � ���� ࠭�� ��㣨�.
     PDLGFIELD Pointer = NULL; PSWP Placement = NULL;

     // ��ᬠ�ਢ��� ᯨ᮪.
     for( INT Count = 0; Count < Quantity; Count ++ )
      {
       // �᫨ ���� ����� ����:
       if( Fields[ Count ].Type != 0 )
        {
         // ���������� ��ࢮ� ���� �����.
         if( Pointer == NULL )
          {
           Pointer = &Fields[ Count ];
           Placement = &Placements[ Count ];
          }
         // ��� ���������� � ���� �����, ���஥ �ᯮ������ ࠭�� ���.
         else
          {
           // �஢��塞, ࠯������� �� ������ ���� ����� ࠭�� ⮣�, ���஥ ��������� �� ����.
           BYTE Situated_before = 0;

           INT X_Middle_line = Placements[ Count ].x + Placements[ Count ].cx / 2;
           INT Y_Middle_line = Placements[ Count ].y + Placements[ Count ].cy / 2;

           if( Y_Middle_line > Placement->y + Placement->cy )
            {
             Situated_before = 1;
            }
           else
            {
             if( Y_Middle_line > Placement->y )
              if( X_Middle_line < Placement->x )
               Situated_before = 1;
            }

           // �᫨ ��� �ᯮ������ ࠭�� - ���������� ���.
           if( Situated_before )
            {
             Pointer = &Fields[ Count ];
             Placement = &Placements[ Count ];
            }
          }
        }
      }

     // ��७�ᨬ ���� ����� �� ���譨� ᯨ᮪ � ���뢠�� �� ����.
     if( Pointer != NULL )
      {
       memcpy( &( Data->Fields[ Main_count ] ), Pointer, sizeof( DLGFIELD ) );
       Pointer->Type = 0;
      }
    }

   // ������ � ����ࠦ���ﬨ ����� ����� ����� ���� "#..." ��� �� ����� ���� ����� - �⠢�� �� ���浪��� �����.
   INT Button_number = 1;
   for( INT Count = 0; Count < Quantity; Count ++ )
    {
     if( Data->Fields[ Count ].Type == DLG_PUSH_BUTTON )
      if( Data->Fields[ Count ].Value[ 0 ] == '#' || Data->Fields[ Count ].Value[ 0 ] == 0 )
       {
        CHAR Number[ 25 ] = ""; itoa( Button_number, Number, 16 ); UpperCase( Number );
        strcpy( Data->Fields[ Count ].Value, "[ " );
        strcat( Data->Fields[ Count ].Value, Number );
        strcat( Data->Fields[ Count ].Value, " ]" );

        Button_number ++;
       }
    }

   // �᫨ �� �� ������ �맮�:
   if( !Recursive_calling )
    {
     // �롨ࠥ� �������� ��אַ㣮�쭨��, ����� ����� ᮤ�ঠ�� ��㣨� ����.
     HWND Internal_rectangles[ DLG_MAX_FIELDS ]; INT Rectangles = 0;
     bzero( Internal_rectangles, sizeof( HWND ) * DLG_MAX_FIELDS );

     for( Count = 0; Count < Quantity; Count ++ )
      if( Data->Fields[ Count ].Type == DLG_STATIC )
       {
        Internal_rectangles[ Rectangles ] = Data->Fields[ Count ].Window;
        Rectangles ++;
       }

     // �᫨ ��� ����:
     if( Rectangles )
      {
       // ��ॡ�ࠥ� ��אַ㣮�쭨��.
       for( INT Rectangle_count = 0; Rectangle_count < Rectangles; Rectangle_count ++ )
        {
         // ������ ᮤ�ন��� ����� ����� � ������ ��אַ㣮�쭨��.
         DLGBOX Rectangle_data; Krnl_DlgBox_ScanDialogWindow( Internal_rectangles[ Rectangle_count ], &Rectangle_data, Condition, RECURSIVE_CALLING );

         // �᫨ ⠬ ��-� ���� - ���������� �������� ����.
         if( Rectangle_data.Quantity > 0 )
          {
           for( INT Field_count = 0; Field_count < Rectangle_data.Quantity; Field_count ++ )
            {
             memcpy( &Data->Fields[ Quantity ], &Rectangle_data.Fields[ Field_count ], sizeof( DLGFIELD ) );
             Quantity ++;
            }
          }
        }
      }
    }

   // ���������� �᫮ �����.
   Data->Quantity = Quantity;

   // ������ ���� ࠬ��.
   HWND Frame_window = QueryFrameWindow( Window );

   // ���������� ��� ᢮��⢠.
   Data->Frame_type = FrameType( Frame_window );
   GetDetectedExeName( Frame_window, Data->Exe_name );
   if( Data->Exe_name[ 0 ] == 0 ) strcpy( Data->Exe_name, "*" );
   GetDetectedWindowTitle( Frame_window, Data->Window_title );
   if( Data->Window_title[ 0 ] == 0 ) strcpy( Data->Window_title, "-" );
  }
 // � �᫨ �� ������ ���� �� �������:
 else
  {
   // ����뢠�� ᮤ�ন��� ���譥�� ᯨ᪠.
   Data->Window_title[ 0 ] = 0;
   Data->Exe_name[ 0 ] = 0;
   Data->Quantity = 0;
  }

 // ������.
 return;
}

// ��� ����⠭�������� ���� ����� � ���� ���

// Window - ���� ࠬ�� ��� ࠡ�祩 ������, Data - 㪠��⥫� �� �����.
VOID Krnl_DlgBox_RestoreDialogFields( HWND Window, PDLGBOX Data )
{
 // �᫨ ���� ���� ࠡ�祩 ������ - �஢���� ���� � ���.
 HWND Client_window = WinWindowFromID( Window, FID_CLIENT );
 if( Client_window != NULLHANDLE ) Window = Client_window;

 // ����砥� ᢥ����� �� ����.
 DLGBOX Current_data; Krnl_DlgBox_ScanDialogWindow( Window, &Current_data );

 // �᫨ �� ������ ���� ����� ��� - ������.
 if( Current_data.Quantity == 0 ) return;

 // ��ᬠ�ਢ��� ��.
 INT Data_count = 0;

 for( INT Current_data_count = 0; Current_data_count < Current_data.Quantity; Current_data_count ++ )
  {
   // �᫨ ���� � ��, �� � �� ���譥� ᯨ᪥ - ���������� ����� ���祭�� ��� ����.
   if( Current_data.Fields[ Current_data_count ].Type == Data->Fields[ Data_count ].Type )
    {
     strcpy( Current_data.Fields[ Current_data_count ].Value, Data->Fields[ Data_count ].Value );
     Data_count ++;
    }
   // � �᫨ �� ��㣮� ���� - ���뢠�� �� ����.
   else
    {
     Current_data.Fields[ Current_data_count ].Type = 0;
    }
  }

 // �᫨ �뫨 �����࠭� ���祭�� ��� ��� �����:
 if( Data_count == Data->Quantity )
  {
   // �᫨ ���� ��७���� ⮫쪮 ⥪�⮢� ���� - ����뢠�� ��㣨� ���祭��.
   if( Data->Text_fields_only )
    {
     for( INT Count = 0; Count < Current_data.Quantity; Count ++ )
      {
       LONG Field_type = Current_data.Fields[ Count ].Type;
       if( Field_type != DLG_INPUT_FIELD )
        if( Field_type != DLG_ENTRY_FIELD )
         Current_data.Fields[ Count ].Type = 0;
      }
    }

   // ��७�ᨬ �� � ����.
   for( INT Count = 0; Count < Current_data.Quantity; Count ++ )
    {
     // �᫨ ���� ����� ���� - ������ ��� ���祭��.
     LONG Field_type = Current_data.Fields[ Count ].Type;
     HWND Field = Current_data.Fields[ Count ].Window;
     PCHAR Value = Current_data.Fields[ Count ].Value;

     if( Field_type == DLG_INPUT_FIELD || Field_type == DLG_ENTRY_FIELD )
      {
       WinSetWindowText( Field, Value );
      }

     if( Field_type == DLG_COMBO_BOX || Field_type == DLG_LIST_BOX )
      {
       strcpy( Krnl_DlgBox.RTSettings.Item_text, Value );
       LONG Index = (LONG) WinSendMsg( Field, LM_SEARCHSTRING, MPFROM2SHORT( LSS_CASESENSITIVE | LSS_SUBSTRING, LIT_FIRST ), Krnl_DlgBox.RTSettings.Item_text );
       if( Index != LIT_NONE ) WinSendMsg( Field, LM_SELECTITEM, (MPARAM) Index, (MPARAM) 1 );
      }

     if( Field_type == DLG_SPIN_BUTTON )
      {
       if( strstr( ":", Value ) )
        {
         strchg( Value, ':', 0x00 ); LONG Index = atol( Value );
         WinSendMsg( Field, SPBM_SETCURRENTVALUE, MPARAM( Index ), 0 );
        }
      }

     if( Field_type == DLG_CHECKBOX_BUTTON || Field_type == DLG_RADIO_BUTTON )
      {
       LONG State = 0;
       if( Value[ 0 ] == '+' ) State = 1;
       if( Value[ 0 ] == '*' ) State = 2;

       WinSendMsg( Field, BM_SETCHECK, (MPARAM) State, 0 );
      }

     if( Field_type == DLG_SLIDER )
      {
       LONG Position = atol( Value );
       WinSendMsg( Field, SLM_SETSLIDERINFO, MPFROM2SHORT( SMA_SLIDERARMPOSITION, SMA_INCREMENTVALUE), MPFROMLONG( Position ) );
      }
    }
  }

 // ������.
 return;
}
