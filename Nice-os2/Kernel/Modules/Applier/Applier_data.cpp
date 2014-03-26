// ��� ��� ���� ���� �믮����� ������� � ���������� � ��� ���� �����.
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

// �������� �� ������ ����� ��஫�.
typedef struct _LOGONWNDINFO
 {
  // ���� ࠬ��.
  HWND Window;
  // �ਫ������, ᮧ���襥 ����.
  PID Process_ID;
  // ����ன��, �易��� � �����.
  PLOGONDLGBOX Related_dialog;
  // �������� �� ���� � ���祭�� ����� �����.
  DLGBOX Dialog;
 }
LOGONWNDINFO; typedef LOGONWNDINFO* PLOGONWNDINFO;

#define APPLIER_MONITORING_LOGON_WINDOWS   4
#define APPLIER_MONITORING_DIALOG_WINDOWS  20

#endif

// ����⢨� � ������ ��������.
typedef struct _APPLIER
 {
  // ����ன��.
  typedef struct _INRSTS
   {
    // ��뢠�� ������� ��᫥ ����� ��஫�? 0 - ���, 1 - ��.
    BYTE Script_after_Logon;
    // ���������� ᮤ�ন��� ����� ����� � ����� �������? 0 - ���, 1 - ��.
    BYTE Remember_dialog_fields;
    // ����뢠�� ���� ᮮ�饭��? 0 - ���, 1 - ��.
    BYTE Send_Yes;

    // ���� ��������.
    DIALOGS Dialogs;
   }
  INRSTS; INRSTS Settings;

  #ifndef INCLUDED_BY_SHELL

  // ����७��� ��६����.
  typedef struct _RTSTS
   {
    // ���� ���� ��஫� � ���� �� ����.
    BYTE Logon_in_process;

    // ��᫥���� ��ࠡ�⠭�� ���� ��������.
    HWND Last_dialog_windows[ APPLIER_MONITORING_DIALOG_WINDOWS ];
   } 
  RTSTS; RTSTS RTSettings;

  typedef struct _RTDLGMEMORY
   {
    // �६���� ����� ��� ᡮ� ᢥ����� �� ����� �������.
    DLGBOX Dialog_data; LOGONDLGBOX Logon_data; MSGDLGBOX Message_data;

    // ���������騥 ���� ����� ��஫�.
    LOGONWNDINFO Logon_windows[ APPLIER_MONITORING_LOGON_WINDOWS ];
   }
  RTDLGMEMORY; RTDLGMEMORY RTDlgMemory;

  #endif
 }
APPLIER;

APPLIER Applier;