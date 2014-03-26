
// ��� ��ࠡ��稪 ᮡ�⨩, ��뢠���� �� ��।�� ����� ᮮ�饭�� �� ���譨� ���ன�� ���

// �ਫ������ ��뢠�� InputHook �� �롮� ᮮ�饭�� �� ��।� � ������� WinGetMsg(),
// � ����⥫� ����砥� ����� � �� ����� � ����� ������ �������� Message. ��������,
// ����⥫� �㤥� �맢�� �����६���� ࠧ�묨 �ਫ�����ﬨ ��� �� ��।�� ᮮ�饭��.

// Application ��।���� �ਫ������, Message - ᮮ�饭��, ���஥ ��।����� ����.
// �����頥��� ���祭�� - �ᥣ�� HK_RESERVED_RETURN_VALUE, � ���� �ᥣ�� 0.
ULONG EXPENTRY Hook_InputHook( HAB Application, PQMSG Message, ULONG Removing )
{
 // �᫨ ᫥����� �� ᮮ�饭�ﬨ �� �� ����祭� - ������.
 if( !Enhancer.Hooks_are_enabled ) return HK_RESERVED_RETURN_VALUE;

 // �᫨ ���� �� 㪠���� � ᮮ�饭�� �� WM_MARK - ��� ��।����� � ��।�, ������.
 if( Message->hwnd == NULLHANDLE ) if( Message->msg != WM_MARK ) return HK_RESERVED_RETURN_VALUE;

 // ����뢠��, �� ᮮ�饭�� ������ ���� ��襭�.
 BYTE Discarding = 0;

 // ��।������� ����ࠦ����.
 ScrollerInputHook( Application, Message, &Discarding );

 // ����� ��� ����.
 PainterInputHook( Application, Message, &Discarding );

 // ����⢨� � ������.
 PerformerInputHook( Application, Message, &Discarding );

 // ��㣨� ����⢨�.
 LauncherInputHook( Application, Message, &Discarding );

 // �������.
 RoomsInputHook( Application, Message, &Discarding );

 // ����� � ⥪�⮢�� �����.
 VIOFontManagerInputHook( Application, Message, &Discarding );

 // ���� � ⥪�⮢�� �����.
 VIOMenuManagerInputHook( Application, Message, &Discarding );

 // �뤥����� ��ப � ⥪�⮢�� ����� � ������� ���.
 ClipperInputHook( Application, Message, &Discarding );

 // ����⢨� � �����.
 MouseMapperInputHook( Application, Message, &Discarding );

 // ����⠢�塞 ���ﭨ� ���������� �� �஢�� V-Keys.
 KbdStateInputHook( Message );

 // ��⠭�������� �ਮ��� �ਫ������.
 PriorityInputHook( Message );

 // �ਡ����� �ਫ������.
 TerminateProcessHook( Message );

 // ��ࠢ������� ����.
 ArrangerInputHook( Application, Message, &Discarding );

 // ����⢨� � ������ ��������.
 ApplierInputHook( Application, Message, &Discarding );

 // ��ࠢ����� �ਮ��⠬� �ਫ������.
 PriorityManagerInputHook( Application, Message, &Discarding );

 // �����⪨ ��� �����窨 OS/2.
 PatcherInputHook( Application, Message, &Discarding );

 // ����뢠�� ᮮ�饭��, �᫨ �� �ॡ����.
 if( Message->msg == WM_MARK || Discarding ) bzero( Message, sizeof( QMSG ) );

 // ������.
 return HK_RESERVED_RETURN_VALUE;
}

// ��� ��ࠡ��稪 ᮡ�⨩, ��뢠���� �� ��।�� ᮮ�饭�� �� ���������� ���

// OS/2 ��뢠�� KbdInputHook ��直� ࠧ �� ��।�� ᮮ�饭�� �� ����������.
// �맮� �ந�������� �� ⮣�, ��� ᮮ�饭�� WM_CHAR �ॢ�頥��� � WM_COMMAND.

// Application ��।���� �ਫ������, Message - ᮮ�饭��, ���஥ ��।����� ����.
// �����頥��� ���祭�� - �ᥣ�� HK_RESERVED_RETURN_VALUE, � ���� �ᥣ�� 0.
ULONG EXPENTRY Hook_KbdInputHook( HAB Application, PQMSG Message, ULONG Removing )
{
 // �᫨ ᫥����� �� ᮮ�饭�ﬨ �� �� ����祭� - ������.
 if( !Enhancer.Hooks_are_enabled ) return HK_RESERVED_RETURN_VALUE;

 // �᫨ ���� �� WM_CHAR - ������.
 if( Message->msg != WM_CHAR ) return HK_RESERVED_RETURN_VALUE;

 // ����뢠��, �� ᮮ�饭�� ������ ���� ��襭�.
 BYTE Discarding = 0;

 // ��७�� 䮪�� ����� �� �ப��⪥ � ������� ���.
 MouseMapperKbdInputHook( Application, Message, &Discarding );

 // ��।������� ����ࠦ����.
 ScrollerKbdInputHook( Application, Message, &Discarding );

 // ����⢨� � ������.
 PerformerKbdInputHook( Application, Message, &Discarding );

 // �������.
 RoomsKbdInputHook( Application, Message, &Discarding );

 // ���� � ⥪�⮢�� �����.
 VIOMenuManagerKbdInputHook( Application, Message, &Discarding );

 // ������ ������.
 MapperKbdInputHook( Application, Message, &Discarding );

 // �믮������ ����⢨� �� ����⨨ �� ������.
 DefinerKbdInputHook( Application, Message, &Discarding );

 // ������ ���뢠��� � ��४���⥫�.
 ControllerKbdInputHook( Application, Message, &Discarding );

 // ��� �� ����⨨ �� �������.
 ClickerKbdInputHook( Application, Message, &Discarding );

 // ���������� ���祭�� � ���� ����� ��஫�.
 ApplierKbdInputHook( Application, Message, &Discarding );

 // �뤥����� ��ப � ⥪�⮢�� ����� � ������� ����������.
 ClipperKbdInputHook( Application, Message, &Discarding );

 // ����뢠�� ᮮ�饭��, �᫨ �� �ॡ����.
 if( Discarding ) bzero( Message, sizeof( QMSG ) );

 // ������.
 return HK_RESERVED_RETURN_VALUE;
}

// ��� ��ࠡ��稪 ᮡ�⨩, ��뢠���� �� ��।�� ����� ᮮ�饭�� �� ��㣨� ���� ���

// OS/2 ��뢠�� SendMsgHook ��直� ࠧ �� ��।�� ����� ᮮ�饭�� �� ��㣨� ����
// � ������� WinSendMsg(), � ������ ����� � ������� Message ����⥫� �� �����.

// Application ��।���� �ਫ������, Message - ᮮ�饭��, ���஥ ��।����� ����.
VOID EXPENTRY Hook_SendMsgHook( HAB Application, PSMHSTRUCT Message, ULONG InterTask )
{
 // �᫨ ᫥����� �� ᮮ�饭�ﬨ �� �� ����祭� - ������.
 if( !Enhancer.Hooks_are_enabled ) return;

 // �஢�ઠ ᢮��⢠ ����.
 WinPrpListAndRepositorySendMsgHook( Message );

 // ��।������� ����ࠦ����.
 ScrollerSendMsgHook( Application, Message );

 // ����� ��� ����.
 PainterSendMsgHook( Application, Message );

 // �������.
 RoomsSendMsgHook( Application, Message );

 // ����� � ⥪�⮢�� �����.
 VIOFontManagerSendMsgHook( Application, Message );

 // ��ࠢ������� ����.
 ArrangerSendMsgHook( Application, Message );

 // ����⢨� � ������ ��������.
 ApplierSendMsgHook( Application, Message );

 // ��ࠢ����� �ਮ��⠬� �ਫ������.
 PriorityManagerSendMsgHook( Application, Message );

 // �����⨥ ��ப � ᯨ᪥ ����.
 RemoverSendMsgHook( Application, Message );

 // ����� � ⥪�⮢�� �����.
 RemoverSendMsgHook( Application, Message );

 // ��४���⥫� �� ���������.
 ControllerSendMsgHook( Application, Message );

 // ���⠢�� �� ����⨨ ����.
 PatcherSendMsgHook( Application, Message );

 // �������� �� ���ﭨ�� �����窨 OS/2.
 LockupSendMsgHook( Message );

 // ������.
 return;
}
