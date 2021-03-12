// Клавиши, которые может переопределить расширитель.
typedef struct _KEYS
{
  // Значение: 0 - не трогать клавишу, иначе - выполнить определенное действие.
  INT F11;
  INT Shift_F11;
  INT F12;
  INT Shift_F12;

  INT PrtScr;
  INT SysRq;
  INT Pause;

  INT Right_Alt;
  INT Shift_Right_Alt;

  INT Left_WinKey;
  INT Right_WinKey;
  INT TaskList;

  INT F1;
  INT F2;
  INT F3;
  INT F4;
  INT F5;
  INT F6;
  INT F7;
  INT F8;
  INT F9;
  INT F10;

  INT WinKey_Backslash;
  INT WinKey_Backspace;

  INT WinKey_Num_Slash;
  INT WinKey_Num_Multiple;
  INT WinKey_Num_Minus;
  INT WinKey_Num_Plus;
  INT WinKey_Num_Enter;

  INT WinKey_F1;
  INT WinKey_F2;
  INT WinKey_F3;
  INT WinKey_F4;
  INT WinKey_F5;
  INT WinKey_F6;
  INT WinKey_F7;
  INT WinKey_F8;
  INT WinKey_F9;
  INT WinKey_F10;
  INT WinKey_F11;
  INT WinKey_F12;

  INT WinKey_A;
  INT WinKey_B;
  INT WinKey_C;
  INT WinKey_D;
  INT WinKey_E;
  INT WinKey_F;
  INT WinKey_G;
  INT WinKey_H;
  INT WinKey_I;
  INT WinKey_J;
  INT WinKey_K;
  INT WinKey_L;
  INT WinKey_M;
  INT WinKey_N;
  INT WinKey_O;
  INT WinKey_P;
  INT WinKey_Q;
  INT WinKey_R;
  INT WinKey_S;
  INT WinKey_T;
  INT WinKey_U;
  INT WinKey_V;
  INT WinKey_W;
  INT WinKey_X;
  INT WinKey_Y;
  INT WinKey_Z;

  INT Power;
  INT Sleep;
  INT WakeUp;

  INT Play;
  INT Stop;
  INT Previous_track;
  INT Next_track;
  INT Volume_decrement;
  INT Volume_increment;
  INT Mute;
  INT Media;

  INT Terminal;
  INT Calculator;
  INT Browser;
  INT Mail_reader;
  INT Search;
  INT Bookmarks;

  INT Back;
  INT Forward;
  INT Cancel;
  INT Refresh;

  INT PageLeft;
  INT PageRight;

  INT UserKey_1;            INT SC_UserKey_1;
  INT UserKey_2;            INT SC_UserKey_2;
  INT UserKey_3;            INT SC_UserKey_3;
  INT UserKey_4;            INT SC_UserKey_4;
  INT UserKey_5;            INT SC_UserKey_5;
  INT UserKey_6;            INT SC_UserKey_6;
  INT UserKey_7;            INT SC_UserKey_7;
  INT UserKey_8;            INT SC_UserKey_8;
  INT UserKey_9;            INT SC_UserKey_9;
  INT UserKey_A;            INT SC_UserKey_A;
  INT UserKey_B;            INT SC_UserKey_B;
  INT UserKey_C;            INT SC_UserKey_C;
  INT UserKey_D;            INT SC_UserKey_D;
  INT UserKey_E;            INT SC_UserKey_E;
  INT UserKey_F;            INT SC_UserKey_F;

  INT Compaq_i;
  INT Compaq_Home;
  INT Compaq_Search;
  INT Compaq_Mail;
  INT Compaq_People;
  INT Compaq_Bench;
  INT Compaq_Chat;
  INT Compaq_Reading;
}
KEYS; typedef KEYS* PKEYS;

// Клавиши и действия.
typedef struct _DEFINER
{
  // Настройки.
  typedef struct _INRSTS
  {
    BYTE Define_keys;
    BYTE Define_common_keys;
    BYTE Define_win_keys;
    BYTE Define_function_keys;
    BYTE Define_quick_keys;
    BYTE Define_numeric_keys;
    BYTE Define_pointer_keys;
    BYTE Define_power_keys;
    BYTE Define_multimedia_keys;
    BYTE Define_toolkit_keys;
    BYTE Define_internet_keys;
    BYTE Define_scrolling_keys;
    BYTE Define_user_keys;
    BYTE Define_Cherry_keys;
    BYTE Define_Compaq_keys;

    KEYS Keys;
  }
  INRSTS; INRSTS Settings;
}
DEFINER;

DEFINER Definer;