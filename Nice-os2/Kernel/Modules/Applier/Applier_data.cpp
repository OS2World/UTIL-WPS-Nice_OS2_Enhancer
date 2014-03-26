// Для этих окон надо выполнять команды и запоминать в них поля ввода.
typedef struct _DIALOGS
 {
  LOGONDLGBOX Logon_dialog_1; LOGONDLGBOX Logon_dialog_2;
  LOGONDLGBOX Logon_dialog_3; LOGONDLGBOX Logon_dialog_4;
  LOGONDLGBOX Logon_dialog_5; LOGONDLGBOX Logon_dialog_6;
  LOGONDLGBOX Logon_dialog_7; LOGONDLGBOX Logon_dialog_8;

  DLGBOX Incomplete_dialog_1; DLGBOX Incomplete_dialog_2;
  DLGBOX Incomplete_dialog_3; DLGBOX Incomplete_dialog_4;
  DLGBOX Incomplete_dialog_5; DLGBOX Incomplete_dialog_6;
  DLGBOX Incomplete_dialog_7; DLGBOX Incomplete_dialog_8;

  MSGDLGBOX Message_dialog_1; MSGDLGBOX Message_dialog_2;
  MSGDLGBOX Message_dialog_3; MSGDLGBOX Message_dialog_4;
  MSGDLGBOX Message_dialog_5; MSGDLGBOX Message_dialog_6;
  MSGDLGBOX Message_dialog_7; MSGDLGBOX Message_dialog_8;
 }
DIALOGS; typedef DIALOGS* PDIALOGS;

#ifndef INCLUDED_BY_SHELL

// Слежение за окнами ввода пароля.
typedef struct _LOGONWNDINFO
 {
  // Окно рамки.
  HWND Window;
  // Приложение, создавшее окно.
  PID Process_ID;
  // Настройки, связанные с окном.
  PLOGONDLGBOX Related_dialog;
  // Сведения об окне и значения полей ввода.
  DLGBOX Dialog;
 }
LOGONWNDINFO; typedef LOGONWNDINFO* PLOGONWNDINFO;

#define APPLIER_MONITORING_LOGON_WINDOWS   4
#define APPLIER_MONITORING_DIALOG_WINDOWS  20

#endif

// Действия с окнами диалогов.
typedef struct _APPLIER
 {
  // Настройки.
  typedef struct _INRSTS
   {
    // Вызывать команду после ввода пароля? 0 - нет, 1 - да.
    BYTE Script_after_Logon;
    // Запоминать содержимое полей ввода в окнах диалога? 0 - нет, 1 - да.
    BYTE Remember_dialog_fields;
    // Закрывать окна сообщений? 0 - нет, 1 - да.
    BYTE Send_Yes;

    // Окна диалогов.
    DIALOGS Dialogs;
   }
  INRSTS; INRSTS Settings;

  #ifndef INCLUDED_BY_SHELL

  // Внутренние переменные.
  typedef struct _RTSTS
   {
    // Идет ввод пароля в одно из окон.
    BYTE Logon_in_process;

    // Последние обработанные окна диалогов.
    HWND Last_dialog_windows[ APPLIER_MONITORING_DIALOG_WINDOWS ];
   } 
  RTSTS; RTSTS RTSettings;

  typedef struct _RTDLGMEMORY
   {
    // Временные данные для сбора сведений об окнах диалога.
    DLGBOX Dialog_data; LOGONDLGBOX Logon_data; MSGDLGBOX Message_data;

    // Присутствующие окна ввода пароля.
    LOGONWNDINFO Logon_windows[ APPLIER_MONITORING_LOGON_WINDOWS ];
   }
  RTDLGMEMORY; RTDLGMEMORY RTDlgMemory;

  #endif
 }
APPLIER;

APPLIER Applier;