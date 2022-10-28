//
// Created by 30398 on 2022/6/20.
//

#ifndef TEST_DEFAULTDEF_H
#define TEST_DEFAULTDEF_H
#include <map>
#include <conio.h>
//数据库目录 - 用户表
#define Accountdb "G:\\C++\\tEST\\Source\\account.db"
//数据库目录 - 书籍表
#define Bookdb "G:\\C++\\tEST\\Source\\book.db"

#define _Sfz string
#define _PassWord string
#define _BOOK_NAME string
#define _BOOK_ID string
#define _ROOT string
#define Clean system("cls")
#define $_Root_Change_PassWord "85276"
//调试功能
#define OPENDEBUG cout<<"DEBUG: "
#define DEBUG(x) cout<<x<<" "
#define DEBUGN cout<<endl;
void About_me(){
    cout<<"@WuZonglin 2022, Powered by WuZonglin"<<endl;
    cout<<"\n"<<
          " __      __     __________                    .____    .__        \n"<<
          "/  \\    /  \\__ _\\____    /____   ____    ____ |    |   |__| ____  \n"<<
          "\\   \\/\\/   /  |  \\/     //  _ \\ /    \\  / ___\\|    |   |  |/    \\ \n"<<
          " \\        /|  |  /     /(  <_> )   |  \\/ /_/  >    |___|  |   |  \\\n"<<
          "  \\__/\\  / |____/_______ \\____/|___|  /\\___  /|_______ \\__|___|  /\n"<<
          "       \\/               \\/          \\//_____/         \\/       \\/ "<<endl;
    cout<<"My Blog: www.wzl1.top";
    _sleep(2000);
    system("start www.wzl1.top");

}
namespace def{
    const int WenXue=0;
    const int Keji=1;
    const int Computer_Program=2;
    const int Arts=3;
    const int SmallTalk=4;
    const int Love=5;
    const int Ohter=6;
}


#endif //TEST_DEFAULTDEF_H
