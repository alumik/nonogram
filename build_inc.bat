@echo off 
set /p var= <build.txt 
set /a var= %var%+1 
echo %var% >build.txt
echo #define BUILD %var% //编译次数总计>build.h
echo %var%