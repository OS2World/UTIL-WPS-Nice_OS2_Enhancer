// ��⮤� ��� ࠡ��� � PIPE-ᮥ������ﬨ.
#define TransactNamedPipe         Pipes_TransactNamedPipe

// ��� ��⮤ ��� ������祭�� ����� ���

VOID Pipes_Start( VOID )
{
 #ifdef Pipes
 bzero( &Pipes, sizeof( Pipes ) );
 #endif

 // ������.
 return;
}
