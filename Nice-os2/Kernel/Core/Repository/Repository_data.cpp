// ����� ���窮� �� ࠡ�祬 �⮫�.
typedef struct _OBJECTS
{
  // ����� ���窮� �� ࠡ�祬 �⮫�.
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

// ���������� ��� �ࠢ����� �ਫ�����ﬨ.
typedef struct _PIPES
{
  // ������� ᮥ�������.
  CHAR PM123_pipe[SIZE_OF_NAME];
  CHAR WarpVision_pipe[SIZE_OF_NAME];
  CHAR ZMP3_pipe[SIZE_OF_NAME];
}
PIPES; typedef PIPES* PPIPES;

// ��।������ ��� 㪠��⥫�� �� �맮�� ��⮤�� ��� �஢�ન.
typedef BYTE (ISAPPWINDOW) (HWND); typedef ISAPPWINDOW* PISAPPWINDOW;

// ����� � ᯨ᪮� �ਫ������.
typedef struct _KRNL_REPOSITORY
{
  // ����ன��.
  typedef struct _INRSTS
  {
    // ���窨 � ᮥ�������.
    OBJECTS Objects;
    PIPES Pipes;
  }
  INRSTS; INRSTS Settings;

  // ����७��� ��६����.
  typedef struct _RTSTS
  {
    // ���᮪ �ਫ������ �� ���⥭.
    BYTE Repository_is_ready;

    // ��ப� ��� ������ � ᯨ᪠�� � ���ﬨ �����.
    // �� ��ப� ������ ���� �ᯮ������ � ����ﭭ�� ����� (Heap Memory) ����⥫�,
    // �⮡� �ਫ������ � ��⮪� ����⥫� ����� �������� � ��� � ����/�������� ��.
    CHAR Item_text[SIZE_OF_ITEM_TEXT];
  }
  RTSTS; RTSTS RTSettings;
}
KRNL_REPOSITORY;

KRNL_REPOSITORY Krnl_Repository;