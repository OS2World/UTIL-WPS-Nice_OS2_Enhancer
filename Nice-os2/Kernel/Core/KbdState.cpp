// ��⮤� ��� ����⠭���� ���ﭨ� ���������� �� �஢�� V-Keys.
#define ChangePMKeyboardState      KbdState_ChangePMKeyboardState
#define RestorePMKeyboardState     KbdState_RestorePMKeyboardState
#define PMKeyboardStateIsChanged   KbdState_PMKeyboardStateIsChanged

// ��� ��⮤ ��� ������祭�� ����� ���

VOID KbdState_Start( VOID )
{
 #ifdef KbdState
 bzero( &KbdState, sizeof( KbdState ) );
 #endif

 // ������.
 return;
}

