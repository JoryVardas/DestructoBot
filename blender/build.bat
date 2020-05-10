for /f %%f in ('dir /b ^| findstr /i .blend$') do blender_bin\blender %%f -P export.txt -- 0.2 0.2 0.6 exit


xcopy *.model ..\bin\data\ /Y