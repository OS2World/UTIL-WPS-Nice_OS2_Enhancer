
// ��� ������뢠�� �ᯮ������� ����� ����� � 㪠������ ���� ���

// Box_window - ����, ��� ���ண� ���� ������� �ᯮ������� ����� �����, Layout - ᯨ᮪ ����� �����.
// �����頥��� ���祭�� �����뢠��, �뫮 �� ��� �� ���� ���� ����� ��६�饭� �� ᠬ�� ����.
BYTE Layout_ResizeInputFields( HWND Box_window, PLTWALL Layout )
{
 // ������ ������ ��� ����� �����.
 #define LTM_FIELDS_IN_ROW  25
 #define LTM_ROWS_IN_MATRIX 50

 #define LTM_FIELDS_IN_MATRIX ( LTM_FIELDS_IN_ROW * LTM_ROWS_IN_MATRIX )

 typedef struct _MATRIX
  {
   // ��� ����� ����� � ����� ᭨�� �����.
   typedef struct _ROW
    {
     // ��ᯮ������� �鸞 �� ���⨪��� � ���� �鸞.
     INT Y; INT Height; BYTE Row_can_be_shrinked;

     // ���� ����� � ������ ��� ᫥�� ���ࠢ�.
     typedef struct _FIELD
      {
       // ��ᯮ������� ���� ����� �� ��ਧ��⠫� � �ਭ� ���� �����.
       INT X; INT Width; BYTE Field_can_be_shrinked;

       // �����⥫� �� ᢥ����� � ���� �����.
       PLTBRICK Layout_pointer;
      }
     FIELD;

     INT Extension; FIELD Fields[ LTM_FIELDS_IN_ROW ];
    }
   ROW;

   INT Altitude; ROW Rows[ LTM_ROWS_IN_MATRIX ];
  }
 MATRIX; typedef MATRIX* PMATRIX;

 // ������塞 ������.
 PMATRIX Matrix = NULL;
 if( DosAllocMem( (PPVOID) &Matrix, sizeof( MATRIX ), PAG_ALLOCATE ) != NO_ERROR ) return 0;

 Matrix->Altitude = 0;

 {
  // ������ �� ���� ����� � 㪠������ ����.
  HWND Fields[ LTM_FIELDS_IN_MATRIX ]; INT Quantity = 0;

  // ��ॡ�ࠥ� ���� � 㪠������ ���� � ���������� ��.
  HENUM Enumeration = WinBeginEnumWindows( Box_window ); HWND Field = NULLHANDLE;
  while( ( Field = WinGetNextWindow( Enumeration ) ) != NULLHANDLE )
   {
    Fields[ Quantity ] = Field; Quantity ++;
   }
  WinEndEnumWindows( Enumeration );

  // �᫨ ���� ����� �뫨 �������:
  if( Quantity )
   {
    // ��ᬠ�ਢ��� ᯨ᮪, ᮤ�ঠ騩 ���祭�� ��� �ᯮ������� ����� ����� � ������塞 ������.
    for( INT Position = 0; Position < Layout->ulQuantity; Position ++ )
     {
      // ������ ���祭�� �� ᯨ᪠.
      HWND Layout_field = NULLHANDLE;

      PLTBRICK Pointer = Layout_GetBrickPointer( Layout, Position );

      if( Pointer != NULL ) Layout_field = Pointer->hwnd;
      else continue;

      // �᫨ �� �ਧ��� ᫥���饣� �鸞 - �த������ ��ᬮ�� ᯨ᪠.
      if( Layout_field == (HWND) LTM_NEXT_ROW_MARK ) continue;

      // ������, ᮮ⢥����� �� ���祭�� �� ᯨ᪠ ������ �� ��������� ����� �����.
      BYTE Field_is_present_in_layout = 0;

      for( INT Count = 0; Count < Quantity; Count ++ )
       if( Fields[ Count ] == Layout_field )
        {
         Field_is_present_in_layout = 1;
         break;
        }

      // �᫨ ���� ����� ��������� � ᯨ᪥:
      if( Field_is_present_in_layout )
       {
        // �᫨ ����� ���� - ����������, �� � ��� ���� ���� ��.
        if( !Matrix->Altitude && !Matrix->Rows[ 0 ].Extension ) Matrix->Altitude = 1;

        // �᫨ �� �� �������� �� �⪠��:
        if( Matrix->Rows[ Matrix->Altitude - 1 ].Extension <= LTM_FIELDS_IN_ROW )
         {
          // ���������� ���� �����.
          Matrix->Rows[ Matrix->Altitude - 1 ].Extension ++;
          Matrix->Rows[ Matrix->Altitude - 1 ].Fields[ Matrix->Rows[ Matrix->Altitude - 1 ].Extension - 1 ].Layout_pointer = Pointer;

          // �஡㥬 ������� ᫥���饥 ���祭�� �� ᯨ᪠.
          INT Latest_position = Layout->ulQuantity - 1;

          if( Position < Latest_position )
           {
            // ��ॡ�ࠥ� ����. ����� ��᫥���� ���祭�� �� ���뢠�� - ⠬ ����� ���� �ਧ��� ᫥���饣� �鸞.
            for( INT Next_position = Position + 1; Next_position < Latest_position - 1; Next_position ++ )
             {
              PLTBRICK Next_pointer = Layout_GetBrickPointer( Layout, Next_position );

              if( Next_pointer != NULL )
               {
                // �᫨ �� ����஭��� ���� ����� - �த������ ����.
                // �᫨ �� ���� ����� � ⮬ �� ���� - �४�頥� ����.
                if( Next_pointer->hwnd != (HWND) LTM_NEXT_ROW_MARK )
                 {
                  if( WinQueryWindow( Next_pointer->hwnd, QW_PARENT ) != Box_window )
                   continue;
                  else
                   break;
                 }

                // �᫨ �� �ਧ��� ᫥���饣� �鸞 - 㢥��稢��� �᫮ �冷� � �����.
                if( Next_pointer->hwnd == (HWND) LTM_NEXT_ROW_MARK )
                 {
                  if( Matrix->Altitude <= LTM_ROWS_IN_MATRIX )
                   {
                    Matrix->Altitude ++;
                    Matrix->Rows[ Matrix->Altitude - 1 ].Extension = 0;
                   }

                  break;
                 }
               }
             }
           }
         }
       }
     }
   }
 }

 // ���� �� ���� ���� ����� �� ��६�饭�.
 BYTE Fields_are_moved = 0;

 // �᫨ � ����� ��������� ��� �� ���� ���� �����:
 if( Matrix->Altitude )
  {
   {
    // ����������, ����� ���� ����� � ��� ����� ᦨ���� �� ����室�����.
    for( INT Row_count = 0; Row_count < Matrix->Altitude; Row_count ++ )
     {
      // ��⠥�, �� �� ����� ���� ᦠ�.
      PBYTE Row_can_be_shrinked = &Matrix->Rows[ Row_count ].Row_can_be_shrinked;

      *Row_can_be_shrinked = 1;

      for( INT Field_count = 0; Field_count < Matrix->Rows[ Row_count ].Extension; Field_count ++ )
       {
        // ������ 㪠��⥫� �� ᢮��⢠ ���� �����.
        PLTBRICK Pointer = Matrix->Rows[ Row_count ].Fields[ Field_count ].Layout_pointer;

        // �᫨ ��� ������� ���� ����� ������ �ਭ� �� � �窠�, � � %% �� ࠧ��� த�⥫�᪮�� ���� - ��� ����� ᦨ����.
        PBYTE Field_can_be_shrinked = &Matrix->Rows[ Row_count ].Fields[ Field_count ].Field_can_be_shrinked;

        *Field_can_be_shrinked = 0;

        if( Pointer != NULL )
         if( Pointer->prpWidthInParent <= 1.00 )
          *Field_can_be_shrinked = 1;

        // �᫨ ��� ������ �� ����� ����� ������ ���� � �窠� - �� ᦨ���� �����.
        if( Pointer->prpHeightInParent > 1.00 ) *Row_can_be_shrinked = 0;
       }
     }
   }

   // ������ ࠧ��� ����.
   RECT Rectangle = {0}; WinQueryWindowRect( Box_window, &Rectangle );

   // ����塞 ����ﭨ� ����� ���ﬨ ����� � ����� ����� ����.
   INT Gap_X = 0; INT Gap_Y = 0;
   INT Margin_X = 0; INT Margin_Y = 0;

   for( INT Count = 0; Count < Layout->ulQuantity; Count ++ )
    {
     PLTBRICK Pointer = Layout_GetBrickPointer( Layout, Count );

     if( Pointer != NULL )
      if( Pointer->hwnd == Box_window )
       {
        if( Pointer->prpGap != 0.00 )
         {
          if( Pointer->prpGap > 1.00 )
           {
            Gap_X = Gap_Y = (INT) Pointer->prpGap;
           }
          else
           {
            Gap_X = (INT) ( Rectangle.xRight * Pointer->prpGap );
            Gap_Y = (INT) ( Rectangle.yTop * Pointer->prpGap );
           }

          if( Gap_X > Rectangle.xRight / 4 ) Gap_X = 0;
          if( Gap_Y > Rectangle.yTop / 4 ) Gap_Y = 0;
         }

        if( Pointer->prpMargin != 0.00 )
         {
          if( Pointer->prpMargin > 1.00 )
           {
            Margin_X = Margin_Y = (INT) Pointer->prpMargin;
           }
          else
           {
            Margin_X = (INT) ( Rectangle.xRight * Pointer->prpMargin );
            Margin_Y = (INT) ( Rectangle.yTop * Pointer->prpMargin );
           }

          if( Margin_X > Rectangle.xRight / 4 ) Margin_X = 0;
          if( Margin_Y > Rectangle.yTop / 4 ) Margin_Y = 0;
         }

        break;
       }
    }

   {
    // ������ �ᯮ������� ��� �冷� � ����� � �����. ��⠥� ����� �����.
    INT Row_bottom = Gap_Y; INT Total_height = Row_bottom + Margin_Y * 2;

    for( INT Row_count = 0; Row_count < Matrix->Altitude; Row_count ++ )
     {
      // ���������� ����� �鸞.
      INT Row_height = 0;

      // ������ �ᯮ������� ����� �����. ��⠥� ����� �ਭ�.
      INT Field_bound = Gap_X; INT Total_width = Field_bound + Margin_X * 2;

      for( INT Field_count = 0; Field_count < Matrix->Rows[ Row_count ].Extension; Field_count ++ )
       {
        // ������ 㪠��⥫� �� ᢮��⢠ ���� �����.
        PLTBRICK Pointer = Matrix->Rows[ Row_count ].Fields[ Field_count ].Layout_pointer;

        if( Pointer != NULL )
         {
          // ������ �ਭ� ���� �����.
          INT Width = 0;

          if( Pointer->prpWidthInParent > 1.00 ) Width = (INT) Pointer->prpWidthInParent;
          else Width = (INT) ( Rectangle.xRight * Pointer->prpWidthInParent );

          Matrix->Rows[ Row_count ].Fields[ Field_count ].X = Field_bound;
          Matrix->Rows[ Row_count ].Fields[ Field_count ].Width = Width;

          Field_bound += Width + Gap_X;
          Total_width += Width + Gap_X;

          // ������ ����� �鸞, ���뢠� ����� ������� ���� �����.
          INT Height = 0;

          if( Pointer->prpHeightInParent > 1.00 ) Height = (INT) Pointer->prpHeightInParent;
          else Height = (INT) ( Rectangle.yTop * Pointer->prpHeightInParent );

          if( Height > Row_height ) Row_height = Height;
         }
       }

      // ������ �ᯮ������� ������� �鸞.
      Matrix->Rows[ Row_count ].Y = Row_bottom;
      Matrix->Rows[ Row_count ].Height = Row_height;

      Row_bottom += Row_height + Gap_Y;
      Total_height += Row_height + Gap_Y;

      // ������� ��� ������� ������ ⠪, �⮡� ��� ���室��� ��� ࠧ��� ����.
      if( Total_width != Rectangle.xRight )
       {
        // �᫨ ���� �ਭ� �鸞 ����� ����室���� - ������� ���� �����.
        if( Total_width < Rectangle.xRight )
         {
          for( INT Pixel_count = 0; Pixel_count < Rectangle.xRight; Pixel_count ++ )
           {
            for( Field_count = 0; Field_count < Matrix->Rows[ Row_count ].Extension; Field_count ++ )
             {
              Matrix->Rows[ Row_count ].Fields[ Field_count ].Width ++; Total_width ++;

              for( INT Right_side_field_count = Field_count + 1; Right_side_field_count < Matrix->Rows[ Row_count ].Extension; Right_side_field_count ++ )
               Matrix->Rows[ Row_count ].Fields[ Right_side_field_count ].X ++;

              if( Total_width >= Rectangle.xRight ) break;
             }

            if( Total_width >= Rectangle.xRight ) break;
           }
         }
        // � �᫨ ���� �ਭ� �ॢ�蠥� �ਭ� �鸞 - ᦨ���� ���� �����.
        else
         {
          for( INT Pixel_count = 0; Pixel_count < Total_width; Pixel_count ++ )
           {
            for( Field_count = 0; Field_count < Matrix->Rows[ Row_count ].Extension; Field_count ++ )
             {
              if( Matrix->Rows[ Row_count ].Fields[ Field_count ].Field_can_be_shrinked )
               {
                Matrix->Rows[ Row_count ].Fields[ Field_count ].Width --; Total_width --;

                for( INT Right_side_field_count = Field_count + 1; Right_side_field_count < Matrix->Rows[ Row_count ].Extension; Right_side_field_count ++ )
                 Matrix->Rows[ Row_count ].Fields[ Right_side_field_count ].X --;
               }

              if( Total_width <= Rectangle.xRight ) break;
             }

            if( Total_width <= Rectangle.xRight ) break;
           }
         }
       }
     }

    // ������� ��� ������� ������ ⠪, �⮡� ��� ���室��� ��� ࠧ��� ����.
    if( Total_height != Rectangle.yTop )
     {
      // �᫨ ���� ���� ����� ����� ���� - ������� ���.
      if( Total_height < Rectangle.yTop )
       {
        for( INT Pixel_count = 0; Pixel_count < Total_height; Pixel_count ++ )
         {
          for( Row_count = 0; Row_count < Matrix->Altitude; Row_count ++ )
           {
            Matrix->Rows[ Row_count ].Height ++; Total_height ++;

            for( INT Top_side_row_count = Row_count + 1; Top_side_row_count < Matrix->Altitude; Top_side_row_count ++ )
             Matrix->Rows[ Top_side_row_count ].Y ++;

            if( Total_height >= Rectangle.yTop ) break;
           }

          if( Total_height >= Rectangle.yTop ) break;
         }
       }
      // � �᫨ ���� ���� �ॢ�蠥� ����� ���� - ᦨ���� ���.
      else
       {
        for( INT Pixel_count = 0; Pixel_count < Total_height; Pixel_count ++ )
         {
          for( Row_count = 0; Row_count < Matrix->Altitude; Row_count ++ )
           {
            if( Matrix->Rows[ Row_count ].Row_can_be_shrinked )
             {
              Matrix->Rows[ Row_count ].Height --; Total_height --;

              for( INT Top_side_row_count = Row_count + 1; Top_side_row_count < Matrix->Altitude; Top_side_row_count ++ )
               Matrix->Rows[ Top_side_row_count ].Y --;
             }

            if( Total_height <= Rectangle.yTop ) break;
           }

          if( Total_height <= Rectangle.yTop ) break;
         }
       }
     }
   }

   {
    // ������ �ᯮ������� ���� � ᮮ⢥��⢨� � ���祭�ﬨ ������ � ����㯮� �� �ࠥ� ����.
    for( INT Row_count = 0; Row_count < Matrix->Altitude; Row_count ++ )
     for( INT Field_count = 0; Field_count < Matrix->Rows[ Row_count ].Extension; Field_count ++ )
      {
       // ������ 㪠��⥫� �� ᢮��⢠ ���� �����.
       PLTBRICK Pointer = Matrix->Rows[ Row_count ].Fields[ Field_count ].Layout_pointer;

       if( Pointer != NULL )
        {
         // ��⠭�������� ����� �ᯮ������� ����.
         INT X_Position = Matrix->Rows[ Row_count ].Fields[ Field_count ].X + Margin_X;
         INT X_Size     = Matrix->Rows[ Row_count ].Fields[ Field_count ].Width;

         if( Pointer->prpWidthInParent != 1.00 )
          {
           INT Width = 0;

           if( Pointer->prpWidthInParent > 1.00 ) Width = (INT) Pointer->prpWidthInParent;
           else Width = (INT) ( Rectangle.xRight * Pointer->prpWidthInParent );

           if( Width && Width < X_Size )
            {
             X_Position += ( X_Size - Width ) / 2; X_Size = Width;
            }
          }

         INT Y_Position = Matrix->Rows[ Row_count ].Y + Margin_Y;
         INT Y_Size     = Matrix->Rows[ Row_count ].Height;

         if( Pointer->prpHeightInParent != 1.00 )
          {
           INT Height = 0;

           if( Pointer->prpHeightInParent > 1.00 ) Height = (INT) Pointer->prpHeightInParent;
           else Height = (INT) ( Rectangle.yTop * Pointer->prpHeightInParent );

           if( Height && Height < Y_Size )
            {
             Y_Position += ( Y_Size - Height ) / 2; Y_Size = Height;
            }
          }

         if( Pointer->ulBoxHeight )
          {
           Y_Size     += Pointer->ulBoxHeight;
           Y_Position -= Pointer->ulBoxHeight;
          }

         // �᫨ �ᯮ������� ���� ������ ���������� - ��।������ ���.
         SWP Current_placement = {0}; WinQueryWindowPos( Box_window, &Current_placement );

         if( Current_placement.x != X_Position || Current_placement.y != Y_Position || Current_placement.cx != X_Size || Current_placement.cy != Y_Size )
          {
           WinSetWindowPos( Pointer->hwnd, NULLHANDLE, X_Position, Y_Position, X_Size, Y_Size, SWP_MOVE | SWP_SIZE | SWP_NOADJUST );
           Fields_are_moved = 1;
          }
        }
      }
   }
  }

 // �᢮������� ������.
 DosFreeMem( Matrix ); Matrix = NULL;

 // ������.
 return Fields_are_moved;
}

// ��� ������뢠�� �ᯮ������� ����� ����� �� ��� ����� ���

// Layout - ᯨ᮪ ����� �����.
VOID Layout_LitApplyLayout( PLTWALL Layout )
{
 // �᫨ ᯨ᮪ ����� ����୮ - ������.
 if( !Layout_ListIsCorrect( Layout ) ) return;

 // �⪫�砥� �ᮢ���� �� ��� �����.
 HWND Changed_windows[ WNDTREE_SIZE ]; EnableWindowTreeUpdate( Layout->hwnd, 0, Changed_windows );

 // ������뢠�� �ᯮ������� ����� ����� �� ��� �����, ��� ��� ����� ����.
 // ���砫� �஡㥬 ��६����� ���� ����� � �᭮���� ����, �⮡� �஢����,
 // ���� �� ����� ������ �� �ᯮ�������, � ��⥬ ��室�� �� ��ॢ� ����.
 HWND Tree[ WNDTREE_SIZE ]; INT Length = WNDTREE_SIZE; ExploreWindowTree( Layout->hwnd, Tree, &Length );

 if( Layout_ResizeInputFields( Tree[ 0 ], Layout ) )
  for( INT Count = 1; Count < Length; Count ++ )
    Layout_ResizeInputFields( Tree[ Count ], Layout );

 // ����砥� �ᮢ���� �� ��� �����.
 EnableWindowTreeUpdate( Layout->hwnd, 1, Changed_windows );

 // ������.
 return;
}

// ��� �����뢠�� ���� ࠬ�� � �ᥬ� ���ﬨ ����� ���

// Layout - ᯨ᮪ ����� �����.
VOID Layout_LitShowFrameWindow( PLTWALL Layout )
{
 // �᫨ ᯨ᮪ ����� ����୮ - ������.
 if( !Layout_ListIsCorrect( Layout ) ) return;

 // ��室�� � ᯨ᪥ ����, ��� ���ண� ������ �᪫����.
 for( INT Count = 0; Count < Layout->ulQuantity; Count ++ )
  {
   // ������ 㪠��⥫� �� ᢮��⢠ ���� �����.
   PLTBRICK Pointer = Layout_GetBrickPointer( Layout, Count );

   // �᫨ �� ����, ��� ���ண� ������ �᪫����:
   if( Pointer != NULL ) if( Pointer->hwnd == Layout->hwnd )
    {
     // �롨ࠥ� ���� ࠬ�� - �� ��� ��������� ����, ��� த�⥫�᪮� ��� ����.
     HWND Frame_window = Layout->hwnd;

     HWND Parent_window = WinQueryWindow( Frame_window, QW_PARENT );
     if( Layout->hwnd == WinWindowFromID( Parent_window, FID_CLIENT ) ) Frame_window = Parent_window;

     // ������ த�⥫�᪮� ���� ��� ���� ࠬ��.
     HWND Container_window = WinQueryWindow( Frame_window, QW_PARENT );

     // ������ ࠧ��� த�⥫�᪮�� ����.
     RECT Rectangle = {0}; WinQueryWindowRect( Container_window, &Rectangle );

     // ������뢠�� ࠧ��� ���� ࠬ��.
     INT Width = 0; INT Height = 0;

     if( Pointer->prpWidthInParent > 1.00 ) Width = (INT) Pointer->prpWidthInParent;
     else Width = (INT) ( Rectangle.xRight * Pointer->prpWidthInParent );

     if( Width > Rectangle.xRight ) Width = Rectangle.xRight;

     if( Pointer->prpHeightInParent > 1.00 ) Height = (INT) Pointer->prpHeightInParent;
     else Height = (INT) ( Rectangle.yTop * Pointer->prpHeightInParent );

     if( Height > Rectangle.yTop ) Height = Rectangle.yTop;

     // ��⠭�������� ����� �ᯮ������� ����.
     INT X = ( Rectangle.xRight - Width ) / 2;
     INT Y = ( Rectangle.yTop - Height ) * 3 / 4;

     WinSetWindowPos( Frame_window, HWND_TOP, X, Y, Width, Height, SWP_MOVE | SWP_SIZE | SWP_SHOW | SWP_ACTIVATE );
    }
  }

 // ������.
 return;
}
