
// ─── Метод для подключения класса ───

VOID Drawing_Start( LONG Settings_to_show = SET_ALL_SETTINGS )
{
 #ifdef Drawing_Themes
 bzero( &Drawing_Themes, sizeof( Drawing_Themes ) );
 #endif

 #ifdef Drawing_Restrictions
 bzero( &Drawing_Restrictions, sizeof( Drawing_Restrictions ) );
 #endif

 #ifdef Drawing_Titlebars
 bzero( &Drawing_Titlebars, sizeof( Drawing_Titlebars ) );
 #endif

 #ifdef Drawing_Buttons
 bzero( &Drawing_Buttons, sizeof( Drawing_Buttons ) );
 #endif

 #ifdef Drawing_Exceptions
 bzero( &Drawing_Exceptions, sizeof( Drawing_Exceptions ) );
 #endif

 // Узнаем страну, в которой работает приложение.
 LONG Code_page = Enhancer.Code_page;

 {
  // Задаем указатели в списке составляющих расширителя.
  {
   PAGE Item; PresetPageItem( &Item );

   if( Code_page == RUSSIAN ) strcpy( Item.Name, StrConst_RU_Pages_Drawing_themes_Name );
   else strcpy( Item.Name, StrConst_EN_Pages_Drawing_themes_Name );

   Item.Settings_to_show = SET_DRAWING;
   strcpy( Item.Icon_name, "Drw_page.ico" );

   Item.CreatePage     = Drawing_Themes_CreatePage;
   Item.SetDefSettings = Painter_SetPreDefinedSettings;
   Item.ReadSettings   = Painter_ReadSettings;

   RememberPageItem( Enhancer.Pages.Drawing_themes, &Item );
  }

  // Задаем ID полей ввода.
  Drawing_Themes.Settings.Container_ID        = 1001;
  Drawing_Themes.Settings.Texture_filebox_ID  = 1002;
  Drawing_Themes.Settings.Texture_label_ID    = 1003;
  Drawing_Themes.Settings.Texture_name_ID     = 1004;
  Drawing_Themes.Settings.Texture_button_ID   = 1005;
  Drawing_Themes.Settings.Theme_list_ID       = 1006;
  Drawing_Themes.Settings.Theme_button_ID     = 1007;
 }

 {
  // Задаем указатели в списке составляющих расширителя.
  {
   PAGE Item; PresetPageItem( &Item );

   Item.Style = BKA_MINOR;

   if( Code_page == RUSSIAN ) strcpy( Item.Name, StrConst_RU_Pages_Drawing_Restrictions_Name );
   else strcpy( Item.Name, StrConst_EN_Pages_Drawing_Restrictions_Name );

   Item.Settings_to_show = SET_DRAWING;
   strcpy( Item.Icon_name, "Drw_page.ico" );

   Item.CreatePage     = Drawing_Restrictions_CreatePage;
   Item.SetDefSettings = Painter_SetPreDefinedSettings;
   Item.ReadSettings   = Painter_ReadSettings;

   RememberPageItem( Enhancer.Pages.Drawing_restrictions, &Item );
  }

  // Задаем ID полей ввода.
  Drawing_Restrictions.Settings.FixedColors_button_ID = 1001;
 }

 {
  // Задаем указатели в списке составляющих расширителя.
  {
   PAGE Item; PresetPageItem( &Item );

   if( Code_page == RUSSIAN ) strcpy( Item.Name, StrConst_RU_Pages_Drawing_Titlebars_Name );
   else strcpy( Item.Name, StrConst_EN_Pages_Drawing_Titlebars_Name );

   Item.Settings_to_show = SET_DRAWING;
   strcpy( Item.Icon_name, "Drw_page.ico" );

   Item.CreatePage     = Drawing_Titlebars_CreatePage;
   Item.SetDefSettings = Painter_SetPreDefinedSettings;
   Item.ReadSettings   = Painter_ReadSettings;

   RememberPageItem( Enhancer.Pages.Drawing_titlebars, &Item );
  }

  // Задаем ID полей ввода.
  Drawing_Titlebars.Settings.NeonPalette_Container_ID  = 1001;
  Drawing_Titlebars.Settings.NeonPalette_Palette_ID    = 1002;
  Drawing_Titlebars.Settings.NeonPalette_Inactive_1_ID = 1003;
  Drawing_Titlebars.Settings.NeonPalette_Inactive_2_ID = 1004;
  Drawing_Titlebars.Settings.NeonPalette_Inactive_3_ID = 1005;
  Drawing_Titlebars.Settings.NeonPalette_Active_1_ID   = 1006;
  Drawing_Titlebars.Settings.NeonPalette_Active_2_ID   = 1007;
  Drawing_Titlebars.Settings.NeonPalette_Active_3_ID   = 1008;
  Drawing_Titlebars.Settings.NeonPalette_FillTB_ID     = 1009;

  Drawing_Titlebars.Settings.WinTitles_Container_ID    = 2001;
  Drawing_Titlebars.Settings.WinTitles_Palette_ID      = 2002;
  Drawing_Titlebars.Settings.WinTitles_Inactive_ID     = 2003;
  Drawing_Titlebars.Settings.WinTitles_Active_ID       = 2004;
  Drawing_Titlebars.Settings.WinTitles_Button_ID       = 2005;
  Drawing_Titlebars.Settings.WinTitles_DrawText_ID     = 2006;
 }

 {
  // Задаем указатели в списке составляющих расширителя.
  {
   PAGE Item; PresetPageItem( &Item );

   if( Code_page == RUSSIAN ) strcpy( Item.Name, StrConst_RU_Pages_Drawing_Buttons_Name );
   else strcpy( Item.Name, StrConst_EN_Pages_Drawing_Buttons_Name );

   Item.Settings_to_show = SET_DRAWING;
   strcpy( Item.Icon_name, "Drw_page.ico" );

   Item.CreatePage     = Drawing_Buttons_CreatePage;
   Item.SetDefSettings = Painter_SetPreDefinedSettings;
   Item.ReadSettings   = Painter_ReadSettings;

   RememberPageItem( Enhancer.Pages.Drawing_buttons, &Item );
  }

  // Задаем ID полей ввода.
  Drawing_Buttons.Settings.Buttons_WPS_ID      = 1001;
  Drawing_Buttons.Settings.Buttons_VIO_ID      = 1003;

  Drawing_Buttons.Settings.RollUp_Container_ID = 2001;
  Drawing_Buttons.Settings.RollUp_List_ID      = 2002;
  Drawing_Buttons.Settings.RollUp_Add_ID       = 2003;
  Drawing_Buttons.Settings.RollUp_Remove_ID    = 2004;
 }

 {
  // Задаем указатели в списке составляющих расширителя.
  {
   PAGE Item; PresetPageItem( &Item );

   if( Code_page == RUSSIAN ) strcpy( Item.Name, StrConst_RU_Pages_Drawing_Exceptions_Name );
   else strcpy( Item.Name, StrConst_EN_Pages_Drawing_Exceptions_Name );

   Item.Settings_to_show = SET_DRAWING;
   strcpy( Item.Icon_name, "Drw_page.ico" );

   Item.CreatePage     = Drawing_Exceptions_CreatePage;
   Item.SetDefSettings = Painter_SetPreDefinedSettings;
   Item.ReadSettings   = Painter_ReadSettings;

   RememberPageItem( Enhancer.Pages.Drawing_exceptions, &Item );
  }

  // Задаем ID полей ввода.
  Drawing_Exceptions.Settings.Container_BorderDraw_ID     = 1001;
  Drawing_Exceptions.Settings.List_BorderDraw_ID          = 1002;
  Drawing_Exceptions.Settings.Add_button_BorderDraw_ID    = 1003;
  Drawing_Exceptions.Settings.Remove_button_BorderDraw_ID = 1004;

  Drawing_Exceptions.Settings.Container_Disable_ID        = 2001;
  Drawing_Exceptions.Settings.List_Disable_ID             = 2002;
  Drawing_Exceptions.Settings.Add_button_Disable_ID       = 2003;
  Drawing_Exceptions.Settings.Remove_button_Disable_ID    = 2004;
 }

 // Возврат.
 return;
}
