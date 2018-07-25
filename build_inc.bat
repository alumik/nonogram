@echo off 
set /p var= <build_number.txt 
set /a var= %var%+1 
echo %var% >build_number.txt
echo #ifndef BUILD_NUMBER_H>build_number.h
echo #define BUILD_NUMBER_H>>build_number.h
echo.>>build_number.h
echo #define BUILD_NUMBER %var%>>build_number.h
echo.>>build_number.h
echo #endif // BUILD_NUMBER_H>>build_number.h