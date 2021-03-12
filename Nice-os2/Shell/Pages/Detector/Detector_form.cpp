
// ─── Обработчик сообщений для окна ───

// Поток приложения вызывает WindowProc всякий раз, когда для окна есть сообщение.
// Window - окно, Message - сообщение, *_parameter - данные, которые передаются вместе с сообщением.
MRESULT EXPENTRY Detector_DlgProc (HWND Window, ULONG Message, MPARAM First_parameter, MPARAM Second_parameter)
{
  // Проверяем сообщение.
  switch (Message)
  {
    // Выполняем действия при создании окна.
    case WM_INITDLG:
    {
      WinPostMsg (Window, SM_INITDLG, 0, 0);
    }
    return DLG_NOFOCUS;

    case SM_INITDLG:
    {
      // Узнаем страну, в которой работает приложение.
      LONG Code_page = Enhancer.Code_page;

      // Задаем текст полей ввода.
      if (Code_page == RUSSIAN)
      {
        WinSetWindowText (WinWindowFromID (Window, ID_DETECTORFORM_WINTITLE),      StrConst_RU_Pages_Detector_form_Window_title);
        WinSetWindowText (WinWindowFromID (Window, ID_DETECTORFORM_NAME4LIST),     StrConst_RU_Pages_Detector_form_Name_for_list);
        WinSetWindowText (WinWindowFromID (Window, ID_DETECTORFORM_PRESSINSERT),   StrConst_RU_Pages_Detector_form_Press_Insrt);
        WinSetWindowText (WinWindowFromID (Window, ID_DETECTORFORM_PRESSSSHIFT),   StrConst_RU_Pages_Detector_form_Press_Shift);
        WinSetWindowText (WinWindowFromID (Window, ID_DETECTORFORM_ESCAPE_BUTTON), StrConst_RU_Pages_Detector_form_Escape);
      }
      else
      {
        WinSetWindowText (WinWindowFromID (Window, ID_DETECTORFORM_WINTITLE),      StrConst_EN_Pages_Detector_form_Window_title);
        WinSetWindowText (WinWindowFromID (Window, ID_DETECTORFORM_NAME4LIST),     StrConst_EN_Pages_Detector_form_Name_for_list);
        WinSetWindowText (WinWindowFromID (Window, ID_DETECTORFORM_PRESSINSERT),   StrConst_EN_Pages_Detector_form_Press_Insrt);
        WinSetWindowText (WinWindowFromID (Window, ID_DETECTORFORM_PRESSSSHIFT),   StrConst_EN_Pages_Detector_form_Press_Shift);
        WinSetWindowText (WinWindowFromID (Window, ID_DETECTORFORM_ESCAPE_BUTTON), StrConst_EN_Pages_Detector_form_Escape);
      }

      if (Enhancer.Detector_dialog.Key_code != NULL)
      {
        WinShowWindow (WinWindowFromID (Window, ID_DETECTORFORM_WINTITLE),         0);
        WinShowWindow (WinWindowFromID (Window, ID_DETECTORFORM_WINTITLE_STRING),  0);
        WinShowWindow (WinWindowFromID (Window, ID_DETECTORFORM_NAME4LIST),        0);
        WinShowWindow (WinWindowFromID (Window, ID_DETECTORFORM_NAME4LIST_STRING), 0);
        WinShowWindow (WinWindowFromID (Window, ID_DETECTORFORM_PRESSSSHIFT),      0);

        if (Code_page == RUSSIAN)
        {
          WinSetWindowText (WinWindowFromID (Window, ID_DETECTORFORM_PRESSINSERT), StrConst_RU_Pages_Detector_form_Press_Key);
        }
        else
        {
          WinSetWindowText (WinWindowFromID (Window, ID_DETECTORFORM_PRESSINSERT), StrConst_EN_Pages_Detector_form_Press_Key);
        }
      }
    }
    return 0;

    // Выполняем действия через заданные промежутки времени.
    // Счетчик времени создается и удаляется перед началом и после завершения диалога.
    case WM_TIMER:
    {
      // Если нажата кнопка мыши - возможно, идет передвижение окна, возврат.
      if (MouseIsBusy ()) return 0;

      // Если окно приложения уменьшено или скрыто - завершаем диалог.
      {
        SWP Window_placement = {0}; WinQueryWindowPos (Enhancer.Frame_window, &Window_placement);

        if (Window_placement.fl & SWP_MINIMIZE || Window_placement.fl & SWP_HIDE)
        {
          WinDismissDlg (Window, 0);
          return 0;
        }
      }

      // Делаем окно выбранным.
      if (Enhancer.Detector_dialog.Detector_is_running)
      {
        // Узнаем выбранное окно.
        HWND Active_window = WinQueryActiveWindow (HWND_DESKTOP);

        // Если это список окон - возврат.
        if (IsWinListWindow (Active_window)) return 0;

        // Делаем выбранным окно приложения.
        if (Active_window != Enhancer.Frame_window)
        {
          WinSetActiveWindow (HWND_DESKTOP, Enhancer.Frame_window);
        }

        // Показываем окно определителя поверх других окон.
        WinSetWindowPos (Window, HWND_TOP, 0, 0, 0, 0, SWP_ZORDER | SWP_NOADJUST);
        WinSetFocus (HWND_DESKTOP, Window);

        // Передвигаем окно в середину окна рамки.
        Detector_MoveToCenter (Window);

        // Перерисовываем окно.
        WinInvalidateRect (Window, NULL, 1);
      }

      // Если надо узнать имя для списка исключений:
      if (Enhancer.Detector_dialog.Window_name_1 != NULL || Enhancer.Detector_dialog.Scan_dialog)
      {
        // Узнаем имя для списка исключений.
        POINT Point = {0};
        HWND Frame_window = NULLHANDLE; HWND Client_window = NULLHANDLE;
        CHAR Title[SIZE_OF_TITLE] = ""; CHAR Name[SIZE_OF_NAME] = "";
        CHAR Exe_name[SIZE_OF_NAME] = "";

        // Узнаем окно, над которым расположен указатель мыши.
        WinQueryPointerPos (HWND_DESKTOP, &Point);
        Detector_Form.Settings.Detected_window = WinWindowFromPoint (HWND_DESKTOP, &Point, 1);

        // Узнаем имя, под которым определено окно под указателем мыши.
        WinQueryClassName (Detector_Form.Settings.Detected_window, SIZE_OF_NAME, Name);

        // Если не включены Caps Lock и Scroll Lock одновременно:
        if (!((WinGetKeyState (HWND_DESKTOP, VK_CAPSLOCK) & KEY_IS_TOGGLED) &&
               (WinGetKeyState (HWND_DESKTOP, VK_SCRLLOCK) & KEY_IS_TOGGLED)))
        {
          // Узнаем окно рамки для выбранного окна.
          Frame_window = QueryFrameWindow (Detector_Form.Settings.Detected_window);

          // Узнаем заголовок окна.
          WinQueryWindowText (Frame_window, SIZE_OF_TITLE, Title);

          // Узнаем название приложения, создавшего окно.
          QueryExeName (Frame_window, Exe_name);

          // Узнаем окно рабочей области.
          Client_window = WinWindowFromID (Frame_window, FID_CLIENT);

          // Если оно есть - узнаем имя, под которым определено окно.
          if (Client_window != NULLHANDLE) WinQueryClassName (Client_window, SIZE_OF_NAME, Name);

          // Если окна рабочей области нет или клавиша Shift не нажата - запоминаем название приложения.
          if (Client_window == NULLHANDLE ||
              !(WinGetKeyState (HWND_DESKTOP, VK_SHIFT) & KEY_IS_PRESSED))
          {
            strcpy (Name, Exe_name);
          }

          // Если окно является частью оболочки или это окно ODIN - запоминаем название приложения.
          if (Name[0] == '#' || IsVIOWindow (Frame_window) ||
              IsWindowsWindow (Frame_window)) strcpy (Name, Exe_name);

          // Некоторые окна не надо включать в список вообще.
          if (WindowIsCreatedBy (APP_NICE_ENHANCER, Frame_window) ||
              WindowIsCreatedBy (APP_NICE_ENHANCER_SHELL, Frame_window)) Name[0] = 0;

          if (!Enhancer.Detector_dialog.Include_shell_windows)
           if (IsPMShellAuxiliaryWindow (Frame_window) ||
               IsWorkplaceShellWindow (Frame_window)) Name[0] = 0;

          if (Enhancer.Detector_dialog.Include_VIO_windows_only)
           if (!IsVIOWindow (Frame_window)) Name[0] = 0;
        }

        // Заменяем в заголовке буквы 0x0D и 0x0A на пробелы.
        {
          INT Length = strlen (Title); INT Count;
          for (Count = 0; Count < Length; Count ++)
           if (Title[Count] == 0x0D || Title[Count] == 0x0A)
            if (Title[Count - 1] != ' ') Title[Count] = ' ';
            else
            {
              strncpy (&Title[Count], &Title[Count + 1], Length - Count);
              Count --;
            }
        }

        // Задаем значения полей.
        WinSetDlgItemText (Window, ID_DETECTORFORM_WINTITLE_STRING, Title);
        WinSetDlgItemText (Window, ID_DETECTORFORM_NAME4LIST_STRING, Name);
      }
    }
    return 0;

    // Обрабатываем нажатия на клавиши.
    case WM_CHAR:
    {
      // Смотрим, какая клавиша нажата.
      BYTE Scan_code = CHAR4FROMMP (First_parameter);
      SHORT State = SHORT1FROMMP (First_parameter);

      // Если надо узнать имя для списка исключений:
      if (Enhancer.Detector_dialog.Window_name_1 != NULL || Enhancer.Detector_dialog.Scan_dialog)
      {
        // Если нажата клавиша Insert:
        if (Scan_code == SC_INSERT || Scan_code == SC_NUM_0)
        {
          // При нажатии клавиши:
          if (!(State & KC_KEYUP))
          {
            // Смотрим, известно ли имя для списка исключений.
            CHAR Name[SIZE_OF_NAME] = "";
            WinQueryDlgItemText (Window, ID_DETECTORFORM_NAME4LIST_STRING, SIZE_OF_NAME, Name);

            // Если оно неизвестно - возврат.
            if (Name[0] == 0) return 0;

            // Если окно неизвестно - возврат.
            if (Detector_Form.Settings.Detected_window == NULLHANDLE) return 0;

            // Если в список надо занести имя окна или приложения, создавшего окно:
            if (Enhancer.Detector_dialog.Window_name_1 != NULL &&
                Enhancer.Detector_dialog.Window_name_2 != NULL &&
                Enhancer.Detector_dialog.Window_name_3 != NULL &&
                Enhancer.Detector_dialog.Window_name_4 != NULL &&
                Enhancer.Detector_dialog.Window_name_5 != NULL &&
                Enhancer.Detector_dialog.Window_name_6 != NULL &&
                Enhancer.Detector_dialog.Window_name_7 != NULL &&
                Enhancer.Detector_dialog.Window_name_8 != NULL)
            {
              // Задаем указатели для занесения в список имени окна.
              PCHAR Window_names[8] = {0};

              // Проверяем, есть ли окно в списке.
              if (strc (Name, Enhancer.Detector_dialog.Window_name_1)) return 0;
              if (strc (Name, Enhancer.Detector_dialog.Window_name_2)) return 0;
              if (strc (Name, Enhancer.Detector_dialog.Window_name_3)) return 0;
              if (strc (Name, Enhancer.Detector_dialog.Window_name_4)) return 0;
              if (strc (Name, Enhancer.Detector_dialog.Window_name_5)) return 0;
              if (strc (Name, Enhancer.Detector_dialog.Window_name_6)) return 0;
              if (strc (Name, Enhancer.Detector_dialog.Window_name_7)) return 0;
              if (strc (Name, Enhancer.Detector_dialog.Window_name_8)) return 0;

              // Добавляем окно в список.
             {
               PCHAR Item = NULL;

               if (Enhancer.Detector_dialog.Window_name_8[0] == 0) Item = Enhancer.Detector_dialog.Window_name_8;
               if (Enhancer.Detector_dialog.Window_name_7[0] == 0) Item = Enhancer.Detector_dialog.Window_name_7;
               if (Enhancer.Detector_dialog.Window_name_6[0] == 0) Item = Enhancer.Detector_dialog.Window_name_6;
               if (Enhancer.Detector_dialog.Window_name_5[0] == 0) Item = Enhancer.Detector_dialog.Window_name_5;
               if (Enhancer.Detector_dialog.Window_name_4[0] == 0) Item = Enhancer.Detector_dialog.Window_name_4;
               if (Enhancer.Detector_dialog.Window_name_3[0] == 0) Item = Enhancer.Detector_dialog.Window_name_3;
               if (Enhancer.Detector_dialog.Window_name_2[0] == 0) Item = Enhancer.Detector_dialog.Window_name_2;
               if (Enhancer.Detector_dialog.Window_name_1[0] == 0) Item = Enhancer.Detector_dialog.Window_name_1;

               if (Item == NULL) return 0;

               strncpy (Item, Name, SIZE_OF_NAME);
             }

              // Обновляем окно, содержащее список.
              WinPostMsg (Enhancer.Detector_dialog.Customer_window, SM_UPDATE_LIST, 0, 0);

              // Вызываем сохранение настроек.
              WinPostMsg (Enhancer.Detector_dialog.Customer_window, WM_COMMAND, MPFROMLONG (OK_BUTTON_ID), 0);
            }

            // Если надо запомнить сведения об окне:
            if (Enhancer.Detector_dialog.Scan_dialog != NULL)
            {
              // Узнаем окно рамки для выбранного окна.
              HWND Frame_window = QueryFrameWindow (Detector_Form.Settings.Detected_window);

              // Вызываем расширитель, чтобы он выполнил требуемое действие и запомнил настройки.
              if (Enhancer.Detector_dialog.Scan_logon_dialog)
              {
                NiceScanLogonDialog (Frame_window);
              }

              if (Enhancer.Detector_dialog.Scan_fields_in_dialog)
              {
                NiceScanIncompleteDialog (Frame_window);
              }

              if (Enhancer.Detector_dialog.Scan_message_box_dialog)
              {
                NiceScanMessageDialog (Frame_window);
              }

              // Ждем некоторое время.
              DosSleep (250);

              // Сообщаем окну, что ему надо прочесть подготовленные настройки.
              WinPostMsg (Enhancer.Detector_dialog.Customer_window, SM_READ_LIST, 0, 0);
              WinPostMsg (Enhancer.Detector_dialog.Customer_window, SM_UPDATE_LIST, 0, 0);
            }

            // Закрываем окно.
            WinDismissDlg (Window, 0);
          }
          // При отжатии клавиши:
          else
          {
            // Клавиша "Insert" используется как переключатель.
            WinSetSysValue (HWND_DESKTOP, SV_INSERTMODE, 1);
          }
        }
      }

      // Если надо узнать клавишу:
      if (Enhancer.Detector_dialog.Key_code != NULL)
      {
        // На некоторые клавиши обращать внимание не надо.
        if (Scan_code != SC_ESC)
        if (Scan_code != SC_LEFT_CTRL) if (Scan_code != SC_RIGHT_CTRL)
        if (Scan_code != SC_LEFT_ALT) if (Scan_code != SC_RIGHT_ALT)
        if (Scan_code != SC_LEFT_SHIFT) if (Scan_code != SC_RIGHT_SHIFT)
        if (Scan_code != SC_LEFT_WINKEY) if (Scan_code != SC_RIGHT_WINKEY)
        if (Scan_code != SC_NEWLINE) if (Scan_code != SC_NUM_ENTER)
        {
          // Запоминаем клавишу.
          *Enhancer.Detector_dialog.Key_code = Scan_code;

          {
            CHAR String[SIZE_OF_ITEM_TEXT] = "";
            CHAR Value[SIZE_OF_ITEM_TEXT] = "";

            itoa (Scan_code, Value, 16); UpperCase (Value);
            strcpy (String, "0x"); if (strlen (Value) == 1) strcat (String, "0");
            strcat (String, Value); strcat (String, " (");
            itoa (Scan_code, Value, 10);
            strcat (String, Value); strcat (String, ")");

            WinSetDlgItemText (Window, ID_DETECTORFORM_PRESSINSERT, String);
          }

          // Скрываем кнопку.
          WinShowWindow (WinWindowFromID (Window, ID_DETECTORFORM_ESCAPE_BUTTON), 0);

          {
            // Меняем цвет поля ввода.
            INT Count;

            for (Count = 0; Count < 3; Count ++)
            {
              ULONG White_color = MAKERGB (255, 255, 255);
              ULONG DarkRed_color = MAKERGB (80, 0, 0);

              WinSetPresParam (WinWindowFromID (Window, ID_DETECTORFORM_PRESSINSERT), PP_FOREGROUNDCOLOR, sizeof (ULONG), &White_color);
              DosSleep (250);
              WinSetPresParam (WinWindowFromID (Window, ID_DETECTORFORM_PRESSINSERT), PP_FOREGROUNDCOLOR, sizeof (ULONG), &DarkRed_color);
              DosSleep (250);
            }
          }

          // Окно должно быть закрыто.
          Scan_code = SC_ESC;
        }
      }

      // Если это клавиша Esc - закрываем окно.
      if (Scan_code == SC_ESC)
      {
        WinDismissDlg (Window, 0);
      }
    }
    return 0;

    // Обрабатываем нажатия на кнопки.
    case WM_COMMAND:
    {
      ULONG WM_Control_Button_ID = SHORT1FROMMP (First_parameter);

      // Единственная кнопка - закрытие окна.
      if (WM_Control_Button_ID == ID_DETECTORFORM_ESCAPE_BUTTON)
      {
        // Завершаем диалог.
        WinDismissDlg (Window, 0);
      }
    }
    return 0;
  }

  // Возврат.
  return WinDefDlgProc (Window, Message, First_parameter, Second_parameter);
}
