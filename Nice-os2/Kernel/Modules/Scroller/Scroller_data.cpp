// Размер списка окон для передвижения изображения. Менять это значение нежелательно.
#define SCROLLER_SCRLIST_SIZE             125

// Длина линий для захвата изображения в окне.
#define SCROLLER_SCRLIST_LINE             150

// Наибольшая поддерживаемая скорость.
#define SCROLLER_MAX_VELOCITY_DD_D        ( 50 / 1 )

// Используемые клавиши.
#define SCROLLER_USE_CAPS_LOCK            1
#define SCROLLER_USE_SCROLL_LOCK          2
#define SCROLLER_USE_SHIFT                3

// Способы плавного передвижения изображения в окне (по умолчанию нулевое значение).
#define SCROLLING_UNKNOWN                 0
#define SCROLLING_DISABLED                0
#define SCROLLING_COMMON                  1
#define SCROLLING_DISCRETE_SBCTL_MB       2
#define SCROLLING_DISCRETE_SBCTL_KBD      3
#define SCROLLING_DISCRETE_SCROLLMSG      4
#define SCROLLING_DISCRETE_SCROLLMSG_IFW  5

// Скорость по умолчанию.
#define SCROLLER_DEF_SPEED_X              8
#define SCROLLER_DEF_SPEED_Y              16

// Список окон, в которых происходит передвижение изображения.
typedef struct _SCRLIST
 {
  // Имя, под которым определено окно.
  CHAR Name[ SIZE_OF_NAME ];
  // Скорость передвижения изображения.
  INT X_Velocity_DD; INT X_Velocity_D;
  INT Y_Velocity_DD; INT Y_Velocity_D;
  // Данные добавлены расширителем.
  BYTE PreDefined; BYTE Method;
 }
SCRLIST; typedef SCRLIST* PSCRLIST;

// Исключения.
typedef struct _SCROLLER_EXCEPTIONS
 {
  // Список исключений, заданный пользователем.
  CHAR Scrolling_1[ SIZE_OF_NAME ];
  CHAR Scrolling_2[ SIZE_OF_NAME ];
  CHAR Scrolling_3[ SIZE_OF_NAME ];
  CHAR Scrolling_4[ SIZE_OF_NAME ];
  CHAR Scrolling_5[ SIZE_OF_NAME ];
  CHAR Scrolling_6[ SIZE_OF_NAME ];
  CHAR Scrolling_7[ SIZE_OF_NAME ];
  CHAR Scrolling_8[ SIZE_OF_NAME ];

  CHAR KeyScrolling_1[ SIZE_OF_NAME ];
  CHAR KeyScrolling_2[ SIZE_OF_NAME ];
  CHAR KeyScrolling_3[ SIZE_OF_NAME ];
  CHAR KeyScrolling_4[ SIZE_OF_NAME ];
  CHAR KeyScrolling_5[ SIZE_OF_NAME ];
  CHAR KeyScrolling_6[ SIZE_OF_NAME ];
  CHAR KeyScrolling_7[ SIZE_OF_NAME ];
  CHAR KeyScrolling_8[ SIZE_OF_NAME ];
 }
SCROLLER_EXCEPTIONS;

// Передвижение изображения в окнах.
typedef struct _SCROLLER
 {
  // Список имен окон, в которых можно двигать изображение.
  SCRLIST Scrolling_list[ SCROLLER_SCRLIST_SIZE ];

  // Настройки.
  typedef struct _INRSTS
   {
    // Сдвигать изображение в окнах при нажатом Scroll Lock? 0 - нет, 1 - да.
    BYTE Key_scrolling;
    // Сделать передвижение изображения при просмотре плавным? 0 - нет, 1 - да.
    BYTE Smooth_scrolling;
    // Сдвигать изображение в окнах с помощью мыши? 0 - нет, 1..3 - если нажата правая кнопка.
    BYTE Image_dragging;
    // Указатель мыши, используемый для передвижения изображения.
    INT Number_of_pointer;

    // Список исключений.
    SCROLLER_EXCEPTIONS Exceptions;
   }
  INRSTS; INRSTS Settings;

  typedef struct _RTSTS
   {
    // Указывает, что скорость передвижения изображения запоминать не надо.
    BYTE Detection_is_disabled;
    // Если 1 или 2, то передвижение только начинается, если 3 или 4 - продолжается.
    BYTE Step_of_scrolling;
    // Идет передвижение изображения. 0 - нет, 1 - да.
    BYTE Dragging;
    // Полоски просмотра в окне.
    HWND VSB_Control; HWND HSB_Control;
    // Точка, в которой начиналось передвижение.
    POINT Start_point; 
    // Расположение движков полосок просмотра в этой точке.
    USHORT Start_VSB_position; USHORT Start_HSB_position;
    // Точка, в которой указатель был в прошлый раз.
    POINT Previous_step_point;
    // Скорость передвижения.
    INT X_Velocity_DD; INT X_Velocity_D;
    INT Y_Velocity_DD; INT Y_Velocity_D;
    // Выбранный способ передвижения.
    INT Dragging_method;
    // Выбранное окно.
    HWND Target_window;

    // Переменные, чтобы запоминать точки в окне как '>', а затем искать их и определять скорость.
    HWND Scrolling_window; 
    BYTE Messages_is_redirected; 
    INT ScrList_position;
    SHORT Slider_position;

    LONG Line_1[ SCROLLER_SCRLIST_LINE ]; 
    LONG Line_2[ SCROLLER_SCRLIST_LINE ];

    // Переменные для хранения состояния полоски просмотра.
    SBCDATA SB_State; SBCDATA VSB_State; SBCDATA HSB_State;
   }
  RTSTS; RTSTS RTSettings;
 }
SCROLLER; typedef SCROLLER* PSCROLLER;

// Переменные должны быть расположены в разделяемой области памяти.
SCROLLER Scroller;
