
// ��� ���������� ����, ���஥ �࠭� ������ ���

// �� ��६���� - ���譨�.
VOID Roller_RememberRolledWindow (HWND Rolled_window, PSWP Rolled_window_placement = NULL)
{
  // ���������� ����.
  Roller.Rolled_window = Rolled_window;

  // ���������� �ᯮ������� ����.
  if (Rolled_window_placement != NULL) memcpy (&Roller.Rolled_window_placement, Rolled_window_placement, sizeof (SWP));
  else bzero (&Roller.Rolled_window_placement, sizeof (SWP));

  // ������.
  return;
}

// ��� �����頥� ����, ���஥ �࠭� ������ ���

HWND Roller_RolledWindow (VOID)
{
  // �����頥� ����.
  return Roller.Rolled_window;
}

// ��� �����頥� �ᯮ������� ����, ���஥ �࠭� ������ ���

VOID Roller_GetRolledWindowPlacement (PINT X, PINT Y, PINT Width, PINT Height)
{
  *X = Roller.Rolled_window_placement.x;
  *Y = Roller.Rolled_window_placement.y;
  *Width = Roller.Rolled_window_placement.cx;
  *Height = Roller.Rolled_window_placement.cy;

  // ������.
  return;
}