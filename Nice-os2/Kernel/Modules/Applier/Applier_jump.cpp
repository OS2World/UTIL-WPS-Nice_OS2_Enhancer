
// ��� �믮���� ����⢨� ��᫥ �⥭�� ����஥� � ᮧ����� ��⮪� ���

VOID Applier_Jump (VOID)
{
  // ��室�� ��������� ����, ������� ����⥫�.
  WinPostQueueMsg (Enhancer.Modules.Applier->Message_queue, SM_FIND_DIALOG_WINDOWS, 0, 0);

  // ������.
  return;
}