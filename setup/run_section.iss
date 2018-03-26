[Run]
Filename: "{app}\{#MyAppServiceName}"; Parameters: -i; Flags: runhidden;
Filename: "{app}\{#MyAppServiceName}"; Flags: runhidden;
Filename: "{app}\{#MyAppTerminalName}"; Parameters: -dump; Flags: runhidden;
Filename: "{app}\{#MyAppExeName}"; Description: "{cm:LaunchProgram,{#StringChange("OddEye Controller in system tray", '&', '&&')}}"; Flags: nowait postinstall skipifsilent
Filename: "{app}\conf\"; Description: "{#StringChange("Open configurations folder", '&', '&&')}"; Flags: shellexec runasoriginaluser nowait postinstall skipifsilent
