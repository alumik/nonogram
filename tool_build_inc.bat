@echo off 
set /p var= <tool_build_number.txt 
set /a var= %var%+1 
echo %var% >tool_build_number.txt
echo #ifndef BUILD_NUMBER_H>util_build_number.h
echo #define BUILD_NUMBER_H>>util_build_number.h
echo.>>util_build_number.h
echo #define BUILD_NUMBER %var%>>util_build_number.h
echo.>>util_build_number.h
echo #endif // BUILD_NUMBER_H>>util_build_number.h