//
// Created by 30398 on 2022/6/20.
//
#ifndef USER_H
#define USER_H
#include "Account.h"

class User:virtual public Account {
public:
    User(const string &userName, const string &userPassword, const string &sfz, const string &regedate,
         const string &newloginDate, int jifen, bool root, int jycs);

    virtual ~User();
};
#endif
