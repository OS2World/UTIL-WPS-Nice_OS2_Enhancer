{
 /* * */

 // Записываем настройки.
 PrfWriteProfileData( Ini_file, "Keys", NULL, NULL, 0 );

 {
  INT Count;
  for( Count = 0; Count < 1000000; Count ++ )
   {
    CHAR Setting_name[ SIZE_OF_NAME ] = ""; PINT Setting_value = NULL; BYTE Terminate = 0;

    switch( Count )
     {
      case  10: strcpy( Setting_name, "F11" ); Setting_value = &Definer.Settings.Keys.F11; break;
      case  11: strcpy( Setting_name, "F12" ); Setting_value = &Definer.Settings.Keys.F12; break;
      case  12: strcpy( Setting_name, "Shift + F11" ); Setting_value = &Definer.Settings.Keys.Shift_F11; break;
      case  13: strcpy( Setting_name, "Shift + F12" ); Setting_value = &Definer.Settings.Keys.Shift_F12; break;

      case  50: strcpy( Setting_name, "PrintScreen" ); Setting_value = &Definer.Settings.Keys.PrtScr; break;
      case  51: strcpy( Setting_name, "SysRq" ); Setting_value = &Definer.Settings.Keys.SysRq; break;
      case  52: strcpy( Setting_name, "Pause" ); Setting_value = &Definer.Settings.Keys.Pause; break;

      case  100: strcpy( Setting_name, "Right Alt" ); Setting_value = &Definer.Settings.Keys.Right_Alt; break;
      case  101: strcpy( Setting_name, "Shift + Right Alt" ); Setting_value = &Definer.Settings.Keys.Shift_Right_Alt; break;
      case  102: strcpy( Setting_name, "Left WinKey" ); Setting_value = &Definer.Settings.Keys.Left_WinKey; break;
      case  103: strcpy( Setting_name, "Right WinKey" ); Setting_value = &Definer.Settings.Keys.Right_WinKey; break;
      case  104: strcpy( Setting_name, "TaskList" ); Setting_value = &Definer.Settings.Keys.TaskList; break;

      case  1000: strcpy( Setting_name, "F1" ); Setting_value = &Definer.Settings.Keys.F1; break;
      case  1001: strcpy( Setting_name, "F2" ); Setting_value = &Definer.Settings.Keys.F2; break;
      case  1002: strcpy( Setting_name, "F3" ); Setting_value = &Definer.Settings.Keys.F3; break;
      case  1003: strcpy( Setting_name, "F4" ); Setting_value = &Definer.Settings.Keys.F4; break;
      case  1004: strcpy( Setting_name, "F5" ); Setting_value = &Definer.Settings.Keys.F5; break;
      case  1005: strcpy( Setting_name, "F6" ); Setting_value = &Definer.Settings.Keys.F6; break;
      case  1006: strcpy( Setting_name, "F7" ); Setting_value = &Definer.Settings.Keys.F7; break;
      case  1007: strcpy( Setting_name, "F8" ); Setting_value = &Definer.Settings.Keys.F8; break;
      case  1008: strcpy( Setting_name, "F9" ); Setting_value = &Definer.Settings.Keys.F9; break;
      case  1009: strcpy( Setting_name, "F10" ); Setting_value = &Definer.Settings.Keys.F10; break;

      case  2000: strcpy( Setting_name, "WK Backslash" ); Setting_value = &Definer.Settings.Keys.WinKey_Backslash; break;
      case  2001: strcpy( Setting_name, "WK Backspace" ); Setting_value = &Definer.Settings.Keys.WinKey_Backspace; break;

      case  2500: strcpy( Setting_name, "WK Num Slash" ); Setting_value = &Definer.Settings.Keys.WinKey_Num_Slash; break;
      case  2501: strcpy( Setting_name, "WK Num Multiple" ); Setting_value = &Definer.Settings.Keys.WinKey_Num_Multiple; break;
      case  2502: strcpy( Setting_name, "WK Num Minus" ); Setting_value = &Definer.Settings.Keys.WinKey_Num_Minus; break;
      case  2503: strcpy( Setting_name, "WK Num Plus" ); Setting_value = &Definer.Settings.Keys.WinKey_Num_Plus; break;
      case  2504: strcpy( Setting_name, "WK Num Enter" ); Setting_value = &Definer.Settings.Keys.WinKey_Num_Enter; break;

      case  3000: strcpy( Setting_name, "WK F1" ); Setting_value = &Definer.Settings.Keys.WinKey_F1; break;
      case  3001: strcpy( Setting_name, "WK F2" ); Setting_value = &Definer.Settings.Keys.WinKey_F2; break;
      case  3002: strcpy( Setting_name, "WK F3" ); Setting_value = &Definer.Settings.Keys.WinKey_F3; break;
      case  3003: strcpy( Setting_name, "WK F4" ); Setting_value = &Definer.Settings.Keys.WinKey_F4; break;
      case  3004: strcpy( Setting_name, "WK F5" ); Setting_value = &Definer.Settings.Keys.WinKey_F5; break;
      case  3005: strcpy( Setting_name, "WK F6" ); Setting_value = &Definer.Settings.Keys.WinKey_F6; break;
      case  3006: strcpy( Setting_name, "WK F7" ); Setting_value = &Definer.Settings.Keys.WinKey_F7; break;
      case  3007: strcpy( Setting_name, "WK F8" ); Setting_value = &Definer.Settings.Keys.WinKey_F8; break;
      case  3008: strcpy( Setting_name, "WK F9" ); Setting_value = &Definer.Settings.Keys.WinKey_F9; break;
      case  3009: strcpy( Setting_name, "WK F10" ); Setting_value = &Definer.Settings.Keys.WinKey_F10; break;
      case  3010: strcpy( Setting_name, "WK F11" ); Setting_value = &Definer.Settings.Keys.WinKey_F11; break;
      case  3011: strcpy( Setting_name, "WK F12" ); Setting_value = &Definer.Settings.Keys.WinKey_F12; break;

      case  3500: strcpy( Setting_name, "WK A" ); Setting_value = &Definer.Settings.Keys.WinKey_A; break;
      case  3501: strcpy( Setting_name, "WK B" ); Setting_value = &Definer.Settings.Keys.WinKey_B; break;
      case  3502: strcpy( Setting_name, "WK C" ); Setting_value = &Definer.Settings.Keys.WinKey_C; break;
      case  3503: strcpy( Setting_name, "WK D" ); Setting_value = &Definer.Settings.Keys.WinKey_D; break;
      case  3504: strcpy( Setting_name, "WK E" ); Setting_value = &Definer.Settings.Keys.WinKey_E; break;
      case  3505: strcpy( Setting_name, "WK F" ); Setting_value = &Definer.Settings.Keys.WinKey_F; break;
      case  3506: strcpy( Setting_name, "WK G" ); Setting_value = &Definer.Settings.Keys.WinKey_G; break;
      case  3507: strcpy( Setting_name, "WK H" ); Setting_value = &Definer.Settings.Keys.WinKey_H; break;
      case  3508: strcpy( Setting_name, "WK I" ); Setting_value = &Definer.Settings.Keys.WinKey_I; break;
      case  3509: strcpy( Setting_name, "WK J" ); Setting_value = &Definer.Settings.Keys.WinKey_J; break;
      case  3510: strcpy( Setting_name, "WK K" ); Setting_value = &Definer.Settings.Keys.WinKey_K; break;
      case  3511: strcpy( Setting_name, "WK L" ); Setting_value = &Definer.Settings.Keys.WinKey_L; break;
      case  3512: strcpy( Setting_name, "WK M" ); Setting_value = &Definer.Settings.Keys.WinKey_M; break;
      case  3513: strcpy( Setting_name, "WK N" ); Setting_value = &Definer.Settings.Keys.WinKey_N; break;
      case  3514: strcpy( Setting_name, "WK O" ); Setting_value = &Definer.Settings.Keys.WinKey_O; break;
      case  3515: strcpy( Setting_name, "WK P" ); Setting_value = &Definer.Settings.Keys.WinKey_P; break;
      case  3516: strcpy( Setting_name, "WK Q" ); Setting_value = &Definer.Settings.Keys.WinKey_Q; break;
      case  3517: strcpy( Setting_name, "WK R" ); Setting_value = &Definer.Settings.Keys.WinKey_R; break;
      case  3518: strcpy( Setting_name, "WK S" ); Setting_value = &Definer.Settings.Keys.WinKey_S; break;
      case  3519: strcpy( Setting_name, "WK T" ); Setting_value = &Definer.Settings.Keys.WinKey_T; break;
      case  3520: strcpy( Setting_name, "WK U" ); Setting_value = &Definer.Settings.Keys.WinKey_U; break;
      case  3521: strcpy( Setting_name, "WK V" ); Setting_value = &Definer.Settings.Keys.WinKey_V; break;
      case  3522: strcpy( Setting_name, "WK W" ); Setting_value = &Definer.Settings.Keys.WinKey_W; break;
      case  3523: strcpy( Setting_name, "WK X" ); Setting_value = &Definer.Settings.Keys.WinKey_X; break;
      case  3524: strcpy( Setting_name, "WK Y" ); Setting_value = &Definer.Settings.Keys.WinKey_Y; break;
      case  3525: strcpy( Setting_name, "WK Z" ); Setting_value = &Definer.Settings.Keys.WinKey_Z; break;

      case  4000: strcpy( Setting_name, "Power" ); Setting_value = &Definer.Settings.Keys.Power; break;
      case  4001: strcpy( Setting_name, "Sleep" ); Setting_value = &Definer.Settings.Keys.Sleep; break;
      case  4002: strcpy( Setting_name, "WakeUp" ); Setting_value = &Definer.Settings.Keys.WakeUp; break;

      case  5000: strcpy( Setting_name, "Play" ); Setting_value = &Definer.Settings.Keys.Play; break;
      case  5001: strcpy( Setting_name, "Stop" ); Setting_value = &Definer.Settings.Keys.Stop; break;
      case  5002: strcpy( Setting_name, "Previous track" ); Setting_value = &Definer.Settings.Keys.Previous_track; break;
      case  5003: strcpy( Setting_name, "Next track" ); Setting_value = &Definer.Settings.Keys.Next_track; break;
      case  5004: strcpy( Setting_name, "Volume decrement" ); Setting_value = &Definer.Settings.Keys.Volume_decrement; break;
      case  5005: strcpy( Setting_name, "Volume increment" ); Setting_value = &Definer.Settings.Keys.Volume_increment; break;
      case  5006: strcpy( Setting_name, "Mute" ); Setting_value = &Definer.Settings.Keys.Mute; break;
      case  5007: strcpy( Setting_name, "Media" ); Setting_value = &Definer.Settings.Keys.Media; break;

      case  6000: strcpy( Setting_name, "MyContooper" ); Setting_value = &Definer.Settings.Keys.MyContooper; break;
      case  6001: strcpy( Setting_name, "Calculator" ); Setting_value = &Definer.Settings.Keys.Calculator; break;
      case  6002: strcpy( Setting_name, "Browser" ); Setting_value = &Definer.Settings.Keys.Browser; break;
      case  6003: strcpy( Setting_name, "Mail reader" ); Setting_value = &Definer.Settings.Keys.Mail_reader; break;
      case  6004: strcpy( Setting_name, "Search" ); Setting_value = &Definer.Settings.Keys.Search; break;
      case  6005: strcpy( Setting_name, "Bookmarks" ); Setting_value = &Definer.Settings.Keys.Bookmarks; break;

      case  7000: strcpy( Setting_name, "Back" ); Setting_value = &Definer.Settings.Keys.Back; break;
      case  7001: strcpy( Setting_name, "Forward" ); Setting_value = &Definer.Settings.Keys.Forward; break;
      case  7002: strcpy( Setting_name, "Cancel" ); Setting_value = &Definer.Settings.Keys.Cancel; break;
      case  7003: strcpy( Setting_name, "Refresh" ); Setting_value = &Definer.Settings.Keys.Refresh; break;

      case  8000: strcpy( Setting_name, "PageLeft" ); Setting_value = &Definer.Settings.Keys.PageLeft; break;
      case  8001: strcpy( Setting_name, "PageRight" ); Setting_value = &Definer.Settings.Keys.PageRight; break;

      case  9021: strcpy( Setting_name, "UserKey 1" ); Setting_value = &Definer.Settings.Keys.UserKey_1; break;
      case  9022: strcpy( Setting_name, "UserKey 1 code" ); Setting_value = &Definer.Settings.Keys.SC_UserKey_1; break;
      case  9023: strcpy( Setting_name, "UserKey 2" ); Setting_value = &Definer.Settings.Keys.UserKey_2; break;
      case  9024: strcpy( Setting_name, "UserKey 2 code" ); Setting_value = &Definer.Settings.Keys.SC_UserKey_2; break;
      case  9025: strcpy( Setting_name, "UserKey 3" ); Setting_value = &Definer.Settings.Keys.UserKey_3; break;
      case  9026: strcpy( Setting_name, "UserKey 3 code" ); Setting_value = &Definer.Settings.Keys.SC_UserKey_3; break;
      case  9027: strcpy( Setting_name, "UserKey 4" ); Setting_value = &Definer.Settings.Keys.UserKey_4; break;
      case  9028: strcpy( Setting_name, "UserKey 4 code" ); Setting_value = &Definer.Settings.Keys.SC_UserKey_4; break;
      case  9029: strcpy( Setting_name, "UserKey 5" ); Setting_value = &Definer.Settings.Keys.UserKey_5; break;
      case  9030: strcpy( Setting_name, "UserKey 5 code" ); Setting_value = &Definer.Settings.Keys.SC_UserKey_5; break;
      case  9031: strcpy( Setting_name, "UserKey 6" ); Setting_value = &Definer.Settings.Keys.UserKey_6; break;
      case  9032: strcpy( Setting_name, "UserKey 6 code" ); Setting_value = &Definer.Settings.Keys.SC_UserKey_6; break;
      case  9033: strcpy( Setting_name, "UserKey 7" ); Setting_value = &Definer.Settings.Keys.UserKey_7; break;
      case  9034: strcpy( Setting_name, "UserKey 7 code" ); Setting_value = &Definer.Settings.Keys.SC_UserKey_7; break;
      case  9035: strcpy( Setting_name, "UserKey 8" ); Setting_value = &Definer.Settings.Keys.UserKey_8; break;
      case  9036: strcpy( Setting_name, "UserKey 8 code" ); Setting_value = &Definer.Settings.Keys.SC_UserKey_8; break;
      case  9037: strcpy( Setting_name, "UserKey 9" ); Setting_value = &Definer.Settings.Keys.UserKey_9; break;
      case  9038: strcpy( Setting_name, "UserKey 9 code" ); Setting_value = &Definer.Settings.Keys.SC_UserKey_9; break;
      case  9039: strcpy( Setting_name, "UserKey A" ); Setting_value = &Definer.Settings.Keys.UserKey_A; break;
      case  9040: strcpy( Setting_name, "UserKey A code" ); Setting_value = &Definer.Settings.Keys.SC_UserKey_A; break;
      case  9041: strcpy( Setting_name, "UserKey B" ); Setting_value = &Definer.Settings.Keys.UserKey_B; break;
      case  9042: strcpy( Setting_name, "UserKey B code" ); Setting_value = &Definer.Settings.Keys.SC_UserKey_B; break;
      case  9043: strcpy( Setting_name, "UserKey C" ); Setting_value = &Definer.Settings.Keys.UserKey_C; break;
      case  9044: strcpy( Setting_name, "UserKey C code" ); Setting_value = &Definer.Settings.Keys.SC_UserKey_C; break;
      case  9045: strcpy( Setting_name, "UserKey D" ); Setting_value = &Definer.Settings.Keys.UserKey_D; break;
      case  9046: strcpy( Setting_name, "UserKey D code" ); Setting_value = &Definer.Settings.Keys.SC_UserKey_D; break;
      case  9047: strcpy( Setting_name, "UserKey E" ); Setting_value = &Definer.Settings.Keys.UserKey_E; break;
      case  9048: strcpy( Setting_name, "UserKey E code" ); Setting_value = &Definer.Settings.Keys.SC_UserKey_E; break;
      case  9049: strcpy( Setting_name, "UserKey F" ); Setting_value = &Definer.Settings.Keys.UserKey_F; break;
      case  9050: strcpy( Setting_name, "UserKey F code" ); Setting_value = &Definer.Settings.Keys.SC_UserKey_F; break;

      case 10000: strcpy( Setting_name, "Compaq i" ); Setting_value = &Definer.Settings.Keys.Compaq_i; break;
      case 10001: strcpy( Setting_name, "Compaq Home" ); Setting_value = &Definer.Settings.Keys.Compaq_Home; break;
      case 10002: strcpy( Setting_name, "Compaq Search" ); Setting_value = &Definer.Settings.Keys.Compaq_Search; break;
      case 10003: strcpy( Setting_name, "Compaq Mail" ); Setting_value = &Definer.Settings.Keys.Compaq_Mail; break;
      case 10004: strcpy( Setting_name, "Compaq People" ); Setting_value = &Definer.Settings.Keys.Compaq_People; break;
      case 10005: strcpy( Setting_name, "Compaq Bench" ); Setting_value = &Definer.Settings.Keys.Compaq_Bench; break;
      case 10006: strcpy( Setting_name, "Compaq Chat" ); Setting_value = &Definer.Settings.Keys.Compaq_Chat; break;
      case 10007: strcpy( Setting_name, "Compaq Reading" ); Setting_value = &Definer.Settings.Keys.Compaq_Reading; break;

      case 20000: Terminate = 1; break;
     }

    if( Terminate ) break;

    if( Setting_value != NULL )
     {
      PrfWriteProfileData( Ini_file, "Keys", Setting_name, Setting_value, sizeof( INT ) );
     }
   }
 }

 {
  INT Position = -1;

  Position = FindApplicationInRepository( APP_USER_TOOL_1 );
  if( Repository.Items[ Position ].Exe_name_1[ 0 ] != 0 ) if( Repository.Items[ Position ].Exe_name_1[ 0 ] != '*' )
   {
    PrfWriteProfileData( Ini_file, "Applications", "UserTool 1 name", Repository.Items[ Position ].Exe_name_1, strlen( Repository.Items[ Position ].Exe_name_1 ) + 1 );
    PrfWriteProfileData( Ini_file, "Applications", "UserTool 1 object", NULL, 0 );
    PrfWriteProfileData( Ini_file, "Applications", "UserTool 1 path", Repository.Items[ Position ].Path, strlen( Repository.Items[ Position ].Path ) + 1 );
   }
  Position = FindApplicationInRepository( APP_USER_TOOL_2 );
  if( Repository.Items[ Position ].Exe_name_1[ 0 ] != 0 ) if( Repository.Items[ Position ].Exe_name_1[ 0 ] != '*' )
   {
    PrfWriteProfileData( Ini_file, "Applications", "UserTool 2 name", Repository.Items[ Position ].Exe_name_1, strlen( Repository.Items[ Position ].Exe_name_1 ) + 1 );
    PrfWriteProfileData( Ini_file, "Applications", "UserTool 2 object", NULL, 0 );
    PrfWriteProfileData( Ini_file, "Applications", "UserTool 2 path", Repository.Items[ Position ].Path, strlen( Repository.Items[ Position ].Path ) + 1 );
   }
  Position = FindApplicationInRepository( APP_USER_TOOL_3 );
  if( Repository.Items[ Position ].Exe_name_1[ 0 ] != 0 ) if( Repository.Items[ Position ].Exe_name_1[ 0 ] != '*' )
   {
    PrfWriteProfileData( Ini_file, "Applications", "UserTool 3 name", Repository.Items[ Position ].Exe_name_1, strlen( Repository.Items[ Position ].Exe_name_1 ) + 1 );
    PrfWriteProfileData( Ini_file, "Applications", "UserTool 3 object", NULL, 0 );
    PrfWriteProfileData( Ini_file, "Applications", "UserTool 3 path", Repository.Items[ Position ].Path, strlen( Repository.Items[ Position ].Path ) + 1 );
   }
  Position = FindApplicationInRepository( APP_USER_TOOL_4 );
  if( Repository.Items[ Position ].Exe_name_1[ 0 ] != 0 ) if( Repository.Items[ Position ].Exe_name_1[ 0 ] != '*' )
   {
    PrfWriteProfileData( Ini_file, "Applications", "UserTool 4 name", Repository.Items[ Position ].Exe_name_1, strlen( Repository.Items[ Position ].Exe_name_1 ) + 1 );
    PrfWriteProfileData( Ini_file, "Applications", "UserTool 4 object", NULL, 0 );
    PrfWriteProfileData( Ini_file, "Applications", "UserTool 4 path", Repository.Items[ Position ].Path, strlen( Repository.Items[ Position ].Path ) + 1 );
   }
  Position = FindApplicationInRepository( APP_USER_TOOL_5 );
  if( Repository.Items[ Position ].Exe_name_1[ 0 ] != 0 ) if( Repository.Items[ Position ].Exe_name_1[ 0 ] != '*' )
   {
    PrfWriteProfileData( Ini_file, "Applications", "UserTool 5 name", Repository.Items[ Position ].Exe_name_1, strlen( Repository.Items[ Position ].Exe_name_1 ) + 1 );
    PrfWriteProfileData( Ini_file, "Applications", "UserTool 5 object", NULL, 0 );
    PrfWriteProfileData( Ini_file, "Applications", "UserTool 5 path", Repository.Items[ Position ].Path, strlen( Repository.Items[ Position ].Path ) + 1 );
   }
  Position = FindApplicationInRepository( APP_USER_TOOL_6 );
  if( Repository.Items[ Position ].Exe_name_1[ 0 ] != 0 ) if( Repository.Items[ Position ].Exe_name_1[ 0 ] != '*' )
   {
    PrfWriteProfileData( Ini_file, "Applications", "UserTool 6 name", Repository.Items[ Position ].Exe_name_1, strlen( Repository.Items[ Position ].Exe_name_1 ) + 1 );
    PrfWriteProfileData( Ini_file, "Applications", "UserTool 6 object", NULL, 0 );
    PrfWriteProfileData( Ini_file, "Applications", "UserTool 6 path", Repository.Items[ Position ].Path, strlen( Repository.Items[ Position ].Path ) + 1 );
   }
  Position = FindApplicationInRepository( APP_USER_TOOL_7 );
  if( Repository.Items[ Position ].Exe_name_1[ 0 ] != 0 ) if( Repository.Items[ Position ].Exe_name_1[ 0 ] != '*' )
   {
    PrfWriteProfileData( Ini_file, "Applications", "UserTool 7 name", Repository.Items[ Position ].Exe_name_1, strlen( Repository.Items[ Position ].Exe_name_1 ) + 1 );
    PrfWriteProfileData( Ini_file, "Applications", "UserTool 7 object", NULL, 0 );
    PrfWriteProfileData( Ini_file, "Applications", "UserTool 7 path", Repository.Items[ Position ].Path, strlen( Repository.Items[ Position ].Path ) + 1 );
   }
  Position = FindApplicationInRepository( APP_USER_TOOL_8 );
  if( Repository.Items[ Position ].Exe_name_1[ 0 ] != 0 ) if( Repository.Items[ Position ].Exe_name_1[ 0 ] != '*' )
   {
    PrfWriteProfileData( Ini_file, "Applications", "UserTool 8 name", Repository.Items[ Position ].Exe_name_1, strlen( Repository.Items[ Position ].Exe_name_1 ) + 1 );
    PrfWriteProfileData( Ini_file, "Applications", "UserTool 8 object", NULL, 0 );
    PrfWriteProfileData( Ini_file, "Applications", "UserTool 8 path", Repository.Items[ Position ].Path, strlen( Repository.Items[ Position ].Path ) + 1 );
   }
  Position = FindApplicationInRepository( APP_USER_TOOL_9 );
  if( Repository.Items[ Position ].Exe_name_1[ 0 ] != 0 ) if( Repository.Items[ Position ].Exe_name_1[ 0 ] != '*' )
   {
    PrfWriteProfileData( Ini_file, "Applications", "UserTool 9 name", Repository.Items[ Position ].Exe_name_1, strlen( Repository.Items[ Position ].Exe_name_1 ) + 1 );
    PrfWriteProfileData( Ini_file, "Applications", "UserTool 9 object", NULL, 0 );
    PrfWriteProfileData( Ini_file, "Applications", "UserTool 9 path", Repository.Items[ Position ].Path, strlen( Repository.Items[ Position ].Path ) + 1 );
   }
  Position = FindApplicationInRepository( APP_USER_TOOL_A );
  if( Repository.Items[ Position ].Exe_name_1[ 0 ] != 0 ) if( Repository.Items[ Position ].Exe_name_1[ 0 ] != '*' )
   {
    PrfWriteProfileData( Ini_file, "Applications", "UserTool A name", Repository.Items[ Position ].Exe_name_1, strlen( Repository.Items[ Position ].Exe_name_1 ) + 1 );
    PrfWriteProfileData( Ini_file, "Applications", "UserTool A object", NULL, 0 );
    PrfWriteProfileData( Ini_file, "Applications", "UserTool A path", Repository.Items[ Position ].Path, strlen( Repository.Items[ Position ].Path ) + 1 );
   }
  Position = FindApplicationInRepository( APP_USER_TOOL_B );
  if( Repository.Items[ Position ].Exe_name_1[ 0 ] != 0 ) if( Repository.Items[ Position ].Exe_name_1[ 0 ] != '*' )
   {
    PrfWriteProfileData( Ini_file, "Applications", "UserTool B name", Repository.Items[ Position ].Exe_name_1, strlen( Repository.Items[ Position ].Exe_name_1 ) + 1 );
    PrfWriteProfileData( Ini_file, "Applications", "UserTool B object", NULL, 0 );
    PrfWriteProfileData( Ini_file, "Applications", "UserTool B path", Repository.Items[ Position ].Path, strlen( Repository.Items[ Position ].Path ) + 1 );
   }
  Position = FindApplicationInRepository( APP_USER_TOOL_C );
  if( Repository.Items[ Position ].Exe_name_1[ 0 ] != 0 ) if( Repository.Items[ Position ].Exe_name_1[ 0 ] != '*' )
   {
    PrfWriteProfileData( Ini_file, "Applications", "UserTool C name", Repository.Items[ Position ].Exe_name_1, strlen( Repository.Items[ Position ].Exe_name_1 ) + 1 );
    PrfWriteProfileData( Ini_file, "Applications", "UserTool C object", NULL, 0 );
    PrfWriteProfileData( Ini_file, "Applications", "UserTool C path", Repository.Items[ Position ].Path, strlen( Repository.Items[ Position ].Path ) + 1 );
   }
  Position = FindApplicationInRepository( APP_USER_TOOL_D );
  if( Repository.Items[ Position ].Exe_name_1[ 0 ] != 0 ) if( Repository.Items[ Position ].Exe_name_1[ 0 ] != '*' )
   {
    PrfWriteProfileData( Ini_file, "Applications", "UserTool D name", Repository.Items[ Position ].Exe_name_1, strlen( Repository.Items[ Position ].Exe_name_1 ) + 1 );
    PrfWriteProfileData( Ini_file, "Applications", "UserTool D object", NULL, 0 );
    PrfWriteProfileData( Ini_file, "Applications", "UserTool D path", Repository.Items[ Position ].Path, strlen( Repository.Items[ Position ].Path ) + 1 );
   }
  Position = FindApplicationInRepository( APP_USER_TOOL_E );
  if( Repository.Items[ Position ].Exe_name_1[ 0 ] != 0 ) if( Repository.Items[ Position ].Exe_name_1[ 0 ] != '*' )
   {
    PrfWriteProfileData( Ini_file, "Applications", "UserTool E name", Repository.Items[ Position ].Exe_name_1, strlen( Repository.Items[ Position ].Exe_name_1 ) + 1 );
    PrfWriteProfileData( Ini_file, "Applications", "UserTool E object", NULL, 0 );
    PrfWriteProfileData( Ini_file, "Applications", "UserTool E path", Repository.Items[ Position ].Path, strlen( Repository.Items[ Position ].Path ) + 1 );
   }
  Position = FindApplicationInRepository( APP_USER_TOOL_F );
  if( Repository.Items[ Position ].Exe_name_1[ 0 ] != 0 ) if( Repository.Items[ Position ].Exe_name_1[ 0 ] != '*' )
   {
    PrfWriteProfileData( Ini_file, "Applications", "UserTool F name", Repository.Items[ Position ].Exe_name_1, strlen( Repository.Items[ Position ].Exe_name_1 ) + 1 );
    PrfWriteProfileData( Ini_file, "Applications", "UserTool F object", NULL, 0 );
    PrfWriteProfileData( Ini_file, "Applications", "UserTool F path", Repository.Items[ Position ].Path, strlen( Repository.Items[ Position ].Path ) + 1 );
   }
 }

 /* * */
}
