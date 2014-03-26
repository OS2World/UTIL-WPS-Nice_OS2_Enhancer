// Действия с мышью.
typedef struct _MOUSEMAPPER
 {
  // Настройки.
  typedef struct _INRSTS
   {
    // Отключить двойное нажатие мыши на картинку в левом верхнем углу окна? 0 - нет, 1 - да.
    BYTE Suppress_double_click_in_sysmenu;
    // Использовать среднюю кнопку для запоминания и вставки текста? 0 - нет, 1 и 2 - да.
    BYTE Use_middle_button_for_CopyPaste;
    // Переносить ввод от клавиатуры под указатель мыши при прокрутке? 0 - нет, 1 - да.
    BYTE Move_input_focus_when_scrolling;
    // Использовать правую кнопку мыши для полосок просмотра? 0 - нет, 1 - да.
    BYTE Use_right_button_in_scrollbars;
    // Менять кнопки мыши если включен Caps Lock? 0 - нет, 1 - да.
    BYTE Invert_mouse_buttons_with_Caps_Lock;
   }
  INRSTS; INRSTS Settings;

  // Внутренние переменные.
  typedef struct _RTSTS
   {
    // Кнопки мыши изменены.
    BYTE Buttons_are_inverted;

    // Состояние мыши изменено.
    BYTE Mouse_state_is_changed;

    // Время последнего нажатия средней кнопки мыши.
    LONG WM_MB_Down_time;
   }
  RTSTS; RTSTS RTSettings;
 }
MOUSEMAPPER;

MOUSEMAPPER MouseMapper;