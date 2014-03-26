
// ─── Возвращает указатель на запись в списке страниц расширителя ───

// Position - номер записи.
PPAGE PageList_GetPageListEntry( INT Position )
{
 // Проверяем значение.
 if( Position < 0 || Position >= PAGELIST_LENGTH ) return NULL;

 // Получаем указатель.
 PPAGE Pointer = &Enhancer.PageList[ Position ];

 // Проверяем его.
 if( Pointer->cb != sizeof( PAGE ) ) Pointer = NULL;

 // Возврат.
 return Pointer;
}

// ─── Подготавливает значение для занесения в список ───

// Item - значение для списка.
VOID PageList_PresetPageItem( PPAGE Item )
{
 // Заполняем переменную нулями.
 bzero( Item, sizeof( PAGE ) );

 // Запоминаем длину структуры.
 Item->cb = sizeof( PAGE );

 // Возврат.
 return;
}

// ─── Заносит значение в список ───

// Pointer - куда положить значение для списка, Item - само значение.
VOID PageList_RememberPageItem( PPAGE Pointer, PPAGE Item )
{
 // Если значение неверно - возврат.
 if( Item->cb != sizeof( PAGE ) ) return;

 // Если в списке уже что-то есть - возврат.
 if( Pointer->cb ) return;

 // Запоминаем значение.
 memcpy( Pointer, Item, sizeof( PAGE ) );

 // Возврат.
 return;
}

// ─── Рассылает сообщение всем окнам страниц ───

VOID PageList_BroadcastMessage( ULONG Message, MPARAM First_parameter = 0, MPARAM Second_parameter = 0 )
{
 // Просматриваем список страниц и рассылаем сообщение.
 for( INT Page_count = 0; Page_count < PAGELIST_LENGTH; Page_count ++ )
  {
   PPAGE Page = PageList_GetPageListEntry( Page_count );
   if( Page != NULL )
    if( Page->Present && Page->Window )
     {
      WinPostMsg( Page->Window, Message, First_parameter, Second_parameter );
     }
  }

 // Возврат.
 return;
}

