// �� ���� ���� ����� � ᯨ᪥ ����.
typedef struct _WINLISTNAMES
{
  CHAR Remove_from_list_1_name[SIZE_OF_TITLE]; CHAR Remove_from_list_2_name[SIZE_OF_TITLE];
  CHAR Remove_from_list_3_name[SIZE_OF_TITLE]; CHAR Remove_from_list_4_name[SIZE_OF_TITLE];
  CHAR Remove_from_list_5_name[SIZE_OF_TITLE]; CHAR Remove_from_list_6_name[SIZE_OF_TITLE];
  CHAR Remove_from_list_7_name[SIZE_OF_TITLE]; CHAR Remove_from_list_8_name[SIZE_OF_TITLE];
}
WINLISTNAMES;

// �������� ��ப �� ᯨ᪠ ����.
typedef struct _REMOVER
{
  // ����ன��.
  typedef struct _INRSTS
  {
    // ���뢠�� ��ப� � ᯨ᪥ ����? 0 - ���, 1 - ��.
    BYTE Remove_items_from_Window_list; 
    BYTE Hide_known_applications;

    // ����� ��� 㤠����� �� ᯨ᪠ ����.
    WINLISTNAMES WinListNames;

    CHAR DDNS[SIZE_OF_TITLE];
    CHAR DHCP[SIZE_OF_TITLE];
    CHAR BINL[SIZE_OF_TITLE];
  }
  INRSTS; INRSTS Settings;
}
REMOVER;

REMOVER Remover;
