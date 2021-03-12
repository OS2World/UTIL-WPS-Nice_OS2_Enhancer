
// ─── Проверяет, можно ли переключиться в окно при переопределении клавиш ───

// Window - окно. Возвращаемое значение: 1, если можно, 0, если нельзя.
BYTE Launcher_PermissionForHotKeySwitching (HWND Window)
{
  // Если в окно вообще нельзя переключаться - возврат.
  if (!PermissionForSwitching (Window)) return 0;

  // Если это не окно диалога и в него нельзя переключиться по Alt + Tab - возврат.
  if (!WindowIsAppDialog (Window)) if (!WindowIsJumpable (Window)) return 0;

  // Если это не окно Win-OS/2 или Odin:
  if (!IsWindowsWindow (Window))
  {
    // Если окно заголовка не показано - переключаться не надо, возврат.
    if (!WindowIsPresent (WinWindowFromID (Window, FID_TITLEBAR))) return 0;
  }

  // Если окно убрано наверх - переключаться не надо, возврат.
  if (WindowIsRolled (Window)) return 0;

  // Возврат.
  return 1;
}
