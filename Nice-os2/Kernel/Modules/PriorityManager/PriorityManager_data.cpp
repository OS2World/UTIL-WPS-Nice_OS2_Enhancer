// ��� ��� ���� � �ਫ������ ���� ��ࠢ������ �ਮ����.
typedef struct _PRIORITY_NAMES
{
  CHAR Exceeded_priority_1_name[SIZE_OF_NAME]; CHAR Exceeded_priority_2_name[SIZE_OF_NAME];
  CHAR Exceeded_priority_3_name[SIZE_OF_NAME]; CHAR Exceeded_priority_4_name[SIZE_OF_NAME];
  CHAR Exceeded_priority_5_name[SIZE_OF_NAME]; CHAR Exceeded_priority_6_name[SIZE_OF_NAME];
  CHAR Exceeded_priority_7_name[SIZE_OF_NAME]; CHAR Exceeded_priority_8_name[SIZE_OF_NAME];
}
PRIORITY_NAMES;

// ����� � �ਮ��⠬� �ਫ������.
typedef struct _PRIORITY_MANAGER
{
  // ����ன��.
  typedef struct _INRSTS
  {
    // ��ࠢ������ �ਮ���� �ਫ������? 0 - ���, 1 - ��.
    BYTE Normalize_priority;

    // �������� �ਮ���� �ਫ������ �� ��४��祭�� ����? 0 - ���, 1 - ��.
    BYTE Dynamic_priority;
    BYTE Dynamic_priority_for_VIO;
    BYTE Dynamic_priority_for_lSwitcher;

    // �ਮ����.
    PRIORITY_NAMES PriorityNames;
  }
  INRSTS; INRSTS Settings;

  // ����७��� ��६����.
  typedef struct _RTSTS
  {
    // ���᮪ ������� � ����㯭�� �ਫ������, � ������ ����� ������ �ਮ����.
    VISIBLEPROCESS Visible_processes[SIZE_OF_VISPROCLIST];
    INT Visible_processes_quantity;
  }
  RTSTS; RTSTS RTSettings;
}
PRIORITY_MANAGER;

PRIORITY_MANAGER PriorityManager;