
// ─── Добавляет в список окна, скорость в которых известна заранее ───

VOID Scroller_CompleteScrList (VOID)
{
  // Добавляем в список окна и скорость передвижения изображения в них.
  // Если этого не делать, то в окно будут отправляться сообщения "WM_xSCROLL", а
  // скорость будет установлена в соответствии с константами "SCROLLER_DEF_SPEED_*".
  Scroller_AddPreDefinedWindowToList ("#1",                   1,  1, SCROLLING_COMMON                );    /* WC_FRAME      */
  Scroller_AddPreDefinedWindowToList ("#5",                   1,  1, SCROLLING_COMMON                );    /* WC_STATIC     */
  Scroller_AddPreDefinedWindowToList ("#7",                  12, 14, SCROLLING_DISCRETE_SBCTL_KBD    );    /* WC_LISTBOX    */
  Scroller_AddPreDefinedWindowToList ("#8",                   0,  0, SCROLLING_COMMON                );    /* WC_SCROLLBAR  */
  Scroller_AddPreDefinedWindowToList ("#10",                  0, 24, SCROLLING_DISCRETE_SBCTL_KBD    );    /* WC_MLE        */
  Scroller_AddPreDefinedWindowToList ("#37",                  1,  1, SCROLLING_COMMON                );    /* WC_CONTAINER  */
  Scroller_AddPreDefinedWindowToList ("#39",                  1,  1, SCROLLING_COMMON                );    /* WC_VALUESET   */
  Scroller_AddPreDefinedWindowToList ("Palette",              1,  1, SCROLLING_COMMON                );    /* WC_VALUESET   */

  Scroller_AddPreDefinedWindowToList ("CLASS_PAGE",           1,  1, SCROLLING_COMMON                );    /* "IBMView.exe" */
  Scroller_AddPreDefinedWindowToList ("CLASS_TOC",           12, 16, SCROLLING_DISCRETE_SBCTL_KBD    );    /* "IBMView.exe" */
  Scroller_AddPreDefinedWindowToList ("NewEditWndClass",     16, 16, SCROLLING_DISCRETE_SBCTL_KBD    );    /* "EPM.exe"     */
  Scroller_AddPreDefinedWindowToList ("Sibyl TOutline",      12, 14, SCROLLING_DISCRETE_SBCTL_MB     );    /* "NewView.exe" */
  Scroller_AddPreDefinedWindowToList ("Sibyl TOutline2",     12, 14, SCROLLING_DISCRETE_SBCTL_MB     );    /* "NewView.exe" */
  Scroller_AddPreDefinedWindowToList ("Sibyl TRichTextView", 10, 14, SCROLLING_DISCRETE_SBCTL_MB     );    /* "NewView.exe" */
  Scroller_AddPreDefinedWindowToList ("MozillaWindowClass",  18, 18, SCROLLING_DISCRETE_SCROLLMSG    );    /* "FireFox.exe" */

  Scroller_AddPreDefinedWindowToList ("QWindow",             24, 24, SCROLLING_DISCRETE_SCROLLMSG_IFW);    /* Qt            */
  Scroller_AddPreDefinedWindowToList ("Win32WindowClass",    12, 16, SCROLLING_DISCRETE_SCROLLMSG    );    /* ODIN          */

  // Возврат.
  return;
}
