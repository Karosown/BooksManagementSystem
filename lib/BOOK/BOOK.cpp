//
// Created by 30398 on 2022/6/19.
//

#include "BOOK.h"

BOOK::BOOK(const string &bookName, const string &bookId, const string &inDate, const string &outDate,
           const string &backDate, int needJifen, int bookType, const string &brower, bool isnotBrow) : book_name(
        bookName), book_id(bookId), inDate(inDate), outDate(outDate), backDate(backDate), needJifen(needJifen),
                                                                                                     book_type(
                                                                                                             bookType),
                                                                                                     Brower(brower),
                                                                                                     isnotBrow(isnotBrow) {}

const string &BOOK::getBookName() const {
    return book_name;
}

void BOOK::setBookName(const string &bookName) {
    book_name = bookName;
}

const string &BOOK::getBookId() const {
    return book_id;
}

void BOOK::setBookId(const string &bookId) {
    book_id = bookId;
}

const string &BOOK::getInDate() const {
    return inDate;
}

void BOOK::setInDate(const string &inDate) {
    BOOK::inDate = inDate;
}

const string &BOOK::getOutDate() const {
    return outDate;
}

void BOOK::setOutDate(const string &outDate) {
    BOOK::outDate = outDate;
}

const string &BOOK::getBackDate() const {
    return backDate;
}

void BOOK::setBackDate(const string &backDate) {
    BOOK::backDate = backDate;
}

int BOOK::getNeedJifen() const {
    return needJifen;
}

void BOOK::setNeedJifen(int needJifen) {
    BOOK::needJifen = needJifen;
}

int BOOK::getBookType() const {
    return book_type;
}

void BOOK::setBookType(int bookType) {
    book_type = bookType;
}

const string &BOOK::getBrower() const {
    return Brower;
}

void BOOK::setBrower(const string &brower) {
    Brower = brower;
}


void BOOK::setisnotBrow(bool isnotBrow) {
    BOOK::isnotBrow = isnotBrow;
}


bool BOOK::isnotBrow1() const {
    return isnotBrow;
}

BOOK::~BOOK() {

}
