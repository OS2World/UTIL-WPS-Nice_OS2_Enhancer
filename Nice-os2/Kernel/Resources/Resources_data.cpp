// ���窨 ��� ����.
#define RC_DEFAULT_ICON    6

#define ICON_LEAVES        0
#define ICON_LEAF          1
#define ICON_WINLIST       2
#define ICON_VIEWDOC       3
#define ICON_SERVER        4
#define ICON_NFTPPM        5

#define RC_ICONS_QUANTITY  12

// �����⥫� ���.
#define PTR_CLIPBOARD      5

// ����㦥��� ����ࠦ����.
typedef struct _RESOURCES
 {
  // �����⥫� ���, �ᯮ��㥬� ��� ��।������� ����ࠦ����.
  HPOINTER Pointer_for_dragging;

  // ���窨 �� 㬮�砭�� ��� ����.
  HPOINTER Default_icons[ RC_ICONS_QUANTITY ];

  // �����⥫� ���, �ᯮ��㥬� �� ��⠢�� ⥪��.
  HPOINTER Pointer_for_CopyPaste;
 }
RESOURCES;

RESOURCES Resources;