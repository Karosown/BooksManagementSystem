//
// Created by 30398 on 2022/6/19.
//
#include <iostream>
#include "./Account/Account.cpp"
#include "./Account/Administrator.cpp"
#include "./Account/User.cpp"
#include "BOOK/BOOK.cpp"
#include "defaultdef.h"
#include <unordered_map>
#include <fstream>
#include <algorithm>
#include <windows.h>
#include <conio.h>
#include <cstring>
#include <vector>
using namespace std;
/**
 * @Distraction:??????-????
 */
class TOOL {
private:
    //当前账号为
    Account *_root_user=NULL;
public:
    Account *getRootUser() const;

private:
    //sort?????????????
    static bool cmp0(Account* a,Account* b){
        return a->getSfz()>b->getSfz();
    }

    static bool cmp1(Account* a,Account* b){
        return a->getJycs()>b->getJifen();
    }
public:

    static TOOL * SingleDemo;
    vector<BOOK*> BookList;
    //存一个就行了
//    vector <Administrator *> AdminList;
//    vector <User *> UserList;
    vector<Account *> AccountList;

    void write(string dir);

//    unordered_map<_Sfz,pair<_PassWord,_ROOT> > ammatch; ?????????????
    ~TOOL(){
        write(Accountdb);
    }
    //利用并查集的思想
    unordered_map<_BOOK_NAME,vector<BOOK *> >BNS;
    //优化后
    unordered_map<_BOOK_ID,BOOK *>BIS;//根据书本ID与BOOK建立联系
    unordered_map<_Sfz,Account *>ASS;//根据用户身份证与用户对象建立联系
    unordered_map<_Sfz,vector<BOOK*> >ASB;//根据用户身份证查询用户借了那些书
    TOOL(){
        read(Accountdb,0);
        read(Bookdb,1);
    }
    /**
     * 读入操作
     * @param dir 文件目录
     * @param flag 操作方式
     */
    void   read(string dir,bool flag=0){
        ifstream is;//输入流对象
        is.open(dir,ios::in);//打开文件 ios::in
        if(!flag){
            AccountList.erase(AccountList.begin(), AccountList.end());
            while(!is.eof()){//EOF
                string s;
                getline(is,s);//通过getline读取一行，给string对象
                if(s[0]=='#')continue;//遇见注释就跳
                if (s.length()<1)break;
                string str[8];
                int _bpos=0,_epos=s.find(' ',0);
//                OPENDEBUG;
                for(int i=0;i<8;i++){
                    str[i]=s.substr(_bpos,_epos-_bpos);
                    _bpos=_epos+1;
                    _epos=s.find(' ',_bpos);
                }
//                DEBUGN;
                string user_name=str[0];
                string user_password=str[1];
                string sfz=str[2];
                string regedate=str[3];
                string newlogin_date=str[4];
                int jifen=stoi(str[5]);
                int root=stoi(str[6]);
                int jycs=stoi(str[7]);
                if (root)AccountList.push_back(new Administrator(
                            user_name,
                            user_password,
                            sfz,
                            regedate,
                            newlogin_date,
                            jifen,
                            root,
                            jycs
                    ));
                else AccountList.push_back(new User(
                            user_name,
                            user_password,
                            sfz,
                            regedate,
                            newlogin_date,
                            jifen,
                            root,
                            jycs
                    ));

                ASS[sfz] = AccountList[AccountList.size() - 1];
                ASS[sfz] = AccountList[AccountList.size() - 1];

            }
            sort(AccountList.begin(), AccountList.end(),cmp0);
//            sort(AccountList.begin(), AccountList.end(),cmp1);
        }
        else{
            BookList.erase(BookList.begin(), BookList.end());
            BIS.erase(BIS.begin(), BIS.end());
            BNS.erase(BNS.begin(), BNS.end());
            ASB.erase(ASB.begin(), ASB.end());
            while(!is.eof()){
                string s;
                getline(is,s);
                if (s[0]=='#')continue;
                if (s.length()<1)break;
                string str[9];
                int _bpos=0,_epos=s.find(' ',0);
//                OPENDEBUG;
                for(int i=0;i<9;i++){
                    str[i]=s.substr(_bpos,_epos-_bpos);
                    _bpos=_epos+1;
                    _epos=s.find(' ',_bpos);
//                    DEBUG(str[i]);
                }
                string book_name=str[0];
                string book_id=str[1];
                string inDate=str[2];
                string outDate=str[3];
                string backDate=str[4];
                int needJifen=stoi(str[5]);
                int book_type=str[6][0]-'0';
                string Brower=str[7];
                bool isnotBrow=str[8][0]-'0';
                BookList.push_back(new BOOK(
                        book_name,
                        book_id,
                        inDate,
                        outDate,
                        backDate,
                        needJifen,
                        book_type,
                        Brower,
                        isnotBrow
                ));
                BIS[book_id]=BookList[BookList.size()-1];
                BNS[book_name].push_back(BookList[BookList.size()-1]);
                if(!BookList[BookList.size()-1]->isnotBrow1())ASB[Brower].push_back(BookList[BookList.size()-1]);
            }
        }
        is.close();
    }
    void Brow_book(){
        Clean;
        read(Bookdb,1);
        cout<<"请输入您要借的图书的编号（时间只能为1个月）：";
        string s;
        cin>>s;
        if (BIS[s]==NULL)cout<<"这本书不存在或还未入库，请等待入库后再来吧..."<<endl;
        else if (!BIS[s]->isnotBrow1())cout<<"这本书被借走了，下次再来吧！";
        else{
            if(_root_user->getJifen()-BIS[s]->getNeedJifen()<0){
                cout<<"您的积分不够，请充值（联系管理员手动添加，个人充值功能待完善...）"<<endl;
            }
            else{
                BIS[s]->setBrower(_root_user->getSfz());
                string newdate=getdate();
                BIS[s]->setOutDate(newdate);
                BIS[s]->setisnotBrow(0);//是否在图书藏中
                newdate[5]++;
                BIS[s]->setBackDate(newdate);
                _root_user->setJifen(_root_user->getJifen()-BIS[s]->getNeedJifen());
                _root_user->setJycs(_root_user->getJycs()+1);
                ASB[_root_user->getSfz()].push_back(BIS[s]);
                cout<<"借用成功！"<<endl;
                cout<<"***********************"<<endl;
                cout<<"图书信息如下："<<endl;
                cout<<"书名："<<BIS[s]->getBookName()<<endl;
                cout<<"书本编号："<<BIS[s]->getBookId()<<endl;
                cout<<"入库时间："<<BIS[s]->getInDate()<<endl;
                cout<<"借出时间："<<BIS[s]->getOutDate()<<endl;
                cout<<"归还时间："<<BIS[s]->getBackDate()<<endl;
                cout<<"借书人："<<BIS[s]->getBrower()<<endl;
                cout<<"耗费积分："<<BIS[s]->getNeedJifen()<<endl;
                cout<<"当前剩余："<<_root_user->getJifen()<<endl;
                cout<<"***********************"<<endl;
            }
//                OPENDEBUG;
//                getch();
            write(Accountdb);
//            getch();
            write(Bookdb);
//            getch();
            read(Accountdb,0);
//            getch();
            read(Bookdb,1);
        }
        cout<<"按任意键返回...";
        getch();
        Show_Menu();
    }
//    static std::mutex mt;
    //?????-??????
    static TOOL* getDemo();
    void show_beginmenu();
    void show_Login();
    void show_regesit(int flag);
    int Login(string name,string password);
    void regist(string name,string password,string sfz);
    static void gotoxy(int x,int y)//光标跳动
    {
        COORD c;     //????????????
        c.X = x - 1; //??????????????
        c.Y = y - 1;
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),c);   //????WindowsAPI???????????
    }
    void Back_book(){
        read(Bookdb,1);
        SetScreenSize(GetSystemMetrics(SM_CXSCREEN),GetSystemMetrics(SM_CYSCREEN));
        int r=60,c=155;
        Clean;
        for(int i=0;i<c;i++) cout<<"*";
        cout<<endl;
        for (int i = 0; i < r; ++i) {
            cout<<"*";
            for (int j = 0; j < c-2; ++j) {
                if (i==1)cout<<"*";
                else cout<<" ";
            }
            cout<<"*"<<endl;
        }
        gotoxy(2,2);
        cout<<"用户 "<<_root_user->getUserName()<<" 所借书籍";
        gotoxy(2,4);
        cout<<"书名\t\t\t编号\t\t入库时间\t上次借出时间\t归还时间\t所需积分\t所属类别\t\t最新借阅人\t被借阅";
        int i=5;
        int flag=0;
        for(auto item:ASB[_root_user->getSfz()]){
            gotoxy(2,i++);
            cout<<(*item);
            flag=1;
        }
        cout<<endl;
        for(int i=0;i<c;i++) cout<<"*";
        if(flag){
            cout<<endl<<"请输入需要归还的书本编号(输入[exit()]返回)：";
            string id;
            cin>>id;
            if(id=="exit()")Show_Menu();
            if(BIS[id]==NULL) cout<<"对不起，这本书还没有入库哟！按任意键返回..."<<endl;
            else{
                BIS[id]->setisnotBrow(1);
                BIS[id]->setBackDate(getdate());
                auto iter=std::find(ASB[_root_user->getSfz()].begin(), ASB[_root_user->getSfz()].end(), BIS[id]);
                if (iter==ASB[_root_user->getSfz()].end()){
                    cout<<"您没有借阅这跟图书哟，请重试~"<<endl;
                    getch();
                    Back_book();
                }else{
                    ASB[_root_user->getSfz()].erase(iter);
                    write(Bookdb);
                    read(Bookdb,1);
                    cout<<"归还成功！按任意键返回..."<<endl;
                }

            }
        }
        else{
            cout<<"目前您没有书需要还哟~！按任意键返回..."<<endl;
        }
        getch();
        Show_Menu();
    }
    void SetScreenSize(int width, int height )
    {
        system(("mode con: cols="+to_string(width)+" lines="+ to_string(height)).c_str());
    }
    void todo(int pos,int x);

    string getdate();

    bool Isdigit(string basicString);

    void Show_Menu();

    void searchBook_view(int flag);

    void show_Best();

    void set_BOOK();

    void Insert_BOOK();

    void Delete_BOOK();

    void Set_User();

    void select_Account();

    void drop_User();

    void update_password();

    void Recharge();

    void set_user_root();
};
/**
 * 个人资料
 */
void Account::showme() {
    Clean;
    cout<<"******************************"<<endl;
    cout<<"*          个人信息"<<endl;
    cout<<"*  用户名："<<endl;
    cout<<"*  身份证："<<endl;
    cout<<"*  用户权限："<<endl;
    cout<<"*  剩余积分："<<endl;
    cout<<"*  注册时间："<<endl;
    cout<<"*  上次登录时间："<<endl;
    cout<<"*  借阅次数："<<endl;
    cout<<"******************************";
    TOOL::gotoxy(30,2);
    cout<<"*";TOOL::gotoxy(30,3);
    cout<<"*";TOOL::gotoxy(30,4);
    cout<<"*";TOOL::gotoxy(30,5);
    cout<<"*";TOOL::gotoxy(30,6);
    cout<<"*";TOOL::gotoxy(30,7);
    cout<<"*";TOOL::gotoxy(30,8);
    cout<<"*";TOOL::gotoxy(30,9);
    cout<<"*";TOOL::gotoxy(30,10);
    cout<<"*";TOOL::gotoxy(18,3);
    cout<<this->getUserName();TOOL::gotoxy(18,4);
    cout<<this->getSfz().substr(0,3)<<"***"<<this->getSfz().substr(this->getSfz().length()-3,3);TOOL::gotoxy(18,5);
    cout<<(this->isRoot()?"管理员":"普通用户");TOOL::gotoxy(18,6);
    cout<<this->getJifen();TOOL::gotoxy(18,7);
    cout<<this->getRegedate();TOOL::gotoxy(18,8);
    cout<<this->getNewloginDate();TOOL::gotoxy(18,9);
    cout<<this->getJycs();
    getch();
    TOOL::getDemo()->Show_Menu();
}
ostream &operator<<(ostream &os, const BOOK &book) {
    os << book.book_name <<((book.book_name.length()>=22)?" ":(book.book_name.length()<=8?"\t\t":"\t"))<< book.book_id << "\t" << book.inDate << "\t"
       << (book.outDate=="0"?"暂未借出":book.outDate) << "\t" << (book.backDate=="0"?"暂未借出":book.backDate) << "\t" << book.needJifen << "\t\t"
            ;
    switch (book.book_type) {
        case def::WenXue:
            os<<"文学创作类";
            break;
        case def::Keji:
            os<<"科技创新类";
            break;
        case def::Arts:
            os<<"艺术作品类";
            break;
        case def::Computer_Program:
            os<<"计算机编程类";
            break;
        case def::Love:
            os<<"美学艺术类";
            break;
        case def::SmallTalk:
            os<<"科幻小说类";
            break;
        case def::Ohter:
            os<<"其他";
            break;
        default:
            os<<"暂未分类";
            break;
    }
    if (book.Brower == "0") {
        os << "\t\t" << "暂未借出" << "\t" << (book.isnotBrow == 1 ? "N" : "Y");
    } else {
        if(TOOL::getDemo()->getRootUser()->isRoot()){
            os << "\t\t" << book.Brower << "   " << (book.isnotBrow == 1 ? "N" : "Y");

        }
        else{
            os << "\t\t" << TOOL::getDemo()->ASS[book.Brower]->getUserName() <<((TOOL::getDemo()->ASS[book.Brower]->getUserName().length()>=15)?"\t": "\t\t")<< (book.isnotBrow == 1 ? "N" : "Y");
        }
    }
    return os;
}
