// Разновидности полей ввода.
#define DLG_INPUT_FIELD      1
#define DLG_ENTRY_FIELD      2

#define DLG_COMBO_BOX        3
#define DLG_LIST_BOX         4

#define DLG_SPIN_BUTTON      5
#define DLG_CHECKBOX_BUTTON  6
#define DLG_RADIO_BUTTON     7

#define DLG_PUSH_BUTTON      8

#define DLG_SLIDER           9

#define DLG_STATIC          10

// Набор полей ввода в окне и свойства окна.
#define DLG_MAX_FIELDS       50
#define DLG_MAX_BUTTONS      10

// Поле ввода в окне диалога.
typedef struct _DLGFIELD
 {
  // Окно поля ввода.
  HWND Window;
  // Вид поля ввода.
  LONG Type;
  // Значение в текстовом виде. Для "[x]" это может быть "-1", "0", "1" и т. д.
  CHAR Value[ SIZE_OF_DIALOG_FIELD ];
  // Поле содержит текстовое значение, пригодное для дальнейшего использования.
  BYTE Useful;
 }
DLGFIELD; typedef DLGFIELD* PDLGFIELD;

// Произвольное окно диалога и набор полей в нем.
typedef struct _DLGBOX
 {
  // Вид рамки окна.
  LONG Frame_type;
  // Имя приложения, создавшего окно.
  CHAR Exe_name[ SIZE_OF_NAME ];
  // Заголовок окна. Для плоского окна сообщения - текст вверху.
  CHAR Window_title[ SIZE_OF_TITLE ];

  // Набор полей ввода в окне и их значения.
  DLGFIELD Fields[ DLG_MAX_FIELDS ];
  INT Quantity;

  // Действия возможны.
  BYTE Enabled; BYTE Text_fields_only;
 }
DLGBOX; typedef DLGBOX* PDLGBOX; typedef PDLGBOX* PPDLGBOX;

// Данные для исполнения приложения после ввода пароля.
typedef struct _LOGONSCRIPTDATA
 {
  // Значения, набранные пользователем.
  DLGFIELD Values[ DLG_MAX_FIELDS ];
  INT Quantity;

  // Приложение, вызвавшее окно ввода пароля.
  PID Process_ID;
 }
LOGONSCRIPTDATA; typedef LOGONSCRIPTDATA* PLOGONSCRIPTDATA;

// Окно для ввода пароля.
typedef struct _LOGONDLGBOX
 {
  // Вид рамки окна.
  LONG Frame_type;
  // Имя приложения, создавшего окно.
  CHAR Exe_name[ SIZE_OF_NAME ];
  // Заголовок окна. Для плоского окна сообщения - текст вверху.
  CHAR Window_title[ SIZE_OF_TITLE ];

  // Команда, связанная с окном для ввода пароля.
  CHAR Logon_command[ SIZE_OF_PATH ];

  // Данные для исполнения приложения после ввода пароля.
  LOGONSCRIPTDATA Parameters;

  // Действия возможны.
  BYTE Enabled; BYTE Only_once; BYTE Action_performed;
 }
LOGONDLGBOX; typedef LOGONDLGBOX* PLOGONDLGBOX; typedef PLOGONDLGBOX* PPLOGONDLGBOX;

// Окно сообщения.
typedef struct _MSGDLGBOX
 {
  // Вид рамки окна.
  LONG Frame_type;
  // Имя приложения, создавшего окно.
  CHAR Exe_name[ SIZE_OF_NAME ];
  // Заголовок окна. Для плоского окна сообщения - текст вверху.
  CHAR Window_title[ SIZE_OF_TITLE ];

  // Кнопки в окне.
  DLGFIELD Buttons[ DLG_MAX_BUTTONS ];
  INT Quantity; INT Close_button;

  // Действия возможны.
  BYTE Enabled;
 }
MSGDLGBOX; typedef MSGDLGBOX* PMSGDLGBOX; typedef PMSGDLGBOX* PPMSGDLGBOX;
