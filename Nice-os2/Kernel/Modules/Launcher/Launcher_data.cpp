// �믮������ ࠧ����� ����⢨�
typedef struct _LAUNCHER
 {
  // ����७��� ��६����.
  typedef struct _RTSTS 
   {
    // ����⠥� �� �ந��뢠⥫�.
    BYTE Player_is_stopped;
    // ���祭�� �஬���� ��� �ந��뢠⥫�.
    INT Player_volume;
    // ���祭�� �஬���� � MMOS2.
    SHORT MMOS2_volume; SHORT MMOS2_volume_from; SHORT MMOS2_volume_to;
   }
  RTSTS; RTSTS RTSettings;
 }
LAUNCHER;

LAUNCHER Launcher;