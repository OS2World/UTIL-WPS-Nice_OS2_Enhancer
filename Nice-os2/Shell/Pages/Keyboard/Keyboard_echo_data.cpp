// ���� ����஥�.
typedef struct _KBDECHOPAGE
{
  // ����ன��.
  typedef struct _INRSTS
  {
    // ���� ����� � ����.
    ULONG Play_sound;
    ULONG For_IRC;
    ULONG For_ICQ;

    ULONG Use_RAMFS;
  }
  INRSTS; INRSTS Settings;
}
KBDECHOPAGE;

KBDECHOPAGE Keyboard_Echo;
