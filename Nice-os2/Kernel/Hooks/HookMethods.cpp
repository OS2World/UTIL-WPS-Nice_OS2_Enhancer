
// ─── Обработчик событий, вызывается при передаче окнам сообщений от внешних устройств ───

// Приложения вызывают InputHook при выборе сообщений из очереди с помощью WinGetMsg(),
// и расширитель получает доступ к их данным и может менять структуру Message. Возможно,
// расширитель будет вызван одновременно разными приложениями для их очередей сообщений.

// Application определяет приложение, Message - сообщение, которое передается окну.
// Возвращаемое значение - всегда HK_RESERVED_RETURN_VALUE, то есть всегда 0.
ULONG EXPENTRY Hook_InputHook( HAB Application, PQMSG Message, ULONG Removing )
{
 // Если слежение за сообщениями еще не включено - возврат.
 if( !Enhancer.Hooks_are_enabled ) return HK_RESERVED_RETURN_VALUE;

 // Если окно не указано и сообщение не WM_MARK - оно передается в очередь, возврат.
 if( Message->hwnd == NULLHANDLE ) if( Message->msg != WM_MARK ) return HK_RESERVED_RETURN_VALUE;

 // Указывает, что сообщение должно быть сброшено.
 BYTE Discarding = 0;

 // Передвижение изображения.
 ScrollerInputHook( Application, Message, &Discarding );

 // Рамки для окон.
 PainterInputHook( Application, Message, &Discarding );

 // Действия с окнами.
 PerformerInputHook( Application, Message, &Discarding );

 // Другие действия.
 LauncherInputHook( Application, Message, &Discarding );

 // Комнаты.
 RoomsInputHook( Application, Message, &Discarding );

 // Шрифты в текстовых окнах.
 VIOFontManagerInputHook( Application, Message, &Discarding );

 // Меню в текстовых окнах.
 VIOMenuManagerInputHook( Application, Message, &Discarding );

 // Выделение строк в текстовых окнах с помощью мыши.
 ClipperInputHook( Application, Message, &Discarding );

 // Действия с мышью.
 MouseMapperInputHook( Application, Message, &Discarding );

 // Подставляем состояние клавиатуры на уровне V-Keys.
 KbdStateInputHook( Message );

 // Устанавливаем приоритет приложения.
 PriorityInputHook( Message );

 // Прибиваем приложение.
 TerminateProcessHook( Message );

 // Выравнивание окон.
 ArrangerInputHook( Application, Message, &Discarding );

 // Действия с окнами диалогов.
 ApplierInputHook( Application, Message, &Discarding );

 // Управление приоритетами приложений.
 PriorityManagerInputHook( Application, Message, &Discarding );

 // Заплатки для оболочки OS/2.
 PatcherInputHook( Application, Message, &Discarding );

 // Сбрасываем сообщение, если это требуется.
 if( Message->msg == WM_MARK || Discarding ) bzero( Message, sizeof( QMSG ) );

 // Возврат.
 return HK_RESERVED_RETURN_VALUE;
}

// ─── Обработчик событий, вызывается при передаче сообщений от клавиатуры ───

// OS/2 вызывает KbdInputHook всякий раз при передаче сообщений от клавиатуры.
// Вызов производится до того, как сообщение WM_CHAR превращается в WM_COMMAND.

// Application определяет приложение, Message - сообщение, которое передается окну.
// Возвращаемое значение - всегда HK_RESERVED_RETURN_VALUE, то есть всегда 0.
ULONG EXPENTRY Hook_KbdInputHook( HAB Application, PQMSG Message, ULONG Removing )
{
 // Если слежение за сообщениями еще не включено - возврат.
 if( !Enhancer.Hooks_are_enabled ) return HK_RESERVED_RETURN_VALUE;

 // Если идет не WM_CHAR - возврат.
 if( Message->msg != WM_CHAR ) return HK_RESERVED_RETURN_VALUE;

 // Указывает, что сообщение должно быть сброшено.
 BYTE Discarding = 0;

 // Перенос фокуса ввода при прокрутке с помощью мыши.
 MouseMapperKbdInputHook( Application, Message, &Discarding );

 // Передвижение изображения.
 ScrollerKbdInputHook( Application, Message, &Discarding );

 // Действия с окнами.
 PerformerKbdInputHook( Application, Message, &Discarding );

 // Комнаты.
 RoomsKbdInputHook( Application, Message, &Discarding );

 // Меню в текстовых окнах.
 VIOMenuManagerKbdInputHook( Application, Message, &Discarding );

 // Замена клавиш.
 MapperKbdInputHook( Application, Message, &Discarding );

 // Выполнение действий при нажатии на клавиши.
 DefinerKbdInputHook( Application, Message, &Discarding );

 // Клавиши прерываний и переключатели.
 ControllerKbdInputHook( Application, Message, &Discarding );

 // Звук при нажатии на клавишу.
 ClickerKbdInputHook( Application, Message, &Discarding );

 // Запоминаем значения в окне ввода пароля.
 ApplierKbdInputHook( Application, Message, &Discarding );

 // Выделение строк в текстовых окнах с помощью клавиатуры.
 ClipperKbdInputHook( Application, Message, &Discarding );

 // Сбрасываем сообщение, если это требуется.
 if( Discarding ) bzero( Message, sizeof( QMSG ) );

 // Возврат.
 return HK_RESERVED_RETURN_VALUE;
}

// ─── Обработчик событий, вызывается при передаче окнам сообщений от других окон ───

// OS/2 вызывает SendMsgHook всякий раз при передаче окнам сообщений от других окон
// с помощью WinSendMsg(), и менять данные в структуре Message расширитель не может.

// Application определяет приложение, Message - сообщение, которое передается окну.
VOID EXPENTRY Hook_SendMsgHook( HAB Application, PSMHSTRUCT Message, ULONG InterTask )
{
 // Если слежение за сообщениями еще не включено - возврат.
 if( !Enhancer.Hooks_are_enabled ) return;

 // Проверка свойства окон.
 WinPrpListAndRepositorySendMsgHook( Message );

 // Передвижение изображения.
 ScrollerSendMsgHook( Application, Message );

 // Рамки для окон.
 PainterSendMsgHook( Application, Message );

 // Комнаты.
 RoomsSendMsgHook( Application, Message );

 // Шрифты в текстовых окнах.
 VIOFontManagerSendMsgHook( Application, Message );

 // Выравнивание окон.
 ArrangerSendMsgHook( Application, Message );

 // Действия с окнами диалогов.
 ApplierSendMsgHook( Application, Message );

 // Управление приоритетами приложений.
 PriorityManagerSendMsgHook( Application, Message );

 // Сокрытие строк в списке окон.
 RemoverSendMsgHook( Application, Message );

 // Шрифты в текстовых окнах.
 RemoverSendMsgHook( Application, Message );

 // Переключатели на клавиатуре.
 ControllerSendMsgHook( Application, Message );

 // Заставки при открытии окон.
 PatcherSendMsgHook( Application, Message );

 // Слежение за состоянием оболочки OS/2.
 LockupSendMsgHook( Message );

 // Возврат.
 return;
}
