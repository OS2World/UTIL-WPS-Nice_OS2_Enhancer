/* Rexx */
Call RxFuncAdd 'SysLoadFuncs', 'RexxUtil', 'SysLoadFuncs'; Call SysLoadFuncs
Call RxFuncAdd 'WPToolsLoadFuncs', 'WPTools', 'WPToolsLoadFuncs'; Call WPToolsLoadFuncs

Parse Arg Parameters
If Pos( '--action=explore-desktop', Parameters ) = 0 then Exit

Parse Pull Query; If Query \= '<<' then Exit

Shell_is_WPS = WPToolsQueryObject( '<WP_DESKTOP>', 'Class', 'Title', 'Setup_string', 'Location' )
If Shell_is_WPS & Class \= '' then
 Do
  If Right( Location, 1 ) \= '\' then Location = Location || '\'
  Desktop = Location || Title

  Call SysFileTree Desktop || '\*', Folders, 'SDO'

  Folders.0 = Folders.0 + 1; Max_entry = Folders.0
  Folders.Max_entry = Desktop

  Do Folder_count = 1 to Folders.0
   Objects_are_present = WPToolsFolderContent( Folders.Folder_count, 'Objects.' )

   If Objects_are_present then
    Do Object_count = 1 to Objects.0

     Object_is_exists = WPToolsQueryObject( Objects.Object_count, 'Class', 'Title', 'Setup_string', 'Location' )
     If Object_is_exists then
      Do
       Object = Objects.Object_count
       If Left( Object, 1 ) = '#' then Object = '#' || X2D( Right( Object, Length( Object ) - 1 ) ) 

       Parse Var Setup_string Before 'EXENAME=' Exe_name ';'
       Parse Var Setup_string Before 'PARAMETERS=' Parameters ';'
       Parse Var Setup_string Before 'STARTUPDIR=' Work_directory ';'

       If Exe_name \= '' then Say '' || Object || 'þ' || Exe_name || 'þ' || Parameters || 'þ' || Work_directory || ''
      End
    End
  End
End

Exit