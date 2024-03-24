# ROS

## 一，ros环境配置

终端输入

```shell
wget http://fishros.com/install -O fishros && . fishros
```

ros相关笔记网站

http://www.autolabor.com.cn/book/ROSTutorials/

https://blog.csdn.net/qq_59657502/article/details/128657345?app_version=6.3.0&code=app_1562916241&csdn_share_tail=%7B%22type%22%3A%22blog%22%2C%22rType%22%3A%22article%22%2C%22rId%22%3A%22128657345%22%2C%22source%22%3A%222301_79695159%22%7D&uLinkId=usr1mkqgl919blen&utm_source=app

## 二，ros简介

ROS=通信+工具+功能+生态

通信：数据传输

工具：例如仿真

功能：官网上有封装，好多时候只是调参

生态： ROS想当老大哈哈哈哈 

ROS是分布式框架

一个可执行文件是一个节点

ros是元操作系统

## 三，使用VScode建立工作空间流程

```shell
终端输入
mkdir -p 工作空间名称/src(必须得有 src)
cd 工作空间名称
catkin_make
code .

现在已到达VScode界面
src文件右击，在菜单中选择create catkin package
设置功能包名，及所需依赖项（依赖通常为roscpp rospy std_msgs）、

Ctrl+Shift+B，上方弹出菜单，catkin_make:build一项点击后方小齿轮即出现tasks.json文件
将tasks.json改成

{
	// 有关 tasks.json 格式的文档，请参见
		// https://go.microsoft.com/fwlink/?LinkId=733558
		"version": "2.0.0",
		"tasks": [
			{
				"label": "catkin_make:debug", //代表提示的描述性信息
				"type": "shell",  //可以选择shell或者process,如果是shell代码是在shell里面运行一个命令，如果是process代表作为一个进程来运行
				"command": "catkin_make",//这个是我们需要运行的命令
				"args": ["-DCMAKE_EXPORT_COMPILE_COMMANDS=1"],//如果需要在命令后面加一些后缀，可以写在这里，比如-DCATKIN_WHITELIST_PACKAGES=“pac1;pac2”
				"group": {"kind":"build","isDefault":true},
				"presentation": {
					"reveal": "always"//可选always或者silence，代表是否输出信息
				},
				"problemMatcher": "$msCompile"
			}
		]
	}
这样每次都可Ctrl+Shift+B编译

功能包下建立launch文件夹，并生成.launch文件，可一次性运行多个节点
在工作空间的终端运行
source ./devel/setup.bash
在此终端执行roslaunch 功能包名 .launch名
即可运行

完毕！！！！！！！！！！！！！！！！！！！！完毕！！！！！！！！！！！！！！！！！！！！！！！！！！！！！完毕
```

## 三，避坑！！！

```shell
执行roslaunch helloworld start.launch后
报错：
RLException: [start.launch] is neither a launch file in package [helloworld] nor is [helloworld] a launch file name
The traceback for the exception was written to the log file
原因是没有在工作空间执行
source ./devel/setup.bash
注意：
只能在同一终端执行roslaunch
```



