//
// Created by 30398 on 2022/6/19.
//

#include "Account.h"
int Account::_size=0;
const string &Account::getUserName() const {
    return user_name;
}

bool Account::operator==(const Account &rhs) const {
    return user_name == rhs.user_name &&
           user_password == rhs.user_password &&
           sfz == rhs.sfz &&
           regedate == rhs.regedate &&
           newlogin_date == rhs.newlogin_date &&
           jifen == rhs.jifen &&
           root == rhs.root &&
           jycs == rhs.jycs;
}

bool Account::operator!=(const Account &rhs) const {
    return !(rhs == *this);
}

int Account::getJifen() const {
    return jifen;
}

const string &Account::getUserPassword() const {
    return user_password;
}

void Account::setUserPassword(const string &userPassword) {
    user_password = userPassword;
}

string Account::getSfz() const {
    return sfz;
}

void Account::setSfz(const string &sfz) {
    Account::sfz = sfz;
}

bool Account::isRoot() const {
    return root;
}

void Account::setRoot(bool root) {
    Account::root = root;
}

int Account::getJycs() const {
    return jycs;
}

void Account::setJycs(int jycs) {
    Account::jycs = jycs;
}

int Account::getSize() {
    return Account::_size;
}

const string &Account::getRegedate() const {
    return regedate;
}

const string &Account::getNewloginDate() const {
    return newlogin_date;
}

void Account::setNewloginDate(string newloginDate) {
    this->newlogin_date=newloginDate;
}

void Account::setJifen(int jifen) {
    Account::jifen = jifen;
}






