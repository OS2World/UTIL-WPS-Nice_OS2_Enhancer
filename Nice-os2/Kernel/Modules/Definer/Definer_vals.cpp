
// ─── Сообщает о том, какие настройки в оболочке OS/2 должны быть изменены ───

// Request_pointer - указатель на список настроек, которые расширитель умеет заменять.
VOID Definer_SysValuesChangeReporter( PVOID Request_pointer )
{
 // Разбираем указатель.
 PPREFERRED_SYSTEM_VALUES Request = (PPREFERRED_SYSTEM_VALUES) Request_pointer;

 // Проверяем его.
 if( Request->cb != sizeof( PREFERRED_SYSTEM_VALUES ) ) return;

 // Если клавиша PrtScr была переопределена:
 if( Definer.Settings.Keys.PrtScr || Definer.Settings.Keys.SysRq )
  {
   // Изменяем внешний список.
   Request->Disable_PrintScreen = 1;
  }

 // Возврат.
 return;
}