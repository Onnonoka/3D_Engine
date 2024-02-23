@echo off

set BUILD_DIR=build

if "%1%"=="release" (
    cd %BUILD_DIR%\bin\Release\
    start OpenGLProject.exe
) else (
    cd %BUILD_DIR%\bin\Debug\
    if "%1%" == "--gdb" (
        gdb OpenGLProject.exe
    ) else (
        start OpenGLProject.exe
    )
)