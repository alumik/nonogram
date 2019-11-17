@echo off 
set /p var= <tool_build_number.txt 
set /a var= %var%+1 
echo %var% >tool_build_number.txt
cd ..
echo #ifndef BUILD_NUMBER_H>src\utils\util_build_number.h
echo #define BUILD_NUMBER_H>>src\utils\util_build_number.h
echo.>>src\utils\util_build_number.h
echo #define BUILD_NUMBER %var%>>src\utils\util_build_number.h
echo.>>src\utils\util_build_number.h
echo #endif // BUILD_NUMBER_H>>src\utils\util_build_number.h