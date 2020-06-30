//
//  user_client.cpp
//  user
//
//  Created by Vincent on 2020/6/25.
//  Copyright © 2020 Vincent. All rights reserved.
//

#include "user_client.hpp"

#include <iostream>
#include <memory>
#include <string>

#include <grpcpp/grpcpp.h>
#include "user.grpc.pb.h"

using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;
using user::UserRequest;
using user::UserReply;
using user::User;
using user::Data;

class UserClient {
    
public:
    UserClient(std::shared_ptr<Channel> channel) : stub_(User::NewStub(channel)) {}
    
    std::string SignUp(const std::string& mobile, const std::string& password) {
        UserRequest request;
        request.set_mobile(mobile);
        // 密码加密
        std::string salt = Encrypt::randomSalt();
        std::string pwdHash = Encrypt::md5(password + salt);
        request.set_password(pwdHash);
        
        UserReply reply;
        
        ClientContext context;
        Status status = stub_->SignUp(&context, request, &reply);
        
        if (status.ok()) {
            return "sign up success";
        } else {
            std::cout << status.error_code() << ": " << status.error_message()
            << std::endl;
            return "sign up failed";
        }
    }
    
    std::string SignIn(const std::string& mobile, const std::string& password) {
        UserRequest request;
        request.set_mobile(mobile);
        std::string salt = Encrypt::randomSalt();
        std::string pwdHash = Encrypt::md5(password + salt);
        request.set_password(pwdHash);
        UserReply reply;
        
        ClientContext context;
        Status status = stub_->SignIn(&context, request, &reply);
        
        if (status.ok()) {
            return "sign in success";
        } else if(status = 1){
            std::cout << status.error_code() << ": " << status.error_message()
            << std::endl;
            // 账号密码错误
            return "sign in failed";
        } else if(status = 2){
            std::cout << status.error_code() << ": " << status.error_message()
            << std::endl;
            // 账号密码错误
            return "Your account is logged in on another terminal, your current account is forced to log off";
        }
    }
    
private:
    std::unique_ptr<UserRequest::Stub> stub_;
};

int main(int argc, char** argv) {

    std::string target_str;
    std::string arg_str("--target");
    if (argc > 1) {
        std::string arg_val = argv[1];
        size_t start_pos = arg_val.find(arg_str);
        if (start_pos != std::string::npos) {
            start_pos += arg_str.size();
            if (arg_val[start_pos] == '=') {
                target_str = arg_val.substr(start_pos + 1);
            } else {
                std::cout << "The only correct argument syntax is --target=" << std::endl;
                return 0;
            }
        } else {
            std::cout << "The only acceptable argument is --target=" << std::endl;
            return 0;
        }
    } else {
        target_str = "localhost:50051";
    }
    UserClient user(grpc::CreateChannel(target_str, grpc::InsecureChannelCredentials()));
    std::string mobile("110");
    std::string password("110");
    // 获取设备号
    std::string signUpReply = user.SignUp(mobile, password, device);
    std::string signInReply = user.SignIn(mobile, password, device);
    std::cout << "UserClient sign up received: " << signUpReply << std::endl;
    std::cout << "UserClient sign in received: " << signUpReply << std::endl;
    
    return 0;
}
