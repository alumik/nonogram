@echo off 
set /p var= <tool_build_number.txt 
set /a var= %var%+1 
echo %var% >tool_build_number.txt
cd ..
echo #ifndef BUILD_NUMBER_H>util\util_build_number.h
echo #define BUILD_NUMBER_H>>util\util_build_number.h
echo.>>util\util_build_number.h
echo #define BUILD_NUMBER %var%>>util\util_build_number.h
echo.>>util\util_build_number.h
echo #endif // BUILD_NUMBER_H>>util\util_build_number.h