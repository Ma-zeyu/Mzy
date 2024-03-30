# ROS1

## 一，ros环境配置

终端输入

```shell
wget http://fishros.com/install -O fishros && . fishros
```

ros相关笔记网站

http://www.autolabor.com.cn/book/ROSTutorials/

https://blog.csdn.net/qq_59657502/article/details/128657345?app_version=6.3.0&code=app_1562916241&csdn_share_tail=%7B%22type%22%3A%22blog%22%2C%22rType%22%3A%22article%22%2C%22rId%22%3A%22128657345%22%2C%22source%22%3A%222301_79695159%22%7D&uLinkId=usr1mkqgl919blen&utm_source=app

## 二，对ros的认识

ROS=通信+工具+功能+生态

通信：数据传输

工具：例如仿真

功能：官网上有封装，好多时候只是调参

生态： ROS想当老大哈哈哈哈 

ROS是分布式框架

一个可执行文件是一个节点

或者一个进程就是一个节点

ros是元操作系统

ros提供了好多内置函数接口，程序员只需要根据具体情况调整或改写函数体，但要保证函数接口不变

ros系统给单片机发出指令，单片机会根据指令控制机械结构

## 三，VScode下编写程序的全流程

```shell
终端输入
mkdir -p 工作空间名称/src(必须得有 src)
cd 工作空间名称
catkin_make
code .

现在已到达VScode界面

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

src文件右击，在菜单中选择create catkin package
设置功能包名，及所需依赖项（依赖通常为roscpp rospy std_msgs）、

src下写源文件，include下写头文件
编辑CMakeLists文件

终端启动ros核心：
终端输入roscore
功能包下建立launch文件夹，并生成.launch文件，可一次性运行多个节点
在工作空间的终端运行
source ./devel/setup.bash
在此终端执行roslaunch 功能包名 .launch名
即可运行

完毕！！！！！！！！！！！！！！！！！！！！完毕！！！！！！！！！！！！！！！！！！！！！！！！！！！！！完毕
```

## 四，避坑！！！

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



VScode在下载插件时，可能会出现 ‘‘提取扩展时出错。XHR failed”，原因很简单，网络问题，关闭外网，重新下载即可

## 五，ros文件命令

#### 1.增

catkin_create_pkg 自定义包名 依赖包 === 创建新的ROS功能包

sudo apt install xxx === 安装 ROS功能包

#### 2.删

sudo apt purge xxx ==== 删除某个功能包

#### 3.查

rospack list === 列出已安装所有功能包

rospack find 包名 === 查找某个功能包是否存在，如果存在返回安装路径

roscd 包名 === 进入某个功能包

rosls 包名 === 列出某个包下的文件

apt search xxx === 在网络上搜索某个功能包

#### 4.改

rosed 包名 文件名 === 修改功能包文件

需要安装 vim

**比如:**rosed turtlesim Color.msg

#### 5.执行

##### 5.1roscore

**roscore ===** 是 ROS 的系统先决条件节点和程序的集合， 必须运行 roscore 才能使 ROS 节点进行通信。

订阅roscore 将启动:

- ros master
- ros 参数服务器
- rosout 日志节点

用法:

```
roscore
Copy
```

或(指定端口号)

```
roscore -p xxxx
Copy
```

##### 5.2rosrun

**rosrun 包名 可执行文件名** === 运行指定的ROS节点

**比如:**`rosrun turtlesim turtlesim_node`

##### 5.3roslaunch

**roslaunch 包名 launch文件名** === 执行某个包下的 launch 文件

## 六，节点图

先打开roslaunch

再在终端执行rqt_graph

可显示节点图

## 七，通信机制订阅

### 话题通迅（发布订阅模式）

**适用**：用于不断更新的、少逻辑处理的数据传输场景。

原理图：01话题通信模型.jpg

注意：连接建立后，Talker 开始向 Listener 发布消息。

> 注意1:上述实现流程中，前五步使用的 RPC协议，最后两步使用的是 TCP 协议
>
> 注意2: Talker 与 Listener 的启动无先后顺序要求
>
> 注意3: Talker 与 Listener 都可以有多个
>
> 注意4: Talker 与 Listener 连接建立后，不再需要 ROS Master（管理匹配话题）。也即，即便关闭ROS Master，Talker 与 Listern 照常通信。

关注点： 0.大部分实现已被封装

​		1.关注话题设置

​		2.关注订阅者实现

​		3.关注发布者实现

​		4.关注消息载体（二者通讯时使用的数据）

流程：1.编写发布方实现

​	    2.编写订阅方实现

​            3.编辑配置文件

​	    4.编译并执行

具体实现：

​	发布方：

​		1.包含头文件 

```cpp
#include "ros/ros.h"
#include "std_msgs/String.h"//存储数据类型的头文件
```

​		2.初始化 ROS 节点:命名(唯一)

```cpp
ros::init(argc, argv, "节点名称");
```

​       	 3.实例化 ROS 句柄

```cpp
ros::NodeHandle nh;
```

​        	4.实例化发布者对象

```cpp
ros::Publisher pub = nh.advertise<std_msgs::String>("fang", 10);
//泛型类型取决于话题名称
//参数分别为话题名称， 队列长度（缓冲区长度）
```

 	      5.组织被发布的数据，并编写逻辑发布数据

```cpp
while(ros::ok()){       //通常采用循环发消息，条件为ros::ok()
        msg.data = "hello";//消息   ros中，通过.data访问变量中的内容
        pub.publish(msg);//发送
    }
```



```cpp
//使用stringstream拼接字符串与编号
std::stringstream ss;
ss << msg_front << count;
msg.data =ss.str();//将其中的数字转换成字符串
```

```cpp
//传输效率
ros::Rate r(1);

//在while循环中使用
r.sleep;
```

​	接收方：

```cpp
/*
    需求: 实现基本的话题通信，一方发布数据，一方接收数据，
         实现的关键点:
         1.发送方
         2.接收方
         3.数据(此处为普通文本)


    消息订阅方:
        订阅话题并打印接收到的消息

    实现流程:
        1.包含头文件 
        2.初始化 ROS 节点:命名(唯一)
        3.实例化 ROS 句柄
        4.实例化 订阅者 对象
        5.处理订阅的消息(回调函数)
        6.设置循环调用回调函数

*/
// 1.包含头文件 
#include "ros/ros.h"
#include "std_msgs/String.h"

void doMsg(const std_msgs::String::ConstPtr& msg_p){
    ROS_INFO("我听见:%s",msg_p->data.c_str());
    // ROS_INFO("我听见:%s",(*msg_p).data.c_str());
}
int main(int argc, char  *argv[])
{
    setlocale(LC_ALL,"");
    //2.初始化 ROS 节点:命名(唯一)
    ros::init(argc,argv,"listener");
    //3.实例化 ROS 句柄
    ros::NodeHandle nh;

    //4.实例化 订阅者 对象
    ros::Subscriber sub = nh.subscribe<std_msgs::String>("chatter",10,doMsg);
    //5.处理订阅的消息(回调函数)

    // 6.设置循环调用回调函数
    ros::spin();//循环读取接收的数据，并调用回调函数处理  一定要写！！！调用回调函数

    return 0;
}

```

执行：

1.启动 roscore;

2.启动发布节点;     不要忘source ./devel/setup.bash      rosrun 包名 节点名

3.启动订阅节点。

4.可以查看节点图观察

### 话题通信自定义msg

相当于结构体

#### 1.定义msg文件

功能包下新建 msg 目录，添加文件 Person.msg

```cpp
string name
uint16 age
float64 height
```

#### 2.编辑配置文件

**package.xml**中添加编译依赖与执行依赖

```xml
  <build_depend>message_generation</build_depend>
  <exec_depend>message_runtime</exec_depend>
  <!-- 
  exce_depend 以前对应的是 run_depend 现在非法
  -->
```

**CMakeLists.txt**编辑 msg 相关配置

```CMAke
#编译时依赖
find_package(catkin REQUIRED COMPONENTS
  roscpp
  rospy
  std_msgs
  message_generation
)
# 需要加入 message_generation,必须有 std_msgs

## 配置 msg 源文件
add_message_files(
  FILES
  Person.msg
)

# 生成消息时依赖于 std_msgs
generate_messages(
  DEPENDENCIES
  std_msgs
)

#执行时依赖
catkin_package(
#  INCLUDE_DIRS include
#  LIBRARIES demo02_talker_listener
  CATKIN_DEPENDS roscpp rospy std_msgs message_runtime
#  DEPENDS system_lib
)

```

#### 3.编译

**编译后的中间文件查看:**

C++ 需要调用的中间文件(.../工作空间/devel/include/包名/xxx.h)

![img](http://www.autolabor.com.cn/book/ROSTutorials/assets/05vscode_%E8%87%AA%E5%AE%9A%E4%B9%89%E6%B6%88%E6%81%AF%E7%9A%84%E4%B8%AD%E9%97%B4%E6%96%87%E4%BB%B6%28C++%29.PNG)

#### 4.配置VScode

在c_cpp_properies.json 文件中添加生成的头文件目录 "includePath": （生成的msg头文件路径）

#### 4.使用

#### 监视是否发出

 ```shell
 cd 工作空间
 rostopic
 ```

订阅方要定义回调函数，发布方不需要回调函数

## 避坑！！！

```shell
Invoking "make cmake_check_build_system" failed
```

解决方法:

检查CMAke中add_dependencies指令，第一个参数应该是可执行文件的名称

或者是因为可执行文件名冲突

```shell\
[rospack] Error: package 'plumbing_pub_sub' not found
```

```shell
ERROR: Unable to load type [xxx]
```

解决办法：**执行source ./devel/setup.bash**（不要忘啊啊啊啊啊啊啊）//这一步是在临时修改环境变量

ROS::INFO输出字符时，要转换成C风格的字符串

```cpp
//使用
p.name.c_str()
ROS::INFO是格式化输出，符合C语言风格
```

先编译msg文件，再编译源文件

订阅方和请求方通过相同的话题产生关联

### 服务通信（**请求响应**）

适用：适用于对时时性有要求、具有一定逻辑处理的应用场景。

客户端和服务端通过相同的话题产生关联

客户端和服务端要先在ROS Master中注册信息

要保证客户端发起请求时，服务端已经启动（发布订阅模式不需要）

服务端和客户端都可以有多个

关注点：

0.流程已经被封装，直接调用即可

1.话题一致

2.服务端具体实现需要程序员完成

3.客户端具体实现需要程序员完成

4.数据载体（可能自定义）

### srv文件的创建

srv文件中=请求+响应

#### 1.定义srv文件

先在功能包下建立srv文件夹，在其下面创建.srv文件

服务通信中，数据分成两部分，请求与响应，在 srv 文件中请求和响应使用`---`分割，具体实现如下:

功能包下新建 srv 目录，添加 xxx.srv 文件，内容:

```
# 客户端请求时发送的两个数字
int32 num1
int32 num2
---
# 服务器响应发送的数据
int32 sum
Copy
```

#### 2.编辑配置文件

**package.xml**中添加编译依赖与执行依赖

```xml
  <build_depend>message_generation</build_depend>
  <exec_depend>message_runtime</exec_depend>
  <!-- 
  exce_depend 以前对应的是 run_depend 现在非法
  -->
Copy
```

**CMakeLists.txt**编辑 srv 相关配置

```
find_package(catkin REQUIRED COMPONENTS
  roscpp
  rospy
  std_msgs
  message_generation
)
# 需要加入 message_generation,必须有 std_msgs
Copy
add_service_files(
  FILES
  AddInts.srv
)
Copy
generate_messages(
  DEPENDENCIES
  std_msgs
)
Copy
```

注意: 官网没有在 catkin_package 中配置 message_runtime,经测试配置也可以

#### 3.编译

编译后的中间文件查看:

C++ 需要调用的中间文件(.../工作空间/devel/include/包名/xxx.h)

![img](http://www.autolabor.com.cn/book/ROSTutorials/assets/07vscode_%E8%87%AA%E5%AE%9A%E4%B9%89%E6%B6%88%E6%81%AF%E7%9A%84%E4%B8%AD%E9%97%B4%E6%96%87%E4%BB%B6%28C++%29.PNG)

#### 4.配置VScode

在c_cpp_properies.json 文件中添加生成的头文件目录 "includePath": （生成的srv头文件路径）

PS：/**是指逐层向下查找 

#### 5.使用

```cpp
/*
    需求: 
        编写两个节点实现服务通信，客户端节点需要提交两个整数到服务器
        服务器需要解析客户端提交的数据，相加后，将结果响应回客户端，
        客户端再解析

    服务器实现:
        1.包含头文件
        2.初始化 ROS 节点
        3.创建 ROS 句柄
        4.创建 服务 对象
        5.回调函数处理请求并产生响应
        6.由于请求有多个，需要调用 ros::spin()

*/
#include "ros/ros.h"
#include "demo03_server_client/AddInts.h"

// bool 返回值由于标志是否处理成功     这个回调函数的返回值只能是bool型
bool doReq(demo03_server_client::AddInts::Request& req,
          demo03_server_client::AddInts::Response& resp){
    int num1 = req.num1;
    int num2 = req.num2;

    ROS_INFO("服务器接收到的请求数据为:num1 = %d, num2 = %d",num1, num2);

    //逻辑处理
    if (num1 < 0 || num2 < 0)
    {
        ROS_ERROR("提交的数据异常:数据不可以为负数");
        return false;
    }

    //如果没有异常，那么相加并将结果赋值给 resp
    resp.sum = num1 + num2;
    return true;


}

int main(int argc, char *argv[])
{
    setlocale(LC_ALL,"");
    // 2.初始化 ROS 节点
    ros::init(argc,argv,"AddInts_Server");
    // 3.创建 ROS 句柄
    ros::NodeHandle nh;
    // 4.创建 服务 对象
    ros::ServiceServer server = nh.advertiseService("AddInts",doReq);
    ROS_INFO("服务已经启动....");
    //     5.回调函数处理请求并产生响应
    //     6.由于请求有多个，需要调用 ros::spin()
    ros::spin();
    return 0;
}

```

服务方要定义回调函数，客户端不需要

```cpp
/*
    需求: 
        编写两个节点实现服务通信，客户端节点需要提交两个整数到服务器
        服务器需要解析客户端提交的数据，相加后，将结果响应回客户端，
        客户端再解析

    服务器实现:
        1.包含头文件
        2.初始化 ROS 节点
        3.创建 ROS 句柄
        4.创建 客户端 对象
        5.请求服务，接收响应

*/
// 1.包含头文件
#include "ros/ros.h"
#include "demo03_server_client/AddInts.h"

int main(int argc, char *argv[])
{
    setlocale(LC_ALL,"");

    // 调用时动态传值,如果通过 launch 的 args 传参，需要传递的参数个数 +3
    if (argc != 3)
    // if (argc != 5)//launch 传参(0-文件路径 1传入的参数 2传入的参数 3节点名称 4日志路径)
    {
        ROS_ERROR("请提交两个整数");
        return 1;
    }


    // 2.初始化 ROS 节点
    ros::init(argc,argv,"AddInts_Client");
    // 3.创建 ROS 句柄
    ros::NodeHandle nh;
    // 4.创建 客户端 对象
    ros::ServiceClient client = nh.serviceClient<demo03_server_client::AddInts>("AddInts");
    //等待服务启动成功
    //方式1
    ros::service::waitForService("AddInts");
    //方式2
    // client.waitForExistence();
    // 5.组织请求数据
    demo03_server_client::AddInts ai;
    ai.request.num1 = atoi(argv[1]);
    ai.request.num2 = atoi(argv[2]);
    // 6.发送请求,返回 bool 值，标记是否成功
    bool flag = client.call(ai);
    // 7.处理响应
    if (flag)
    {
        ROS_INFO("请求正常处理,响应结果:%d",ai.response.sum);
    }
    else
    {
        ROS_ERROR("请求处理失败....");
        return 1;
    }

    return 0;
}

```

**注意:**

如果先启动客户端，那么会导致运行失败

**优化:**

在客户端发送请求前添加:`client.waitForExistence();`(client是客户端名称)

或:`ros::service::waitForService("AddInts");`(AddInts是话题名称)

这是一个阻塞式函数，只有服务启动成功后才会继续执行

此处可以使用 launch 文件优化，但是需要注意 args 传参特点

### 参数服务器

参数服务器相当于是独立于所有节点的一个公共容器，可以将数据存储在该容器中，被不同的节点调用，当然不同的节点也可以往其中存储数据

相当于C++中全局变量

实现参数增删改查操作

注意:参数服务器不是为高性能而设计的，因此最好用于存储静态的非二进制的简单数据

个人理解的句柄就是ros Master

```cpp
//参数新增
//1.使用NodeHandle类
		ros::NodeHandle nh;
		nh.setParam("key", valua);
//2.使用ros::param命名空间
		ros::param::set("key", valua);

//修改与上述一样，key要是之前定义好的，值会被覆盖

//参数查询
//1.使用NodeHandle类
		param(键,默认值)   
            存在，返回对应结果，否则返回默认值
			int radius = nh.param("radius", 0.5);
 		getParam(键,存储结果的变量)
            存在,返回 true,且将值赋值给参数2
            如果键不存在，那么返回值为 false，且不为参数2赋值

        getParamCached(键,存储结果的变量)--提高变量获取效率
            存在,返回 true,且将值赋值给参数2
            若果键不存在，那么返回值为 false，且不为参数2赋值

        getParamNames(std::vector<std::string>)
            获取所有的键的名称,并存储在参数 vector 中 

        hasParam(键)
            是否包含某个键，存在返回 true，否则返回 false

        searchParam(参数1，参数2)
            搜索键，参数1是被搜索的键，参数2存储搜索结果的变量
//2.使用ros::param命名空间
    	ros::param ----- 与 NodeHandle 类似

//参数删除
//1.使用NodeHandle类
        deleteParam("键")
        根据键删除参数，删除成功，返回 true，否则(参数不存在)，返回 false（是键的参数，不是键的本身）
//2.使用ros::param命名空间
        del("键")
        根据键删除参数，删除成功，返回 true，否则(参数不存在)，返回 false（是键的参数，不是键的本身）     
```

### 案例操作

```shell
roscore  启动ros核心
rosrun turtlesim  turtlesim_node  启动乌龟运动节点
rosrun turtlesim turtle_teleop_key 启动键盘控制
```

#### 一，让乌龟以固定速度运动

**实现流程:**

1. 通过计算图结合ros命令获取话题与消息信息。

   ```shell
   获取话题/turtle1/pose
   rqt_graph
   或者rostopic list
   
   获取消息类型(消息类型相当于自定义的srv与msg)turtlesim/Pose
   rostopic type /turtle1/cmd_vel    （/turtle1/cmd_vel是节点图箭头上面的文字）
   获取消息格式
   rosmsg info turtlesim/Pose 
   ```

   

2. 编码实现运动控制节点。

3. 启动 roscore、turtlesim_node 以及自定义的控制节点，查看运行结果。

PS：对运动的解释

​	线速度：x水平前后运动的速度

​                       y水平左右运动的速度（麦轮）

​			z垂直平面的速度

​	角速度：x翻滚角：机舱不动，机翼上下转动

​			y俯仰角：机翼不动，机舱上下转动

​			z偏航角水平转动

#### 二，实时获取乌龟位姿

##### 1.话题与消息获取

**获取话题:**/turtle1/pose

```shell
rostopic list
```

**获取消息类型:**turtlesim/Pose（位姿）

```shell
rostopic type  /turtle1/pose
```

**获取消息格式:**

```shell
rosmsg info turtlesim/Pose
```

**响应结果:**

```shell
float32 x
float32 y
float32 theta
float32 linear_velocity
float32 angular_velocity
```

简短认识：不同话题表示不同情况

```cpp
/*  
    订阅小乌龟的位姿: 时时获取小乌龟在窗体中的坐标并打印
    准备工作:
        1.获取话题名称 /turtle1/pose
        2.获取消息类型 turtlesim/Pose
        3.运行前启动 turtlesim_node 与 turtle_teleop_key 节点

    实现流程:
        1.包含头文件
        2.初始化 ROS 节点
        3.创建 ROS 句柄
        4.创建订阅者对象
        5.回调函数处理订阅的数据
        6.spin
*/

#include "ros/ros.h"
#include "turtlesim/Pose.h"

void doPose(const turtlesim::Pose::ConstPtr& p){
    ROS_INFO("乌龟位姿信息:x=%.2f,y=%.2f,theta=%.2f,lv=%.2f,av=%.2f",
        p->x,p->y,p->theta,p->linear_velocity,p->angular_velocity
    );
}

int main(int argc, char *argv[])
{
    setlocale(LC_ALL,"");
    // 2.初始化 ROS 节点
    ros::init(argc,argv,"sub_pose");
    // 3.创建 ROS 句柄
    ros::NodeHandle nh;
    // 4.创建订阅者对象
    ros::Subscriber sub = nh.subscribe<turtlesim::Pose>("/turtle1/pose",1000,doPose);
    // 5.回调函数处理订阅的数据
    // 6.spin
    ros::spin();
    return 0;
}

```

