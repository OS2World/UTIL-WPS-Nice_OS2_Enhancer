
// ─── Собирает сведения о полях ввода в окне ───

// Window - окно рамки или рабочей области, Data - указатель на данные.
// Condition - какие значения запоминать и в каких условиях происходит вызов.
// Во время работы возможен повторный вызов, при этом Recursive_calling != 0.
VOID Krnl_DlgBox_ScanDialogWindow( HWND Window, PDLGBOX Data, BYTE Condition = SCAN_ALL_FIELDS, BYTE Recursive_calling = 0 )
{
 // Сбрасываем внешний список.
 Data->Frame_type = FT_UNKNOWN;
 Data->Quantity = 0;
 Data->Enabled = 0;
 Data->Exe_name[ 0 ] = 0;
 Data->Window_title[ 0 ] = 0;

 // Если есть окно рабочей области - проводим поиск в нем.
 HWND Client_window = WinWindowFromID( Window, FID_CLIENT );
 if( Client_window != NULLHANDLE ) Window = Client_window;

 // Число полей ввода.
 INT Quantity = 0;

 // Массивы для сбора данных.
 DLGFIELD Fields[ DLG_MAX_FIELDS ]; SWP Placements[ DLG_MAX_FIELDS ];
 bzero( Fields, sizeof( DLGFIELD ) * DLG_MAX_FIELDS );

 {
  // Перебираем поля ввода в указанном окне.
  HENUM Enumeration = WinBeginEnumWindows( Window ); HWND Field = NULLHANDLE;
  while( ( Field = WinGetNextWindow( Enumeration ) ) != NULLHANDLE )
   {
    // Если поле ввода недоступно - продолжаем перебор окон.
    if( !WindowIsPresent( Field ) ) continue;

    // Узнаем, что это за поле ввода. Выбор зависит от внешних условий.
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

    // Распознаем невидимые прямоугольники, которые могут содержать другие поля.
    if( !Field_type ) if( IsStaticWindow( Field ) ) Field_type = DLG_STATIC;

    // Если это не кнопка и не прямоугольник и окно выключено - продолжаем перебор окон.
    if( Field_type != DLG_PUSH_BUTTON )
     if( Field_type != DLG_STATIC )
      if( !WinIsWindowEnabled( Field ) ) continue;

    // Если поле ввода надо запомнить:
    if( Field_type )
     {
      // Запоминаем окно.
      Fields[ Quantity ].Window = Field;

      // Запоминаем, что это за поле ввода.
      Fields[ Quantity ].Type = Field_type;

      // Сбрасываем временные переменные.
      Krnl_DlgBox.RTSettings.Item_index = LIT_NONE; Krnl_DlgBox.RTSettings.Item_text[ 0 ] = 0;

      // Запоминаем содержимое поля ввода.
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

      // Запоминаем расположение окна.
      WinQueryWindowPos( Field, &Placements[ Quantity ] );

      // Увеличиваем счетчик.
      Quantity ++; if( Quantity == DLG_MAX_FIELDS ) break;
     }
   }
  WinEndEnumWindows( Enumeration );
 }

 // Если найдено хотя бы одно окно:
 if( Quantity > 0 )
  {
   // Сравниваем расположение полей ввода и переносим их во внешний список.
   for( INT Main_count = 0; Main_count < Quantity; Main_count ++ )
    {
     // Запоминаем поле ввода, которое расположено в окне раньше других.
     PDLGFIELD Pointer = NULL; PSWP Placement = NULL;

     // Просматриваем список.
     for( INT Count = 0; Count < Quantity; Count ++ )
      {
       // Если поле ввода есть:
       if( Fields[ Count ].Type != 0 )
        {
         // Запоминаем первое поле ввода.
         if( Pointer == NULL )
          {
           Pointer = &Fields[ Count ];
           Placement = &Placements[ Count ];
          }
         // Или запоминаем то поле ввода, которое расположено раньше всех.
         else
          {
           // Проверяем, раположено ли данное поле ввода раньше того, которое запомнили до него.
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

           // Если оно расположено раньше - запоминаем его.
           if( Situated_before )
            {
             Pointer = &Fields[ Count ];
             Placement = &Placements[ Count ];
            }
          }
        }
      }

     // Переносим поле ввода во внешний список и забываем про него.
     if( Pointer != NULL )
      {
       memcpy( &( Data->Fields[ Main_count ] ), Pointer, sizeof( DLGFIELD ) );
       Pointer->Type = 0;
      }
    }

   // Кнопки с изображениями могут иметь имена вида "#..." или не иметь имен вообще - ставим им порядковый номер.
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

   // Если это не повторный вызов:
   if( !Recursive_calling )
    {
     // Выбираем невидимые прямоугольники, которые могут содержать другие поля.
     HWND Internal_rectangles[ DLG_MAX_FIELDS ]; INT Rectangles = 0;
     bzero( Internal_rectangles, sizeof( HWND ) * DLG_MAX_FIELDS );

     for( Count = 0; Count < Quantity; Count ++ )
      if( Data->Fields[ Count ].Type == DLG_STATIC )
       {
        Internal_rectangles[ Rectangles ] = Data->Fields[ Count ].Window;
        Rectangles ++;
       }

     // Если они есть:
     if( Rectangles )
      {
       // Перебираем прямоугольники.
       for( INT Rectangle_count = 0; Rectangle_count < Rectangles; Rectangle_count ++ )
        {
         // Узнаем содержимое полей ввода в каждом прямоугольнике.
         DLGBOX Rectangle_data; Krnl_DlgBox_ScanDialogWindow( Internal_rectangles[ Rectangle_count ], &Rectangle_data, Condition, RECURSIVE_CALLING );

         // Если там что-то есть - запоминаем найденные поля.
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

   // Запоминаем число полей.
   Data->Quantity = Quantity;

   // Узнаем окно рамки.
   HWND Frame_window = QueryFrameWindow( Window );

   // Запоминаем его свойства.
   Data->Frame_type = FrameType( Frame_window );
   GetDetectedExeName( Frame_window, Data->Exe_name );
   if( Data->Exe_name[ 0 ] == 0 ) strcpy( Data->Exe_name, "*" );
   GetDetectedWindowTitle( Frame_window, Data->Window_title );
   if( Data->Window_title[ 0 ] == 0 ) strcpy( Data->Window_title, "-" );
  }
 // А если ни одного окна не найдено:
 else
  {
   // Сбрасываем содержимое внешнего списка.
   Data->Window_title[ 0 ] = 0;
   Data->Exe_name[ 0 ] = 0;
   Data->Quantity = 0;
  }

 // Возврат.
 return;
}

// ─── Восстанавливает поля ввода в окне ───

// Window - окно рамки или рабочей области, Data - указатель на данные.
VOID Krnl_DlgBox_RestoreDialogFields( HWND Window, PDLGBOX Data )
{
 // Если есть окно рабочей области - проводим поиск в нем.
 HWND Client_window = WinWindowFromID( Window, FID_CLIENT );
 if( Client_window != NULLHANDLE ) Window = Client_window;

 // Получаем сведения об окне.
 DLGBOX Current_data; Krnl_DlgBox_ScanDialogWindow( Window, &Current_data );

 // Если ни одного поля ввода нет - возврат.
 if( Current_data.Quantity == 0 ) return;

 // Просматриваем их.
 INT Data_count = 0;

 for( INT Current_data_count = 0; Current_data_count < Current_data.Quantity; Current_data_count ++ )
  {
   // Если поле то же, что и во внешнем списке - запоминаем новое значение для него.
   if( Current_data.Fields[ Current_data_count ].Type == Data->Fields[ Data_count ].Type )
    {
     strcpy( Current_data.Fields[ Current_data_count ].Value, Data->Fields[ Data_count ].Value );
     Data_count ++;
    }
   // А если это другое поле - забываем про него.
   else
    {
     Current_data.Fields[ Current_data_count ].Type = 0;
    }
  }

 // Если были подобраны значения для всех полей:
 if( Data_count == Data->Quantity )
  {
   // Если надо переносить только текстовые поля - выбрасываем другие значения.
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

   // Переносим их в окно.
   for( INT Count = 0; Count < Current_data.Quantity; Count ++ )
    {
     // Если поле ввода есть - задаем его значение.
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

 // Возврат.
 return;
}
