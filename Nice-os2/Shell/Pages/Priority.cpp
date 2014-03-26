
// ─── Метод для подключения класса ───

VOID Priority_Start( LONG Settings_to_show = SET_ALL_SETTINGS )
{
 #ifdef Priority_Variable
 bzero( &Priority_Variable, sizeof( Priority_Variable ) );
 #endif

 #ifdef Priority_Sedative
 bzero( &Priority_Sedative, sizeof( Priority_Sedative ) );
 #endif

 // Узнаем страну, в которой работает приложение.
 LONG Code_page = Enhancer.Code_page;

 {
  // Задаем указатели в списке составляющих расширителя.
  {
   PAGE Item; PresetPageItem( &Item );

   if( Code_page == RUSSIAN ) strcpy( Item.Name, StrConst_RU_Pages_Priority_variable_Name );
   else strcpy( Item.Name, StrConst_EN_Pages_Priority_variable_Name );

   Item.Settings_to_show = SET_PRIORITY;
   strcpy( Item.Icon_name, "Pty_page.ico" );

   Item.CreatePage     = Priority_Variable_CreatePage;
   Item.SetDefSettings = PriorityManager_SetPreDefinedSettings;
   Item.ReadSettings   = PriorityManager_ReadSettings;

   RememberPageItem( Enhancer.Pages.Priority_variable, &Item );
  }

  // Задаем ID полей ввода.
  Priority_Variable.Settings.Calculate_ID = 1001;
  Priority_Variable.Settings.VIO_ID       = 1002;
  Priority_Variable.Settings.lSwitcher_ID = 1003;
 }

 {
  // Задаем указатели в списке составляющих расширителя.
  {
   PAGE Item; PresetPageItem( &Item );

   if( Code_page == RUSSIAN ) strcpy( Item.Name, StrConst_RU_Pages_Priority_sedative_Name );
   else strcpy( Item.Name, StrConst_EN_Pages_Priority_sedative_Name );

   Item.Settings_to_show = SET_PRIORITY;
   strcpy( Item.Icon_name, "Pty_page.ico" );

   Item.CreatePage     = Priority_Sedative_CreatePage;
   Item.SetDefSettings = PriorityManager_SetPreDefinedSettings;
   Item.ReadSettings   = PriorityManager_ReadSettings;

   RememberPageItem( Enhancer.Pages.Priority_sedative, &Item );
  }

  // Задаем ID полей ввода.
  Priority_Sedative.Settings.WinList_Container_ID = 1001;
  Priority_Sedative.Settings.SelectBox_ID         = 1002;
  Priority_Sedative.Settings.AddRemove_ID         = 1003;
  Priority_Sedative.Settings.Window_list_ID       = 1004;
  Priority_Sedative.Settings.Window_Add_ID        = 1005;
  Priority_Sedative.Settings.Window_Remove_ID     = 1006;
  Priority_Sedative.Settings.Normalize_button_ID  = 1009;
 }

 // Возврат.
 return;
}
