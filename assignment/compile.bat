@ECHO OFF

IF NOT EXIST ".\bin\i686-elf-tools\" (
	IF NOT EXIST ".\bin\i686-elf-tools-windows.zip" (
		ECHO downloading toolchain...
		.\bin\wget.exe -P .\bin\ "https://github.com/lordmilko/i686-elf-tools/releases/download/7.1.0/i686-elf-tools-windows.zip"
	)

	ECHO decompressing toolchain...
	.\bin\7za.exe x bin\i686-elf-tools-windows.zip -o.\bin\i686-elf-tools\ -y
)

IF NOT EXIST "%PROGRAMFILES%\qemu\" (
	IF NOT EXIST ".\bin\qemu-w64-setup-20181211.exe" (
		ECHO downloading QEMU...
		.\bin\wget.exe -P .\bin\ "https://qemu.weilnetz.de/w64/qemu-w64-setup-20181211.exe"
	)

	ECHO installing QEMU...
	ECHO please use the default installation path '%PROGRAMFILES%\qemu\' or modify this script
	.\bin\qemu-w64-setup-20181211.exe
	PAUSE

	IF NOT EXIST "%PROGRAMFILES%\qemu\" (
		ECHO unable to find QEMU at '%PROGRAMFILES%\qemu\'
		PAUSE
		EXIT
	)
)

ECHO updating PATH variable...
SET PATH=%PATH%;%PROGRAMFILES%\qemu

ECHO compiling...
.\bin\make.exe run
