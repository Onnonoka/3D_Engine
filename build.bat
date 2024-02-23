@echo off

set BUILD_DIR=build

:: Création du répertoire de build s'il n'existe pas
if not exist %BUILD_DIR% mkdir %BUILD_DIR%

:: Création du répertoire de build/temp s'il n'existe pas
if not exist %BUILD_DIR%/temp mkdir %BUILD_DIR%/temp

:: Configuration du build en fonction de l'argument passé
if "%1"=="release" (
    cmake -S . -B %BUILD_DIR%/temp -DCMAKE_BUILD_TYPE=Release
    cmake --build %BUILD_DIR%/temp
) else (
    cmake -S . -B %BUILD_DIR%/temp -DCMAKE_BUILD_TYPE=Debug
    cmake --build %BUILD_DIR%/temp
)
