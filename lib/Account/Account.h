#ifndef ACCOUNT_H
#define ACCOUNT_H
#include <iostream>
using namespace std;

class Account {
protected:
    string user_name;//用户名
    string user_password;//密码
    string sfz;
public:
    const string &getUserPassword() const;

    void setUserPassword(const string &userPassword);

   string getSfz() const;

    void setSfz(const string &sfz);

    bool isRoot() const;

    void setRoot(bool root);

    int getJycs() const;

    void setJycs(int jycs);

    static int getSize();

    static void setSize(int size);

protected:
    string regedate;
    string newlogin_date;
    int jifen=100;//剩余积分
    bool root=0;
    int jycs=0;//借用次数
public:
    static int _size;
public:
    Account(const string &userName, const string &userPassword, const string &sfz, const string &regedate,
            const string &newloginDate, int jifen, bool root, int jycs) : user_name(userName),
                                                                          user_password(userPassword), sfz(sfz),
                                                                          regedate(regedate),
                                                                          newlogin_date(newloginDate), jifen(jifen),
                                                                          root(root), jycs(jycs) {
        Account::_size++;
    }

    virtual ~Account() {

    }

    const string &getUserName() const;
    int getJifen() const;

    void setUserName(const string &userName);


    void setRegedate(const string &regedate);

    const string &getRegedate() const;

    const string &getNewloginDate() const;

    void setNewloginDate(string newloginDate);

    void setJifen(int jifen);

    void change_PassWord(string old,string _new){
        if (old==this->user_password){
            this->user_password=_new;
        }
        else throw "密码错误";
    }

    friend ostream &operator<<(ostream &os, const Account &account) {
        os << account.user_name << " " <<
        account.user_password << " "  <<
        account.sfz<<" "<<
        account.regedate << " " <<
        account.newlogin_date << " " <<
        account.jifen << " " <<
        account.root<<" "<<
        account.jycs;
        return os;
    }

    bool operator==(const Account &rhs) const;

    bool operator!=(const Account &rhs) const;

    void showme();
};
#endif //TEST_DEFAULTDEF_H