@echo off
SET mypath=%~dp0
cd %mypath:~0,-1%

for /f "tokens=2*" %%a in ('reg query "HKLM\System\CurrentControlSet\Control\Session Manager\Environment" /v PROCESSOR_ARCHITECTURE') do set "PROCESSOR_ARCHITECTURE=%%b"

echo WinPCAP NDIS6.0 driver installer
echo    architecture = %PROCESSOR_ARCHITECTURE% 
echo    system dir = %SystemRoot%
echo    current dir = %mypath:~0,-1%

echo Stopping service
net stop aegis
taskkill /F /IM aegis.exe /T

echo Removing files

del /f /q %SystemRoot%\system32\packet-ndis6.dll
del /f /q %SystemRoot%\system32\wpcap.dll
del /f /q %SystemRoot%\SysWOW64\packet-ndis6.dll
del /f /q %SystemRoot%\SysWOW64\wpcap.dll

if %PROCESSOR_ARCHITECTURE%  == x86 goto x86
:x64
echo Uninstalling drivers
x64\DriverInstaller.exe /uninstall
del /f /q %SystemRoot%\system32\pcap-ndis6.*

goto exit

:x86
echo Uninstalling drivers
x86\DriverInstaller.exe /uninstall
del /f /q %SystemRoot%\system32\pcap-ndis6.*

goto exit
:exit
echo Finished
