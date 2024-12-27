
set MATLAB=E:\matlab2023a\matlab

cd .

if "%1"=="" ("E:\matlab2023a\matlab\bin\win64\gmake"  -f AppMain.mk all) else ("E:\matlab2023a\matlab\bin\win64\gmake"  -f AppMain.mk %1)
@if errorlevel 1 goto error_exit

exit /B 0

:error_exit
echo The make command returned an error of %errorlevel%
exit /B 1