// Убирание окна наверх.
typedef struct _ROLLER
{
  // Окно, которое убрано наверх.
  HWND Rolled_window; 

  // Предыдущее расположение окна.
  SWP Rolled_window_placement;
}
ROLLER;

ROLLER Roller;