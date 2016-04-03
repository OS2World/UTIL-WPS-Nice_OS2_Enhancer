
// ─── Соединяется с другим приложением ───

// Pipe_name - имя PIPE-соединения, Query_string - команда, Reply_string - ответ, Reply_length - длина строки для ответа.
VOID Pipes_TransactNamedPipe( PCHAR Pipe_name, PCHAR Query_string, PCHAR Reply_string = NULL, INT Reply_length = 0 )
{
 // Проверяем доступность PIPE-соединения.
 APIRET Result = DosWaitNPipe( Pipe_name, 1 );

 // Если PIPE-соединение недоступно - возврат.
 if( Result != NO_ERROR ) return;

 // Открываем PIPE-соединение.
 HFILE Pipe = NULLHANDLE; ULONG Report = 0; ULONG New_size = 0; PEAOP2 EAs = NULL;

 ULONG Action = OPEN_ACTION_OPEN_IF_EXISTS;
 ULONG Mode = OPEN_FLAGS_FAIL_ON_ERROR | OPEN_SHARE_DENYNONE;
 if( Reply_string != NULL ) Mode |= OPEN_ACCESS_READWRITE;
 else Mode |= OPEN_ACCESS_WRITEONLY;

 Result = DosOpen( Pipe_name, &Pipe, &Report, New_size, FILE_PIPE_ATTRIBUTES, Action, Mode, EAs );

 // Если PIPE-соединение недоступно - возврат.
 if( Pipe == NULLHANDLE ) return;

 // Посылаем строку.
 Result = DosWrite( Pipe, Query_string, strlen( Query_string ), &Report );

 // Принимаем ответ, если это требуется.
 if( Reply_string != NULL ) Result = DosRead( Pipe, Reply_string, Reply_length, &Report );

 // Закрываем PIPE-соединение.
 DosClose( Pipe ); Pipe = NULLHANDLE;

 // Возврат.
 return;
}
