// ��⮤� ��� �ᯮ�������� ���㦥���.
#define Rnd            StdLib_Rnd

#define Unsigned       StdLib_Unsigned
#define Min            StdLib_Min
#define Max            StdLib_Max
#define DivideMultiply StdLib_DivideMultiply
#define DivideDivideLR StdLib_DivideDivideLR
#define DivideDivideRL StdLib_DivideDivideRL

#define Retard         StdLib_Retard

// ��� ��⮤ ��� ������祭�� ����� ���

// Application - �ਫ������.
VOID StdLib_Start (HAB Application = NULLHANDLE)
{
  #ifdef StdLib
  bzero (&StdLib, sizeof (StdLib));
  #endif

  // ����᪠�� ���稪 ��砩��� �ᥫ.
  srand (WinGetCurrentTime (Application));

  // ������.
  return;
}
