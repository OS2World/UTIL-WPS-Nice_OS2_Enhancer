// Окно-занавеска, которое закрывает экран и ничего не рисует.
typedef struct _CURTAIN
 {
  // Постоянные величины.
  typedef struct _CONSTANTS
   {
    // Значения времени для сокрытия окна.
    INT Curtain_present_time;
   }
  CONSTANTS; CONSTANTS Constants;

  // Окно, закрывающее экран.
  HWND Curtain_window;
 }
CURTAIN; 

CURTAIN Curtain;
