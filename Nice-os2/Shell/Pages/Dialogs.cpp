
// ─── Метод для подключения класса ───

VOID Dialogs_Start( LONG Settings_to_show = SET_ALL_SETTINGS )
{
 #ifdef Dialogs_Logon
 bzero( &Dialogs_Logon, sizeof( Dialogs_Logon ) );
 #endif

 #ifdef Dialogs_Fields
 bzero( &Dialogs_Fields, sizeof( Dialogs_Fields ) );
 #endif

 #ifdef Dialogs_Boxes
 bzero( &Dialogs_Boxes, sizeof( Dialogs_Boxes ) );
 #endif

 // Узнаем страну, в которой работает приложение.
 LONG Code_page = Enhancer.Code_page;

 {
  // Задаем указатели в списке составляющих расширителя.
  {
   PAGE Item; PresetPageItem( &Item );

   if( Code_page == RUSSIAN ) strcpy( Item.Name, StrConst_RU_Pages_Dialogs_logon_Name );
   else strcpy( Item.Name, StrConst_EN_Pages_Dialogs_logon_Name );

   Item.Settings_to_show = SET_DIALOG_BOXES;
   strcpy( Item.Icon_name, "Dlg_page.ico" );

   Item.CreatePage     = Dialogs_Logon_CreatePage;
   Item.SetDefSettings = Applier_SetPreDefinedSettings;
   Item.ReadSettings   = Applier_ReadSettings;

   RememberPageItem( Enhancer.Pages.Dialogs_logon, &Item );
  }

  // Задаем ID полей ввода.
  Dialogs_Logon.Settings.WinList_Container_ID = 1001;
  Dialogs_Logon.Settings.CommandBox_ID        = 1002;
  Dialogs_Logon.Settings.AddRemove_ID         = 1003;
  Dialogs_Logon.Settings.OnlyOnce_button_ID   = 1004;
  Dialogs_Logon.Settings.Command_entry_ID     = 1005;
  Dialogs_Logon.Settings.Command_button_ID    = 1006;
  Dialogs_Logon.Settings.Window_list_ID       = 1007;
  Dialogs_Logon.Settings.Window_Add_ID        = 1008;
  Dialogs_Logon.Settings.Window_Remove_ID     = 1009;
  Dialogs_Logon.Settings.Execute_button_ID    = 1010;
 }

 {
  // Задаем указатели в списке составляющих расширителя.
  {
   PAGE Item; PresetPageItem( &Item );

   if( Code_page == RUSSIAN ) strcpy( Item.Name, StrConst_RU_Pages_Dialogs_fields_Name );
   else strcpy( Item.Name, StrConst_EN_Pages_Dialogs_fields_Name );

   Item.Settings_to_show = SET_DIALOG_BOXES;
   strcpy( Item.Icon_name, "Dlg_page.ico" );

   Item.CreatePage     = Dialogs_Fields_CreatePage;
   Item.SetDefSettings = Applier_SetPreDefinedSettings;
   Item.ReadSettings   = Applier_ReadSettings;

   RememberPageItem( Enhancer.Pages.Dialogs_fields, &Item );
  }

  // Задаем ID полей ввода.
  Dialogs_Fields.Settings.WinList_Container_ID = 1001;
  Dialogs_Fields.Settings.ControlBox_ID        = 1002;
  Dialogs_Fields.Settings.AddRemove_ID         = 1003;
  Dialogs_Fields.Settings.TextOnly_button_ID   = 1004;
  Dialogs_Fields.Settings.Restore_button_ID    = 1005;
  Dialogs_Fields.Settings.Window_list_ID       = 1006;
  Dialogs_Fields.Settings.Window_Add_ID        = 1007;
  Dialogs_Fields.Settings.Window_Remove_ID     = 1008;
  Dialogs_Fields.Settings.Remember_button_ID   = 1009;
 }

 {
  // Задаем указатели в списке составляющих расширителя.
  {
   PAGE Item; PresetPageItem( &Item );

   if( Code_page == RUSSIAN ) strcpy( Item.Name, StrConst_RU_Pages_Dialogs_boxes_Name );
   else strcpy( Item.Name, StrConst_EN_Pages_Dialogs_boxes_Name );

   Item.Settings_to_show = SET_DIALOG_BOXES;
   strcpy( Item.Icon_name, "Dlg_page.ico" );

   Item.CreatePage     = Dialogs_Boxes_CreatePage;
   Item.SetDefSettings = Applier_SetPreDefinedSettings;
   Item.ReadSettings   = Applier_ReadSettings;

   RememberPageItem( Enhancer.Pages.Dialogs_boxes, &Item );
  }

  // Задаем ID полей ввода.
  Dialogs_Boxes.Settings.WinList_Container_ID = 1001;
  Dialogs_Boxes.Settings.ButtonBox_ID         = 1002;
  Dialogs_Boxes.Settings.AddRemove_ID         = 1003;
  Dialogs_Boxes.Settings.UseCmd_button_ID     = 1004;
  Dialogs_Boxes.Settings.Action_cmbox_ID      = 1005;
  Dialogs_Boxes.Settings.Window_list_ID       = 1006;
  Dialogs_Boxes.Settings.Window_Add_ID        = 1007;
  Dialogs_Boxes.Settings.Window_Remove_ID     = 1008;
  Dialogs_Boxes.Settings.SendYes_button_ID    = 1009;
 }

 // Возврат.
 return;
}

