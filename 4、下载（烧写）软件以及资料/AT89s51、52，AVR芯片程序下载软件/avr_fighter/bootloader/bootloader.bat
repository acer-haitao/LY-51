@echo off
color 9c
echo ��ӭʹ��USB bootloader���򣬸ó���������ͨ��USB����ɹ̼��ĸ��²���������ǰ��ȷ�ϵ�ǰĿ¼����bootloadhid.exe�����ڸ��µ�main.hex�ļ����밴��Ļ��ʾ������
echo ���ȣ��뽫Ŀ����PC2�Եض̽ӣ�Ȼ��Ŀ�����������ӣ��ȴ����԰�װ��������ȷ������������������³���
pause
echo ���ڸ��¹̼������Ժ򡣡���������
bootloadhid -r main.hex
pause