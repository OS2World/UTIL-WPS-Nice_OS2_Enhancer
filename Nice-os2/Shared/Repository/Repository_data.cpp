// Свойства приложения.
typedef struct _PROCESSINFO
 {
  // Приложение и родительское приложение.
  PID Process_ID;
  PID Parent_ID;

  // Имя и путь к приложению.
  CHAR Exe_name[ SIZE_OF_NAME ];
  CHAR Exe_path[ SIZE_OF_PATH ];
 }
PROCESSINFO; typedef PROCESSINFO* PPROCESSINFO;

// Известные расширителю приложения.
typedef struct _APPLICATIONS
 {
  // Значение вида APP_..., определяющее приложение в списке. Не повторяется.
  INT Application;
  // Действие для вызова приложения - значение вида SHOW_..., используемое в настройках. Может повторяться.
  INT Action;
  // Задача, для которой используется приложение - значение вида BROWSE_... и т.п.
  INT Purpose;

  // Вид приложения - значения вида PROG_..., описанные в PMShl.h, можно не задавать.
  PROGCATEGORY Mode;

  // Признак, что это часто используемое приложение (его окно будет вызываться в первую очередь).
  BYTE Desired;

  // Имена значков для вызова приложения, может быть несколько.
  CHAR WPS_name_A[ SIZE_OF_NAME ];
  CHAR WPS_name_B[ SIZE_OF_NAME ];
  CHAR WPS_name_C[ SIZE_OF_NAME ];
  CHAR WPS_name_D[ SIZE_OF_NAME ];

  // Имена файлов для вызова приложения, может быть несколько.
  CHAR Exe_name_1[ SIZE_OF_NAME ];
  CHAR Exe_name_2[ SIZE_OF_NAME ];
  CHAR Exe_name_3[ SIZE_OF_NAME ];
  CHAR Exe_name_4[ SIZE_OF_NAME ];

  // Имя настройки в INI, содержащей это значение.
  CHAR Exe_INI_setting_name[ SIZE_OF_NAME ];

  // Значок на рабочем столе.
  CHAR Object[ SIZE_OF_NAME ];
  // Имя настройки в INI, содержащей это значение.
  CHAR Object_INI_setting_name[ SIZE_OF_NAME ];

  // Путь к приложению.
  CHAR Path[ SIZE_OF_PATH ];
  // Имя настройки в INI, содержащей это значение.
  CHAR Path_INI_setting_name[ SIZE_OF_NAME ];

  // Ключевые слова для поиска значка, может быть несколько.
  CHAR WPS_keyword_1[ SIZE_OF_NAME ];
  CHAR WPS_keyword_2[ SIZE_OF_NAME ];
  CHAR WPS_keyword_3[ SIZE_OF_NAME ];
  CHAR WPS_keyword_4[ SIZE_OF_NAME ];

  // Ключевые слова для поиска окна, может быть несколько.
  CHAR Window_keyword_1[ SIZE_OF_NAME ];
  CHAR Window_keyword_2[ SIZE_OF_NAME ];
  CHAR Window_keyword_3[ SIZE_OF_NAME ];
  CHAR Window_keyword_4[ SIZE_OF_NAME ];

  // Окно и очередь сообщений, могут быть не заполнены.
  HWND Window; HMQ Message_queue;
 }
APPLICATIONS; typedef APPLICATIONS* PAPPLICATIONS;

// Список известных расширителю приложений.
typedef struct _REPOSITORY
 {
  // Число приложений в списке.
  INT Length;
  // Сами приложения.
  APPLICATIONS Items[ MAX_RP_ENTRIES ];
 }
REPOSITORY; typedef REPOSITORY* PREPOSITORY;

// Переменные должны быть расположены в разделяемой области памяти.
REPOSITORY Repository;