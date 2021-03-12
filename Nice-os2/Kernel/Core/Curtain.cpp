// Методы для работы с окном-"занавеской", закрывающим все остальные окна.
#define ShowCurtainWindow  Curtain_ShowCurtainWindow
#define HideCurtainWindow  Curtain_HideCurtainWindow

#define CurtainWindow      Curtain_CurtainWindow

#define DestroyCurtain     Curtain_DestroyCurtain

// ─── Метод для подключения класса ───

VOID Curtain_Start (VOID)
{
  #ifdef Curtain
  bzero (&Curtain, sizeof (Curtain));
  #endif

  // Задаем постоянные величины.
  Curtain.Constants.Curtain_present_time = 7000;

  // Создаем окно-занавеску.
  Curtain_CreateCurtain ();

  // Возврат.
  return;
}
