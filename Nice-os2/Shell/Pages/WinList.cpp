
// ─── Метод для подключения класса ───

VOID WinList_Start( LONG Settings_to_show = SET_ALL_SETTINGS )
{
 #ifdef WinList_Settings
 bzero( &WinList_Settings, sizeof( WinList_Settings ) );
 #endif

 // Узнаем страну, в которой работает приложение.
 LONG Code_page = Enhancer.Code_page;

 {
  // Задаем указатели в списке составляющих расширителя.
  {
   PAGE Item; PresetPageItem( &Item );

   if( Code_page == RUSSIAN ) strcpy( Item.Name, StrConst_RU_Pages_WinList_settings_Name );
   else strcpy( Item.Name, StrConst_EN_Pages_WinList_settings_Name );

   Item.Settings_to_show = SET_WINLIST;
   strcpy( Item.Icon_name, "Lst_page.ico" );

   Item.CreatePage     = WinList_Settings_CreatePage;
   Item.SetDefSettings = Remover_SetPreDefinedSettings;
   Item.ReadSettings   = Remover_ReadSettings;

   RememberPageItem( Enhancer.Pages.WinList_settings, &Item );
  }

  // Задаем ID полей ввода.
  WinList_Settings.Settings.Modify_WinList_button_ID   = 1001;
  WinList_Settings.Settings.Container_ID               = 1002;
  WinList_Settings.Settings.Hidden_list_ID             = 1003;
  WinList_Settings.Settings.Hidden_buttons_ID          = 1004;
  WinList_Settings.Settings.Hidden_Move2V_button_ID    = 1005;
  WinList_Settings.Settings.Visible_list_ID            = 1006;
  WinList_Settings.Settings.Visible_buttons_ID         = 1007;
  WinList_Settings.Settings.Visible_Move2H_button_ID   = 1008;
  WinList_Settings.Settings.Visible_Refresh_button_ID  = 1009;
 }

 // Возврат.
 return;
}

