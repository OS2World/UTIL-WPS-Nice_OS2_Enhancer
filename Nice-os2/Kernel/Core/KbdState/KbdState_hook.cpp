
// ─── Восстанавливает состояние клавиатуры ───

// Message - сообщение, которое передается окну.
VOID KbdStateInputHook( PQMSG Message )
{
 // Восстанавливаем состояние клавиатуры.
 // Это сообщение посылается в очередь окна при замене сообщений от клавиатуры.
 if( KbdState.Keyboard_state_is_changed )
  if( Message->hwnd == NULLHANDLE ) if( Message->msg == WM_MARK )
   if( Message->mp1 == (MPARAM) MRK_KBD_MODIFIERS )
    KbdState_RestorePMKeyboardState();

 // Возврат.
 return;
}