// Свойства окна.
typedef struct _WINDOWPROPERTY
{
  // Окно рамки.
  HWND Frame_window;

  // Заголовок окна.
  CHAR Title[SIZE_OF_TITLE];
  // Значок.
  HPOINTER Icon; BYTE Icon_was_loaded;
  // Ширина рамки окна.
  INT Frame_width;
  // Состояние кнопок.
  LONG Buttons;
  // Для окна заданы действия.
  BYTE Actions;
  // Справа от заголовка есть дополнительные окна.
  BYTE Advanced_controls;

  // Выполнена задержка перед сменой свойств рамки.
  BYTE Retards_performed;

  // Обработчик сообщений для окна заголовка.
  PFNWP TitleBar_performer;
  // Обработчик сообщений для окна обычных кнопок.
  PFNWP MinMax_performer;
  // Обработчик сообщений для окна меню.
  PFNWP Menu_performer;

  // Окно было выбранным.
  BYTE Activated;
  // Окно было увеличено.
  BYTE Maximized;
  // Комната, в которой располагается окно.
  INT Room;
  // Действие, выполняемое с окном.
  LONG Performed_action;
  // Предыдущий размер окна.
  INT Previous_width;
  INT Previous_height;

  // Окно получило сообщение о закрытии.
  BYTE Close_message_received;

  // Окну было дано лучшее расположение на экране.
  ULONG Time_of_arrange;
  // Для окна был показан диалог выбора шрифта.
  BYTE VIO_font_dialog;

  // Значения для задания приоритета.
  LONG Priority_class;
  LONG Priority_delta;

  // Имя приложения, создавшего окно.
  CHAR Exe_name[SIZE_OF_NAME];
  // Путь к приложению, создавшему окно.
  CHAR Exe_path[SIZE_OF_PATH];
}
WINDOWPROPERTY;

// Список свойств окон.
#define WINPRPLIST_LENGTH 256

typedef struct _WINPRPLIST
{
  // Список свойств.
  WINDOWPROPERTY Properties_list[WINPRPLIST_LENGTH];
  // Сведения о списке свойств.
  PRPLISTDESC Descendant;
}
WINPRPLIST;

WINPRPLIST WinPrpList;
