// ��⮤� ��� ࠡ��� � �����-"������᪮�", ����뢠�騬 �� ��⠫�� ����.
#define ShowCurtainWindow  Curtain_ShowCurtainWindow
#define HideCurtainWindow  Curtain_HideCurtainWindow

#define CurtainWindow      Curtain_CurtainWindow

#define DestroyCurtain     Curtain_DestroyCurtain

// ��� ��⮤ ��� ������祭�� ����� ���

VOID Curtain_Start (VOID)
{
  #ifdef Curtain
  bzero (&Curtain, sizeof (Curtain));
  #endif

  // ������ ����ﭭ� ����稭�.
  Curtain.Constants.Curtain_present_time = 7000;

  // ������� ����-��������.
  Curtain_CreateCurtain ();

  // ������.
  return;
}
