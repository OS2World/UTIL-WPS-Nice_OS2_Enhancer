// ��� �����頥� ⥪�騩 ��⠫�� ���

VOID GetCurrentPath (PCHAR Current_directory)
{
  // �롨ࠥ� ����.
  ULONG Current_drive = 0; ULONG Drive_map = 0;

  DosQueryCurrentDisk (&Current_drive, &Drive_map);
  Current_directory[0] = (CHAR) Current_drive + 64;
  Current_directory[1] = ':';
  Current_directory[2] = 0;

  // ������.
  return;
}
