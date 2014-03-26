// Значки для окон.
#define RC_DEFAULT_ICON    6

#define ICON_LEAVES        0
#define ICON_LEAF          1
#define ICON_WINLIST       2
#define ICON_VIEWDOC       3
#define ICON_SERVER        4
#define ICON_NFTPPM        5

#define RC_ICONS_QUANTITY  12

// Указатели мыши.
#define PTR_CLIPBOARD      5

// Загруженные изображения.
typedef struct _RESOURCES
 {
  // Указатель мыши, используемый для передвижения изображения.
  HPOINTER Pointer_for_dragging;

  // Значки по умолчанию для окон.
  HPOINTER Default_icons[ RC_ICONS_QUANTITY ];

  // Указатель мыши, используемый при вставке текста.
  HPOINTER Pointer_for_CopyPaste;
 }
RESOURCES;

RESOURCES Resources;