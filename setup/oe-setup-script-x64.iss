; Script generated by the Inno Setup Script Wizard.
; SEE THE DOCUMENTATION FOR DETAILS ON CREATING INNO SETUP SCRIPT FILES!

#define ServiceRelDir       "src\build-OEAgentService-Desktop_Qt_5_6_3_MSVC2013_64bit-Release\release"
#define GuiControllerRelDir "src\control\build-OESystemTrayController-Desktop_Qt_5_6_3_MSVC2013_64bit-Release\release"
#define CuiControllerRelDir "src\control\build-OEConsolController-Desktop_Qt_5_6_3_MSVC2013_64bit-Release\release"
#define BinDir              "setup\bin64"

#include "common.iss"

[Setup]
OutputBaseFilename=oe-agent-setup-x64
ArchitecturesInstallIn64BitMode=x64

[Files]
Source: "{#OddEyeDevDir}\{#BinDir}\vcredist_msvc2013_x64.exe"; DestDir: {tmp};  Flags: deleteafterinstall

[Run]
Filename: "{tmp}\vcredist_msvc2013_x64.exe"; Check: VCRedistNeedsInstall
#include "run_section.iss"

[Code]
#IFDEF UNICODE
  #DEFINE AW "W"
#ELSE
  #DEFINE AW "A"
#ENDIF
type
  INSTALLSTATE = Longint;
const
  INSTALLSTATE_INVALIDARG = -2;  { An invalid parameter was passed to the function. }
  INSTALLSTATE_UNKNOWN = -1;     { The product is neither advertised or installed. }
  INSTALLSTATE_ADVERTISED = 1;   { The product is advertised but not installed. }
  INSTALLSTATE_ABSENT = 2;       { The product is installed for a different user. }
  INSTALLSTATE_DEFAULT = 5;      { The product is installed for the current user. }

  { Visual C++ 2013 Redistributable 12.0.21005 }
  VC_2013_REDIST_X86_MIN = '{13A4EE12-23EA-3371-91EE-EFB36DDFFF3E}';
  VC_2013_REDIST_X64_MIN = '{A749D8E6-B613-3BE3-8F5F-045C84EBA29B}';

  VC_2013_REDIST_X86_ADD = '{F8CFEB22-A2E7-3971-9EDA-4B11EDEFC185}';
  VC_2013_REDIST_X64_ADD = '{929FBD26-9020-399B-9A7A-751D61F0B942}';

function MsiQueryProductState(szProduct: string): INSTALLSTATE; 
  external 'MsiQueryProductState{#AW}@msi.dll stdcall';

function VCVersionInstalled(const ProductID: string): Boolean;
begin
  Result := MsiQueryProductState(ProductID) = INSTALLSTATE_DEFAULT;
end;

function VCRedistNeedsInstall: Boolean;
begin
  Result := not VCVersionInstalled(VC_2013_REDIST_X64_MIN);
end;
