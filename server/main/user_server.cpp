//
//  user_server.cpp
//  user
//
//  Created by Vincent on 2020/6/25.
//  Copyright © 2020 Vincent. All rights reserved.
//

#include "user_server.hpp"
#include <iostream>
#include <memory>
#include <string>

#include <grpcpp/grpcpp.h>
#include <grpcpp/health_check_service_interface.h>
#include <grpcpp/ext/proto_server_reflection_plugin.h>
#include "user.grpc.pb.h"

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Status;
using user::UserRequest;
using user::UserReply;
using user::User;
using user::Data;

// Logic and data behind the server's behavior.
class UserServiceImpl final : public User::Service {
    ServerResult SignUp(ServerContext* context, const UserRequest* request,
                  UserReply* reply) override {
        UserDB userDb;
        ServerResult result;
        User user = userBb.getuser(mobile,password);
        if(user != null){
            result->setErr(1);
            result->sermessage("user already exit");
        }else{
            // 对密码进行二次加密
            std::string salt = Encrypt::randomSalt();
            std::string pwdHash = Encrypt::md5(request->password() + salt);
            userDb.save(request->mobile(),pwdHash,request->devive());
            // 根据 mobie 生成 uuid
            string uuid = EncryptUtil->getTokenForUser(mobile);
            // 以 mobile 作为 key，uuid 作为 value 放入 redis，采用 string 数据类型
            // 以 uuid 作为 key， session 作为 value 放入 redis，采用 hash 数据类型
        }
        return result;
    }
    
    ServerResult SignIn(ServerContext* context, const UserRequest* request,
                  UserReply* reply) override {
        UserDB userDb;
        ServerResult result;
        // 根据手机号获取 salt
        String salt = userBb.getSalt(mobile);
        // salt 与 第一次加密后的密码 进行二次加密
        std::string salt = Encrypt::randomSalt();
        std::string pwdHash = Encrypt::md5(request->password() + salt);
        User user userDb->getUser(request->mobile(),pwdHash);
        if(user == null){
            result->setErr(1);
            result->sermessage("user is not exit, please sign up");
        }
        // 根据 mobie 生成 uuid
        string uuid = EncryptUtil->getTokenForUser(mobile);
        // 通过 mobile 查询 redis
        string old_uuid = redisString.get(mobile);
        if(old_uuid != null && old_uuid != uuid){
            // 启动下线通知
        }
        // 以 mobile 作为 key，uuid 作为 value 放入 redis，采用 string 数据类型
        // 以 uuid 作为 key， session 作为 value 放入 redis，采用 hash 数据类型
    }
};

void RunServer() {
    std::string server_address("0.0.0.0:50051");
    UserServiceImpl service;
    
    grpc::EnableDefaultHealthCheckService(true);
    grpc::reflection::InitProtoReflectionServerBuilderPlugin();
    ServerBuilder builder;
    // Listen on the given address without any authentication mechanism.
    builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
    // Register "service" as the instance through which we'll communicate with
    // clients. In this case it corresponds to an *synchronous* service.
    builder.RegisterService(&service);
    // Finally assemble the server.
    std::unique_ptr<Server> server(builder.BuildAndStart());
    std::cout << "Server listening on " << server_address << std::endl;
    
    // Wait for the server to shutdown. Note that some other thread must be
    // responsible for shutting down the server for this call to ever return.
    server->Wait();
}

int main(int argc, char** argv)
{
  
    //初始化数据库
    MysqlPool *mysql = MysqlPool::getMysqlPoolObject();
    mysql->setParameter(MYSQL_ADDRESS,MYSQL_USRNAME,MYSQL_USRPASSWORD,MYSQL_USEDB,MYSQL_PORT,NULL,0,MYSQL_MAX_CONNECTCOUNT);

    //初始化redis
    RedisPool *redis = RedisPool::getRedisPoolObject();
    redis->setParameter(REDIS_ADDRESS,REDIS_PORT,NULL,0,REDIS_MAX_CONNECTCOUNT);
  
    delete mysql;
    delete redis;

    return 0;
}
