// Воспроизведение звука при нажатии на клавишу.
typedef struct _CLICKER
{
  // Настройки.
  typedef struct _INRSTS
  {
    // Звук при нажатии на клавишу? 0 - нет, 1 - да.
    BYTE Keyboard_echo; 
    BYTE Keyboard_echo_for_IRC;
    BYTE Keyboard_echo_for_ICQ;

    // Переносить файл со звуком на диск в памяти? 0 - нет, 1 - да.
    BYTE Cache_echo_file;
  }
  INRSTS; INRSTS Settings;

  // Внутренние переменные.
  typedef struct _RTSTS 
  {
    // Звук при нажатии на клавишу.
    CHAR Keyboard_wav[SIZE_OF_PATH];
    CHAR Keyboard_exe[SIZE_OF_PATH];
  }
  RTSTS; RTSTS RTSettings;
}
CLICKER;

CLICKER Clicker;