// ��⮪� �ਫ������.
typedef struct _THREADS
 {
  // ����� ����⥫�.
  TID Launcher;
  HMQ Launcher_queue;
  HAB Launcher_anchor;
 }
THREADS; THREADS Threads;

// ����� ����⥫�.
VOID LauncherThread( VOID );

// ������ �⥪� ��� ��⮪��.
#define STACK_SIZE 32768
