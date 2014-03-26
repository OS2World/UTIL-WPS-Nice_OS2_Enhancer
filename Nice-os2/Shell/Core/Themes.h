// Структуры для обращения к функциям, изменяющим внешний вид полей ввода в окне.
typedef struct _THEMEPAGEDEF
 {
  HWND NeonPalette_FillTB_window;
  HWND NeonPalette_Container_window;

  HWND NeonPalette_Active_1_window;
  HWND NeonPalette_Active_2_window;
  HWND NeonPalette_Active_3_window;

  HWND NeonPalette_Inactive_1_window;
  HWND NeonPalette_Inactive_2_window;
  HWND NeonPalette_Inactive_3_window;
 }
THEMEPAGEDEF;

typedef THEMEPAGEDEF* PTHEMEPAGEDEF;
