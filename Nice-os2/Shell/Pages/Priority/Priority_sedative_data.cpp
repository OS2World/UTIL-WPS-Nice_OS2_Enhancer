// Окно настроек.
typedef struct _PRTYSDTPAGE
{
  // Настройки.
  typedef struct _INRSTS
  {
    // Поля ввода в окне.
    ULONG WinList_Container_ID;
    ULONG SelectBox_ID;
    ULONG AddRemove_ID;
    ULONG Window_list_ID;
    ULONG Window_Add_ID;
    ULONG Window_Remove_ID;
    ULONG Normalize_button_ID;
  }
  INRSTS; INRSTS Settings;
}
PRTYSDTPAGE;

PRTYSDTPAGE Priority_Sedative;
