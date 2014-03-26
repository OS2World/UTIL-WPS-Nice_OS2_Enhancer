
// ─── Метод для подключения класса ───

VOID Scrolling_Start( LONG Settings_to_show = SET_ALL_SETTINGS )
{
 #ifdef Scrolling_Settings
 bzero( &Scrolling_Settings, sizeof( Scrolling_Settings ) );
 #endif

 #ifdef Scrolling_Exceptions
 bzero( &Scrolling_Exceptions, sizeof( Scrolling_Exceptions ) );
 #endif

 // Узнаем страну, в которой работает приложение.
 LONG Code_page = Enhancer.Code_page;

 {
  // Задаем указатели в списке составляющих расширителя.
  {
   PAGE Item; PresetPageItem( &Item );

   if( Code_page == RUSSIAN ) strcpy( Item.Name, StrConst_RU_Pages_Scrolling_settings_Name );
   else strcpy( Item.Name, StrConst_EN_Pages_Scrolling_settings_Name );

   Item.Settings_to_show = SET_SCROLLING;
   strcpy( Item.Icon_name, "Scr_page.ico" );

   Item.CreatePage     = Scrolling_Settings_CreatePage;
   Item.SetDefSettings = Scroller_SetPreDefinedSettings;
   Item.ReadSettings   = Scroller_ReadSettings;

   RememberPageItem( Enhancer.Pages.Scrolling_settings, &Item );
  }

  // Задаем ID полей ввода.
  Scrolling_Settings.Settings.Smooth_scrolling_button_ID   = 1001;
  Scrolling_Settings.Settings.Keyboard_scrolling_button_ID = 1002;
  Scrolling_Settings.Settings.Mouse_scrolling_button_ID    = 1003;
  Scrolling_Settings.Settings.Mouse_scrolling_cmbox_ID     = 1004;
  Scrolling_Settings.Settings.Mouse_pointer_button_ID      = 1005;
  Scrolling_Settings.Settings.Mouse_pointer_cmbox_ID       = 1006;
 }

 {
  // Задаем указатели в списке составляющих расширителя.
  {
   PAGE Item; PresetPageItem( &Item );

   if( Code_page == RUSSIAN ) strcpy( Item.Name, StrConst_RU_Pages_Scrolling_exceptions_Name );
   else strcpy( Item.Name, StrConst_EN_Pages_Scrolling_exceptions_Name );

   Item.Settings_to_show = SET_SCROLLING;
   strcpy( Item.Icon_name, "Scr_page.ico" );

   Item.CreatePage     = Scrolling_Exceptions_CreatePage;
   Item.SetDefSettings = Scroller_SetPreDefinedSettings;
   Item.ReadSettings   = Scroller_ReadSettings;

   RememberPageItem( Enhancer.Pages.Scrolling_exceptions, &Item );
  }

  // Задаем ID полей ввода.
  Scrolling_Exceptions.Settings.Container_Kbd_ID     = 1001;
  Scrolling_Exceptions.Settings.List_Kbd_ID          = 1002;
  Scrolling_Exceptions.Settings.Add_button_Kbd_ID    = 1003;
  Scrolling_Exceptions.Settings.Remove_button_Kbd_ID = 1004;

  Scrolling_Exceptions.Settings.Container_Mou_ID     = 2001;
  Scrolling_Exceptions.Settings.List_Mou_ID          = 2002;
  Scrolling_Exceptions.Settings.Add_button_Mou_ID    = 2003;
  Scrolling_Exceptions.Settings.Remove_button_Mou_ID = 2004;
 }

 // Возврат.
 return;
}
