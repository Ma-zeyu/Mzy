# Docker

## 零，安装及基础概念

安装参照[官网](https://docs.docker.com/engine/install/ubuntu/)

vscode 中安装 Docker 插件

镜像：类似软件包的概念，镜像中包含软件，所需环境，配置，系统函数库等

容器：运行镜像时，创建的独立环境

[镜像仓库](https://hub.docker.com/)：用于存储官方或个人创建的镜像 

## 一，Docker 指令

[官方指南](https://docs.docker.com/reference/cli/docker/)

```shell
---------------------------------对镜像的操作------------------s-------------------

# 查看本地镜像
docker images

# 查找镜像仓库中的镜像
docker search

# 从镜像仓库下载镜像
docker pull <镜像名>  # 可以从镜像仓库官网直接复制

# 删除镜像
docker rmi <镜像名>  # 若镜像已经在容器中生成，需要先删除容器再删除镜像

----------------------------------对容器的操作------------------------------------

# 查看所有容器
docker ps -a

# 查看正在运行的容器
docker ps

# 删除容器# 设置环境变量
export DOCKER_BUILDKIT=1 
docker rm ${容器ID}

# 启动镜像并创建容器
docker run -d -p 主机端口:容器端口 镜像名称

# 保存容器
docker commit <容器ID> <新镜像源> # 直接退出容器则更改不会保存(但数据不会丢)，需要保存到一个新的镜像中

# 暂停容器
docker pause [容器ID或名称] 

# 停止容器
docker stop [容器ID或名称] 

# 启动容器
docker start [容器ID或名称] 

# 重启容器
docker restart [容器ID或名称] 

# 进入容器
docker exec
```

## 二，Dockerfile 

### 1. 理解创建镜像时的步骤

通常情况下，选择基础环境 -> 分层构建 -> 入口

分层构建的好处：提高镜像的复用性，加快构建速度

### 2. Dockerfile 的编写

[官方指南](https://docs.docker.com/reference/dockerfile/)

```dockerfile
# 指定基础镜像
FROM 

# 设置工作目录
WORKDIR

# 添加shell命令
ADD

# 设置环境变量  采用键值对的方式
ENV

# 复制文件
COPY

# 指定容器启动时执行的命令或可执行文件 可以是数组的形式
ENTRYPOINT  
CMD
```

## 三，工作流程

![](./docker.png)

## 四，数据卷

理解：从字面意思来理解就是存放数据的地方 ， 是容器中的文件会映射到主机 ， 方便对其进行操作

```shell
# 创建数据卷两种情况
# 使用数据卷的名字和容器进行创建
# 此时创建的数据卷的位置位于 /var/lib/docker/volumes/数据卷名/_data 目录下
docker run -v 数据卷名:容器内地址 


# 使用主机地址和容器内地址进行创建
# 意味着以/ 或 ./ 开头 
docker run -v 本地目录:容器内目录
			-v 本地文件:容器内文件

```

```shell
# 创建数据卷
docker volume create
# 查看所有数据卷
docker volume ls
# 删除指定数据卷
docker volume rm
# 查看某个数据卷的详情
docker volume inspect
# 清除数据卷
docker volume prune
```

注意：即便不指定数据卷，在创建容器时，也会创建默认的数据卷，名字通常是一串数字字母的组合，比较奇怪

## 五，容器间通信

### 1. 理解工作原理

docker 在安装后会自己创建一个虚拟网桥，创建的容器会连接在同一个网桥（网段），每次使用可以通过地址访问，但是由于是动态地址，非常不便

那么自己定义一个网段可以解决上面问题，通过容器名直接访问

### 2. 常用命令

```shell
# 创建一个网络
docker network create
# 查看所有网络
docker network ls
# 删除指定网络
docker network rm
# 清除未使用的网络
docker network prune
# 使指定容器连接加入某网络
docker network connect
# 使指定容器连接离开某网络
docker network disconnect
# 查看网络详细信息
docker network inspect
```

