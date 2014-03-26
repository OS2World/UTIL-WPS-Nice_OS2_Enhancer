
// ─── Метод для подключения класса ───

VOID SysPatches_Start( LONG Settings_to_show = SET_ALL_SETTINGS )
{
 #ifdef SysPatches_Settings
 bzero( &SysPatches_Settings, sizeof( SysPatches_Settings ) );
 #endif

 #ifdef SysPatches_Background
 bzero( &SysPatches_Background, sizeof( SysPatches_Background ) );
 #endif

 // Узнаем страну, в которой работает приложение.
 LONG Code_page = Enhancer.Code_page;

 {
  // Задаем указатели в списке составляющих расширителя.
  {
   PAGE Item; PresetPageItem( &Item );

   if( Code_page == RUSSIAN ) strcpy( Item.Name, StrConst_RU_Pages_SysPatches_settings_Name );
   else strcpy( Item.Name, StrConst_EN_Pages_SysPatches_settings_Name );

   Item.Settings_to_show = SET_SYS_PATCHES;
   strcpy( Item.Icon_name, "Dsk_page.ico" );

   Item.CreatePage          = SysPatches_Settings_CreatePage;
   Item.SetDefSettings      = Patcher_SetPreDefinedSettings;
   Item.ReadSettings        = Patcher_ReadSettings;

   RememberPageItem( Enhancer.Pages.SysPatches_settings, &Item );
  }

  // Задаем ID полей ввода.
  SysPatches_Settings.Settings.Animation_button_ID   = 1001;
  SysPatches_Settings.Settings.RestoreWnd_button_ID  = 1002;
 }

 {
  // Задаем указатели в списке составляющих расширителя.
  {
   PAGE Item; PresetPageItem( &Item );

   if( Code_page == RUSSIAN ) strcpy( Item.Name, StrConst_RU_Pages_SysPatches_background_Name );
   else strcpy( Item.Name, StrConst_EN_Pages_SysPatches_background_Name );

   Item.Settings_to_show = SET_SYS_PATCHES;
   strcpy( Item.Icon_name, "Dsk_page.ico" );

   Item.CreatePage     = SysPatches_Background_CreatePage;
   Item.SetDefSettings = SysPatches_Background_DoNothing;
   Item.ReadSettings   = SysPatches_Background_DoNothing;

   RememberPageItem( Enhancer.Pages.SysPatches_background, &Item );
  }

  // Задаем ID полей ввода.
  SysPatches_Background.Settings.Wallpaper_filebox_ID = 1001;
  SysPatches_Background.Settings.Wallpaper_label_ID   = 1002;
  SysPatches_Background.Settings.Wallpaper_name_ID    = 1003;
  SysPatches_Background.Settings.Wallpaper_button_ID  = 1004;

  SysPatches_Background.Settings.Example_ID           = 1005;
  SysPatches_Background.Settings.Comment_ID           = 1006;
 }

 // Возврат.
 return;
}
