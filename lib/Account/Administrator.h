//
// Created by 30398 on 2022/6/20.
//

#ifndef TEST_ADMINISTRATOR_H
#define TEST_ADMINISTRATOR_H
#include "Account.h"

class Administrator:virtual public Account{
public:
    Administrator(const string &userName, const string &userPassword, const string &sfz, const string &regedate,
                  const string &newloginDate, int jifen, bool root, int jycs);
};


#endif //TEST_ADMINISTRATOR_H
