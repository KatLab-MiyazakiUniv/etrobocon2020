# etrobocon2020

## 環境構築

NOTE: Macで上手くいくかはわかりません。

### 前提条件
- WSL1 の Ubuntu18.04 をインストール済み
- [etroboパッケージ](https://github.com/ETrobocon/etrobo)をインストール済み
- `etrobo シミュレータ v1.0`をダウンロードしている

### 手順

#### 1. etrobo シミュレータ v1.0 にアップデートする

   すでに `etrobo シミュレータ v1.0` にアップデートしている人は、飛ばしてください。

   ##### 1.1 開発環境を起動し、VSCodeを開く

   ##### 1.2 エクスプローラからダウンロードした`etrobo シミュレータ v1.0`のファイル（例：`etrobosim2020_1.0_win.tar.gz`）があるディレクトリを開く
   
   ##### 1.3 `etrobo シミュレータ v1.0`のファイルを`dist`ディレクトリにコピーする

   <details><summary>【画像】詳しい手順を見るにはここをクリック！！！</summary><div>
   
   ![Update](docs/img/etrobo-update01.png)
   
   </div></details>
   
   ##### 1.4 アップデート

   念のため、開発環境のアップデートを行います

   ```
   $ cd ~/etrobo
   $ update
   ```

#### 2. リポジトリを`Fork`する

   <details><summary>【画像】詳しい手順を見るにはここをクリック！！！</summary><div>

   ![Fork手順01](docs/img/github-fork01.png)

   ![Fork手順02](docs/img/github-fork02.png)

   ![Fork手順03](docs/img/github-fork03.png)

   ![Fork手順04](docs/img/github-fork04.png)

   </div></details>

#### 3. etrobo/workspace/ に `Fork`先のetrobocon2020 を配置する 

   ```
   $ cd ~/etrobo/workspace
   $ git clone https://github.com/[自分のGitHubユーザ名]/etrobocon2020.git
   ```
   ※）`https://github.com/[自分のGitHubユーザ名]/etrobocon2020.git`の部分は先ほどコピーしたURLを使う。


## ビルド方法

  etrobocon2020 ディレクトリで以下のコマンドを実行する  
  `./make.sh sim up`

  または、etrobo ディレクトリで以下のコマンドを実行する  
  `make app=etrobocon2020 sim up`

## Google Test の実行方法

`~/etrobo/workspace/etrobocon2020`にある`gtest_all.sh`ファイルを実行することで、 Google Test を実行できます。

```
$ cd ~/etrobo/workspace/etrobocon2020
$ ./gtest_all.sh
```

#### **!!** エラーが発生した場合
- `cmake`をインストールしていない場合

   以下のようなエラーが発生した際は、`sudo apt install cmake`を実行して`cmake`をインストールした後、もう一度`gtest_all.sh`ファイルを実行してください。

   ```
   ./test/gtest/gtest_build.sh: 9: ./test/gtest/gtest_build.sh: cmake: not found
   ```

TODO: 後で整備する
