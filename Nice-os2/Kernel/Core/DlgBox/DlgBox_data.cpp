
// ����� � ������ ��������.
typedef struct _KRNL_DLGBOX
 {
  // ����७��� ��६����.
  typedef struct _RTSTS
   {
    // ��ப� ��� ������ � ᯨ᪠�� � ���ﬨ �����.
    // �� ��ப� ������ ���� �ᯮ������ � ����ﭭ�� ����� (Heap Memory) ����⥫�,
    // �⮡� �ਫ������ � ��⮪� ����⥫� ����� �������� � ��� � ����/�������� ��.
    CHAR Item_text[ SIZE_OF_ITEM_TEXT ];

    // ���祭�� ��� ������ � ᯨ᪠��.
    LONG Item_index;
   }
  RTSTS; RTSTS RTSettings;
 }
KRNL_DLGBOX;

KRNL_DLGBOX Krnl_DlgBox;