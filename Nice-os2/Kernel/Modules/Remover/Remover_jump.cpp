
// ��� �믮���� ����⢨� ��᫥ �⥭�� ����஥� � ᮧ����� ��⮪� ���

VOID Remover_Jump (VOID)
{
  // ���뢠�� ��� �����뢠�� ��ப� � ᯨ᪥ ����.
  if (Remover.Settings.Remove_items_from_Window_list) Remover_ShowAllItemsInSwitchList (0, Remover.Settings.Hide_known_applications);
  else Remover_ShowAllItemsInSwitchList (1);

  // ������.
  return;
}