REM this script builds sqlite3 if it doesn't already exist.
REM under linux try something like `apt-get install libsqlite3`

REM set up visual studio command environment
call "C:\Program Files (x86)\Microsoft Visual Studio 14.0\VC\vcvarsall.bat" x86_amd64

REM create lib directory
if not exist "%~dp0..\lib\" (mkdir "%~dp0..\lib\")

REM build sqlite3
if not exist "%~dp0..\lib\sqlite3.dll" (cl %~dp0..\include\sqlite3\sqlite3.c -link -dll -out:%~dp0..\lib\sqlite3.dll)

REM make a .lib file
if not exist "%~dp0..\lib\sqlite3.lib" (lib /out:%~dp0..\lib\sqlite3.lib %~dp0sqlite3.obj)

echo "SQLite3 has been build. Files are in <project root>/lib"
pause
