// ��⮤� ��� ���� ᮮ�饭��.
#define MessageBox      Krnl_MessageBox_MessageBox

// ��� ��⮤ ��� ������祭�� ����� ���

VOID Krnl_MessageBox_Start (VOID)
{
  #ifdef Krnl_MessageBox
  bzero (&Krnl_MessageBox, sizeof (Krnl_MessageBox));
  #endif

  // ������.
  return;
}
