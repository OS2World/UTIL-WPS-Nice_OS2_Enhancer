// Слежение за текстовым окном.
typedef struct _VIOMONITOR
 {
  // Постоянные величины.
  typedef struct _CONSTANTS
   {
    // Число задержек при слежении за текстовым окном.
    INT Retards_when_VIO_monitoring;
   }
  CONSTANTS; CONSTANTS Constants;
 }
VIOMONITOR;

VIOMONITOR VIOMonitor;
