@echo off
echo Building ConvertZH plugin with proper encoding...

REM Set the code page to UTF-8
chcp 65001 >nul

REM Set environment variables for UTF-8 compilation
set _CL_=/utf-8
set _CXX_=/utf-8

echo Compiling with UTF-8 encoding...
msbuild ConvertZH.vcxproj /p:Configuration=Debug /p:Platform=x64 /p:CharacterSet=Unicode

if %ERRORLEVEL% EQU 0 (
    echo.
    echo Build successful!
    echo Plugin DLL location: Debug\ConvertZH.dll
) else (
    echo.
    echo Build failed! Check the error messages above.
)

pause
