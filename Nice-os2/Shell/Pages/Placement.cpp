
// ─── Метод для подключения класса ───

VOID Placement_Start( LONG Settings_to_show = SET_ALL_SETTINGS )
{
 #ifdef Placement_Settings
 bzero( &Placement_Settings, sizeof( Placement_Settings ) );
 #endif

 // Узнаем страну, в которой работает приложение.
 LONG Code_page = Enhancer.Code_page;

 {
  // Задаем указатели в списке составляющих расширителя.
  {
   PAGE Item; PresetPageItem( &Item );

   if( Code_page == RUSSIAN ) strcpy( Item.Name, StrConst_RU_Pages_Placement_settings_Name );
   else strcpy( Item.Name, StrConst_EN_Pages_Placement_settings_Name );

   Item.Settings_to_show = SET_PLACEMENT;
   strcpy( Item.Icon_name, "Wnd_page.ico" );

   Item.CreatePage     = Placement_Settings_CreatePage;
   Item.SetDefSettings = Arranger_SetPreDefinedSettings;
   Item.ReadSettings   = Arranger_ReadSettings;

   RememberPageItem( Enhancer.Pages.Placement_settings, &Item );
  }

  // Задаем ID полей ввода.
  Placement_Settings.Settings.VIO_button_ID        = 1001;
  Placement_Settings.Settings.FC2_button_ID        = 1002;
  Placement_Settings.Settings.WindowList_button_ID = 1003;
  Placement_Settings.Settings.WPS_button_ID        = 1004;
  Placement_Settings.Settings.Browser_button_ID    = 1005;
 }

 // Возврат.
 return;
}

