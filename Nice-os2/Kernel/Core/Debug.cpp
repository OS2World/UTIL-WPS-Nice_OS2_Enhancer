#ifdef DEBUG_VERSION

// ��⮤� ��� �⫠���.
#define Bzz      Krnl_Debug_Bzz
#define Log      Krnl_Debug_Log

// ��� ��⮤ ��� ������祭�� ����� ���

VOID Krnl_Debug_Start (VOID)
{
  #ifdef Krnl_Debug
  bzero (&Krnl_Debug, sizeof (Krnl_Debug));
  #endif

  // ����塞 䠩�� ��⮢�� ���ᨨ.
  DosForceDelete ("_log.txt"); DosForceDelete ("XTest.exe");

  // ������.
  return;
}

#endif