// ���� ����஥�.
typedef struct _RMSALLOCSPAGE
{
  // ����ன��.
  typedef struct _INRSTS
  {
    // ���� ����� � ����.
    ULONG AppList_Container_ID;
    ULONG SelectBox_ID;
    ULONG Selected_room_cmbox_ID;
    ULONG Application_list_ID;
    ULONG AddRemove_ID;
    ULONG Application_Add_ID;
    ULONG Application_Remove_ID;

    ULONG KnownApps_button_ID;
    ULONG Allocate_button_ID;

    // ��࠭��� ������.
    ULONG Selected_room;
    ULONG Allocation_list_is_locked;
    PINT Preferable_room_variable;
  }
  INRSTS; INRSTS Settings;
}
RMSALLOCSPAGE;

RMSALLOCSPAGE Rooms_Allocations;
