
// ─── Рассчитывает расположение полей ввода в указанном окне ───

// Box_window - окно, для которого надо рассчитать расположение полей ввода, Layout - список полей ввода.
// Возвращаемое значение показывает, было ли хотя бы одно поле ввода перемещено на самом деле.
BYTE Layout_ResizeInputFields( HWND Box_window, PLTWALL Layout )
{
 // Задаем матрицу для полей ввода.
 #define LTM_FIELDS_IN_ROW  25
 #define LTM_ROWS_IN_MATRIX 50

 #define LTM_FIELDS_IN_MATRIX ( LTM_FIELDS_IN_ROW * LTM_ROWS_IN_MATRIX )

 typedef struct _MATRIX
  {
   // Ряды полей ввода в матрице снизу вверх.
   typedef struct _ROW
    {
     // Расположение ряда по вертикали и высота ряда.
     INT Y; INT Height; BYTE Row_can_be_shrinked;

     // Поля ввода в каждом ряду слева направо.
     typedef struct _FIELD
      {
       // Расположение поля ввода по горизонтали и ширина поля ввода.
       INT X; INT Width; BYTE Field_can_be_shrinked;

       // Указатель на сведения о поле ввода.
       PLTBRICK Layout_pointer;
      }
     FIELD;

     INT Extension; FIELD Fields[ LTM_FIELDS_IN_ROW ];
    }
   ROW;

   INT Altitude; ROW Rows[ LTM_ROWS_IN_MATRIX ];
  }
 MATRIX; typedef MATRIX* PMATRIX;

 // Заполняем матрицу.
 PMATRIX Matrix = NULL;
 if( DosAllocMem( (PPVOID) &Matrix, sizeof( MATRIX ), PAG_ALLOCATE ) != NO_ERROR ) return 0;

 Matrix->Altitude = 0;

 {
  // Узнаем все поля ввода в указанном окне.
  HWND Fields[ LTM_FIELDS_IN_MATRIX ]; INT Quantity = 0;

  // Перебираем окна в указанном окне и запоминаем их.
  HENUM Enumeration = WinBeginEnumWindows( Box_window ); HWND Field = NULLHANDLE;
  while( ( Field = WinGetNextWindow( Enumeration ) ) != NULLHANDLE )
   {
    Fields[ Quantity ] = Field; Quantity ++;
   }
  WinEndEnumWindows( Enumeration );

  // Если поля ввода были найдены:
  if( Quantity )
   {
    // Просматриваем список, содержащий значения для расположения полей ввода и заполняем матрицу.
    for( INT Position = 0; Position < Layout->ulQuantity; Position ++ )
     {
      // Узнаем значение из списка.
      HWND Layout_field = NULLHANDLE;

      PLTBRICK Pointer = Layout_GetBrickPointer( Layout, Position );

      if( Pointer != NULL ) Layout_field = Pointer->hwnd;
      else continue;

      // Если это признак следующего ряда - продолжаем просмотр списка.
      if( Layout_field == (HWND) LTM_NEXT_ROW_MARK ) continue;

      // Узнаем, соответствует ли значение из списка одному из найденных полей ввода.
      BYTE Field_is_present_in_layout = 0;

      for( INT Count = 0; Count < Quantity; Count ++ )
       if( Fields[ Count ] == Layout_field )
        {
         Field_is_present_in_layout = 1;
         break;
        }

      // Если поле ввода присутствует в списке:
      if( Field_is_present_in_layout )
       {
        // Если матрица пуста - запоминаем, что у нее есть один ряд.
        if( !Matrix->Altitude && !Matrix->Rows[ 0 ].Extension ) Matrix->Altitude = 1;

        // Если ряд не заполнен до отказа:
        if( Matrix->Rows[ Matrix->Altitude - 1 ].Extension <= LTM_FIELDS_IN_ROW )
         {
          // Запоминаем поле ввода.
          Matrix->Rows[ Matrix->Altitude - 1 ].Extension ++;
          Matrix->Rows[ Matrix->Altitude - 1 ].Fields[ Matrix->Rows[ Matrix->Altitude - 1 ].Extension - 1 ].Layout_pointer = Pointer;

          // Пробуем получить следующее значение из списка.
          INT Latest_position = Layout->ulQuantity - 1;

          if( Position < Latest_position )
           {
            // Перебираем поля. Самое последнее значение не учитываем - там может быть признак следующего ряда.
            for( INT Next_position = Position + 1; Next_position < Latest_position - 1; Next_position ++ )
             {
              PLTBRICK Next_pointer = Layout_GetBrickPointer( Layout, Next_position );

              if( Next_pointer != NULL )
               {
                // Если это постороннее поле ввода - продолжаем поиск.
                // Если это поле ввода в том же окне - прекращаем поиск.
                if( Next_pointer->hwnd != (HWND) LTM_NEXT_ROW_MARK )
                 {
                  if( WinQueryWindow( Next_pointer->hwnd, QW_PARENT ) != Box_window )
                   continue;
                  else
                   break;
                 }

                // Если это признак следующего ряда - увеличиваем число рядов в матрице.
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

 // Пока ни одно поле ввода не перемещено.
 BYTE Fields_are_moved = 0;

 // Если в матрице оказалось хотя бы одно поле ввода:
 if( Matrix->Altitude )
  {
   {
    // Запоминаем, какие поля ввода и ряды можно сжимать при необходимости.
    for( INT Row_count = 0; Row_count < Matrix->Altitude; Row_count ++ )
     {
      // Считаем, что ряд может быть сжат.
      PBYTE Row_can_be_shrinked = &Matrix->Rows[ Row_count ].Row_can_be_shrinked;

      *Row_can_be_shrinked = 1;

      for( INT Field_count = 0; Field_count < Matrix->Rows[ Row_count ].Extension; Field_count ++ )
       {
        // Узнаем указатель на свойства поля ввода.
        PLTBRICK Pointer = Matrix->Rows[ Row_count ].Fields[ Field_count ].Layout_pointer;

        // Если для данного поля ввода задана ширина не в точках, а в %% от размера родительского окна - его можно сжимать.
        PBYTE Field_can_be_shrinked = &Matrix->Rows[ Row_count ].Fields[ Field_count ].Field_can_be_shrinked;

        *Field_can_be_shrinked = 0;

        if( Pointer != NULL )
         if( Pointer->prpWidthInParent <= 1.00 )
          *Field_can_be_shrinked = 1;

        // Если для одного из полей ввода задана высота в точках - ряд сжимать нельзя.
        if( Pointer->prpHeightInParent > 1.00 ) *Row_can_be_shrinked = 0;
       }
     }
   }

   // Узнаем размер окна.
   RECT Rectangle = {0}; WinQueryWindowRect( Box_window, &Rectangle );

   // Вычисляем расстояние между полями ввода и отступ внутри окна.
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
    // Задаем расположение всех рядов и полей в матрице. Считаем общую высоту.
    INT Row_bottom = Gap_Y; INT Total_height = Row_bottom + Margin_Y * 2;

    for( INT Row_count = 0; Row_count < Matrix->Altitude; Row_count ++ )
     {
      // Запоминаем высоту ряда.
      INT Row_height = 0;

      // Задаем расположение полей ввода. Считаем общую ширину.
      INT Field_bound = Gap_X; INT Total_width = Field_bound + Margin_X * 2;

      for( INT Field_count = 0; Field_count < Matrix->Rows[ Row_count ].Extension; Field_count ++ )
       {
        // Узнаем указатель на свойства поля ввода.
        PLTBRICK Pointer = Matrix->Rows[ Row_count ].Fields[ Field_count ].Layout_pointer;

        if( Pointer != NULL )
         {
          // Задаем ширину поля ввода.
          INT Width = 0;

          if( Pointer->prpWidthInParent > 1.00 ) Width = (INT) Pointer->prpWidthInParent;
          else Width = (INT) ( Rectangle.xRight * Pointer->prpWidthInParent );

          Matrix->Rows[ Row_count ].Fields[ Field_count ].X = Field_bound;
          Matrix->Rows[ Row_count ].Fields[ Field_count ].Width = Width;

          Field_bound += Width + Gap_X;
          Total_width += Width + Gap_X;

          // Задаем высоту ряда, учитывая высоту каждого поля ввода.
          INT Height = 0;

          if( Pointer->prpHeightInParent > 1.00 ) Height = (INT) Pointer->prpHeightInParent;
          else Height = (INT) ( Rectangle.yTop * Pointer->prpHeightInParent );

          if( Height > Row_height ) Row_height = Height;
         }
       }

      // Задаем расположение каждого ряда.
      Matrix->Rows[ Row_count ].Y = Row_bottom;
      Matrix->Rows[ Row_count ].Height = Row_height;

      Row_bottom += Row_height + Gap_Y;
      Total_height += Row_height + Gap_Y;

      // Сжимаем или растягиваем матрицу так, чтобы она подходила под размер окна.
      if( Total_width != Rectangle.xRight )
       {
        // Если общая ширина ряда меньше необходимой - растягиваем поля ввода.
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
        // А если общая ширина превышает ширину ряда - сжимаем поля ввода.
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

    // Сжимаем или растягиваем матрицу так, чтобы она подходила под размер окна.
    if( Total_height != Rectangle.yTop )
     {
      // Если общая высота меньше высоты окна - растягиваем ряды.
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
      // А если общая высота превышает высоту окна - сжимаем ряды.
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
    // Задаем расположение окон в соответствии со значениями матрицы и отступом от краев окна.
    for( INT Row_count = 0; Row_count < Matrix->Altitude; Row_count ++ )
     for( INT Field_count = 0; Field_count < Matrix->Rows[ Row_count ].Extension; Field_count ++ )
      {
       // Узнаем указатель на свойства поля ввода.
       PLTBRICK Pointer = Matrix->Rows[ Row_count ].Fields[ Field_count ].Layout_pointer;

       if( Pointer != NULL )
        {
         // Устанавливаем новое расположение окна.
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

         // Если расположение окна должно измениться - передвигаем его.
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

 // Освобождаем память.
 DosFreeMem( Matrix ); Matrix = NULL;

 // Возврат.
 return Fields_are_moved;
}

// ─── Рассчитывает расположение полей ввода во всех окнах ───

// Layout - список полей ввода.
VOID Layout_LitApplyLayout( PLTWALL Layout )
{
 // Если список задан неверно - возврат.
 if( !Layout_ListIsCorrect( Layout ) ) return;

 // Отключаем рисование во всех окнах.
 HWND Changed_windows[ WNDTREE_SIZE ]; EnableWindowTreeUpdate( Layout->hwnd, 0, Changed_windows );

 // Рассчитываем расположение полей ввода во всех окнах, где они могут быть.
 // Вначале пробуем переместить поля ввода в основном окне, чтобы проверить,
 // надо ли вообще менять их расположение, а затем проходим все дерево окон.
 HWND Tree[ WNDTREE_SIZE ]; INT Length = WNDTREE_SIZE; ExploreWindowTree( Layout->hwnd, Tree, &Length );

 if( Layout_ResizeInputFields( Tree[ 0 ], Layout ) )
  for( INT Count = 1; Count < Length; Count ++ )
    Layout_ResizeInputFields( Tree[ Count ], Layout );

 // Включаем рисование во всех окнах.
 EnableWindowTreeUpdate( Layout->hwnd, 1, Changed_windows );

 // Возврат.
 return;
}

// ─── Показывает окно рамки со всеми полями ввода ───

// Layout - список полей ввода.
VOID Layout_LitShowFrameWindow( PLTWALL Layout )
{
 // Если список задан неверно - возврат.
 if( !Layout_ListIsCorrect( Layout ) ) return;

 // Находим в списке окно, для которого задана раскладка.
 for( INT Count = 0; Count < Layout->ulQuantity; Count ++ )
  {
   // Узнаем указатель на свойства поля ввода.
   PLTBRICK Pointer = Layout_GetBrickPointer( Layout, Count );

   // Если это окно, для которого задана раскладка:
   if( Pointer != NULL ) if( Pointer->hwnd == Layout->hwnd )
    {
     // Выбираем окно рамки - это или найденное окно, или родительское для него.
     HWND Frame_window = Layout->hwnd;

     HWND Parent_window = WinQueryWindow( Frame_window, QW_PARENT );
     if( Layout->hwnd == WinWindowFromID( Parent_window, FID_CLIENT ) ) Frame_window = Parent_window;

     // Узнаем родительское окно для окна рамки.
     HWND Container_window = WinQueryWindow( Frame_window, QW_PARENT );

     // Узнаем размер родительского окна.
     RECT Rectangle = {0}; WinQueryWindowRect( Container_window, &Rectangle );

     // Рассчитываем размер окна рамки.
     INT Width = 0; INT Height = 0;

     if( Pointer->prpWidthInParent > 1.00 ) Width = (INT) Pointer->prpWidthInParent;
     else Width = (INT) ( Rectangle.xRight * Pointer->prpWidthInParent );

     if( Width > Rectangle.xRight ) Width = Rectangle.xRight;

     if( Pointer->prpHeightInParent > 1.00 ) Height = (INT) Pointer->prpHeightInParent;
     else Height = (INT) ( Rectangle.yTop * Pointer->prpHeightInParent );

     if( Height > Rectangle.yTop ) Height = Rectangle.yTop;

     // Устанавливаем новое расположение окна.
     INT X = ( Rectangle.xRight - Width ) / 2;
     INT Y = ( Rectangle.yTop - Height ) * 3 / 4;

     WinSetWindowPos( Frame_window, HWND_TOP, X, Y, Width, Height, SWP_MOVE | SWP_SIZE | SWP_SHOW | SWP_ACTIVATE );
    }
  }

 // Возврат.
 return;
}
