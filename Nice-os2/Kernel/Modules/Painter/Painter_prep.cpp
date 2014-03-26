
// ��� �����⠢������ ���� ��� �ᮢ���� ���

// *_window - ���� ࠬ��, ���������, ������ 㬥��襭�� � 㢥��祭��. *_rectangle - �� ࠧ����.
// �����頥��� ���祭��: 1 - �冷� � ���������� ���� �������⥫�� ����, 0 - ��� ⠪�� ����.
BYTE Painter_PrepareWindowControls( HWND Frame_window, LONG Frame_type, PRECT Frame_rectangle, PSWP Frame_placement, HWND TitleBar_window, HWND SysMenu_window, HWND MinMax_window )
{
 // ���� ������ ������ ᦨ������ � "|" � �ᯮ�������� ᫥�� �� ����� ������. ����
 // ��������� ��������� ��� ᦨ������ ⠪, �⮡� ��� ��ᠫ��� ����� ������. ��
 // ����, �ᯮ������� ����� ����, ��।�������� ��ࠢ� ��� �����. ����� �஢�����
 // �ᯮ������� ������ ������ � 㧭����� ᬥ饭�� ��� ��������� � ��㣨� ����.
 // �᫨ ���� ������ ������ ��� - ���� ��।������ ����.
 BYTE Controls_are_present = 0;

 // �᫨ ���� ���������, ���⨭�� � ������ ��������� - 㧭��� ��.
 if( TitleBar_window == NULLHANDLE ) TitleBar_window = WinWindowFromID( Frame_window, FID_TITLEBAR );
 if( SysMenu_window == NULLHANDLE ) SysMenu_window = WinWindowFromID( Frame_window, FID_SYSMENU );
 if( MinMax_window == NULLHANDLE ) MinMax_window = WinWindowFromID( Frame_window, FID_MINMAX );

 // �᫨ ���� ��������� ���� - 㧭��� ��� �ᯮ�������.
 SWP TitleBar_placement = {0};
 if( TitleBar_window != NULLHANDLE ) WinQueryWindowPos( TitleBar_window, &TitleBar_placement );

 // �᫨ ���� ���� ��������� - �஢��塞 ��� �ᯮ������� ����� ���� ࠬ��:
 if( TitleBar_window != NULLHANDLE )
  {
   // �᫨ ���� ��������� ����� ��� �ਭ� - ������.
   if( TitleBar_placement.cy > TitleBar_placement.cx ) return 0;

   // ������ ���� ����ﭭ��� ࠧ��� �ᯮ������ ��������� � ���⨭�� � ����� ���孥� 㣫�
   // �� ⠪, ��� ����, �������, �� �ਭ� �� ࠬ�� ࠢ�� �ਭ� ࠬ�� ���� ��६������ ࠧ���.
   if( Frame_type == FT_CONST )
    {
     // ������ �ਭ� ࠬ�� ����.
     INT Const_frame = 0; FindProperty( Frame_window, PRP_BORDER, &Const_frame );
     if( !Const_frame ) Const_frame = FrameWidth( Frame_window );

     // �஢��塞 �ᯮ������� ���� ���������. �᫨ ��� �� �� ����:
     if( TitleBar_placement.y + TitleBar_placement.cy < Frame_rectangle->yTop - Const_frame + 1 )
      if( TitleBar_placement.y + TitleBar_placement.cy > Frame_rectangle->yTop - Const_frame * 2 )
       {
        // ������ �ࠢ��쭮� �ᯮ������� ����.
        INT Offset = ( Frame_rectangle->yTop - Const_frame + 1 ) - ( TitleBar_placement.y + TitleBar_placement.cy );
        TitleBar_placement.y += Offset; TitleBar_placement.x -= Offset; TitleBar_placement.cx += Offset * 2;
        WinSetWindowPos( TitleBar_window, NULLHANDLE, TitleBar_placement.x, TitleBar_placement.y, TitleBar_placement.cx, TitleBar_placement.cy, SWP_SIZE | SWP_MOVE | SWP_NOADJUST );

        // �᫨ ���� ���� ���⨭�� - �஢��塞 ��� �ᯮ������� ����� ���� ࠬ��.
        if( SysMenu_window != NULLHANDLE )
         {
          // ������ �ᯮ������� ���� ���⨭��.
          SWP SysMenu_placement = {0};
          if( SysMenu_window != NULLHANDLE ) WinQueryWindowPos( SysMenu_window, &SysMenu_placement );

          // �஢��塞 �ᯮ������� ���� ���⨭��. �᫨ ��� �� �� ����:
          if( SysMenu_placement.y + SysMenu_placement.cy < Frame_rectangle->yTop - Const_frame + 1 )
           if( SysMenu_placement.y + SysMenu_placement.cy > Frame_rectangle->yTop - Const_frame * 2 )
            {
             // ������ �ࠢ��쭮� �ᯮ������� ����.
             INT Offset = ( Frame_rectangle->yTop - Const_frame + 1 ) - ( SysMenu_placement.y + SysMenu_placement.cy );
             SysMenu_placement.y += Offset; SysMenu_placement.x -= Offset;
             WinSetWindowPos( SysMenu_window, NULLHANDLE, SysMenu_placement.x, SysMenu_placement.y, SysMenu_placement.cx, SysMenu_placement.cy, SWP_MOVE | SWP_NOADJUST );
            }
         }
       }
    }
  }

 // �᫨ ������ �ᮢ��� �� ���� - ������.
 if( !Painter.Settings.Draw_buttons ) return 0;

 // ������ ࠧ��� ���� ���������
 RECT TitleBar_rectangle = {0}; WinQueryWindowRect( TitleBar_window, &TitleBar_rectangle );

 // ������ ��אַ㣮�쭨� ��� ������, ����� ���� ���ᮢ��� � ����.
 RECT All_buttons = {0};
 INT Size = Painter_CalculateButtonRectangles( Frame_window, Frame_rectangle, TitleBar_window, &TitleBar_rectangle, NULL, NULL, NULL, NULL, &All_buttons );

 // �᫨ ���� ������ ������ ���� - 㧭��� ��� �ᯮ�������.
 SWP MinMax_placement = {0};
 if( MinMax_window != NULLHANDLE ) WinQueryWindowPos( MinMax_window, &MinMax_placement );

 // ����������, ���� �� ������, �⮡� �筮 �஢����� �ᯮ������� ����.
 BYTE MinMax_is_available = 1;

 // ���� ������ ����� �� ����.
 if( MinMax_window == NULLHANDLE ) MinMax_is_available = 0;

 // �� ᮧ����� ���� ࠬ�� ���� ������ ������ ᦠ� � �ᯮ�������� �ࠢ� ��
 // ��אַ㣮�쭨��, ����� ��� ���� �।�����祭. ��⥬ ��� ����� �ᯮ�������.
 if( MinMax_placement.x == All_buttons.xRight + 1 )
  if( MinMax_placement.cx == 0 ) MinMax_is_available = 0;

 // �᫨ ������ �� ��⮢� � �� ��� - ������.
 if( !MinMax_is_available )
  if( All_buttons.xLeft == All_buttons.xRight )
   return 0;

 // �᫨ ���� ���� ���������:
 if( TitleBar_window != NULLHANDLE )
  {
   // ���� ��������� ����, ����� ������ ���� ��।������ � �, ����� ����� �������.
   HWND Controls[ PAINTER_MAX_CONTROLS ]; RECT Controls_rects[ PAINTER_MAX_CONTROLS ];
   HWND Fields[ PAINTER_MAX_CONTROLS ]; RECT Fields_rects[ PAINTER_MAX_CONTROLS ];
   INT Controls_quantity = 0; INT Fields_quantity = 0;

   // �஢�����, ����� �� ���� ������� ���� ⮫쪮 �᫨ ���� �࠭� ������.
   BYTE Hide_fields = 0;
   if( Frame_window == RolledWindow() ) Hide_fields = 1;

   // ���������� ����, ����� �஢����� �� ����.
   HWND Menu_window = WinWindowFromID( Frame_window, FID_MENU );
   HWND HSBar_window = WinWindowFromID( Frame_window, FID_HORZSCROLL );
   HWND VSBar_window = WinWindowFromID( Frame_window, FID_VERTSCROLL );

   // ��ॡ�ࠥ� ����, �ᯮ������ � ���� ࠬ�� � �஢��塞 ��.
   HENUM Enumeration = WinBeginEnumWindows( Frame_window ); HWND Window = NULLHANDLE;
   while( ( Window = WinGetNextWindow( Enumeration ) ) != NULLHANDLE )
    {
     // �᫨ �� ���� ���������, ����� ������ � �. �. - �த������ ��ॡ��.
     if( Window == SysMenu_window || Window == TitleBar_window || Window == MinMax_window ||
         Window == Menu_window    || Window == HSBar_window    || Window == VSBar_window )
      continue;

     // ������ �ᯮ������� ����.
     SWP Window_placement = {0}; WinQueryWindowPos( Window, &Window_placement );

     // �᫨ ���� �ᯮ������ ����� ���������� � �������� - ��� ���� ��।������.
     POINT Central_point = { Window_placement.x + Window_placement.cx / 2, Window_placement.y + Window_placement.cy / 2 };
     if( Central_point.y > TitleBar_placement.y )
      if( Central_point.y < TitleBar_placement.y + TitleBar_placement.cy )
       if( MinMax_is_available && ( Central_point.x > TitleBar_placement.x + TitleBar_placement.cx ) ||
          !MinMax_is_available && ( Central_point.x > TitleBar_placement.x + TitleBar_placement.cx / 2 ) )
        if( WinIsWindowVisible( Window ) )
         {
          // ���������� ���� � ��� �ᯮ�������.
          if( Controls_quantity < PAINTER_MAX_CONTROLS )
           {
            Controls[ Controls_quantity ] = Window;

            Controls_rects[ Controls_quantity ].xLeft = Window_placement.x;
            Controls_rects[ Controls_quantity ].xRight = Window_placement.x + Window_placement.cx;
            Controls_rects[ Controls_quantity ].yBottom = Window_placement.y;
            Controls_rects[ Controls_quantity ].yTop = Window_placement.y + Window_placement.cy;

            Controls_quantity ++;
           }
         }

     // �஢��塞, ����� �� ���� ����� �������.
     if( Hide_fields )
      {
       // �᫨ ���� ����뢠�� ������ - ��� ���� ᦠ��.
       BYTE Wring_out = 0;
       // ���� ����� ���筮 ����뢠�� ������.
       INT X_Allowable_space = 1; INT Y_Allowable_space = Size * 2 / 3;
       // �஢��塞 �ᯮ������� ��אַ㣮�쭨��� ᫥�� ���ࠢ�.
       if( Window_placement.y <= All_buttons.yTop &&
           Window_placement.y + Window_placement.cy > All_buttons.yBottom )
        {
         if( Window_placement.x >= All_buttons.xLeft &&
             Window_placement.x < All_buttons.xRight ) Wring_out = 1;
         if( Window_placement.x + Window_placement.cx > All_buttons.xLeft + X_Allowable_space &&
             Window_placement.x + Window_placement.cx <= All_buttons.xRight ) Wring_out = 1;
        }
       // �஢��塞 �ᯮ������� ��אַ㣮�쭨��� ᢥ��� ����.
       if( Window_placement.x <= All_buttons.xRight &&
           Window_placement.x + Window_placement.cx > All_buttons.xLeft )
        {
         if( Window_placement.y >= All_buttons.yBottom &&
             Window_placement.y < All_buttons.yTop ) Wring_out = 1;
         if( Window_placement.y + Window_placement.cy > All_buttons.yBottom + Y_Allowable_space &&
             Window_placement.y + Window_placement.cy <= All_buttons.yTop ) Wring_out = 1;
        }

       // ���������� ���� � ��� �ᯮ�������.
       if( Wring_out )
        if( Fields_quantity < PAINTER_MAX_CONTROLS )
         {
          Fields[ Fields_quantity ] = Window;

          Fields_rects[ Fields_quantity ].xLeft = Window_placement.x;
          Fields_rects[ Fields_quantity ].xRight = Window_placement.x + Window_placement.cx;
          Fields_rects[ Fields_quantity ].yBottom = Window_placement.y;
          Fields_rects[ Fields_quantity ].yTop = Window_placement.y + Window_placement.cy;

          Fields_quantity ++;
         }
      }
    }
   WinEndEnumWindows( Enumeration );

   // ��室�� �ࠩ��� �ࠢ�� ���� � ���������� ��� �ᯮ�������.
   INT Right_point = 0;
   for( INT Controls_count = 0; Controls_count < Controls_quantity; Controls_count ++ )
    if( Controls_rects[ Controls_count ].xRight > Right_point )
     Right_point = Controls_rects[ Controls_count ].xRight;

   // �᫨ ������ �� �� �����⮢���� - ���� �஢���� �ᯮ������� ����. ���� ����� ����
   // �ᯮ������ ᫥�� �� ��אַ㣮�쭨�� ��� ������, � ���� ⠪, ��� ��� ������ ����.
   if( !MinMax_is_available )
    if( All_buttons.xLeft != All_buttons.xRight )
     if( Right_point < All_buttons.xLeft + Size / 2 )
      Controls_quantity = 0;

   // ����塞 ᬥ饭�� ��� ����, �ᯮ������� ������ �㤥� ��������.
   INT Offset = 0;
   if( MinMax_window != NULLHANDLE ) Offset = All_buttons.xLeft - MinMax_placement.x;
   else
    if( Controls_quantity != 0 ) Offset = All_buttons.xLeft - Right_point;
    else Offset = Size;

   // ����� ���� �ਭ�� �襭�� � ⮬, �⮡� ᦠ�� �� ����.
   BYTE Hide_controls = 0;

   // ��।������ ����, �᫨ �� �ॡ����.
   if( Offset != 0 || Hide_controls )
    for( INT Controls_count = 0; Controls_count < Controls_quantity; Controls_count ++ )
     {
      // ��।������ ���� ��� ᦨ���� ���.
      INT X = 0; INT Y = 0; INT Width = 0;
      INT Height = Controls_rects[ Controls_count ].yTop - Controls_rects[ Controls_count ].yBottom;
      if( !Hide_controls )
       {
        X = Controls_rects[ Controls_count ].xLeft + Offset;
        Y = Controls_rects[ Controls_count ].yBottom;
        Width = Controls_rects[ Controls_count ].xRight - Controls_rects[ Controls_count ].xLeft;
       }
      else
       {
        X = All_buttons.xLeft;
        Y = All_buttons.yBottom;
        Width = 0;
       }

       // ��।������ ����.
       WinSetWindowPos( Controls[ Controls_count ], NULLHANDLE, X, Y, Width, Height, SWP_SIZE | SWP_MOVE | SWP_NOADJUST );

       // ���� ������ ���� ����ᮢ���. �� �������� ��� ����� �� ᤥ���� �⮣�.
       WinInvalidateRect( Controls[ Controls_count ], NULL, 0 );
     }

   // ���祬 ����, ����� ����� �������.
   if( Hide_fields )
    {
     // �஢��塞, ��� �� ����஢ � ᯨ᪠� ����.
     if( Controls_quantity != 0 && Fields_quantity != 0 )
      for( INT Fields_count = 0; Fields_count < Fields_quantity; Fields_count ++ )
       for( INT Controls_count = 0; Controls_count < Controls_quantity; Controls_count ++ )
        {
         // �᫨ ��������� ��������� �����:
         if( Fields[ Fields_count ] == Controls[ Controls_count ] )
          {
           // �������� ᯨ᮪ � ��砫� �� ���� ������.
           for( INT Count = Fields_count; Count < Fields_quantity - 1; Count ++ )
            {
             Fields[ Count ] = Fields[ Count + 1 ];
             memcpy( &Fields_rects[ Count ], &Fields_rects[ Count + 1 ], sizeof( RECT ) );
            }

           // �����蠥� ���稪.
           Fields_quantity --;
          }
        }

     // ������� ����, �᫨ ��� ����.
     if( Fields_quantity != 0 )
      for( INT Fields_count = 0; Fields_count < Fields_quantity; Fields_count ++ )
       {
        // ������ ����� �ᯮ������� ����
        INT X = Fields_rects[ Fields_count ].xLeft;
        INT Y = Fields_rects[ Fields_count ].yBottom;
        INT Width = Fields_rects[ Fields_count ].xRight - Fields_rects[ Fields_count ].xLeft;
        INT Height = 0;

        // ��।������ ����.
        WinSetWindowPos( Fields[ Fields_count ], NULLHANDLE, X, Y, Width, Height, SWP_SIZE | SWP_MOVE | SWP_NOADJUST );
       }
    }

   // �஢��塞, ���� �� ������ ���� ���������.
   BYTE Change_TitleBar = 0;
   INT New_width = All_buttons.xLeft - TitleBar_placement.x;
   if( Controls_quantity != 0 ) New_width = TitleBar_placement.cx + Offset;

   // �᫨ ��������� ������ ���� ᤢ���� ��ࠢ� ��� �����:
   if( !Hide_controls )
    {
     // �஢��塞 ᬥ饭��.
     if( Offset != 0 ) Change_TitleBar = 1;
    }
   // � �᫨ ��������� ������ ������� ����� ������:
   else
    {
     // �஢��塞 �ᯮ������� ���� ���������.
     if( TitleBar_placement.cx != New_width ) Change_TitleBar = 1;
    }

   // �᫨ ��� ���� ���� �ᮢ��� ⮫쪮 ������ ������� - ���� ������� ���� ���������.
   if( !Change_TitleBar ) if( Painter_OneActionIsAllowed( Frame_window ) ) Change_TitleBar = 1;

   // ��।������ �ࠢ� �ࠩ ���� ���������.
   if( Change_TitleBar )
    {
     INT X = TitleBar_placement.x;
     INT Y = TitleBar_placement.y;
     INT Height = TitleBar_placement.cy;

     for( INT Corrections_count = 0; Corrections_count < 10; Corrections_count ++ )
      {
       WinSetWindowPos( TitleBar_window, NULLHANDLE, X, Y, New_width, Height, SWP_SIZE | SWP_MOVE | SWP_NOADJUST );

       RECT TitleBar_rectangle = {0}; WinQueryWindowRect( TitleBar_window, &TitleBar_rectangle );
       if( TitleBar_rectangle.xRight - TitleBar_rectangle.xLeft == New_width ) break;
      }
    }

   // ����������, �뫨 �� ��।������ ���� � ���� ࠬ��.
   if( Controls_quantity != 0 ) Controls_are_present = 1;
  }

 // ���祬 ���� ������ ������.
 if( MinMax_window != NULLHANDLE )
  {
   // �஢��塞, ���� �� ������ ������.
   BYTE Change_MinMax = 0;
   if( MinMax_placement.cx != 0 ) Change_MinMax = 1;
   if( MinMax_placement.x != All_buttons.xLeft ) Change_MinMax = 1;

   // ���祬 ���� ������, �᫨ �� �ॡ����.
   if( Change_MinMax )
    {
     // ������� ����.
     INT X = All_buttons.xLeft;
     INT Y = All_buttons.yBottom;
     INT Width = 0;
     INT Height = MinMax_placement.cy;

     WinSetWindowPos( MinMax_window, NULLHANDLE, X, Y, Width, Height, SWP_SIZE | SWP_MOVE | SWP_NOADJUST );
    }
  }

 // ������.
 return Controls_are_present;
}
