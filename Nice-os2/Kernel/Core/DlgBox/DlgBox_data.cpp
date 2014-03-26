
// Работа с окнами диалогов.
typedef struct _KRNL_DLGBOX
 {
  // Внутренние переменные.
  typedef struct _RTSTS
   {
    // Строка для обмена со списками и полями ввода.
    // Эта строка должна быть расположена в постоянной памяти (Heap Memory) расширителя,
    // чтобы приложение и потоки расширителя могли обратиться к ней и читать/изменять ее.
    CHAR Item_text[ SIZE_OF_ITEM_TEXT ];

    // Значение для обмена со списками.
    LONG Item_index;
   }
  RTSTS; RTSTS RTSettings;
 }
KRNL_DLGBOX;

KRNL_DLGBOX Krnl_DlgBox;