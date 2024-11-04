@echo off
::作者：金宪均
::时间：2021年12月01日
::作用：清除编译产生的文件减小文件大小
::del *.map /s
del *.crf /s
del *.d /s
del *.o /s
del *.htm /s
del *.lnp /s
del *.sct /s
del *.dep /s
del *.Bak /s
del *.iex /s
del JLinkLog.txt /s
exit