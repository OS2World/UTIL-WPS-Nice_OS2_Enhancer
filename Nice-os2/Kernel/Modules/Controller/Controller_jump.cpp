
// ��� �믮���� ����⢨� ��᫥ �⥭�� ����஥� � ᮧ����� ��⮪� ���

VOID Controller_Jump (VOID)
{
  // ��⠭�������� ��४���⥫� �� ���������.
  if (Controller.Settings.Turn_Num_Lock) 
  { 
    Controller_SetNumLock (); 
    Controller_SetVIONumLock (); 
  }

  // ������.
  return;
}