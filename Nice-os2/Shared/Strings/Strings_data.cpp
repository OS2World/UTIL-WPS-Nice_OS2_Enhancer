
// ����७��� ��६����.
typedef struct _STRINGS
{
  // ����� � ��ப���.
  typedef struct _INRSTS
  {
    // ��࠭�, � ���ன ࠡ�⠥� �ਫ������.
    COUNTRYCODE Country;

    // ���� ��� ��ॢ���.
    CHAR Case_map[255];
  }
  INRSTS; INRSTS Inner_settings;
}
STRINGS; typedef STRINGS* PSTRINGS;

// ��६���� ������ ���� �ᯮ������ � ࠧ���塞�� ������ �����.
STRINGS Strings_static_data; PSTRINGS Strings = &Strings_static_data;
