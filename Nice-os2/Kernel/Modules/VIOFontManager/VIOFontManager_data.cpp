// ��� ��� ���� ���� ������ ࠧ��� ����.
typedef struct _VIOFONTMETRICS
{
  CHAR Shell_1_name[SIZE_OF_NAME]; CHAR Shell_2_name[SIZE_OF_NAME];
  CHAR Shell_3_name[SIZE_OF_NAME]; CHAR Shell_4_name[SIZE_OF_NAME];
  CHAR Shell_5_name[SIZE_OF_NAME]; CHAR Shell_6_name[SIZE_OF_NAME];
  CHAR Shell_7_name[SIZE_OF_NAME]; CHAR Shell_8_name[SIZE_OF_NAME];

  INT X_1; INT Y_1; INT X_2; INT Y_2;
  INT X_3; INT Y_3; INT X_4; INT Y_4;
  INT X_5; INT Y_5; INT X_6; INT Y_6;
  INT X_7; INT Y_7; INT X_8; INT Y_8;
}
VIOFONTMETRICS;

// ����� � ⥪�⮢�� �����.
typedef struct _VIOFONTMANAGER
{
  // ����ன��.
  typedef struct _INRSTS
  {
    // �������� ࠧ��� ���� � ⥪�⮢�� �����? 0 - ���, 1 - ��.
    BYTE Change_VIO_font_metrics; 
    BYTE Change_fonts_for_known_applications;

    // ����� � ⥪�⮢�� �����.
    VIOFONTMETRICS VIOFontMetrics;
  }
  INRSTS; INRSTS Settings;

  // ����७��� ��६����.
  typedef struct _RTSTS 
  {
    // ��ப� ��� ������ � ᯨ᪠�� � ���ﬨ �����.
    // �� ��ப� ������ ���� �ᯮ������ � ����ﭭ�� ����� (Heap Memory) ����⥫�,
    // �⮡� �ਫ������ � ��⮪� ����⥫� ����� �������� � ��� � ����/�������� ��.
    CHAR Item_text[SIZE_OF_ITEM_TEXT];
  }
  RTSTS; RTSTS RTSettings;
}
VIOFONTMANAGER; 

VIOFONTMANAGER VIOFontManager;