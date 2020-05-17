SETLOCAL

SET oldDir=%cd%

cd %~dp0

xcopy lib\glfw3\lib-vc2019\glfw3.dll bin\glfw3.dll* /Y

cd %oldDir%

ENDLOCAL