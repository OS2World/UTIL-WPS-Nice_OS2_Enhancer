// Имена значков на рабочем столе.
typedef struct _OBJECTS
{
  // Имена значков на рабочем столе.
  CHAR Drives_name[SIZE_OF_NAME];

  CHAR Printer_prtname[SIZE_OF_NAME];
  CHAR Printers_name[SIZE_OF_NAME];

  CHAR Viewer_name[SIZE_OF_NAME];
  CHAR Clock_name[SIZE_OF_NAME];
  CHAR Pulse_name[SIZE_OF_NAME];
  CHAR PowerMgr_name[SIZE_OF_NAME];

  CHAR LaunchPad_name[SIZE_OF_NAME];
  CHAR WarpCenter_name[SIZE_OF_NAME];
  CHAR SysTray_name[SIZE_OF_NAME];
  CHAR XWPTaskBar_name[SIZE_OF_NAME];

  CHAR HiResPalette_name[SIZE_OF_NAME];
}
OBJECTS; typedef OBJECTS* POBJECTS;

// Соединения для управления приложениями.
typedef struct _PIPES
{
  // Известные соединения.
  CHAR PM123_pipe[SIZE_OF_NAME];
  CHAR WarpVision_pipe[SIZE_OF_NAME];
  CHAR ZMP3_pipe[SIZE_OF_NAME];
}
PIPES; typedef PIPES* PPIPES;

// Определения для указателей на вызовы методов для проверки.
typedef BYTE (ISAPPWINDOW) (HWND); typedef ISAPPWINDOW* PISAPPWINDOW;

// Работа со списком приложений.
typedef struct _KRNL_REPOSITORY
{
  // Настройки.
  typedef struct _INRSTS
  {
    // Значки и соединения.
    OBJECTS Objects;
    PIPES Pipes;
  }
  INRSTS; INRSTS Settings;

  // Внутренние переменные.
  typedef struct _RTSTS
  {
    // Список приложений был прочтен.
    BYTE Repository_is_ready;

    // Строка для обмена со списками и полями ввода.
    // Эта строка должна быть расположена в постоянной памяти (Heap Memory) расширителя,
    // чтобы приложение и потоки расширителя могли обратиться к ней и читать/изменять ее.
    CHAR Item_text[SIZE_OF_ITEM_TEXT];
  }
  RTSTS; RTSTS RTSettings;
}
KRNL_REPOSITORY;

KRNL_REPOSITORY Krnl_Repository;