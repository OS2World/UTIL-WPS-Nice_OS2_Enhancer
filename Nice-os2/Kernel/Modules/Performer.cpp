// ��⮤� ��� �믮������ ����⢨� � ������.
#define SetNextButtons           Performer_SetNextButtons

#define PerformAction            Performer_PerformAction

#define WindowIsRolled           Performer_WindowIsRolled
#define UnrollWindow             Performer_UnrollWindow

#define ArrangerMustBeDisabled   Performer_ArrangerMustBeDisabled

// ��� ��⮤ ��� ������祭�� ����� ���

VOID Performer_Start (VOID)
{
  #ifdef Performer
  bzero (&Performer, sizeof (Performer));
  #endif

  // ������.
  return;
}

