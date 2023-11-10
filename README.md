# QT版本

Qt 6.5.2 MinGW 64-bit（现在版本里的套件都比较完善，不需要再额外下载其它的编译器，默认即可）。

# 包含文件及说明

qtnew文件夹包含：qt工程文件（qtnew.pro）、一些初步的cpp头文件和源文件、一个测试用的Excel文件~~以及三个当时用的==机器人API文件（include、lib、thirdParty）==。三个API文件目前可以删除，但要记得在qt工程文件中删掉一些代码（主要是==includePath==和==link lib==之类的代码）~~。

# 功能说明

~~==utilities.cpp==和==utilities.h==文件也是有关机器人API调用的，可删除。~~

目前有主界面mainwindow和跟踪界面track。

在主界面的菜单栏点击action-->simulation后可跳转到跟踪界面。在跟踪界面点击Import Data后能够读取Excel文件中的数据。（读取Excel文件需要安装额外的库，我记得在安装程序中是可选的，稍后详细说明）