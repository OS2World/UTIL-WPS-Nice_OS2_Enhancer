// ��⮤� ��� ࠡ��� � ��������ன � �����.
#define MouseIsBusy          KbdMouse_MouseIsBusy
#define MouseIsUnderPressure KbdMouse_MouseIsUnderPressure
#define MouseButtonIsPressed KbdMouse_MouseButtonIsPressed

#define ShakePointer         KbdMouse_ShakePointer
#define ResetPointer         KbdMouse_ResetPointer

// ��� ��⮤ ��� ������祭�� ����� ���

VOID KbdMouse_Start (VOID)
{
  #ifdef KbdMouse
  bzero (&KbdMouse, sizeof (KbdMouse));
  #endif

  // ������.
  return;
}

