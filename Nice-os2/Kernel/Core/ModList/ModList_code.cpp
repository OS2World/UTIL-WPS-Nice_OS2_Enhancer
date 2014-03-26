
// ─── Возвращает указатель на запись в списке составляющих расширителя ───

// Position - номер записи.
PMODULE ModList_GetModListEntry( INT Position )
{
 // Проверяем значение.
 if( Position < 0 || Position >= MODLIST_LENGTH ) return NULL;

 // Получаем указатель.
 PMODULE Pointer = &Enhancer.ModList[ Position ];

 // Проверяем его.
 if( Pointer->cb != sizeof( MODULE ) ) Pointer = NULL;

 // Возврат.
 return Pointer;
}

// ─── Подготавливает значение для занесения в список ───

// Item - значение для списка.
VOID ModList_PresetModuleItem( PMODULE Item )
{
 // Заполняем переменную нулями.
 bzero( Item, sizeof( MODULE ) );

 // Запоминаем длину структуры.
 Item->cb = sizeof( MODULE );

 // Возврат.
 return;
}

// ─── Заносит значение в список ───

// Pointer - куда положить значение для списка, Item - само значение.
VOID ModList_RememberModuleItem( PMODULE Pointer, PMODULE Item )
{
 // Если значение неверно - возврат.
 if( Item->cb != sizeof( MODULE ) ) return;

 // Если в списке уже что-то есть - возврат.
 if( Pointer->cb ) return;

 // Запоминаем значение.
 memcpy( Pointer, Item, sizeof( MODULE ) );

 // Возврат.
 return;
}

