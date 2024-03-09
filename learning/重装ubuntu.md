# 重装ubuntu

## 一，卸载ubuntu

DiskGenius

不要忘记清理引导

## 二，clash

解压缩

运行cfw

改代理

HTTP HTTPS Socks 127.0.0.1 7890

FTP 空 0

## 三，typora

官网

```shell
sudo dpkg -i ....deb
```

## 四，搜狗输入法

官网

## 五，QQ

官网

```shell
sudo dpkg -i ....deb
```

## 六，git

````shell
sudo apt-get update
sudo apt-get install git
//验证
git --version
````

## 七，g++

```shell
//sudo apt-get update
sudo apt-get install g++
```

## 八，CMake

```shell
sudo apt update
sudo apt install cmake
```

## 九，fmt

```shell
sudo apt-get update
sudo apt-get install libfmt-dev
```

## 十，OpenCV

```shell
//sudo apt update
sudo apt install libopencv-dev
```

## 十一，eigen

```shell
//sudo apt-get update
sudo apt-get install libeigen3-dev
```

## 十二，sophus

```shell
git clone https://github.com/strasdat/Sophus.git
cd Sophus
mkdir build && cd build
cmake ..
make
sudo make install
```

## 十三，Clion

```shell
官网下载压缩包
tar -xzf ....gz
cd .../bin
./clion.sh   //启动
```

## 十四，解决ubuntu伪输出

```shell
sudo gedit  /etc/modprobe.d/alsa-base.conf 
文末加options snd-hda-intel dmic_detect=0
sudo gedit /etc/modprobe.d/blacklist.conf
文末加blacklist snd_soc_skl
重启
```

## 十五，locate 

```shell
sudo apt install mlocate
使用（定位文件）：
locate+文件名
```

## 十六，Google

```shell
官网下载Google Chrome安装包.deb
sudo dpkg -i ....deb
```

## 十七，tree

```cmake
sudo apt install tree
//树状输出
```

## 十八，安装pthread库

```shell
sudo apt install libpthread-stubs0-dev
```



