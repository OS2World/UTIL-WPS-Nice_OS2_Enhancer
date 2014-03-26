// Работа с меню.
typedef struct _MENUITEMS
 {
  // Внутренние переменные.
  typedef struct _RTSTS
   {
    // Данные для обмена с меню.
    // Эти данные должны быть расположены в постоянной памяти (Heap Memory) расширителя,
    // чтобы приложение и потоки расширителя могли обратиться к ним и читать/изменять их.
    MENUITEM Menu_item;
   }
  RTSTS; RTSTS RTSettings;
 }
MENUITEMS;

MENUITEMS MenuItems;