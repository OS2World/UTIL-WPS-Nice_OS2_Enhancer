
// ─── Устанавливает настройки по умолчанию ───

// Division - какие настройки надо установить.
VOID PriorityManager_SetPreDefinedSettings( LONG Division )
{
 // Задаем настройки.
 if( Division == SET_ALL_SETTINGS )
  {
   bzero( &PriorityManager.Settings.PriorityNames, sizeof( PRIORITY_NAMES ) );
  }

 if( Division == SET_ALL_SETTINGS || Division == SET_PRIORITY )
  {
   PriorityManager.Settings.Normalize_priority = 0;

   PriorityManager.Settings.Dynamic_priority = 0;
   PriorityManager.Settings.Dynamic_priority_for_VIO = 1;
   PriorityManager.Settings.Dynamic_priority_for_lSwitcher = 1;
  }

 // Возврат.
 return;
}

// ─── Читает настройки ───

// Ini_file - файл настроек.
VOID PriorityManager_ReadSettings( HINI Ini_file )
{
 // Читаем настройки.
 ULONG Byte = 0; ULONG Name = 0; ULONG Byte_data = 0;

 Byte = sizeof( BYTE ); if( PrfQueryProfileData( Ini_file, "Settings", "Normalize priority", &Byte_data, &Byte ) ) PriorityManager.Settings.Normalize_priority = Byte_data;

 Byte = sizeof( BYTE ); if( PrfQueryProfileData( Ini_file, "Settings", "Dynamic priority", &Byte_data, &Byte ) ) PriorityManager.Settings.Dynamic_priority = Byte_data;
 Byte = sizeof( BYTE ); if( PrfQueryProfileData( Ini_file, "Settings", "Dynamic priority for VIO", &Byte_data, &Byte ) ) PriorityManager.Settings.Dynamic_priority_for_VIO = Byte_data;
 Byte = sizeof( BYTE ); if( PrfQueryProfileData( Ini_file, "Settings", "Dynamic priority for lSwitcher", &Byte_data, &Byte ) ) PriorityManager.Settings.Dynamic_priority_for_lSwitcher = Byte_data;

 {
  CHAR Item[ SIZE_OF_PATH ] = "";

  Name = SIZE_OF_NAME; PrfQueryProfileData( Ini_file, "Priority", "Exceeded priority 1 name", Item, &Name );
  if( Item[ 0 ] != 0 ) { strcpy( PriorityManager.Settings.PriorityNames.Exceeded_priority_1_name, Item ); Item[ 0 ] = 0; }
  Name = SIZE_OF_NAME; PrfQueryProfileData( Ini_file, "Priority", "Exceeded priority 2 name", Item, &Name );
  if( Item[ 0 ] != 0 ) { strcpy( PriorityManager.Settings.PriorityNames.Exceeded_priority_2_name, Item ); Item[ 0 ] = 0; }
  Name = SIZE_OF_NAME; PrfQueryProfileData( Ini_file, "Priority", "Exceeded priority 3 name", Item, &Name );
  if( Item[ 0 ] != 0 ) { strcpy( PriorityManager.Settings.PriorityNames.Exceeded_priority_3_name, Item ); Item[ 0 ] = 0; }
  Name = SIZE_OF_NAME; PrfQueryProfileData( Ini_file, "Priority", "Exceeded priority 4 name", Item, &Name );
  if( Item[ 0 ] != 0 ) { strcpy( PriorityManager.Settings.PriorityNames.Exceeded_priority_4_name, Item ); Item[ 0 ] = 0; }
  Name = SIZE_OF_NAME; PrfQueryProfileData( Ini_file, "Priority", "Exceeded priority 5 name", Item, &Name );
  if( Item[ 0 ] != 0 ) { strcpy( PriorityManager.Settings.PriorityNames.Exceeded_priority_5_name, Item ); Item[ 0 ] = 0; }
  Name = SIZE_OF_NAME; PrfQueryProfileData( Ini_file, "Priority", "Exceeded priority 6 name", Item, &Name );
  if( Item[ 0 ] != 0 ) { strcpy( PriorityManager.Settings.PriorityNames.Exceeded_priority_6_name, Item ); Item[ 0 ] = 0; }
  Name = SIZE_OF_NAME; PrfQueryProfileData( Ini_file, "Priority", "Exceeded priority 7 name", Item, &Name );
  if( Item[ 0 ] != 0 ) { strcpy( PriorityManager.Settings.PriorityNames.Exceeded_priority_7_name, Item ); Item[ 0 ] = 0; }
  Name = SIZE_OF_NAME; PrfQueryProfileData( Ini_file, "Priority", "Exceeded priority 8 name", Item, &Name );
  if( Item[ 0 ] != 0 ) { strcpy( PriorityManager.Settings.PriorityNames.Exceeded_priority_8_name, Item ); Item[ 0 ] = 0; }
 }

 // Возврат.
 return;
}