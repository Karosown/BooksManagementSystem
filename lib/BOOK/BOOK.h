    //
// Created by 30398 on 2022/6/19.
//
#ifndef BOOK_H
#define BOOK_H
#include <iostream>
#include "../defaultdef.h"
using namespace std;
class BOOK {
private:
    string book_name;
    string book_id;
    string inDate;
    string outDate;
    string backDate;
    int needJifen;
    int book_type;
    bool isnotBrow;//ÊÇ·ñÔÚ¿â
public:
    string Brower;

    friend ostream &operator<<(ostream &os, const BOOK &book);

    BOOK(const string &bookName, const string &bookId, const string &inDate, const string &outDate,
         const string &backDate, int needJifen, int bookType, const string &brower, bool isnotBrow);

    virtual ~BOOK();

    const string &getBookName() const;

    void setBookName(const string &bookName);

    const string &getBookId() const;

    void setBookId(const string &bookId);

    const string &getInDate() const;

    void setInDate(const string &inDate);

    const string &getOutDate() const;

    void setOutDate(const string &outDate);

    const string &getBackDate() const;

    void setBackDate(const string &backDate);

    int getNeedJifen() const;

    void setNeedJifen(int needJifen);

    int getBookType() const;

    void setBookType(int bookType);

    const string &getBrower() const;

    void setBrower(const string &brower);

    bool isnotBrow1() const;

    void setisnotBrow(bool isnotBrow);
};
#endif