// �뤥����� ��ப � �����.
typedef struct _MARKER
{
  // ����ன��.
  typedef struct _INRSTS
  {
    // ��।����� "Ctrl/Shift+Ins" � ⥪�⮢�� �����? 0 - ���, 1 - ��.
    BYTE CopyPaste_keys_in_VIO;

    // ������� ����⢨� � ����� � ⥪�⮢�� �����? 0 - ���, 1 - ��.
    BYTE Mouse_in_VIO;
    BYTE Mouse_in_VIO_requires_Shift;
    BYTE Mouse_in_VIO_sends_Copy;
  }
  INRSTS; INRSTS Settings;

  // �६���� ��६����.
  typedef struct _RTSTS
  {
    // ����ন��� Clipboard �� �ᥬ� ������ FireFox-������.
    PBYTE Clipboard_data_Text; INT Clipboard_data_Text_length;
    PBYTE Clipboard_data_UCS2; INT Clipboard_data_UCS2_length;
  }
  RTSTS; RTSTS RTSettings;
}
MARKER;

MARKER Clipper;