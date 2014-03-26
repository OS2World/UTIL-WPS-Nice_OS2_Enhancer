// Значения для задания размеров окон.
#define LTM_X                0
#define LTM_Y                0
#define LTM_CX               0
#define LTM_CY               0

#define LTM_FULL_WIDTH       1.00
#define LTM_FULL_HEIGHT      1.00
#define LTM_VSPLIT_WIDTH     0.50
#define LTM_HSPLIT_HEIGHT    0.50

#define LTM_COMMON_WIDTH     ( LTM_FULL_WIDTH )
#define LTM_COMMON_HEIGHT    ( (ULONG) ( WinQuerySysValue( HWND_DESKTOP, SV_CYMENU ) >= 22 ) ? \
                                       ( WinQuerySysValue( HWND_DESKTOP, SV_CYMENU ) ) : 22 )
#define LTM_BUTTON_WIDTH     ( LTM_FULL_WIDTH  )
#define LTM_BUTTON_HEIGHT    ( (ULONG) ( LTM_COMMON_HEIGHT * 1.33333 ) )
#define LTM_COMBOBOX_WIDTH   ( LTM_FULL_WIDTH  )
#define LTM_COMBOBOX_HEIGHT  ( LTM_COMMON_HEIGHT )
#define LTM_COMBOBOX_LIST    ( (ULONG) ( LTM_COMMON_HEIGHT * 5 ) )

#define LTM_TOP_FRAME_WIDTH  0.75
#define LTM_TOP_FRAME_HEIGHT 0.75
#define LTM_TOP_FRAME_MARGIN 0.01

// Прямоугольник или поле ввода.
typedef struct _LTBRICK
 {
  // Размер структуры.
  ULONG cb;
  // Окно, создаваемое заранее.
  HWND hwnd;

  // Размер окна в точках или в %% от размера родительского окна.
  // Задается с учетом того, что Layout не рекурсивен, и размеры
  // окон внутри этого окна учитываться не будут - для расчета 
  // используется только размер родительского окна.
  FLOAT prpWidthInParent;
  FLOAT prpHeightInParent;

  // Отступ от краев, если внутри есть еще другие окна.
  FLOAT prpMargin;
  // Расстояние между полями ввода, если они есть внутри окна.
  FLOAT prpGap;

  // Настоящая высота окна, если оно частично перекрывается другими окнами и
  // должна быть видна только его верхняя часть (таковы окна "WC_COMBOBOX").
  // Это значение задается только в точках (требование Presentation Manager).
  ULONG ulBoxHeight;
 }
LTBRICK; typedef LTBRICK* PLTBRICK;

// Список прямоугольников или полей ввода.
// Такое значение возвращается после создания списка.
typedef struct _LTWALL
 {
  // Окно, для которого создается список.
  HWND hwnd;

  // Указатель на список прямоугольников и полей ввода.
  LTBRICK* pList;

  // Длина списка и число полей ввода в нем.
  ULONG ulLength; ULONG ulQuantity;
 }
LTWALL; typedef LTWALL* PLTWALL;
