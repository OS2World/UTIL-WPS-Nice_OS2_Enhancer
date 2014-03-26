// ��⮤� ��� ࠡ��� � ᯨ᪮� ᢮��� ����.
#define SetProperty                     WinPrpList_SetProperty
#define FindProperty                    WinPrpList_FindProperty

#define DiscardUnusedProperties         WinPrpList_DiscardUnusedProperties
#define PropertiesForDrawingAreDetected WinPrpList_PropertiesForDrawingAreDetected

// ��� ��⮤ ��� ������祭�� ����� ���

VOID WinPrpList_Start( VOID )
{
 // ��뢠�� த�⥫� ��� ⮣�, �⮡� �� �����⮢�� �� ����室��� ��६����.
 // ����뢠�� �� ���祭�� � ������� bzero() �� �⮬ ������⥫쭮 - 㢥������ ��室 �����.
 AbstractPrpList_PrepareList( &WinPrpList.Descendant );

 // ���������� ᢥ����� � ᯨ᪥ ᢮��� ����.
 // ����� ᯨ᪠ ᮮ⢥����� �ਬ�୮�� ��� ���� �ਫ������, ����� ����� ���� ������ �����६����.
 WinPrpList.Descendant.Length = WINPRPLIST_LENGTH;

 WinPrpList.Descendant.IsItemEqualsTo = WinPrpList_IsItemEqualsTo;
 WinPrpList.Descendant.IsItemEmpty = WinPrpList_IsItemEmpty;
 WinPrpList.Descendant.CreateNewItem = WinPrpList_CreateNewItem;
 WinPrpList.Descendant.DiscardItem = WinPrpList_DiscardItem;
 WinPrpList.Descendant.GetPointerForData = WinPrpList_GetPointerForData;
 WinPrpList.Descendant.GetSizeOfData = WinPrpList_GetSizeOfData;

 // ������.
 return;
}

