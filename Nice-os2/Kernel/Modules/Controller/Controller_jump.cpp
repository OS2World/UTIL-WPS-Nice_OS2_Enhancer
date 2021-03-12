
// ─── Выполняет действия после чтения настроек и создания потока ───

VOID Controller_Jump (VOID)
{
  // Устанавливаем переключатели на клавиатуре.
  if (Controller.Settings.Turn_Num_Lock) 
  { 
    Controller_SetNumLock (); 
    Controller_SetVIONumLock (); 
  }

  // Возврат.
  return;
}