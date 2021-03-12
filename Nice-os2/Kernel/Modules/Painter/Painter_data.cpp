// Темы для окон. Эти значения пишутся в INI. Менять их нежелательно.
#define PAINTER_THEME_PHOENIX              1
#define PAINTER_THEME_BLUE_LION            5
#define PAINTER_THEME_ECOMSTATION         10
#define PAINTER_THEME_CLASSIC_GRAY        20
#define PAINTER_THEME_CLASSIC_RGB         30
#define PAINTER_THEME_WHITE_SNOW          40

// Перерисовывать рамки.
#define PA_METHOD_CALLED_BY_WINDOW_MANAGER 1

// Наибольшее обрабатываемое число окон в окне рамки.
#define PAINTER_MAX_CONTROLS              50

// Число проверок размера и расположения окна рамки.
#define MAX_FCHECKS                       5

// Объединение сообщений.
typedef struct _PAINTERDEMAND
{
  // Окно рамки.
  HWND Frame_window;
  // Окно, требующее перерисования.
  ULONG Target;
}
PAINTERDEMAND; typedef PAINTERDEMAND* PPAINTERDEMAND;

#define PAINTER_DEMAND_TABLE              256

// Отлов ошибки, вызывающей "мигание" рамки.
typedef struct _MSGQUEUEINFO
{
  // Очередь сообщений.
  HMQ Queue;
  // Счетчик сообщений.
  INT Quantity;
  // Время последнего увеличения счетчика.
  LONG Time;
}
MSGQUEUEINFO; typedef MSGQUEUEINFO* PMSGQUEUEINFO;

#define PAINTER_MONITORING_QUEUES         64
#define PAINTER_STUBBORN_PID_TABLE        16

// Исключения.
typedef struct _PAINTER_EXCEPTIONS
{
  CHAR Drawing_1[SIZE_OF_NAME];
  CHAR Drawing_2[SIZE_OF_NAME];
  CHAR Drawing_3[SIZE_OF_NAME];
  CHAR Drawing_4[SIZE_OF_NAME];
  CHAR Drawing_5[SIZE_OF_NAME];
  CHAR Drawing_6[SIZE_OF_NAME];
  CHAR Drawing_7[SIZE_OF_NAME];
  CHAR Drawing_8[SIZE_OF_NAME];

  CHAR BorderDrawing_1[SIZE_OF_NAME];
  CHAR BorderDrawing_2[SIZE_OF_NAME];
  CHAR BorderDrawing_3[SIZE_OF_NAME];
  CHAR BorderDrawing_4[SIZE_OF_NAME];
  CHAR BorderDrawing_5[SIZE_OF_NAME];
  CHAR BorderDrawing_6[SIZE_OF_NAME];
  CHAR BorderDrawing_7[SIZE_OF_NAME];
  CHAR BorderDrawing_8[SIZE_OF_NAME];

  CHAR Rolling_1[SIZE_OF_NAME];
  CHAR Rolling_2[SIZE_OF_NAME];
  CHAR Rolling_3[SIZE_OF_NAME];
  CHAR Rolling_4[SIZE_OF_NAME];
  CHAR Rolling_5[SIZE_OF_NAME];
  CHAR Rolling_6[SIZE_OF_NAME];
  CHAR Rolling_7[SIZE_OF_NAME];
  CHAR Rolling_8[SIZE_OF_NAME];
}
PAINTER_EXCEPTIONS;

// Рисование рамок для окон.
typedef struct _PAINTER
{
  // Постоянные величины.
  typedef struct _CONSTANTS
  {
    // Значения времени и счетчика для определения "мигания" рамки при рисовании.
    INT Permanent_drawing;
    INT Drawing_check_timeout;
  }
  CONSTANTS; CONSTANTS Constants;

  // Настройки.
  typedef struct _INRSTS
  {
    // Изменять рамки окон? 0 - нет, 1 - да.
    BYTE Draw_frames;
    // Тема для рамок.
    INT Theme;
    // Рисовать обычные рамки? 0 - нет, 1 - да.
    BYTE Draw_normal_frames;
    // Рисовать рамки для окон постоянного размера? 0 - нет, 1 - да.
    BYTE Draw_const_frames;
    // Рисовать рамки в 1 точку? 0 - нет, 1 - да.
    BYTE Draw_point_frames;
    // Рисовать рамки для плоских окон? 0 - нет, 1 - да.
    BYTE Draw_flat_frames;
    // Рисовать картинку в правом верхнем углу окна? 0 - нет, 1 - да.
    BYTE Draw_system_menus;
    // Рисовать заголовок окна? 0 - нет, 1 - да.
    BYTE Draw_titles;
    // Цвета для текста в заголовке.
    ULONG AT_Text_color;          ULONG IT_Text_color;
    ULONG Northern_AT_Text_color; ULONG Northern_IT_Text_color;
    ULONG Western_AT_Text_color;  ULONG Western_IT_Text_color;
    ULONG Eastern_AT_Text_color;  ULONG Eastern_IT_Text_color;
    ULONG Southern_AT_Text_color; ULONG Southern_IT_Text_color;
    // Цвета для заполнения заголовков.
    ULONG AT_Background_color;          ULONG IT_Background_color;
    ULONG Northern_AT_Background_color; ULONG Northern_IT_Background_color;
    ULONG Western_AT_Background_color;  ULONG Western_IT_Background_color;
    ULONG Eastern_AT_Background_color;  ULONG Eastern_IT_Background_color;
    ULONG Southern_AT_Background_color; ULONG Southern_IT_Background_color;
    // Подчеркивать объем заголовка для окон постоянного размера? 0 - нет, 1 - да.
    BYTE Draw_volume_lines;
    // Подчеркивать объем меню окна? 0 - нет, 1 - да.
    BYTE Draw_menus;
    // Рисовать кнопки в правом верхнем углу окна? 0 - нет, 1 - да.
    BYTE Draw_buttons;
    // Оставлять для окон WPS только кнопку закрытия? 0 - нет, 1 - да.
    BYTE Accelerate_folders_closing;
    // Рисовать кнопку "Убрать наверх" для текстовых окон? 0 - нет, 1 - да.
    BYTE Rollup_VIO_windows;

    // Цвета для изображений.
    LONG AT_Color_1;          LONG AT_Color_2;          LONG AT_Color_3;
    LONG IT_Color_1;          LONG IT_Color_2;          LONG IT_Color_3;
    LONG Northern_AT_Color_1; LONG Northern_AT_Color_2; LONG Northern_AT_Color_3;
    LONG Northern_IT_Color_1; LONG Northern_IT_Color_2; LONG Northern_IT_Color_3;
    LONG Western_AT_Color_1;  LONG Western_AT_Color_2;  LONG Western_AT_Color_3;
    LONG Western_IT_Color_1;  LONG Western_IT_Color_2;  LONG Western_IT_Color_3;
    LONG Eastern_AT_Color_1;  LONG Eastern_AT_Color_2;  LONG Eastern_AT_Color_3;
    LONG Eastern_IT_Color_1;  LONG Eastern_IT_Color_2;  LONG Eastern_IT_Color_3;
    LONG Southern_AT_Color_1; LONG Southern_AT_Color_2; LONG Southern_AT_Color_3;
    LONG Southern_IT_Color_1; LONG Southern_IT_Color_2; LONG Southern_IT_Color_3;

    // Узор для изображений.
    CHAR TitleBar_pattern[SIZE_OF_PATH];

    // Не менять системные цвета? 0 - нет, 1 - да.
    BYTE Keep_frame_colors;

    // Список исключений.
    PAINTER_EXCEPTIONS Exceptions;
  }
  INRSTS; INRSTS Settings;

  // Внутренние переменные.
  typedef struct _RTSTS
  {
    // Окно, в котором нажата кнопка в заголовке.
    HWND Selected_window;
    // Какая кнопка нажата.
    LONG Selected_button;
    // Окно картинки, если но выбрано.
    HWND Prev_selected_menu;

    // Изображения для заполнения заголовка.
    HBITMAP AT_Bitmap; HBITMAP IT_Bitmap; INT AT_Bitmap_width; INT AT_Bitmap_height;

    // Узор для заголовка, загруженный с диска.
    CHAR Pattern_name[SIZE_OF_NAME];
    HBITMAP Pattern; INT Pattern_width; INT Pattern_height;

    // Объединение сообщений.
    PAINTERDEMAND Demand[PAINTER_DEMAND_TABLE];

    // Отлов ошибки, которая вызывает "мигание" рамки.
    MSGQUEUEINFO Drawing_windows[PAINTER_MONITORING_QUEUES];
    ULONG Stubborn_processes[PAINTER_STUBBORN_PID_TABLE];
  }
  RTSTS; RTSTS RTSettings;
}
PAINTER; PAINTER Painter;
