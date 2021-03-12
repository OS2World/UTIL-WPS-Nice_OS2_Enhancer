// Методы для работы с клавиатурой и мышью.
#define MouseIsBusy          KbdMouse_MouseIsBusy
#define MouseIsUnderPressure KbdMouse_MouseIsUnderPressure
#define MouseButtonIsPressed KbdMouse_MouseButtonIsPressed

#define ShakePointer         KbdMouse_ShakePointer
#define ResetPointer         KbdMouse_ResetPointer

// ─── Метод для подключения класса ───

VOID KbdMouse_Start (VOID)
{
  #ifdef KbdMouse
  bzero (&KbdMouse, sizeof (KbdMouse));
  #endif

  // Возврат.
  return;
}

