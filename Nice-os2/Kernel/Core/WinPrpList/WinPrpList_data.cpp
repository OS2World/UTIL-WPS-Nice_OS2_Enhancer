// �����⢠ ����.
typedef struct _WINDOWPROPERTY
{
  // ���� ࠬ��.
  HWND Frame_window;

  // ��������� ����.
  CHAR Title[SIZE_OF_TITLE];
  // ���箪.
  HPOINTER Icon; BYTE Icon_was_loaded;
  // ��ਭ� ࠬ�� ����.
  INT Frame_width;
  // ����ﭨ� ������.
  LONG Buttons;
  // ��� ���� ������ ����⢨�.
  BYTE Actions;
  // ��ࠢ� �� ��������� ���� �������⥫�� ����.
  BYTE Advanced_controls;

  // �믮����� ����প� ��। ᬥ��� ᢮��� ࠬ��.
  BYTE Retards_performed;

  // ��ࠡ��稪 ᮮ�饭�� ��� ���� ���������.
  PFNWP TitleBar_performer;
  // ��ࠡ��稪 ᮮ�饭�� ��� ���� ������ ������.
  PFNWP MinMax_performer;
  // ��ࠡ��稪 ᮮ�饭�� ��� ���� ����.
  PFNWP Menu_performer;

  // ���� �뫮 ��࠭��.
  BYTE Activated;
  // ���� �뫮 㢥��祭�.
  BYTE Maximized;
  // ������, � ���ன �ᯮ�������� ����.
  INT Room;
  // ����⢨�, �믮��塞�� � �����.
  LONG Performed_action;
  // �।��騩 ࠧ��� ����.
  INT Previous_width;
  INT Previous_height;

  // ���� ����稫� ᮮ�饭�� � �����⨨.
  BYTE Close_message_received;

  // ���� �뫮 ���� ���襥 �ᯮ������� �� �࠭�.
  ULONG Time_of_arrange;
  // ��� ���� �� ������� ������ �롮� ����.
  BYTE VIO_font_dialog;

  // ���祭�� ��� ������� �ਮ���.
  LONG Priority_class;
  LONG Priority_delta;

  // ��� �ਫ������, ᮧ���襣� ����.
  CHAR Exe_name[SIZE_OF_NAME];
  // ���� � �ਫ������, ᮧ���襬� ����.
  CHAR Exe_path[SIZE_OF_PATH];
}
WINDOWPROPERTY;

// ���᮪ ᢮��� ����.
#define WINPRPLIST_LENGTH 256

typedef struct _WINPRPLIST
{
  // ���᮪ ᢮���.
  WINDOWPROPERTY Properties_list[WINPRPLIST_LENGTH];
  // �������� � ᯨ᪥ ᢮���.
  PRPLISTDESC Descendant;
}
WINPRPLIST;

WINPRPLIST WinPrpList;
