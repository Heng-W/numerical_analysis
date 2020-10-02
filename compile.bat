@echo off
setlocal enabledelayedexpansion
set compile_cnt=0
set build_cnt=0
IF EXIST build (
    del build\*.exe
) else (
    md build
)
for %%i in (*.c) do (
	set source=%%i
	set target=build\!source:~0,-2!.exe
	set /a compile_cnt+=1
	echo No.!compile_cnt! compile !source!
	gcc -std=c99 -fexec-charset=gbk !source! -o !target!
	if exist !target! (set /a build_cnt+=1)
)
echo.
echo %build_cnt%/%compile_cnt% targets built successfully!
pause