
// ��� ����⠭�������� ���ﭨ� ���������� ���

// Message - ᮮ�饭��, ���஥ ��।����� ����.
VOID KbdStateInputHook( PQMSG Message )
{
 // ����⠭�������� ���ﭨ� ����������.
 // �� ᮮ�饭�� ���뫠���� � ��।� ���� �� ������ ᮮ�饭�� �� ����������.
 if( KbdState.Keyboard_state_is_changed )
  if( Message->hwnd == NULLHANDLE ) if( Message->msg == WM_MARK )
   if( Message->mp1 == (MPARAM) MRK_KBD_MODIFIERS )
    KbdState_RestorePMKeyboardState();

 // ������.
 return;
}