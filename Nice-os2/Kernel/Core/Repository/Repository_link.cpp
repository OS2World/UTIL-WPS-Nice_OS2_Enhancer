
// ─── Возвращает указатель на список имен значков ───

POBJECTS Krnl_Repository_GetKnownObjects (VOID)
{
  // Возвращаем указатель.
  return &Krnl_Repository.Settings.Objects;
}

// ─── Возвращает указатель на список PIPE-соединений ───

PPIPES Krnl_Repository_GetKnownPipes (VOID)
{
  // Возвращаем указатель.
  return &Krnl_Repository.Settings.Pipes;
}
