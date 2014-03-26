// Эти окна надо переносить в определенные комнаты при появлении.
typedef struct _ALLOCATIONS
 {
  CHAR Unit_1_name[ SIZE_OF_NAME ]; CHAR Unit_2_name[ SIZE_OF_NAME ];
  CHAR Unit_3_name[ SIZE_OF_NAME ]; CHAR Unit_4_name[ SIZE_OF_NAME ];
  CHAR Unit_5_name[ SIZE_OF_NAME ]; CHAR Unit_6_name[ SIZE_OF_NAME ];
  CHAR Unit_7_name[ SIZE_OF_NAME ]; CHAR Unit_8_name[ SIZE_OF_NAME ];

  INT Preferable_room_1; INT Preferable_room_2;
  INT Preferable_room_3; INT Preferable_room_4;
  INT Preferable_room_5; INT Preferable_room_6;
  INT Preferable_room_7; INT Preferable_room_8;
 }
ALLOCATIONS;

// Действия с окном оболочки при смене комнат.
#define ROOMS_DO_NOT_RESTORE_WINDOW  0xFF

// Исключения.
typedef struct _ROOMS_EXCEPTIONS
 {
  CHAR Rooms_1[ SIZE_OF_NAME ];
  CHAR Rooms_2[ SIZE_OF_NAME ];
  CHAR Rooms_3[ SIZE_OF_NAME ];
  CHAR Rooms_4[ SIZE_OF_NAME ];
  CHAR Rooms_5[ SIZE_OF_NAME ];
  CHAR Rooms_6[ SIZE_OF_NAME ];
  CHAR Rooms_7[ SIZE_OF_NAME ];
  CHAR Rooms_8[ SIZE_OF_NAME ];
 }
ROOMS_EXCEPTIONS;

// Комнаты.
typedef struct _ROOMS
 {
  // Постоянные величины.
  typedef struct _CONSTANTS
   {
    // Число задержек после смены комнат.
    INT Retards_after_room_change;
   }
  CONSTANTS; CONSTANTS Constants;

  // Настройки.
  typedef struct _INRSTS
   {
    // Добавить комнаты к рабочему столу? 0 - нет, 1 - да.
    BYTE Create_Rooms;
    BYTE Allocate_windows_to_Rooms;
    BYTE Allocate_known_applications;
    BYTE Draw_wallpaper;
    BYTE Switch_by_WarpCenter;
    BYTE Switch_by_keyboard;

    // Добиваться правильной работы потоков после перехода между комнатами? 0 - нет, 1 - да.
    BYTE Synchronize_arranger_and_rooms;

    // Изображения для рабочего стола.
    CHAR Wallpaper_for_shell_room[ SIZE_OF_PATH ];
    CHAR Wallpaper_for_northern_room[ SIZE_OF_PATH ];
    CHAR Wallpaper_for_western_room[ SIZE_OF_PATH ];
    CHAR Wallpaper_for_eastern_room[ SIZE_OF_PATH ];
    CHAR Wallpaper_for_southern_room[ SIZE_OF_PATH ];

    // Расположение окон по умолчанию.
    ALLOCATIONS Allocations;

    // Список исключений.
    ROOMS_EXCEPTIONS Exceptions;
   }
  INRSTS; INRSTS Settings;

  // Внутренние переменные.
  typedef struct _RTSTS
   {
    // Окно оболочки.
    POINT Shell_window_angle;

    // Изображение, которое используется для закрашивания рабочего стола.
    HBITMAP Wallpaper;
   }
  RTSTS; RTSTS RTSettings;

 }
ROOMS;

ROOMS Rooms;
