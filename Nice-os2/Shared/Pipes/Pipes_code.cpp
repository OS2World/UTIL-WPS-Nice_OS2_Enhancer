
// ��� ���������� � ��㣨� �ਫ������� ���

// Pipe_name - ��� PIPE-ᮥ�������, Query_string - �������, Reply_string - �⢥�, Reply_length - ����� ��ப� ��� �⢥�.
VOID Pipes_TransactNamedPipe( PCHAR Pipe_name, PCHAR Query_string, PCHAR Reply_string = NULL, INT Reply_length = 0 )
{
 // �஢��塞 ����㯭���� PIPE-ᮥ�������.
 APIRET Result = DosWaitNPipe( Pipe_name, 1 );

 // �᫨ PIPE-ᮥ������� ������㯭� - ������.
 if( Result != NO_ERROR ) return;

 // ���뢠�� PIPE-ᮥ�������.
 HFILE Pipe = NULLHANDLE; ULONG Report = 0; ULONG New_size = 0; PEAOP2 EAs = NULL;

 ULONG Action = OPEN_ACTION_OPEN_IF_EXISTS;
 ULONG Mode = OPEN_FLAGS_FAIL_ON_ERROR | OPEN_SHARE_DENYNONE;
 if( Reply_string != NULL ) Mode |= OPEN_ACCESS_READWRITE;
 else Mode |= OPEN_ACCESS_WRITEONLY;

 Result = DosOpen( Pipe_name, &Pipe, &Report, New_size, FILE_PIPE_ATTRIBUTES, Action, Mode, EAs );

 // �᫨ PIPE-ᮥ������� ������㯭� - ������.
 if( Pipe == NULLHANDLE ) return;

 // ���뫠�� ��ப�.
 Result = DosWrite( Pipe, Query_string, strlen( Query_string ), &Report );

 // �ਭ����� �⢥�, �᫨ �� �ॡ����.
 if( Reply_string != NULL ) Result = DosRead( Pipe, Reply_string, Reply_length, &Report );

 // ����뢠�� PIPE-ᮥ�������.
 DosClose( Pipe ); Pipe = NULLHANDLE;

 // ������.
 return;
}
