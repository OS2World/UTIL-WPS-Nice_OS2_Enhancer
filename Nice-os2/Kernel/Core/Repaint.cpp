// ��⮤� ��� ���������� ����.
#define UpdateWindow           Repaint_UpdateWindow
#define UpdateAllWindows       Repaint_UpdateAllWindows
#define UpdateFrameBorder      Repaint_UpdateFrameBorder

// ��� ��⮤ ��� ������祭�� ����� ���

VOID Repaint_Start (VOID)
{
  #ifdef Repaint
  bzero (&Repaint, sizeof (Repaint));
  #endif

  // ������.
  return;
}
