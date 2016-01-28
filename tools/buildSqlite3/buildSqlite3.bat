@echo off

REM this script builds sqlite3 if it doesn't already exist and places it in <ProjectRoot>\lib



REM set up visual studio command environment

call "C:\Program Files (x86)\Microsoft Visual Studio 14.0\VC\vcvarsall.bat" x86_amd64



REM create lib dir if it isn't already there
if not exist "%~dp0..\..\lib" mkdir "%~dp0..\..\lib"


REM make a .lib file if it isn't already there

if not exist "%~dp0..\..\lib\sqlite3.lib"  (lib /def:%~dp0\sqlite3.def /out:%~dp0..\..\lib\sqlite3.lib /machine:x86) else (echo SQLite3.lib already exists)

