
// ─── Метод для подключения класса ───

VOID Keyboard_Start( LONG Settings_to_show = SET_ALL_SETTINGS )
{
 #ifdef Keyboard_Keys
 bzero( &Keyboard_Keys, sizeof( Keyboard_Keys ) );
 #endif

 #ifdef Keyboard_Actions
 bzero( &Keyboard_Actions, sizeof( Keyboard_Actions ) );
 #endif

 #ifdef Keyboard_Repository
 bzero( &Keyboard_Repository, sizeof( Keyboard_Repository ) );
 #endif

 #ifdef Keyboard_Clipboard
 bzero( &Keyboard_Clipboard, sizeof( Keyboard_Clipboard ) );
 #endif

 #ifdef Keyboard_FireFox
 bzero( &Keyboard_FireFox, sizeof( Keyboard_FireFox ) );
 #endif

 #ifdef Keyboard_Break
 bzero( &Keyboard_Break, sizeof( Keyboard_Break ) );
 #endif

 #ifdef Keyboard_Various
 bzero( &Keyboard_Various, sizeof( Keyboard_Various ) );
 #endif

 #ifdef Keyboard_VIO
 bzero( &Keyboard_VIO, sizeof( Keyboard_VIO ) );
 #endif

 #ifdef Keyboard_Speed
 bzero( &Keyboard_Speed, sizeof( Keyboard_Speed ) );
 #endif

 #ifdef Keyboard_Echo
 bzero( &Keyboard_Echo, sizeof( Keyboard_Echo ) );
 #endif

 // Узнаем страну, в которой работает приложение.
 LONG Code_page = Enhancer.Code_page;

 {
  // Задаем указатели в списке составляющих расширителя.
  {
   PAGE Item; PresetPageItem( &Item );

   if( Code_page == RUSSIAN ) strcpy( Item.Name, StrConst_RU_Pages_Keyboard_keys_Name );
   else strcpy( Item.Name, StrConst_EN_Pages_Keyboard_keys_Name );

   Item.Settings_to_show = SET_KEYBOARD;
   strcpy( Item.Icon_name, "Kbd_page.ico" );

   Item.CreatePage     = Keyboard_Keys_CreatePage;
   Item.SetDefSettings = Definer_SetPreDefinedSettings;
   Item.ReadSettings   = Definer_ReadSettings;

   RememberPageItem( Enhancer.Pages.Keyboard_keys, &Item );
  }

  // Задаем ID полей ввода.
  Keyboard_Keys.Settings.Container_ID     = 1001;
  Keyboard_Keys.Settings.Use_button_ID    = 1002;
  Keyboard_Keys.Settings.Kbd_list_ID      = 1003;
  Keyboard_Keys.Settings.Define_button_ID = 1004;
 }

 {
  // Задаем указатели в списке составляющих расширителя.
  {
   PAGE Item; PresetPageItem( &Item );

   if( Code_page == RUSSIAN ) strcpy( Item.Name, StrConst_RU_Pages_Keyboard_actions_Name );
   else strcpy( Item.Name, StrConst_EN_Pages_Keyboard_actions_Name );

   Item.Settings_to_show = SET_KEYBOARD;
   strcpy( Item.Icon_name, "Kbd_page.ico" );

   Item.CreatePage     = Keyboard_Actions_CreatePage;
   Item.SetDefSettings = Definer_SetPreDefinedSettings;
   Item.ReadSettings   = Definer_ReadSettings;

   RememberPageItem( Enhancer.Pages.Keyboard_actions, &Item );
  }

  // Задаем ID полей ввода.
  Keyboard_Actions.Settings.Detect_button_ID   = 1001;

  Keyboard_Actions.Settings.ExeName_filebox_ID = 1002;
  Keyboard_Actions.Settings.ExeName_label_ID   = 1003;
  Keyboard_Actions.Settings.ExeName_name_ID    = 1004;
  Keyboard_Actions.Settings.ExeName_button_ID  = 1005;

  Keyboard_Actions.Settings.SplitView_ID       = 1006;
  Keyboard_Actions.Settings.Key_list_ID        = 1007;
  Keyboard_Actions.Settings.Action_list_ID     = 1008;
 }

 {
  // Задаем указатели в списке составляющих расширителя.
  {
   PAGE Item; PresetPageItem( &Item );

   Item.Style = BKA_MINOR;

   if( Code_page == RUSSIAN ) strcpy( Item.Name, StrConst_RU_Pages_Keyboard_repository_Name );
   else strcpy( Item.Name, StrConst_EN_Pages_Keyboard_repository_Name );

   Item.Settings_to_show = SET_KEYBOARD;
   strcpy( Item.Icon_name, "Kbd_page.ico" );

   Item.CreatePage     = Keyboard_Repository_CreatePage;
   Item.SetDefSettings = Inspector_SetPreDefinedSettings;
   Item.ReadSettings   = Inspector_ReadSettings;

   RememberPageItem( Enhancer.Pages.Keyboard_repository, &Item );
  }

  // Задаем ID полей ввода.
  Keyboard_Repository.Settings.CheckWPS_button_ID  = 1001;
 }

 {
  // Задаем указатели в списке составляющих расширителя.
  {
   PAGE Item; PresetPageItem( &Item );

   if( Code_page == RUSSIAN ) strcpy( Item.Name, StrConst_RU_Pages_Keyboard_ffx_Name );
   else strcpy( Item.Name, StrConst_EN_Pages_Keyboard_ffx_Name );

   Item.Settings_to_show = SET_KEYBOARD;
   strcpy( Item.Icon_name, "Kbd_page.ico" );

   Item.CreatePage     = Keyboard_FireFox_CreatePage;
   Item.SetDefSettings = KeyMapper_SetPreDefinedSettings;
   Item.ReadSettings   = KeyMapper_ReadSettings;

   RememberPageItem( Enhancer.Pages.Keyboard_ffx, &Item );
  }

  // Задаем ID полей ввода.
  Keyboard_FireFox.Settings.Dash      = 1001;
  Keyboard_FireFox.Settings.Ctrl_Dash = 1002;
 }

 {
  // Задаем указатели в списке составляющих расширителя.
  {
   PAGE Item; PresetPageItem( &Item );

   if( Code_page == RUSSIAN ) strcpy( Item.Name, StrConst_RU_Pages_Keyboard_break_Name );
   else strcpy( Item.Name, StrConst_EN_Pages_Keyboard_break_Name );

   Item.Settings_to_show = SET_KEYBOARD;
   strcpy( Item.Icon_name, "Kbd_page.ico" );

   Item.CreatePage     = Keyboard_Break_CreatePage;
   Item.SetDefSettings = Controller_SetPreDefinedSettings;
   Item.ReadSettings   = Controller_ReadSettings;

   RememberPageItem( Enhancer.Pages.Keyboard_break, &Item );
  }

  // Задаем ID полей ввода.
  Keyboard_Break.Settings.CB_button_ID  = 1001;
  Keyboard_Break.Settings.CAD_button_ID = 1002;
 }

 {
  // Задаем указатели в списке составляющих расширителя.
  {
   PAGE Item; PresetPageItem( &Item );

   if( Code_page == RUSSIAN ) strcpy( Item.Name, StrConst_RU_Pages_Keyboard_various_Name );
   else strcpy( Item.Name, StrConst_EN_Pages_Keyboard_various_Name );

   Item.Settings_to_show = SET_KEYBOARD;
   strcpy( Item.Icon_name, "Kbd_page.ico" );

   Item.CreatePage          = Keyboard_Various_CreatePage;
   Item.SetDefSettings      = Controller_SetPreDefinedSettings;
   Item.SetDefSettings_Ext1 = KeyMapper_SetPreDefinedSettings;
   Item.ReadSettings        = Controller_ReadSettings;
   Item.ReadSettings_Ext1   = KeyMapper_ReadSettings;

   RememberPageItem( Enhancer.Pages.Keyboard_various, &Item );
  }

  // Задаем ID полей ввода.
  Keyboard_Various.Settings.Keep_NumLock   = 1001;
  Keyboard_Various.Settings.NumLock_cbox   = 1002;
  Keyboard_Various.Settings.NumKeys        = 1003;

  Keyboard_Various.Settings.Ctrl_CV        = 1005;
  Keyboard_Various.Settings.WPS_Enter      = 1006;
  Keyboard_Various.Settings.CUA_F3         = 1007;
 }

 {
  // Задаем указатели в списке составляющих расширителя.
  {
   PAGE Item; PresetPageItem( &Item );

   if( Code_page == RUSSIAN ) strcpy( Item.Name, StrConst_RU_Pages_Keyboard_VIO_Name );
   else strcpy( Item.Name, StrConst_EN_Pages_Mouse_VIO_Name );

   Item.Settings_to_show = SET_KEYBOARD;
   strcpy( Item.Icon_name, "Kbd_page.ico" );

   Item.CreatePage          = Keyboard_VIO_CreatePage;
   Item.SetDefSettings      = Clipper_SetPreDefinedSettings;
   Item.SetDefSettings_Ext1 = KeyMapper_SetPreDefinedSettings;
   Item.ReadSettings        = Clipper_ReadSettings;
   Item.ReadSettings_Ext1   = KeyMapper_ReadSettings;

   RememberPageItem( Enhancer.Pages.Keyboard_VIO, &Item );
  }

  // Задаем ID полей ввода.
  Keyboard_VIO.Settings.CopyPaste_button_ID       = 1001;
  Keyboard_VIO.Settings.WinCloseHide_button_ID    = 1002;
 }

 {
  // Задаем указатели в списке составляющих расширителя.
  {
   PAGE Item; PresetPageItem( &Item );

   if( Code_page == RUSSIAN ) strcpy( Item.Name, StrConst_RU_Pages_Keyboard_speed_Name );
   else strcpy( Item.Name, StrConst_EN_Pages_Keyboard_speed_Name );

   Item.Settings_to_show = SET_KEYBOARD;
   strcpy( Item.Icon_name, "Kbd_page.ico" );

   Item.CreatePage     = Keyboard_Speed_CreatePage;
   Item.SetDefSettings = Controller_SetPreDefinedSettings;
   Item.ReadSettings   = Controller_ReadSettings;

   RememberPageItem( Enhancer.Pages.Keyboard_speed, &Item );
  }

  // Задаем ID полей ввода.
  Keyboard_Speed.Settings.Reset_Shift_button_ID = 1001;

  Keyboard_Speed.Settings.SpeedUp_button_ID     = 1002;
  Keyboard_Speed.Settings.Rate_cbox_ID          = 1003;
 }

 {
  // Задаем указатели в списке составляющих расширителя.
  {
   PAGE Item; PresetPageItem( &Item );

   if( Code_page == RUSSIAN ) strcpy( Item.Name, StrConst_RU_Pages_Keyboard_echo_Name );
   else strcpy( Item.Name, StrConst_EN_Pages_Keyboard_echo_Name );

   Item.Settings_to_show = SET_KEYBOARD;
   strcpy( Item.Icon_name, "Kbd_page.ico" );

   Item.CreatePage     = Keyboard_Echo_CreatePage;
   Item.SetDefSettings = Clicker_SetPreDefinedSettings;
   Item.ReadSettings   = Clicker_ReadSettings;

   RememberPageItem( Enhancer.Pages.Keyboard_echo, &Item );
  }

  // Задаем ID полей ввода.
  Keyboard_Echo.Settings.Play_sound = 1001;
  Keyboard_Echo.Settings.For_IRC    = 1002;
  Keyboard_Echo.Settings.For_ICQ    = 1003;

  Keyboard_Echo.Settings.Use_RAMFS  = 1004;
 }

 // Возврат.
 return;
}

