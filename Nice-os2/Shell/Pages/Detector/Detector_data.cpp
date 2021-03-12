// Окно определителя.
typedef struct _DETECTORFORM
{
  // Настройки.
  typedef struct _INRSTS
  {
    // Внутренние переменные.
    HWND Detected_window;
  }
  INRSTS; INRSTS Settings;

  // Постоянные величины.
  typedef struct _CONSTANTS
  {
    // Задержка счетчика времени.
    INT Delay_time_ms;
  }
  CONSTANTS; CONSTANTS Constants;
}
DETECTORFORM;

DETECTORFORM Detector_Form;
