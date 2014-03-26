// Потоки приложения.
typedef struct _THREADS
 {
  // Запуск расширителя.
  TID Launcher;
  HMQ Launcher_queue;
  HAB Launcher_anchor;
 }
THREADS; THREADS Threads;

// Запуск расширителя.
VOID LauncherThread( VOID );

// Размер стека для потоков.
#define STACK_SIZE 32768
