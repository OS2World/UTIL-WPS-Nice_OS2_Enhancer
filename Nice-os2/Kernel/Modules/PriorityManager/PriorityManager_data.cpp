// Для этих окон и приложений надо выравнивать приоритеты.
typedef struct _PRIORITY_NAMES
{
  CHAR Exceeded_priority_1_name[SIZE_OF_NAME]; CHAR Exceeded_priority_2_name[SIZE_OF_NAME];
  CHAR Exceeded_priority_3_name[SIZE_OF_NAME]; CHAR Exceeded_priority_4_name[SIZE_OF_NAME];
  CHAR Exceeded_priority_5_name[SIZE_OF_NAME]; CHAR Exceeded_priority_6_name[SIZE_OF_NAME];
  CHAR Exceeded_priority_7_name[SIZE_OF_NAME]; CHAR Exceeded_priority_8_name[SIZE_OF_NAME];
}
PRIORITY_NAMES;

// Работа с приоритетами приложений.
typedef struct _PRIORITY_MANAGER
{
  // Настройки.
  typedef struct _INRSTS
  {
    // Выравнивать приоритеты приложений? 0 - нет, 1 - да.
    BYTE Normalize_priority;

    // Изменять приоритеты приложений при переключении окон? 0 - нет, 1 - да.
    BYTE Dynamic_priority;
    BYTE Dynamic_priority_for_VIO;
    BYTE Dynamic_priority_for_lSwitcher;

    // Приоритеты.
    PRIORITY_NAMES PriorityNames;
  }
  INRSTS; INRSTS Settings;

  // Внутренние переменные.
  typedef struct _RTSTS
  {
    // Список видимых и доступных приложений, у которых можно менять приоритеты.
    VISIBLEPROCESS Visible_processes[SIZE_OF_VISPROCLIST];
    INT Visible_processes_quantity;
  }
  RTSTS; RTSTS RTSettings;
}
PRIORITY_MANAGER;

PRIORITY_MANAGER PriorityManager;