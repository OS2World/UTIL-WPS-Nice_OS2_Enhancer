
// ��� �����頥� 㪠��⥫� �� ᯨ᮪ ���� ���窮� ���

POBJECTS Krnl_Repository_GetKnownObjects (VOID)
{
  // �����頥� 㪠��⥫�.
  return &Krnl_Repository.Settings.Objects;
}

// ��� �����頥� 㪠��⥫� �� ᯨ᮪ PIPE-ᮥ������� ���

PPIPES Krnl_Repository_GetKnownPipes (VOID)
{
  // �����頥� 㪠��⥫�.
  return &Krnl_Repository.Settings.Pipes;
}
