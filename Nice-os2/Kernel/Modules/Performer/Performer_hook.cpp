
// ��� ����⠭�������� "ᢥ����" ���� ���

// Message - ᮮ�饭��, ���஥ ��।����� ������ �� ����.
VOID Performer_RolledWindowRestoreNode (PQMSG Message)
{
  // �᫨ ���� ����, ���஥ �࠭� ������:
  if (RolledWindow () != NULLHANDLE)
  {
    // �᫨ ����, ���஥ �뫮 �࠭� ������, ������� ࠧ��� ��� ����뢠����:
    if (Message->hwnd == RolledWindow ())
     if ((Message->msg == WM_SYSCOMMAND && Message->mp1 == (MPARAM) SC_HIDE) ||
         (Message->msg == WM_SYSCOMMAND && Message->mp1 == (MPARAM) SC_RESTORE) ||
         (FrameWindowIsClosing (Message)))
     {
       // �����頥� ��� � ���筮� ���ﭨ�.
       Performer_UnrollWindow (Message->hwnd);
     }

    // �᫨ ����� ������ 㬥��襭�� - ��⠥�, �� �� ���� ���� �� �࠭� ������.
    if (Message->msg == WM_SYSCOMMAND && Message->mp1 == (MPARAM) SC_MINIMIZE)
     RememberRolledWindow (NULLHANDLE);
  }

  // ������.
  return;
}


// ��� �������� �� ᮮ�饭�ﬨ ���

// �� ��६���� - ���譨�.
VOID PerformerInputHook (HAB Application, PQMSG Message, PBYTE Discarding)
{
  // ����⠭�������� ���� �� �����⨨.
  Performer_RolledWindowRestoreNode (Message);

  // ������.
  return;
}


// ��� �������� �� ᮮ�饭�ﬨ �� ���������� ���

// �� ��६���� - ���譨�.
VOID PerformerKbdInputHook (HAB Application, PQMSG Message, PBYTE Discarding)
{
  // ����⠭�������� ���� �� �����⨨.
  Performer_RolledWindowRestoreNode (Message);

  // ������.
  return;
}

