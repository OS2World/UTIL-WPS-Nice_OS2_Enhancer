// �������� ������ ��� �����襭�� �ਫ������.
typedef struct _WAITER
{
  // ����ﭭ� ����稭�.
  typedef struct _CONSTANTS
  {
    // ��᫮ ����থ� ��� ���⮣� ��������.
    INT Sleep_to_wait_some_time;

    // ��᫮ ����থ� ��� �������� �ਫ������ (��� ������ ��� �����).
    INT Retards_to_wait_process;

    // �६� ��㡮���� ᭠ �� ᮯ஢������� �ਫ������ (��� ������ ��� �����).
    INT Sleep_when_escorting_process;

    // ��᫮ ����থ� ��� ᮪���� �ਫ������ � ��砫� ��� ᮯ஢�������.
    INT Retards_at_escorting_process;
  }
  CONSTANTS; CONSTANTS Constants;
}
WAITER;

WAITER Waiter;