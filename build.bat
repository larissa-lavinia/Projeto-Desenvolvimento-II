@echo off
setlocal

cd /d "%~dp0"

echo ==========================================
echo       ENEM PROJETO - BUILD
echo ==========================================
echo.

if not exist build (
    mkdir build
)

echo [1/2] Configurando CMake...
cmake -S . -B build

if errorlevel 1 (
    echo.
    echo [ERRO] Falha ao configurar o projeto.
    pause
    exit /b 1
)

echo.
echo [2/2] Compilando...
cmake --build build --config Release

if errorlevel 1 (
    echo.
    echo [ERRO] Falha na compilacao.
    pause
    exit /b 1
)

echo.
echo ==========================================
echo       BUILD CONCLUIDA
echo ==========================================
echo.

start "" "build\Release\ENEMzandia.exe"

endlocal