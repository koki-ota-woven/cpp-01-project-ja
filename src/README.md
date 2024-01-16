# テキストベースのドライブアドベンチャーゲーム
このプロジェクトは、C++で作成されたテキストベースのドライビングゲームです。プレイヤーはコマンドを入力して街の中を走行することができます。

## ゲームのルール
- プレイヤーはコマンドを入力して操作します。
- プレイヤーは車を操作し、街の中を移動します。
- ゲームの目的は、街を探索しながらプレイヤーの目標に到達することです。

## インストールと実行方法
1. プロジェクトのリポジトリをクローンします。
```bash
git clone https://github.com/koki-ota-woven/cpp-01-project-ja.git
```


2. プロジェクトのディレクトリに移動します。
```bash
cd cpp-01-project-ja
````


3. ソースコードをコンパイルします。
    - GCCを使用する場合:
```bash
g++ -std=c++17 -o game src/main.cpp src/Player.cpp -lncurses
```

- Clangを使用する場合:
```bash
clang++ src/main.cpp src/Player.cpp -o game
```


4. ゲームを実行します。
```bash
./game
```


5. ゲームが起動し、コマンドの入力待ち状態になります。以下のコマンドを使って車を操作します。
   - `turn left`: 左折します。
   - `turn right`: 右折します。
   - `continue straight`: 直進します。
   - `accelerate`: 加速します。
   - `decelerate`: 減速します。
   - `stop`: 停止します。
   - `refuel`: 燃料を補給します。
   - `show info`: 現在の状態を表示します。
   - `exit`: ゲームを終了します。


6. ゲームを終了するには、`exit` コマンドを入力します。
