;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;
; @(#) $Id: zint.nsi,v 1.1 2009/11/17 22:23:06 hooper114 Exp $
;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

; Script generated by the HM NIS Edit Script Wizard.
; HM NIS Edit Wizard helper defines
; ver 1.0.0.1 20090914 tgotic removed WinSxS check
;******************************************************************************
!define PRODUCT_NAME "Zint"
!define PRODUCT_EXE "qtZint.exe"
!define PRODUCT_VERSION "2.11.0"
!define PRODUCT_WEB_SITE "http://www.zint.org.uk"
!define PRODUCT_PUBLISHER "Robin Stuart & BogDan Vatra"
!define PRODUCT_DIR_REGKEY "Software\Microsoft\Windows\CurrentVersion\App Paths\${PRODUCT_EXE}"
!define PRODUCT_UNINST_KEY "Software\Microsoft\Windows\CurrentVersion\Uninstall\${PRODUCT_NAME}"
!define PRODUCT_STARTMENU_REGVAL "NSIS:StartMenuDir"
;******************************************************************************
Name "${PRODUCT_NAME} ${PRODUCT_VERSION}"
OutFile "Setup_${PRODUCT_NAME}_${PRODUCT_VERSION}.exe"
BrandingText "GPLv3, ${PRODUCT_PUBLISHER}"
;******************************************************************************
;ShowInstDetails show -ne zapisuje podatke u log datoteku
ShowInstDetails show
ShowUnInstDetails show

XPStyle on
SetCompress auto
SetCompressor lzma
AutoCloseWindow false
CRCCheck force
;******************************************************************************
; MUI 1.8 compatible ------
!define MULTIUSER_EXECUTIONLEVEL Highest
!define MULTIUSER_MUI
!define MULTIUSER_INSTALLMODE_COMMANDLINE
!define MULTIUSER_INSTALLMODE_INSTDIR "${PRODUCT_NAME}\"
!define MULTIUSER_INSTALLMODE_INSTDIR_REGISTRY_KEY "${PRODUCT_UNINST_KEY}"
!define MULTIUSER_INSTALLMODE_INSTDIR_REGISTRY_VALUENAME "InstallLocation"
;******************************************************************************
!include MultiUser.nsh
!include MUI2.nsh
!include LogicLib.nsh
!include WinMessages.nsh
!include FileFunc.nsh
;******************************************************************************
; MUI Settings
!define MUI_ABORTWARNING
; odkomentirati za prikaz MUI_PAGE_INSTFILES
!define MUI_FINISHPAGE_NOAUTOCLOSE
!define MUI_UNFINISHPAGE_NOAUTOCLOSE

;******************************************************************************
Var USER
Var ICONS_GROUP
;******************************************************************************
; Welcome page
!insertmacro MUI_PAGE_WELCOME
!insertmacro MUI_PAGE_LICENSE "gpl-3.0.txt"
; Mixed mode instalation page
!insertmacro MULTIUSER_PAGE_INSTALLMODE
; Components page
; !insertmacro MUI_PAGE_COMPONENTS
; Directory page
!insertmacro MUI_PAGE_DIRECTORY
!define MUI_STARTMENUPAGE_NODISABLE
!define MUI_STARTMENUPAGE_DEFAULTFOLDER "${PRODUCT_NAME}"
!define MUI_STARTMENUPAGE_REGISTRY_ROOT SHCTX
!define MUI_STARTMENUPAGE_REGISTRY_KEY "${PRODUCT_UNINST_KEY}"
!define MUI_STARTMENUPAGE_REGISTRY_VALUENAME "${PRODUCT_STARTMENU_REGVAL}"
!insertmacro MUI_PAGE_STARTMENU Application $ICONS_GROUP
; Instfiles page
!insertmacro MUI_PAGE_INSTFILES
;Finish page
!insertmacro MUI_PAGE_FINISH

; Uninstaller pages
!insertmacro MUI_UNPAGE_CONFIRM
!insertmacro MUI_UNPAGE_INSTFILES
!insertmacro MUI_UNPAGE_FINISH
; MUI end ------
;******************************************************************************
; Language files
!insertmacro MUI_LANGUAGE "English"
!insertmacro MUI_RESERVEFILE_LANGDLL
;******************************************************************************
Function .onInit
  !insertmacro MULTIUSER_INIT
FunctionEnd
;******************************************************************************
Function startInstall
  SetOutPath "$INSTDIR"
  StrCpy $USER 0
  UserInfo::GetName
  Pop $USER

  ${GetTime} "" "L" $0 $1 $2 $3 $4 $5 $6

#  LogSet on
  DetailPrint "--------------------------------------------------------------------------------"
  DetailPrint "Install start $2-$1-$0 $4:$5:$6 user:$USER ($MultiUser.Privileges)"
  DetailPrint "--------------------------------------------------------------------------------"
FunctionEnd
;******************************************************************************
;******************************************************************************
Section ${PRODUCT_NAME} SEC01
  SectionIn RO
  Call startInstall
  SetOverwrite ifnewer
  File ".\frontend_qt4\release\${PRODUCT_EXE}"
  File ".\win32\Release\zint.exe"
  
  WriteUninstaller "$INSTDIR\uninst.exe"

!insertmacro MUI_STARTMENU_WRITE_BEGIN Application
  CreateDirectory "$SMPROGRAMS\$ICONS_GROUP"
  CreateShortCut "$SMPROGRAMS\$ICONS_GROUP\Zint Barcode Studio.lnk" "$INSTDIR\${PRODUCT_EXE}"
  CreateShortCut "$SMPROGRAMS\$ICONS_GROUP\Uninstall.lnk" "$INSTDIR\uninst.exe"
!insertmacro MUI_STARTMENU_WRITE_END
SectionEnd
;******************************************************************************
Section -Post
  WriteRegStr SHCTX  "${PRODUCT_DIR_REGKEY}" "" "$INSTDIR\${PRODUCT_EXE}"
  WriteRegStr SHCTX  "${PRODUCT_DIR_REGKEY}" "Path" "$INSTDIR"
  WriteRegStr SHCTX  "${PRODUCT_UNINST_KEY}" "DisplayName" "${PRODUCT_NAME}"
  WriteRegStr SHCTX  "${PRODUCT_UNINST_KEY}" "UninstallString" "$INSTDIR\uninst.exe"
  WriteRegStr SHCTX  "${PRODUCT_UNINST_KEY}" "DisplayIcon" "$INSTDIR\${PRODUCT_EXE}"
  WriteRegStr SHCTX  "${PRODUCT_UNINST_KEY}" "DisplayVersion" "${PRODUCT_VERSION}"
  WriteRegStr SHCTX  "${PRODUCT_UNINST_KEY}" "Publisher" "${PRODUCT_PUBLISHER}"
  WriteRegStr SHCTX  "${PRODUCT_UNINST_KEY}" "URLUpdateInfo" "${PRODUCT_WEB_SITE}"
  WriteRegStr SHCTX  "${PRODUCT_UNINST_KEY}" "URLInfoAbout" "${PRODUCT_WEB_SITE}"
  WriteRegStr SHCTX  "${PRODUCT_UNINST_KEY}" "InstallLocation" "$INSTDIR"
  WriteRegStr SHCTX  "${PRODUCT_UNINST_KEY}" "InstallSource" "$EXEDIR"
  WriteRegDWORD SHCTX  "${PRODUCT_UNINST_KEY}" "NoModify" 1
  WriteRegDWORD SHCTX  "${PRODUCT_UNINST_KEY}" "NoRepair" 1

  DetailPrint "--------------------------------------------------------------------------------"
  ClearErrors
SectionEnd
;******************************************************************************
LangString MSG1 ${LANG_ENGLISH}   "$(^Name) was successfully removed from your computer."
LangString MSG2 ${LANG_ENGLISH}   "${PRODUCT_EXE} could not be closed.$\r$\nTry again?"
LangString MSG3 ${LANG_ENGLISH}   "Are you sure you want to completely remove $(^Name) and all of its components?"
LangString MSG4 ${LANG_ENGLISH}   "$(^Name) application"
LangString MSG5 ${LANG_ENGLISH}   "Unable to create $INSTDIR"
;******************************************************************************
Function un.onInit
  !insertmacro MULTIUSER_UNINIT
  StrCpy $USER 0
  UserInfo::GetName
  Pop $USER

  ${GetTime} "" "L" $0 $1 $2 $3 $4 $5 $6

#  LogSet on
  DetailPrint "--------------------------------------------------------------------------------"
  DetailPrint "Uninstall start $2-$1-$0 $4:$5:$6 user:$USER ($MultiUser.Privileges)"
  DetailPrint "--------------------------------------------------------------------------------"

  MessageBox MB_ICONQUESTION|MB_YESNO|MB_DEFBUTTON2 $(MSG3) /SD IDYES IDYES +2
  Abort
FunctionEnd
;******************************************************************************
Function un.onUninstSuccess
  HideWindow
  MessageBox MB_ICONINFORMATION|MB_OK $(MSG1) /SD IDOK
  DetailPrint "--------------------------------------------------------------------------------"
  DetailPrint "*** Uninstall finish OK ***"
  DetailPrint "--------------------------------------------------------------------------------"
FunctionEnd
;******************************************************************************
Function un.onUninstFailed
  DetailPrint "--------------------------------------------------------------------------------"
  DetailPrint "*** Uninstall finish FAILED ***"
  DetailPrint "--------------------------------------------------------------------------------"
FunctionEnd
;******************************************************************************
Section Uninstall
  DetailPrint "--------------------------------------------------------------------------------"
  DeleteRegKey SHCTX  "${PRODUCT_UNINST_KEY}"
  DeleteRegKey SHCTX  "${PRODUCT_DIR_REGKEY}"

!insertmacro MUI_STARTMENU_GETFOLDER "Application" $ICONS_GROUP
  RmDir /r "$SMPROGRAMS\$ICONS_GROUP"
  Delete /REBOOTOK "$INSTDIR\${PRODUCT_EXE}"
  Delete /REBOOTOK "$INSTDIR\zint.exe"
  Delete /REBOOTOK "$INSTDIR\uninst.exe"
  Delete /REBOOTOK "$INSTDIR\install.log"
  RmDir /REBOOTOK "$INSTDIR"
SectionEnd
;******************************************************************************
VIProductVersion ${PRODUCT_VERSION}
VIAddVersionKey /LANG=${LANG_ENGLISH} "ProductName" "${PRODUCT_NAME}"
VIAddVersionKey /LANG=${LANG_ENGLISH} "CompanyName" "${PRODUCT_PUBLISHER}"
VIAddVersionKey /LANG=${LANG_ENGLISH} "FileDescription" "${PRODUCT_NAME} Setup"
VIAddVersionKey /LANG=${LANG_ENGLISH} "FileVersion" "${PRODUCT_VERSION}"
VIAddVersionKey /LANG=${LANG_ENGLISH} "LegalCopyright" "Copyright � 2020 Robin Stuart & BogDan Vatra"
VIAddVersionKey /LANG=${LANG_ENGLISH} "License" "GNU General Public License version 3"
VIAddVersionKey /LANG=${LANG_ENGLISH} "WWW" "${PRODUCT_WEB_SITE}"
;******************************************************************************
