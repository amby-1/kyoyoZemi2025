# kyoyoZemi2025

ダイナミクセルMx28を動かすためのサンプルプログラムです．
Windowsで動かすことを想定しています．

## 事前準備
以下の2つのソフトウェアを入れてください．

### ダイナミクセルウィザード
こちらのサイトに従って，ダイナミクセルウィザードをインストールしてください．
このソフトを使えば，ダイナミクセルを簡単に動かすことができます．
https://emanual.robotis.com/docs/en/software/dynamixel/dynamixel_wizard2/

ソフトウェアの使い方などは，日本語だと以下のサイトがまとまっています．
https://www.besttechnology.co.jp/modules/knowledge/?DYNAMIXEL%20basic%20tutorial#q270593c

使い方は最小限は授業中に教えますので，インストールまでできればOKです．

### C++プログラミング環境

C++言語のプログラムを作成・実行できる環境を作ってください．やり方は問いません．
このページでは，VS Code＋GCC with MinGWというやり方を紹介します．

以下の，マイクロソフトの公式サイトの案内に従ってVSCODEとMinGWをインストールしてください．
https://code.visualstudio.com/docs/cpp/config-mingw
（Prerequisites，Installing the MinGW-w64 toolchain，Check your MinGW installation　の3つの節をやってください）


## ダイナミクセルを動かすためのハードウェアの準備

ＵＳＢダイナミクセルをＰＣに接続する．

ダイナミクセルウィザードを使って，ポートの確認を行う．


## プログラムの実行
ここに上がっているプログラム一式を任意のフォルダ内に保存．

通信ポートや，ダイナミクセルＩＤなどを変更する．


### 通信のテストプログラムのコンパイルと実行
ターミナルにてプログラムファイルと同じ階層にて，以下のコマンドを売ってください．
```bash
g++ -o testComm.exe  main_test_commSpeed.cpp  serial.cpp  amBasic.cpp  -lstdc++
```

### 制御サンプルプログラムのコンパイルと実行
ターミナルにてプログラムファイルと同じ階層にて，以下のコマンドを売ってください．
```bash
g++ -o testComm.exe  main_test_ctrLoop.cpp  serial.cpp  amBasic.cpp  -lstdc++
```


