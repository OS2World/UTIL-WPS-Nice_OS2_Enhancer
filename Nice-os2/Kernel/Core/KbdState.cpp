// Методы для подстановки состояния клавиатуры на уровне V-Keys.
#define ChangePMKeyboardState      KbdState_ChangePMKeyboardState
#define RestorePMKeyboardState     KbdState_RestorePMKeyboardState
#define PMKeyboardStateIsChanged   KbdState_PMKeyboardStateIsChanged

// ─── Метод для подключения класса ───

VOID KbdState_Start( VOID )
{
 #ifdef KbdState
 bzero( &KbdState, sizeof( KbdState ) );
 #endif

 // Возврат.
 return;
}

