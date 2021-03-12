// Метод для вызова определителя.
#define OpenDETECTOR Detector_OpenDETECTOR

// ─── Метод для подключения класса ───

VOID Detector_Start (VOID)
{
  #ifdef Detector_Form
  bzero (&Detector_Form, sizeof (Detector_Form));
  #endif

  // Задаем постоянные величины.
  Detector_Form.Constants.Delay_time_ms = 500;

  // Возврат.
  return;
}

