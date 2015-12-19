// Список известных расширителю приложений.
#define MAX_RP_ENTRIES               128

#define APP_NICE                     1010
#define APP_NICE_ECS                 1011

#define APP_CMD                      10000
#define APP_COM                      10001

#define APP_JAVA_RUNTIME             10011
#define APP_APPLETVIEWER             10012

#define APP_WATCHCAT                 10020
#define APP_THESEUS                  10021
#define APP_KTASKMAN                 10022
#define APP_MPCPUMON                 10023

#define APP_NPSWPS                   10030
#define APP_SYSBAR                   10031
#define APP_ESPS                     10032

#define APP_PMFORMAT                 10040
#define APP_PMCHKDSK                 10041

#define APP_CDRECORD                 10050
#define APP_CDREC_PM                 10051

#define APP_DVDRECORD                10055

#define APP_NETDRIVE                 10060
#define APP_DISCON                   10061
#define APP_NETUSE                   10062
#define APP_SAFEFIRE                 10063
#define APP_INJOY                    10064
#define APP_ISDNPM                   10065
#define APP_ECSCONET                 10066

#define APP_FC                       10070
#define APP_DN                       10071
#define APP_XC                       10072

#define APP_LCMD                     10080
#define APP_EFCOMM                   10081
#define APP_FM2                      10082
#define APP_FBROWSER                 10083
#define APP_FFREEDOM                 10084

#define APP_GTU_FILES                10090

#define APP_MOZILLA                  10100
#define APP_FIREFOX                  10101
#define APP_ARORA                    10102
#define APP_QUPZILLA                 10103
#define APP_LINKS                    10104

#define APP_THUNDERBIRD              10110
#define APP_PMMAIL                   10111
#define APP_POLARBAR                 10112

#define APP_OPENCHAT                 10120
#define APP_PMBITCHX                 10121

#define APP_PWICQ                    10130
#define APP_ICECQ                    10131
#define APP_AICQ                     10132

#define APP_FTPBROWSER               10140
#define APP_NFTPPM                   10141
#define APP_FTPPM                    10142

#define APP_SSH                      10150
#define APP_MINDTERM                 10151

#define APP_MED                      10160
#define APP_KON                      10161
#define APP_FTEPM                    10162
#define APP_FWE                      10163
#define APP_E                        10164
#define APP_EPM                      10165
#define APP_EDPLUS                   10166
#define APP_ZED                      10167

#define APP_EULER                    10170
#define APP_SCALC                    10171
#define APP_ECALC                    10172

#define APP_WORDPRO                  10180
#define APP_LOTUS123                 10181
#define APP_MESA                     10182
#define APP_APPROACH                 10183
#define APP_DBEXPERT                 10184

#define APP_LATEX                    10190
#define APP_VIEWDOC                  10191
#define APP_NEWVIEW                  10192

#define APP_PMVIEW                   10200

#define APP_PM123                    10210
#define APP_WARPVISION               10211
#define APP_ZMP3                     10212
#define APP_MIKMOD                   10213
#define APP_TIMIDITY                 10214
#define APP_COOLFM                   10215

#define APP_MMOS2_VOLUME             10220
#define APP_UNIAUDIO_MIXER           10221

#define APP_VACPP                    10230
#define APP_PMDIFF                   10231

#define APP_VIRTUALPC                10500

#define APP_MSQL                     10810
#define APP_MYSQL                    10820
#define APP_WEB2                     10830
#define APP_HTTPD                    10840
#define APP_FTPD                     10850
#define APP_SSHD                     10860

#define APP_USER_TOOL_1              50000
#define APP_USER_TOOL_2              50001
#define APP_USER_TOOL_3              50002
#define APP_USER_TOOL_4              50003
#define APP_USER_TOOL_5              50004
#define APP_USER_TOOL_6              50005
#define APP_USER_TOOL_7              50006
#define APP_USER_TOOL_8              50007
#define APP_USER_TOOL_9              50008
#define APP_USER_TOOL_A              50009
#define APP_USER_TOOL_B              50010
#define APP_USER_TOOL_C              50011
#define APP_USER_TOOL_D              50012
#define APP_USER_TOOL_E              50013
#define APP_USER_TOOL_F              50014

#define APP_EMBELLISH                99999

// Действия, которые могут выполняться при нажатии на клавиши.
// Эти значения записываются в INI, их нельзя менять.
// Цифры не начинаются с нулей, т.к. это десятичные значения.
#define EMPTY_ACTION_ITEM            -1
#define EMPTY_KEY_ITEM               NULL

#define DO_NOT_DEFINE                0

#define SYSTEM_LOCKUP                1
#define SYSTEM_HIBERNATE             2
#define SYSTEM_SHUTDOWN              3

#define SHOW_PMSHELL_FIRST           SHOW_WINDOW_LIST

#define SHOW_WINDOW_LIST             100
#define SHOW_NEXT_WINDOW             110
#define SHOW_PREV_WINDOW             120

#define SHOW_PMSHELL_LAST            SHOW_PREV_WINDOW

#define SHOW_OBJECT_FIRST            SHOW_DRIVES

#define SHOW_DRIVES                  1000

#define SHOW_PRINTER                 1010
#define SHOW_PRINTERS                1020

#define SHOW_WINVIEWER               1100
#define SHOW_WPS_CLOCK               1110
#define SHOW_PULSE                   1120
#define SHOW_POWER_MGR               1130

#define SHOW_ECENTER                 1201
#define SHOW_EPAGER                  1211
#define SHOW_WARPCENTER              1221
#define SHOW_LAUNCHPAD               1231

#define SHOW_USER_GUIDE              1500

#define SHOW_OBJECT_LAST             SHOW_USER_GUIDE

#define SHOW_APPLICATION_FIRST       SHOW_SYSBAR

#define SHOW_SYSBAR                  10000
#define SHOW_FILEBAR                 10010
#define SHOW_SYSTRAY                 10020

#define SHOW_TASK_MANAGER            10100

#define SHOW_NETWORK                 11000
#define SHOW_DIALER                  11010

#define SHOW_VIO_COMMANDER           12000
#define SHOW_PM_COMMANDER            12010
#define SHOW_FINDER                  12020

#define SHOW_WEB_BROWSER             13000
#define SHOW_MAIL_READER             13010
#define SHOW_INTERNET_CHAT           13020
#define SHOW_ICQ_PAGER               13030
#define SHOW_FTP_BROWSER             13040

#define SHOW_VIO_SSH_TERMINAL        14000
#define SHOW_PM_SSH_TERMINAL         14010

#define SHOW_TEXT_EDITOR             14500
#define SHOW_CALCULATOR              14510
#define SHOW_IMAGE_VIEWER            14520

#define SHOW_MP3_PLAYER              15000
#define SHOW_MOD_PLAYER              15010
#define SHOW_FM_TUNER                15020

#define SHOW_MMOS2_VOLUME            16000
#define SHOW_UNIAUDIO_MIXER          16010

#define SHOW_EMULATOR                25000

#define SHOW_APPLICATION_LAST        SHOW_EMULATOR

#define SHOW_USER_TOOL_FIRST         SHOW_USER_TOOL_1

#define SHOW_USER_TOOL_1             50000
#define SHOW_USER_TOOL_2             50010
#define SHOW_USER_TOOL_3             50020
#define SHOW_USER_TOOL_4             50030
#define SHOW_USER_TOOL_5             50040
#define SHOW_USER_TOOL_6             50050
#define SHOW_USER_TOOL_7             50060
#define SHOW_USER_TOOL_8             50070
#define SHOW_USER_TOOL_9             50080
#define SHOW_USER_TOOL_A             50090
#define SHOW_USER_TOOL_B             50100
#define SHOW_USER_TOOL_C             50110
#define SHOW_USER_TOOL_D             50120
#define SHOW_USER_TOOL_E             50130
#define SHOW_USER_TOOL_F             50140

#define SHOW_USER_TOOL_LAST          SHOW_USER_TOOL_F

#define MM_FIRST                     MM_VOLUME_INCREMENT

#define MM_VOLUME_INCREMENT          80000
#define MM_VOLUME_DECREMENT          80010
#define MM_VOLUME_INCREMENT_MMOS2    80020
#define MM_VOLUME_DECREMENT_MMOS2    80030

#define MM_REPEAT                    90000
#define MM_PAUSE                     90010
#define MM_NEXT                      90020
#define MM_PREVIOUS                  90025
#define MM_STOP                      90030

#define MM_LAST                      MM_STOP

#define CHAR_FIRST                   CHAR_ESC

#define CHAR_ESC                     100000

#define CHAR_CTRL_F1                 100010
#define CHAR_CTRL_F2                 100020
#define CHAR_CTRL_F3                 100030
#define CHAR_CTRL_F4                 100040
#define CHAR_CTRL_F5                 100050
#define CHAR_CTRL_F6                 100060
#define CHAR_CTRL_F7                 100070
#define CHAR_CTRL_F8                 100080
#define CHAR_CTRL_F9                 100090
#define CHAR_CTRL_F10                100100
#define CHAR_CTRL_F11                100110
#define CHAR_CTRL_F12                100120

#define CHAR_ALT_F1                  101010
#define CHAR_ALT_F2                  101020
#define CHAR_ALT_F3                  101030
#define CHAR_ALT_F4                  101040
#define CHAR_ALT_F5                  101050
#define CHAR_ALT_F6                  101060
#define CHAR_ALT_F7                  101070
#define CHAR_ALT_F8                  101080
#define CHAR_ALT_F9                  101090
#define CHAR_ALT_F10                 101100
#define CHAR_ALT_F11                 101110
#define CHAR_ALT_F12                 101120

#define CHAR_ALT_LEFT                101210
#define CHAR_ALT_RIGHT               101220

#define CHAR_CTRL_A                  102010
#define CHAR_CTRL_B                  102020
#define CHAR_CTRL_C                  102030
#define CHAR_CTRL_D                  102040
#define CHAR_CTRL_E                  102050
#define CHAR_CTRL_F                  102060
#define CHAR_CTRL_G                  102070
#define CHAR_CTRL_H                  102080
#define CHAR_CTRL_I                  102090
#define CHAR_CTRL_J                  102100
#define CHAR_CTRL_K                  102110
#define CHAR_CTRL_L                  102120
#define CHAR_CTRL_M                  102130
#define CHAR_CTRL_N                  102140
#define CHAR_CTRL_O                  102150
#define CHAR_CTRL_P                  102160
#define CHAR_CTRL_Q                  102170
#define CHAR_CTRL_R                  102180
#define CHAR_CTRL_S                  102190
#define CHAR_CTRL_T                  102200
#define CHAR_CTRL_U                  102210
#define CHAR_CTRL_V                  102220
#define CHAR_CTRL_W                  102230
#define CHAR_CTRL_X                  102240
#define CHAR_CTRL_Y                  102250
#define CHAR_CTRL_Z                  102260

#define CHAR_ALT_A                   103010
#define CHAR_ALT_B                   103020
#define CHAR_ALT_C                   103030
#define CHAR_ALT_D                   103040
#define CHAR_ALT_E                   103050
#define CHAR_ALT_F                   103060
#define CHAR_ALT_G                   103070
#define CHAR_ALT_H                   103080
#define CHAR_ALT_I                   103090
#define CHAR_ALT_J                   103100
#define CHAR_ALT_K                   103110
#define CHAR_ALT_L                   103120
#define CHAR_ALT_M                   103130
#define CHAR_ALT_N                   103140
#define CHAR_ALT_O                   103150
#define CHAR_ALT_P                   103160
#define CHAR_ALT_Q                   103170
#define CHAR_ALT_R                   103180
#define CHAR_ALT_S                   103190
#define CHAR_ALT_T                   103200
#define CHAR_ALT_U                   103210
#define CHAR_ALT_V                   103220
#define CHAR_ALT_W                   103230
#define CHAR_ALT_X                   103240
#define CHAR_ALT_Y                   103250
#define CHAR_ALT_Z                   103260

#define CHAR_LAST                    CHAR_ALT_Z

// Действия, которые могут выполняться при нажатии на кнопки мыши.
#define MOUSE_CLIPBOARD_COPY         10
#define MOUSE_CLIPBOARD_PASTE        20

// Задачи, решаемые приложениями.
// Эти значения объединяют несколько приложений, исполняющих разные действия с одной и той же целью.
#define DO_ANYTHING                    0
#define DO_IMPROVE_WORKPLACE          10

#define DO_EXECUTE_COMMANDS          100
#define DO_EXECUTE_APPLICATIONS      110
#define DO_MONITOR_SYSTEM            120

#define DO_PREPARE_DRIVES            200
#define DO_CONNECT_DRIVES            210
#define DO_CONNECT_INTERNET          220

#define DO_MANAGE_FILES              300
#define DO_SEARCH_FILES              310

#define DO_BROWSE_WEB_PAGES          400
#define DO_BROWSE_FTP_SITES          410
#define DO_READ_MESSAGES             420
#define DO_INTERNET_CHAT             430
#define DO_CONTACT_PEOPLE            440
#define DO_REMOTE_CONTROL            450
#define DO_NETWORK_COMPUTING         460

#define DO_EDIT_TEXT                 500
#define DO_EDIT_DATA                 510
#define DO_CALCULATION               520

#define DO_BROWSE_TEX_TEXT           600
#define DO_BROWSE_IPF_HELP           610

#define DO_BROWSE_IMAGES             700
#define DO_CREATE_IMAGES             710

#define DO_ENTERTAINMENT             800
#define DO_PLAY_GAME                 810

#define DO_DEVELOP_PROGRAMS          900
#define DO_INSTALL_PACKAGES          910

#define DO_EMULATION                1000

#define DO_DATABASE                 1500
#define DO_WEB_SERVER               1510
#define DO_FTP_SERVER               1520
#define DO_SSH_SERVER               1530

// Свойства окон и значков (и правила их вызова).
#define FLT_ALL                     0
#define FLT_DESIRED                 1
#define FLT_SUITABLE                2
