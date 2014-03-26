
// ─── Возвращает время последнего нажатия на среднюю кнопку мыши ───

ULONG MouseMapper_WMMBDownTime( VOID )
{
 // Возвращаем время.
 return MouseMapper.RTSettings.WM_MB_Down_time;
}

// ─── Сбрасывает время последнего нажатия на среднюю кнопку мыши ───

VOID MouseMapper_DiscardWMMBDownTime( VOID )
{
 // Сбрасываем значение.
 MouseMapper.RTSettings.WM_MB_Down_time = 0;

 // Возврат.
 return;
}
