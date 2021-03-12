// Для этих окон надо менять размер шрифта.
typedef struct _VIOFONTMETRICS
{
  CHAR Shell_1_name[SIZE_OF_NAME]; CHAR Shell_2_name[SIZE_OF_NAME];
  CHAR Shell_3_name[SIZE_OF_NAME]; CHAR Shell_4_name[SIZE_OF_NAME];
  CHAR Shell_5_name[SIZE_OF_NAME]; CHAR Shell_6_name[SIZE_OF_NAME];
  CHAR Shell_7_name[SIZE_OF_NAME]; CHAR Shell_8_name[SIZE_OF_NAME];

  INT X_1; INT Y_1; INT X_2; INT Y_2;
  INT X_3; INT Y_3; INT X_4; INT Y_4;
  INT X_5; INT Y_5; INT X_6; INT Y_6;
  INT X_7; INT Y_7; INT X_8; INT Y_8;
}
VIOFONTMETRICS;

// Шрифты в текстовых окнах.
typedef struct _VIOFONTMANAGER
{
  // Настройки.
  typedef struct _INRSTS
  {
    // Изменять размер шрифта в текстовых окнах? 0 - нет, 1 - да.
    BYTE Change_VIO_font_metrics; 
    BYTE Change_fonts_for_known_applications;

    // Шрифты в текстовых окнах.
    VIOFONTMETRICS VIOFontMetrics;
  }
  INRSTS; INRSTS Settings;

  // Внутренние переменные.
  typedef struct _RTSTS 
  {
    // Строка для обмена со списками и полями ввода.
    // Эта строка должна быть расположена в постоянной памяти (Heap Memory) расширителя,
    // чтобы приложение и потоки расширителя могли обратиться к ней и читать/изменять ее.
    CHAR Item_text[SIZE_OF_ITEM_TEXT];
  }
  RTSTS; RTSTS RTSettings;
}
VIOFONTMANAGER; 

VIOFONTMANAGER VIOFontManager;