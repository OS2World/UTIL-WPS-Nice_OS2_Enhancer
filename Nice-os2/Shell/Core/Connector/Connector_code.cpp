
// ��� �।������ ����⥫� ������ ����ன�� ���

// ��뢠���� �� ��������� ����஥� ���짮��⥫��.
// Update_windows - ���� �� �������� �� ����.
VOID Connector_NiceReadSettings (BYTE Update_windows = 0, BYTE Arrange_windows = 0)
{
  // ���뫠�� ᮮ�饭��.
  WinPostMsg (WinWindowFromID (Enhancer.Remote_window, FID_CLIENT), SM_RECEIVE_SETTINGS, (MPARAM) Update_windows, (MPARAM) Arrange_windows);

  // ������.
  return;
}

// ��� �।������ ����⥫� ������ ᯨ᮪ �ਫ������ ���

// ��뢠���� �� ��������� ᯨ᪠ �ਫ������.
VOID Connector_NiceReadRepository (VOID)
{
  // ���뫠�� ᮮ�饭��.
  WinPostMsg (WinWindowFromID (Enhancer.Remote_window, FID_CLIENT), SM_RECEIVE_REPOSITORY, 0, 0);

  // ������.
  return;
}

// ��� �।������ ����⥫� ᮡ��� ᢥ����� �� ���� ����� ��஫� ���

// Window - ���� ����� ��஫�.
VOID Connector_NiceScanLogonDialog (HWND Window)
{
  // ���뫠�� ᮮ�饭��.
  WinPostMsg (WinWindowFromID (Enhancer.Remote_window, FID_CLIENT), SM_SCAN_LOGON_DIALOG, (MPARAM) Window, 0);

  // ������.
  return;
}

// ��� �।������ ����⥫� ᮡ��� ᢥ����� �� ���� ������� ���

// Window - ���� �������.
VOID Connector_NiceScanIncompleteDialog (HWND Window)
{
  // ���뫠�� ᮮ�饭��.
  WinPostMsg (WinWindowFromID (Enhancer.Remote_window, FID_CLIENT), SM_SCAN_INCOMPLETE_DIALOG, (MPARAM) Window, 0);

  // ������.
  return;
}

// ��� �।������ ����⥫� ᮡ��� ᢥ����� �� ���� ᮮ�饭�� ���

// Window - ���� ᮮ�饭��.
VOID Connector_NiceScanMessageDialog (HWND Window)
{
  // ���뫠�� ᮮ�饭��.
  WinPostMsg (WinWindowFromID (Enhancer.Remote_window, FID_CLIENT), SM_SCAN_MESSAGE_DIALOG, (MPARAM) Window, 0);

  // ������.
  return;
}
