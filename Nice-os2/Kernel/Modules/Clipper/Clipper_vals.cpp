
// ─── Сообщает о том, какие настройки в оболочке OS/2 должны быть изменены ───

// Request_pointer - указатель на список настроек, которые расширитель умеет заменять.
VOID Clipper_SysValuesChangeReporter( PVOID Request_pointer )
{
 // Разбираем указатель.
 PPREFERRED_SYSTEM_VALUES Request = (PPREFERRED_SYSTEM_VALUES) Request_pointer;

 // Проверяем его.
 if( Request->cb != sizeof( PREFERRED_SYSTEM_VALUES ) ) return;

 // Если в текстовых окнах надо выполнять действия с помощью мыши:
 if( Clipper.Settings.Mouse_in_VIO )
  {
   // Изменяем внешний список.
   Request->Disable_VIO_mouse_actions = 1;
  }

 // Возврат.
 return;
}