@echo off
color 9c
echo 欢迎使用USB bootloader程序，该程序将引导您通过USB口完成固件的更新操作，更新前请确认当前目录下有bootloadhid.exe及用于更新的main.hex文件，请按屏幕提示操作。
echo 首先，请将目标板的PC2对地短接，然后将目标板跟电脑连接，等待电脑安装驱动程序，确认无误后按任意键进入更新程序。
pause
echo 正在更新固件，请稍候。。。。。。
bootloadhid -r main.hex
pause