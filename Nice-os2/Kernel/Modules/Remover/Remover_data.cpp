// Эти окна надо скрыть в списке окон.
typedef struct _WINLISTNAMES
{
  CHAR Remove_from_list_1_name[SIZE_OF_TITLE]; CHAR Remove_from_list_2_name[SIZE_OF_TITLE];
  CHAR Remove_from_list_3_name[SIZE_OF_TITLE]; CHAR Remove_from_list_4_name[SIZE_OF_TITLE];
  CHAR Remove_from_list_5_name[SIZE_OF_TITLE]; CHAR Remove_from_list_6_name[SIZE_OF_TITLE];
  CHAR Remove_from_list_7_name[SIZE_OF_TITLE]; CHAR Remove_from_list_8_name[SIZE_OF_TITLE];
}
WINLISTNAMES;

// Удаление строк из списка окон.
typedef struct _REMOVER
{
  // Настройки.
  typedef struct _INRSTS
  {
    // Скрывать строки в списке окон? 0 - нет, 1 - да.
    BYTE Remove_items_from_Window_list; 
    BYTE Hide_known_applications;

    // Имена для удаления из списка окон.
    WINLISTNAMES WinListNames;

    CHAR DDNS[SIZE_OF_TITLE];
    CHAR DHCP[SIZE_OF_TITLE];
    CHAR BINL[SIZE_OF_TITLE];
  }
  INRSTS; INRSTS Settings;
}
REMOVER;

REMOVER Remover;
