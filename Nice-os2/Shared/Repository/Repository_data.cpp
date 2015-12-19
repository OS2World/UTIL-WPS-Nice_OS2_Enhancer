// �����⢠ �ਫ������.
typedef struct _PROCESSINFO
 {
  // �ਫ������ � த�⥫�᪮� �ਫ������.
  PID Process_ID;
  PID Parent_ID;

  // ��� � ���� � �ਫ������.
  CHAR Exe_name[ SIZE_OF_NAME ];
  CHAR Exe_path[ SIZE_OF_PATH ];
 }
PROCESSINFO; typedef PROCESSINFO* PPROCESSINFO;

// ������� ����⥫� �ਫ������.
typedef struct _APPLICATIONS
 {
  // ���祭�� ���� APP_..., ��।����饥 �ਫ������ � ᯨ᪥. �� ���������.
  INT Application;
  // ����⢨� ��� �맮�� �ਫ������ - ���祭�� ���� SHOW_..., �ᯮ��㥬�� � ����ன���. ����� ����������.
  INT Action;
  // �����, ��� ���ன �ᯮ������ �ਫ������ - ���祭�� ���� BROWSE_... � �.�.
  INT Purpose;

  // ��� �ਫ������ - ���祭�� ���� PROG_..., ���ᠭ�� � PMShl.h, ����� �� ��������.
  PROGCATEGORY Mode;

  // �ਧ���, �� �� ��� �ᯮ��㥬�� �ਫ������ (��� ���� �㤥� ��뢠���� � ����� ��।�).
  BYTE Desired;

  // ����� ���窮� ��� �맮�� �ਫ������, ����� ���� ��᪮�쪮.
  CHAR WPS_name_A[ SIZE_OF_NAME ];
  CHAR WPS_name_B[ SIZE_OF_NAME ];
  CHAR WPS_name_C[ SIZE_OF_NAME ];
  CHAR WPS_name_D[ SIZE_OF_NAME ];

  // ����� 䠩��� ��� �맮�� �ਫ������, ����� ���� ��᪮�쪮.
  CHAR Exe_name_1[ SIZE_OF_NAME ];
  CHAR Exe_name_2[ SIZE_OF_NAME ];
  CHAR Exe_name_3[ SIZE_OF_NAME ];
  CHAR Exe_name_4[ SIZE_OF_NAME ];

  // ��� ����ன�� � INI, ᮤ�ঠ饩 �� ���祭��.
  CHAR Exe_INI_setting_name[ SIZE_OF_NAME ];

  // ���箪 �� ࠡ�祬 �⮫�.
  CHAR Object[ SIZE_OF_NAME ];
  // ��� ����ன�� � INI, ᮤ�ঠ饩 �� ���祭��.
  CHAR Object_INI_setting_name[ SIZE_OF_NAME ];

  // ���� � �ਫ������.
  CHAR Path[ SIZE_OF_PATH ];
  // ��� ����ன�� � INI, ᮤ�ঠ饩 �� ���祭��.
  CHAR Path_INI_setting_name[ SIZE_OF_NAME ];

  // ���祢� ᫮�� ��� ���᪠ ���窠, ����� ���� ��᪮�쪮.
  CHAR WPS_keyword_1[ SIZE_OF_NAME ];
  CHAR WPS_keyword_2[ SIZE_OF_NAME ];
  CHAR WPS_keyword_3[ SIZE_OF_NAME ];
  CHAR WPS_keyword_4[ SIZE_OF_NAME ];

  // ���祢� ᫮�� ��� ���᪠ ����, ����� ���� ��᪮�쪮.
  CHAR Window_keyword_1[ SIZE_OF_NAME ];
  CHAR Window_keyword_2[ SIZE_OF_NAME ];
  CHAR Window_keyword_3[ SIZE_OF_NAME ];
  CHAR Window_keyword_4[ SIZE_OF_NAME ];

  // ���� � ��।� ᮮ�饭��, ����� ���� �� ���������.
  HWND Window; HMQ Message_queue;
 }
APPLICATIONS; typedef APPLICATIONS* PAPPLICATIONS;

// ���᮪ �������� ����⥫� �ਫ������.
typedef struct _REPOSITORY
 {
  // ��᫮ �ਫ������ � ᯨ᪥.
  INT Length;
  // ���� �ਫ������.
  APPLICATIONS Items[ MAX_RP_ENTRIES ];
 }
REPOSITORY; typedef REPOSITORY* PREPOSITORY;

// ��६���� ������ ���� �ᯮ������ � ࠧ���塞�� ������ �����.
REPOSITORY Repository;