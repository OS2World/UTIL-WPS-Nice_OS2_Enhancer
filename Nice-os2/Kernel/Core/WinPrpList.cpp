// Методы для работы со списком свойств окон.
#define SetProperty                     WinPrpList_SetProperty
#define FindProperty                    WinPrpList_FindProperty

#define DiscardUnusedProperties         WinPrpList_DiscardUnusedProperties
#define PropertiesForDrawingAreDetected WinPrpList_PropertiesForDrawingAreDetected

// ─── Метод для подключения класса ───

VOID WinPrpList_Start( VOID )
{
 // Вызываем родителя для того, чтобы он подготовил все необходимые переменные.
 // Сбрасывать все значения с помощью bzero() при этом нежелательно - увеличится расход памяти.
 AbstractPrpList_PrepareList( &WinPrpList.Descendant );

 // Запоминаем сведения о списке свойств окон.
 // Длина списка соответствует примерному числу окон приложений, которые могут быть открыты одновременно.
 WinPrpList.Descendant.Length = WINPRPLIST_LENGTH;

 WinPrpList.Descendant.IsItemEqualsTo = WinPrpList_IsItemEqualsTo;
 WinPrpList.Descendant.IsItemEmpty = WinPrpList_IsItemEmpty;
 WinPrpList.Descendant.CreateNewItem = WinPrpList_CreateNewItem;
 WinPrpList.Descendant.DiscardItem = WinPrpList_DiscardItem;
 WinPrpList.Descendant.GetPointerForData = WinPrpList_GetPointerForData;
 WinPrpList.Descendant.GetSizeOfData = WinPrpList_GetSizeOfData;

 // Возврат.
 return;
}

