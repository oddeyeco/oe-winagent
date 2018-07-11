#define MyAppName "OddEye Agent"
#define MyAppVersion "1.0.1"
#define MyAppPublisher "OddEye, Inc."
#define MyAppURL "https://www.oddeye.co/"

#define MyAppExeName "oe-tray-menu.exe"
#define MyAppServiceName "agent-service.exe"
#define MyAppTerminalName "oe-terminal.exe"
#define OddEyeDirName "OddEye Agent"
#define OddEyeDevDir "C:\Users\User\Documents\OE-Agent"

[Setup]
; NOTE: The value of AppId uniquely identifies this application.
; Do not use the same AppId value in installers for other applications.
; (To generate a new GUID, click Tools | Generate GUID inside the IDE.)
AppId={{2BB3A430-E50D-48AA-890C-6988492633A7}
AppName={#MyAppName}
AppVersion={#MyAppVersion}
;AppVerName={#MyAppName} {#MyAppVersion}
DefaultDirName={pf}\{#MyAppName}
DisableProgramGroupPage=yes
LicenseFile={#OddEyeDevDir}\src\setup\LICENSE.TXT
OutputDir={#OddEyeDevDir}\setup\output\
Compression=lzma
SolidCompression=yes
AppMutex=oe_agent_sys_tray

[Languages]
Name: "english"; MessagesFile: "compiler:Default.isl"

[Tasks]
Name: desktopicon; Description: "{cm:CreateDesktopIcon}"; GroupDescription: "Additional icons:"; 
Name: desktopicon\user; Description: "For the current user only"; GroupDescription: "Additional icons:";  Flags: exclusive 
Name: desktopicon\common; Description: "For all users"; GroupDescription: "Additional icons:"; Flags: exclusive unchecked

[Dirs]
Name: "{app}\scripts_available"
Name: "{app}\scripts_enabled"
Name: "{app}\perf_counters_available"; Flags: uninsalwaysuninstall

[Files]
Source: "{#OddEyeDevDir}\{#GuiControllerRelDir}\OEAgentControl.exe";     DestDir: "{app}"; Flags: ignoreversion; DestName: {#MyAppExeName}
Source: "{#OddEyeDevDir}\{#CuiControllerRelDir}\OEConsolController.exe"; DestDir: "{app}"; Flags: ignoreversion; DestName: {#MyAppTerminalName}        
Source: "{#OddEyeDevDir}\{#ServiceRelDir}\OE-Agent.exe";                 DestDir: "{app}"; Flags: ignoreversion; DestName: {#MyAppServiceName}
         
Source: "{#OddEyeDevDir}\{#BinDir}\platforms\*";  DestDir: "{app}\platforms"; Flags: ignoreversion recursesubdirs createallsubdirs
Source: "{#OddEyeDevDir}\{#BinDir}\conf\*";       DestDir: "{app}\conf"; Flags: onlyifdoesntexist recursesubdirs createallsubdirs
Source: "{#OddEyeDevDir}\{#BinDir}\scripts_available\*";       DestDir: "{app}\scripts_available"; Flags: ignoreversion recursesubdirs createallsubdirs
Source: "{#OddEyeDevDir}\{#BinDir}\libeay32.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "{#OddEyeDevDir}\{#BinDir}\libssl32.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "{#OddEyeDevDir}\{#BinDir}\Qt5Core.dll";  DestDir: "{app}"; Flags: ignoreversion
Source: "{#OddEyeDevDir}\{#BinDir}\Qt5Gui.dll";   DestDir: "{app}"; Flags: ignoreversion
Source: "{#OddEyeDevDir}\{#BinDir}\Qt5Network.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "{#OddEyeDevDir}\{#BinDir}\Qt5Widgets.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "{#OddEyeDevDir}\{#BinDir}\ssleay32.dll"; DestDir: "{app}"; Flags: ignoreversion

[Icons]
Name: "{userprograms}\{#MyAppName}"; Filename: "{app}\{#MyAppExeName}"; Tasks: desktopicon\user
Name: "{userdesktop}\{#MyAppName}"; Filename: "{app}\{#MyAppExeName}"; Tasks: desktopicon\user
Name: "{commondesktop}\{#MyAppName}"; Filename: "{app}\{#MyAppExeName}"; Tasks: desktopicon\common
Name: "{commonprograms}\{#MyAppName}"; Filename: "{app}\{#MyAppExeName}"; Tasks: desktopicon\common

[UninstallRun]
Filename: "{app}\{#MyAppTerminalName}"; Parameters: -stop; Flags: runhidden;
Filename: "{app}\{#MyAppServiceName}"; Parameters: -t; Flags: runhidden;
Filename: "{app}\{#MyAppServiceName}"; Parameters: -u; Flags: runhidden; 

[UninstallDelete]
;This works only if it is installed in default location
Type: filesandordirs; Name: "{app}\perf_counters_available"

[Registry]
;current user only
Root: HKCU; Subkey: "Software\Microsoft\Windows\CurrentVersion\Run"; ValueType: string; ValueName: "OddEye Agent Control"; ValueData: "{app}\{#MyAppExeName}"; Flags: uninsclearvalue
Root: HKCU; Subkey: "Software\OddEyeAgent\"; ValueType: string; ValueName: "uuid"; ValueData: {code:GetSpecifiedUuid}

[INI]
Filename: "{app}\conf\conf.ini"; Section: "TSDB"; Key: "uuid"; String: {code:GetSpecifiedUuid}; 


[Code]
var
  MainPage: TWizardPage; 
  InstallHelpCheckBox: TNewCheckBox;  
  FolderToInstall: TNewEdit;

{ ================================================================== }
{ util method, equivalent to C# string.StartsWith }
function StartsWith(SubStr, S: String): Boolean;
begin
  Result:= Pos(SubStr, S) = 1;
end;

{ util method, equivalent to C# string.Replace }
function StringReplace(S, oldSubString, newSubString: String): String;
var
  stringCopy: String;
begin
  stringCopy := S; { Prevent modification to the original string }
  StringChange(stringCopy, oldSubString, newSubString);
  Result := stringCopy;
end;

function GetCommandlineParam(inParamName: String): String; 
var
   paramNameAndValue: String;
   i: Integer;
begin
   Result := '';

   for i := 0 to ParamCount do
   begin
     paramNameAndValue := ParamStr(i);
     if (StartsWith(inParamName, paramNameAndValue)) then
     begin
       Result := StringReplace(paramNameAndValue, inParamName + '=', '');
       break;
     end;
   end;
end;
{ ================================================================== }

procedure YourControlClick(Sender: TObject);
begin
  FolderToInstall.Enabled := Not FolderToInstall.Enabled;
  if FolderToInstall.Enabled = False Then 
    Wizardform.NextButton.Enabled := True
  else
    Wizardform.NextButton.Enabled := FolderToInstall.Text <> '';
end;

procedure MyEditChange(Sender: TObject);
begin
  // enable the next button if the edit box is not empty; disable otherwise
  WizardForm.NextButton.Enabled := FolderToInstall.Text <> '';
end;

procedure InitializeWizard;
var  
  LabelFolder: TLabel;
  sRegUUid: String; 
    
begin
  Wizardform.NextButton.Enabled := False;

  MainPage := CreateCustomPage(wpSelectComponents  , 'Insert OddEye profile UUid', '(Optional)');
  LabelFolder := TLabel.Create(MainPage);
  {LabelFolder.Parent := WizardForm;}
  LabelFolder.Top := 20;
  LabelFolder.Left := 6;
  LabelFolder.Caption := 'UUID:'

  InstallHelpCheckBox := TNewCheckBox.Create(MainPage);
  InstallHelpCheckBox.Parent := MainPage.Surface;
  InstallHelpCheckBox.Top := LabelFolder.Top + LabelFolder.Height + 8;
  InstallHelpCheckBox.Left := LabelFolder.Left;
  InstallHelpCheckBox.Width := 380;
  InstallHelpCheckBox.Caption := 'Insert OddEye profile UUid';

  FolderToInstall := TNewEdit.Create(MainPage);
  FolderToInstall.Parent := MainPage.Surface;
  FolderToInstall.Top := InstallHelpCheckBox.Top + InstallHelpCheckBox.Height + 8;
  FolderToInstall.Left := InstallHelpCheckBox.Left;
  FolderToInstall.Width := InstallHelpCheckBox.Width;
  FolderToInstall.Enabled := False;
  FolderToInstall.OnChange := @MyEditChange;

  FolderToInstall.Text := GetCommandLineParam('/uuid');
  if  FolderToInstall.Text = '' then
  begin
    RegQueryStringValue(HKEY_CURRENT_USER, 'Software\OddEyeAgent\','uuid', sRegUUid);
    FolderToInstall.Text := sRegUUid;    
  end;

  InstallHelpCheckBox.OnClick := @YourControlClick;
  InstallHelpCheckBox.Checked := True;

end;

procedure  CurPageChanged(CurPageID: Integer);
begin
  if CurPageID = MainPage.ID Then
  begin
     if  (Not WizardSilent) and (InstallHelpCheckBox.Checked = True) and (FolderToInstall.Text = '') then
      Wizardform.NextButton.Enabled := False
     else
      Wizardform.NextButton.Enabled := True;
  end;
    
end;

function GetSpecifiedUuid(Param: String  ): string;
var sUUidFromCmd : String;
begin
  Result := 'xxxxxxxx-xxxx-xxxx-xxxx-xxxxxxxxxxxx';

  if WizardSilent then
  begin
    sUUidFromCmd := GetCommandLineParam('/uuid');
    if sUUidFromCmd <> '' then
      Result := sUUidFromCmd;
  end
  else if (InstallHelpCheckBox.Checked = true) and (FolderToInstall.Text <> '') then
    Result := FolderToInstall.Text
end;

