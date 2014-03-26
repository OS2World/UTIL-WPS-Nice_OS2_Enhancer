
// ─── Создает поток ───

VOID Controller_StartThread( VOID )
{
 // Сбрасываем переменную для ответа от потока.
 Thread_responds.Thread_is_created = 0;

 // Если поток уже создан - выход.
 CHAR Semaphore_name[] = "\\SEM32\\NICE-OS2!Krnl!Controller"; HMTX hmtxAlreadyRunning = NULLHANDLE;
 if( DosOpenMutexSem( Semaphore_name, &hmtxAlreadyRunning ) == NO_ERROR ) return;
 else DosCreateMutexSem( Semaphore_name, &hmtxAlreadyRunning, DC_SEM_SHARED, 1 );

 // Создаем поток.
 APIRET Thread_is_created = DosCreateThread( &Enhancer.Modules.Controller->Thread, (PFNTHREAD) Controller_ControllerThread, 0, 0, THREAD_STACK_SIZE );
 // Если он создан - ждем, пока в нем будет создана очередь сообщений.
 if( Thread_is_created == NO_ERROR ) while( Thread_responds.Thread_is_created == 0 ) { Retard(); }
 // Если поток создать не удалось - возврат.
 if( Thread_is_created != NO_ERROR || Thread_responds.Thread_is_created == -1 ) { Enhancer.Modules.Controller->Thread = 0; return; }
 // Устанавливаем приоритет потока.
 WinPostQueueMsg( Enhancer.Modules.Controller->Message_queue, SM_PRIORITY, (MPARAM) PRTYC_REGULAR, (MPARAM) PRTYD_QUICK );

 // Возврат.
 return;
}

// ─── Посылает в поток сообщение WM_QUIT ───

VOID Controller_PostQuitMsg( VOID )
{
 // Посылаем сообщение в поток.
 WinPostQueueMsg( Enhancer.Modules.Controller->Message_queue, WM_QUIT, 0, 0 );

 // Возврат.
 return;
}
