# docker-compose-bazel-grpc_user
一个暂时还不能运行起来的用户单终端登录系统


# 系统设计
https://xiangou.blog.csdn.net/article/details/106878176

# How to use
## 服务端启动方法(需要安装docker、docker-compose):
cd user 

docker-compose up --build (安装bazel环境的过程可能有点长) 

## 客户端启动方法(本地命令行客户端,需要安装grpc C++、bazel):
bazel build //main:user_client 

bazel-bin/src/user_client
