# kyoyoZemi2025

ダイナミクセルMx28を動かすためのサンプルプログラムです．
Windowsで動かすことを想定しています．

## 環境設定



## プログラムの実行

### 通信のテストプログラムのコンパイルと実行
ターミナルにてプログラムファイルと同じ階層にて，以下のコマンドを売ってください．
'''
g++ -o testComm.exe  main_test_commSpeed.cpp  serial.cpp  amBasic.cpp  -lstdc++
'''

### 制御サンプルプログラムのコンパイルと実行
ターミナルにてプログラムファイルと同じ階層にて，以下のコマンドを売ってください．
'''
g++ -o testComm.exe  main_test_ctrLoop.cpp  serial.cpp  amBasic.cpp  -lstdc++
'''


