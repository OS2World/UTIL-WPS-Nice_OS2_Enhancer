
// ─── Добавляет в список окна, скорость в которых известна заранее ───

VOID Scroller_CompleteScrList( VOID )
{
 // Добавляем в список окна и скорость передвижения изображения в них.
 // Если этого не делать, то в окно будут отправляться сообщения "WM_xSCROLL", а
 // скорость будет установлена в соответствии с константами "SCROLLER_DEF_SPEED_*".
 Scroller_AddPreDefinedWindowToList( "#1",                   1,  1, SCROLLING_COMMON                 );
 Scroller_AddPreDefinedWindowToList( "#5",                   1,  1, SCROLLING_COMMON                 );
 Scroller_AddPreDefinedWindowToList( "#7",                   1,  1, SCROLLING_COMMON                 );
 Scroller_AddPreDefinedWindowToList( "#8",                   1,  1, SCROLLING_COMMON                 );
 Scroller_AddPreDefinedWindowToList( "#10",                  1,  1, SCROLLING_COMMON                 );
 Scroller_AddPreDefinedWindowToList( "#37",                  1,  1, SCROLLING_COMMON                 );
 Scroller_AddPreDefinedWindowToList( "Palette",              1,  1, SCROLLING_COMMON                 );
 Scroller_AddPreDefinedWindowToList( "CLASS_PAGE",           1,  1, SCROLLING_COMMON                 );
 Scroller_AddPreDefinedWindowToList( "CLASS_TOC",           12, 16, SCROLLING_DISCRETE_SBCTL_KBD     );
 Scroller_AddPreDefinedWindowToList( "NewEditWndClass",     16, 16, SCROLLING_DISCRETE_SBCTL_KBD     );
 Scroller_AddPreDefinedWindowToList( "Sibyl TOutline",      12, 14, SCROLLING_DISCRETE_SBCTL_MB      );
 Scroller_AddPreDefinedWindowToList( "Sibyl TOutline2",     12, 14, SCROLLING_DISCRETE_SBCTL_MB      );
 Scroller_AddPreDefinedWindowToList( "Sibyl TRichTextView", 10, 14, SCROLLING_DISCRETE_SBCTL_MB      );
 Scroller_AddPreDefinedWindowToList( "MozillaWindowClass",  18, 18, SCROLLING_DISCRETE_SCROLLMSG     );
 Scroller_AddPreDefinedWindowToList( "Win32WindowClass",    12, 16, SCROLLING_DISCRETE_SCROLLMSG     );
 Scroller_AddPreDefinedWindowToList( "QWindow",             24, 24, SCROLLING_DISCRETE_SCROLLMSG_IFW );

 // Возврат.
 return;
}
