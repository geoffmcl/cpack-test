@setlocal
@set TMPRPJ=test-cpack
@set TMPLOG=bldlog-1.txt
@set TMPSRC=F:\Projects\test-cpack
@set TMPINST=F:\Projects\install\msvc100\test-cpack
@if NOT EXIST %TMPSRC%\CMakeLists.txt goto NOCM
@set TMPOPTS=
@set TMPOPTS=%TMPOPTS% -DCMAKE_INSTALL_PREFIX=%TMPINST%

@call setupqt32

@echo %TMPSRC% %DATE% %TIME% > %TMPLOG%

cmake %TMPSRC% %TMPOPTS% >> %TMPLOG% 2>&1
@if ERRORLEVEL 1 goto ERR1

cmake --build . --config Debug >> %TMPLOG% 2>&1
@if ERRORLEVEL 1 goto ERR2

cmake --build . --config Release >> %TMPLOG% 2>&1
@if ERRORLEVEL 1 goto ERR3

@echo Appear successful...  >> %TMPLOG% 2>&1
@echo Appear successful...
@echo.
@echo *** Continue with install? to %TMPINST%
@echo.
@pause

cmake --build . --config Debug --target INSTALL >> %TMPLOG% 2>&1
@if ERRORLEVEL 1 goto ERR4

cmake --build . --config Release --target INSTALL >> %TMPLOG% 2>&1
@if ERRORLEVEL 1 goto ERR5

@fa4 " -- " %TMPLOG%

@goto END

:NOCM
@echo Can NOT find %TMPSRC%\CMakeLists.txt! *** FIX ME ***
@goto END

:ERR1
@echo cmake config gen ERROR!
@goto END

:ERR2
@echo cmake build Debug ERROR!
@goto END

:ERR3
@echo cmake build Release ERROR!
@goto END

:ERR4
@echo install debug ERROR!
@goto END

:ERR5
@echo install release ERROR!
@goto END

:END
