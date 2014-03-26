// Scan-коды клавиш.
#define SC_ESC                  0x01

#define SC_F1                   0x3B
#define SC_F2                   0x3C
#define SC_F3                   0x3D
#define SC_F4                   0x3E
#define SC_F5                   0x3F
#define SC_F6                   0x40
#define SC_F7                   0x41
#define SC_F8                   0x42
#define SC_F9                   0x43
#define SC_F10                  0x44
#define SC_F11                  0x57
#define SC_F12                  0x58

#define SC_PRSCR                0x5D
#define SC_SYSRQ                0x54
#define SC_SCRLLOCK             0x46
#define SC_PAUSE                0x5F
#define SC_BREAK                0x6E

#define SC_BACKQUOTE            0x29
#define SC_A_1                  0x02
#define SC_A_2                  0x03
#define SC_A_3                  0x04
#define SC_A_4                  0x05
#define SC_A_5                  0x06
#define SC_A_6                  0x07
#define SC_A_7                  0x08
#define SC_A_8                  0x09
#define SC_A_9                  0x0A
#define SC_A_0                  0x0B
#define SC_MINUS                0x0C
#define SC_EQUALS               0x0D
#define SC_BACKSPACE            0x0E

#define SC_TAB                  0x0F
#define SC_Q                    0x10
#define SC_W                    0x11
#define SC_E                    0x12
#define SC_R                    0x13
#define SC_T                    0x14
#define SC_Y                    0x15
#define SC_U                    0x16
#define SC_I                    0x17
#define SC_O                    0x18
#define SC_P                    0x19
#define SC_BRACE_L              0x1A
#define SC_BRACE_R              0x1B
#define SC_NEWLINE              0x1C

#define SC_CAPSLOCK             0x3A
#define SC_A                    0x1E
#define SC_S                    0x1F
#define SC_D                    0x20
#define SC_F                    0x21
#define SC_G                    0x22
#define SC_H                    0x23
#define SC_J                    0x24
#define SC_K                    0x25
#define SC_L                    0x26
#define SC_SEMICOLON            0x27
#define SC_QUOTE                0x28
#define SC_BACKSLASH            0x2B

#define SC_LEFT_SHIFT           0x2A
#define SC_DASH                 0x56
#define SC_Z                    0x2C
#define SC_X                    0x2D
#define SC_C                    0x2E
#define SC_V                    0x2F
#define SC_B                    0x30
#define SC_N                    0x31
#define SC_M                    0x32
#define SC_COLON                0x33
#define SC_POINT                0x34
#define SC_SLASH                0x35
#define SC_RIGHT_SHIFT          0x36

#define SC_LEFT_CTRL            0x1D
#define SC_LEFT_WINKEY          0x7E
#define SC_LEFT_ALT             0x38
#define SC_SPACE                0x39
#define SC_RIGHT_ALT            0x5E
#define SC_RIGHT_WINKEY         0x7F
#define SC_WINDOW_LIST          0x7C
#define SC_RIGHT_CTRL           0x5B

#define SC_LEFT                 0x63
#define SC_DOWN                 0x66
#define SC_RIGHT                0x64
#define SC_UP                   0x61

#define SC_INSERT               0x68
#define SC_HOME                 0x60
#define SC_PAGEUP               0x62
#define SC_DELETE               0x69
#define SC_END                  0x65
#define SC_PAGEDOWN             0x67

#define SC_NUMLOCK              0x45
#define SC_NUM_SLASH            0x5C
#define SC_NUM_MULTIPLE         0x37
#define SC_NUM_MINUS            0x4A
#define SC_NUM_PLUS             0x4E
#define SC_NUM_ENTER            0x5A
#define SC_NUM_7                0x47
#define SC_NUM_8                0x48
#define SC_NUM_9                0x49
#define SC_NUM_4                0x4B
#define SC_NUM_5                0x4C
#define SC_NUM_6                0x4D
#define SC_NUM_1                0x4F
#define SC_NUM_2                0x50
#define SC_NUM_3                0x51
#define SC_NUM_0                0x52
#define SC_NUM_P                0x53

#define SC_NUM_FIRST            SC_NUM_7
#define SC_NUM_LAST             SC_NUM_P

#define SC_A_MIN                0x10
#define SC_A_MAX                0x32

#define SC_ACPI_POWER           0xFF     /* E0:5E              */
#define SC_ACPI_SLEEP           0xFF     /* E0:5F, E0:5F (USB) */
#define SC_ACPI_WAKE_UP         0x89     /* E0:63              */

#define SC_MM_PLAY              0xD2     /* E0:22              */
#define SC_MM_STOP              0xD4     /* E0:24              */
#define SC_MM_PREVIOUS_TRACK    0xC0     /* E0:10              */
#define SC_MM_NEXT_TRACK        0xC9     /* E0:19              */
#define SC_MM_VOLUME_DECREMENT  0xDE     /* E0:2E              */
#define SC_MM_VOLUME_INCREMENT  0xCC     /* E0:30              */
#define SC_MM_MUTE              0xD0     /* E0:20              */
#define SC_MM_MEDIA             0x6D     /* E0:6D, E0:3D (USB) */

#define SC_APP_MY_CONTOOPER     0x6B     /* E0:6B              */
#define SC_APP_CALCULATOR       0xD1     /* E0:21              */
#define SC_APP_BROWSER          0xDA     /* E0:32              */
#define SC_APP_MAIL_READER      0xFF     /* E0:6C, E0:6C (USB) */
#define SC_APP_SEARCH           0x8B     /* E0:65              */
#define SC_APP_BOOKMARKS        0x8C     /* E0:66              */

#define SC_WEB_BACK             0x6A     /* E0:6A              */
#define SC_WEB_FORWARD          0x8F     /* E0:69              */
#define SC_WEB_CANCEL           0x8E     /* E0:68              */
#define SC_WEB_REFRESH          0x8D     /* E0:67              */

#define SC_PAGE_LEFT            0xFF     /*        E0:6A (USB) */
#define SC_PAGE_RIGHT           0xFF     /*        E0:69 (USB) */

#define SC_CMQ_I                0xD3     /* E0:23              */
#define SC_CMQ_HOME             0xCF     /* E0:1F              */
#define SC_CMQ_SEARCH           0xCA     /* E0:1A              */
#define SC_CMQ_MAIL             0xCE     /* E0:1E              */
#define SC_CMQ_PEOPLE           0xC3     /* E0:13              */
#define SC_CMQ_BENCH            0xC4     /* E0:14              */
#define SC_CMQ_CHAT             0xC5     /* E0:15              */
#define SC_CMQ_READING          0xCB     /* E0:1B              */

#define SC_CHERRY_K_F1          SC_WEB_BACK
#define SC_CHERRY_K_F2          SC_WEB_FORWARD
#define SC_CHERRY_K_F3          SC_WEB_STOP
#define SC_CHERRY_K_F4          SC_WEB_REFRESH
#define SC_CHERRY_K_F5          SC_MM_PLAY
#define SC_CHERRY_K_F6          SC_MM_STOP
#define SC_CHERRY_K_F7          SC_MM_PREVIOUS_TRACK
#define SC_CHERRY_K_F8          SC_MM_NEXT_TRACK
#define SC_CHERRY_K_F9          SC_WEB_SEARCH
#define SC_CHERRY_K_F10         SC_APP_MY_CONTOOPER
#define SC_CHERRY_K_F11         SC_WEB_FAVORITES
#define SC_CHERRY_CALCULATOR    SC_APP_CALCULATOR
#define SC_CHERRY_MAIL          SC_APP_MAIL_READER
#define SC_CHERRY_BROWSER       SC_APP_BROWSER
#define SC_CHERRY_SLEEP         SC_ACPI_SLEEP
#define SC_CHERRY_WAKE_UP       SC_ACPI_WAKE_UP
#define SC_CHERRY_MINUS         SC_MM_VOLUME_DECREMENT
#define SC_CHERRY_PLUS          SC_MM_VOLUME_INCREMENT
#define SC_CHERRY_MUTE          SC_MM_MUTE
#define SC_CHERRY_PLAYER        SC_MM_MEDIA

