//
//  UserDB.cpp
//  user
//
//  Created by Vincent on 2020/6/26.
//  Copyright © 2020 Vincent. All rights reserved.
//

#include "UserDB.hpp"

#include "driver.h"
#include "prepared_statement.h"

std::string MYSQL_HOST("tcp://docker_mysql:3306");
std::string MYSQL_USER("root");
std::string MYSQL_PWD("root");

   User UserDB::getUser(std::string mobile, std::string password)
   {
    int ret = -1;
    sql::Driver *driver;
    sql::Connection *con;
    sql::ResultSet *res;
    sql::PreparedStatement* stmt;
    try {
        driver = get_driver_instance();
        con = driver->connect(MYSQL_HOST, MYSQL_USER, MYSQL_PWD);
        stmt = con->prepareStatement("SELECT `mobile`, `password`, `salt` from t_user where `mobile`=?");
        stmt->setString(1, userName);
        stmt->setString(2, password);
        res = stmt->executeQuery();
        return stmt->executeQuery();
    }
    
    int UserDB::save(std::string mobile, std::string password, std::string salt,  std::string device)
    {
        sql::Driver *driver;
        sql::Connection *con;
        sql::PreparedStatement* stmt;
        driver = get_driver_instance();
        con = driver->connect(MYSQL_HOST, MYSQL_USER, MYSQL_PWD);
        stmt = con->prepareStatement("insert into `t_user`(`user_name`, `password`, `salt`) values (?, ?, ?)");
        stmt->setString(1, account->getUserName());
        stmt->setString(2, account->getPwdHash());
        stmt->setString(3, account->getSalt());
        stmt->setString(4, account->getDevice());
        return stmt->executeUpdate();
    }
}
