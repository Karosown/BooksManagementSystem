//
// Created by 30398 on 2022/6/20.
//

#include "User.h"

User::User(const string &userName, const string &userPassword, const string &sfz, const string &regedate,
           const string &newloginDate, int jifen, bool root, int jycs) : Account(userName, userPassword, sfz, regedate,
                                                                                 newloginDate, jifen, root, jycs) {}

User::~User() {

}
