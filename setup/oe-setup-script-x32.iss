; Script generated by the Inno Setup Script Wizard.
; SEE THE DOCUMENTATION FOR DETAILS ON CREATING INNO SETUP SCRIPT FILES!

#define ServiceRelDir       "src\build-OEAgentService-Desktop_Qt_5_5_0_MSVC2013_32bit-Release\release"
#define GuiControllerRelDir "src\control\build-OESystemTrayController-Desktop_Qt_5_5_0_MSVC2013_32bit-Release\release"
#define CuiControllerRelDir "src\control\build-OEConsolController-Desktop_Qt_5_5_0_MSVC2013_32bit-Release\release"
#define BinDir              "setup\bin32"

#include "common.iss"


[Setup]
OutputBaseFilename=oe-agent-setup-x86


[Files]
Source: "{#OddEyeDevDir}\{#BinDir}\msvcp120.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "{#OddEyeDevDir}\{#BinDir}\msvcr120.dll"; DestDir: "{app}"; Flags: ignoreversion

#include "run_section.iss"


