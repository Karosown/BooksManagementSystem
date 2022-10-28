//
// Created by 30398 on 2022/6/19.
//
#include "TOOL.h"
#include "conio.h"
#include "ctime"
#include <vector>
TOOL * TOOL::SingleDemo=NULL;

void TOOL::show_beginmenu() {
    Clean;
    cout<<"**********************************"<<endl;
    cout<<"*           图书管理系统           ";
    gotoxy(34,2);
    cout<<"*"<<endl;
    cout<<"*          1.用户登录             ";
    gotoxy(34,3);
    cout<<"*"<<endl;
    cout<<"*          2.用户注册             ";
    gotoxy(34,4);
    cout<<"*"<<endl;
    cout<<"*          3.关于本系统           ";
    gotoxy(34,5);
    cout<<"*"<<endl;
    cout<<"*          4.退出                ";
    gotoxy(34,6);    cout<<"*"<<endl;
    cout<<"*    请输入序号选择：【 】          ";
    gotoxy(34,7);    cout<<"*"<<endl;
    cout<<"**********************************"<<endl;
    gotoxy(24,7);
    int x;
    cin>>x;
    todo(0,x);
}

void TOOL::show_Login() {
    read(Accountdb,0);
    Clean;
    cout<<"**********************************"<<endl;
    cout<<"*           用户登录";
    gotoxy(34,2);
    cout<<"*"<<endl;
    cout<<"*   身份证号:";
    gotoxy(34,3);
    cout<<"*"<<endl;
    cout<<"*   用户密码:";
    gotoxy(34,4);    cout<<"*"<<endl;
    cout<<"**********************************"<<endl;
    cout<<"若没有注册请全部填写00000000前往注册";
    gotoxy(14,3);
    string account,password;
    cin>>account;
    while(1){
        gotoxy(14,4);
        char ch;
        int len=0;
        while((ch=getch())&&ch!=13){
            if(ch==8){
                if(0<len&&len<=8) cout<<"\b \b";
                if(len)password.erase(password.end()-1),len--;
                continue;
            }
            else password+=ch,len++;
            if (len<=8)cout<<"*";
        }
        if (password.length()>=6&&password.length()<=8)break;
        gotoxy(1,7);
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED);
        cout<<"密码不符合规范"<<endl;
        password="";
        gotoxy(14,4);
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 07);
        cout<<"\r";
        cout<<"*   用户密码:                       ";
        gotoxy(34,4);    cout<<"*"<<endl;
    }
    if (account=="00000000"&&password=="00000000")show_regesit(0);
    int _root=Login(account,password);
//    DEBUG(_root);
    if (_root) {
        //优化后
        _root_user=ASS[account];
//        if (_root-1){
//            for(auto temp:AdminList){
//                if (temp->getSfz()==account){
//                    this->_root_user=temp;
//                }
//            }
//        }else{
//            for(auto temp:UserList){
//                if (temp->getSfz()==account){
//                    this->_root_user=temp;
//                }
//            }
//        }
        this->_root_user->setNewloginDate(getdate());
        Show_Menu();
    }
    else{
        gotoxy(1,8);
        cerr<<"请检查身份证号码或密码是否正确匹配，若账号密码不对请联系管理员进行修改"<<endl;
        getch();
        show_Login();
    }
}

void TOOL::show_regesit(int flag=0) {
    Clean;
    read(Accountdb,0);
    cout<<"**********************************"<<endl;
    cout<<"*           用户注册";
    gotoxy(34,2);
    cout<<"*"<<endl;
    cout<<"*      用户名:";
    gotoxy(34,3);
    cout<<"*"<<endl;
    cout<<"*      用户密码:";
    gotoxy(34,4);    cout<<"*"<<endl;
    cout<<"*      身份证:";
    gotoxy(34,5);    cout<<"*"<<endl;
    cout<<"**********************************"<<endl;
    cout<<"注意事项:用户名在4~6个字符以内（不能以#开头）,用户密码最少有6个字符,最长8个";
    string account,password;
    while(1){
        gotoxy(16,3);
        cin>>account;
        if(account[0]!='#'&&account.length()<=6&&account.length()>=4)break;
        gotoxy(1,8);
        cout<<"用户名不符合规范";
        getch();
        show_regesit();
    }
    while(1){
        gotoxy(17,4);
        char ch;
        int len=0;
        while((ch=getch())&&ch!=13){
            //退格键
            if(ch==8){
                //当屏幕上的*不超过8个时
                if(0<len&&len<=8) cout<<"\b \b";
                //迭代器
                if(len)password.erase(password.end()-1),len--;
                continue;
            }
            else password+=ch,len++;
            if (len<=8)cout<<"*";
        }
        if (password.length()>=6&&password.length()<=8)break;
        gotoxy(1,8);
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED);

        cout<<"密码不符合规范"<<endl;
        password="";
        gotoxy(17,4);
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 07);

        cout<<"\r";
        cout<<"*      用户密码:                         ";
        gotoxy(34,4);    cout<<"*"<<endl;
    }
    string sfz;
    while(1){
        gotoxy(15,5);
        cin>>sfz;
        gotoxy(1,8);
        if (sfz.length()==18&&Isdigit(sfz)&&sfz[0]>='1') {
//            if (ammatch.find(sfz)!=ammatch.end())cerr<<"当前身份证已注册过账号！";
            if (ASS.find(sfz)!=ASS.end())cerr<<"当前身份证已注册过账号！";
            else break;
        }
        else cout<<"身份证不符合规范"<<endl;
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED);
        gotoxy(16,5);
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 07 );
        cout<<"\r";
        cout<<"*      身份证:                       ";
        gotoxy(34,5);    cout<<"*"<<endl;
    }
    regist(account,password,sfz);
    gotoxy(1,8);
    if(!flag){
        cout<<"注册成功，即将前往登录！"<<endl;
        getch();
        show_Login();
    }else{
        cout<<"用户添加成功！"<<endl;
        getch();
        Set_User();
    }
}

int TOOL::Login(string name, string password) {
//    pair<_PassWord,_ROOT> temp=ammatch[name];
//    DEBUG(temp.first);
    Account *temp = ASS[name];
    if (temp==NULL)return 0;
//    if (temp.first==password) return temp.second[0]-'0'+1;
    if (temp->getUserPassword()==password) return 1;
    return 0;
}

void TOOL::regist(string name, string password,string sfz) {
    ofstream os;
    os.open(Accountdb,ios::out|ios::ate|ios::app);
    string date=getdate();
    os<<name<<" "<<password<<" "<<sfz<<" "<<date<<" "<<date<<" "<<100<<" "<<0<<" "<<0<<endl;
    os.close();
}

void TOOL::searchBook_view(int flag=0) {
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
    cout<<"请输入书名（输入*查询所有图书）：";
    gotoxy(2,4);
    cout<<"书名\t\t\t编号\t\t入库时间\t上次借出时间\t归还时间\t所需积分\t所属类别\t\t最新借阅人\t被借阅";
    gotoxy(35,2);
    string book_name;
    cin>>book_name;
    int i=5;
    if(book_name=="*"){

        for(auto item:BookList){
            gotoxy(2,i++);
            cout<<(*item);
        }
    }
    else{
        for(auto item:BNS["《"+book_name+"》"]){
            gotoxy(2,i++);
            cout<<(*item);
        }
    }
    cout<<endl;
    for(int i=0;i<c;i++) cout<<"*";
    cout<<endl;
    cout<<"按任意键返回上一页...";
    getch();
    if(!flag)Show_Menu();
    else set_BOOK();
}

TOOL *TOOL::getDemo() {
//        mt.lock();
    if(TOOL::SingleDemo== NULL){
        TOOL::SingleDemo=new TOOL;
    }
//        mt.unlock();
    return TOOL::SingleDemo;

}

void TOOL::todo(int pos,int x) {

    switch (pos) {
        //开始菜单界面
        case 0:
            switch (x) {
                //用户登录
                case 1:
                    Clean;
                    show_Login();
                    break;
                    //用户注册
                case 2:
                    Clean;
                    show_regesit();
                    break;
                    //about
                case 3:
                    Clean;
                    About_me();
                    getch();
                    show_beginmenu();
                    break;
                case 4:
                    return ;
                    break;
                default:
                    show_beginmenu();
                    break;
            }
            break;
            //菜单界面
        case 1:
            switch (x) {
//                返回菜单
                case 0:
                    show_beginmenu();
                    break;
                case 1:
                    _root_user->showme();
                    break;
//                书籍查询
                case 2:
                    searchBook_view();
                    break;
//                借阅图书
                case 3:
                    Brow_book();
                    break;
//                归还图书
                case 4:
                    Back_book();
                    break;
//                借书达人
                case 5:
                    show_Best();
                    break;
                case 6:
                    set_BOOK();
                    break;
                case 7:
                    Set_User();
                    break;
            }
            break;
            //管理书籍界面
        case 2:
            switch(x){
                case 1:
                    searchBook_view(1);
                    break;
                case 2:
                    Insert_BOOK();
                    break;
                case 3:
                    Delete_BOOK();
                    break;
                default:
                    Show_Menu();
                    break;
            }
            break;
            //管理用户界面
        case 3:
            switch (x) {
                case 1:
                    select_Account();
                    break;
                case 2:
                    show_regesit(1);
                    break;
                case 3:
                    drop_User();
                    break;
                case 4:
                    update_password();
                    break;
                case 5:
                    Recharge();
                    break;
                case 6:
                    set_user_root();
                default:
                    Show_Menu();
                    break;
            }
    }
}

string TOOL::getdate(){
    time_t t=time(nullptr);
    tm *now = localtime(&t);
    return to_string(now->tm_year+1900)+"-"+ to_string(now->tm_mon+1)+"-"+to_string(now->tm_mday);
}

bool TOOL::Isdigit(string num) {
    for(char item:num){
        if (isdigit(item))continue;
        return false;
    }
    return true;
}

void TOOL::Show_Menu() {
    Clean;
    cout<<"****************************************"<<endl;
    cout<<"*     图书管理系统-"+_root_user->getUserName()+"("+
          (this->_root_user->isRoot()==true?("管理员"):("普通用户"))
          +")";
    gotoxy(40,2);
    cout<<"*"<<endl;
    cout<<"*   1.个人信息";
    gotoxy(40,3);
    cout<<"*"<<endl;
    cout<<"*   2.书籍查询";
    gotoxy(40,4);
    cout<<"*"<<endl;
    cout<<"*   3.借阅图书";
    gotoxy(40,5);
    cout<<"*"<<endl;
    cout<<"*   4.归还图书";
    gotoxy(40,6);
    cout<<"*"<<endl;
    cout<<"*   5.借书总榜";
    gotoxy(40,7);
    cout<<"*"<<endl;
    if (this->_root_user->isRoot()){
        //管理员用户
        cout<<"*   6.书籍管理";
        gotoxy(40,8);
        cout<<"*"<<endl;
        cout<<"*   7.用户管理";
        gotoxy(40,9);
        cout<<"*"<<endl;
    }
    if (this->_root_user->isRoot())gotoxy(1,10);
    else gotoxy(1,8);
    cout<<"* 请选择对应序号(0返回):【 】";
    if (this->_root_user->isRoot())gotoxy(40,10);
    else gotoxy(40,8);
    cout<<"*"<<endl;
    cout<<"****************************************"<<endl;
    if (this->_root_user->isRoot())gotoxy(27,10);
    else gotoxy(27,8);
    int x;
    cin>>x;
    todo(1,x);
}

void TOOL::show_Best() {
    Clean;
    read(Accountdb,0);
    sort(AccountList.begin(), AccountList.end(),cmp1);
    cout<<"巅峰榜："<<endl;
    cout<<"排名\t\t用户名\t\t借书次数"<<endl;
    int i=1;
    for(auto item:AccountList){
        cout<<i<<"\t\t"<<item->getUserName()<<"\t\t"<<item->getJycs()<<endl;
    }
    getch();
    Show_Menu();
}

void TOOL::write(string dir) {
    ifstream is;
    is.open(dir,ios::in);
    string str;
    while(!is.eof()){
        string s;
        getline(is,s);
        s+='\n';
        if(s[0]=='#')str+=s;
        else break;
    }
    is.close();
    ofstream os;
    os.open(dir,ios::out);
    os<<str;
    if (dir == Accountdb){
        for(auto item:AccountList){
            os<<*(item)<<endl;
        }
    }
    if (dir == Bookdb){
        for(auto item:BookList){
            //#书名 编号 入库时间 上次借出时间 归还时间 所需积分 所属类别 最新借阅人 被借阅
            os<<item->getBookName()<<" "<<
              item->getBookId()<<" "<<
              item->getInDate()<<" "<<
              item->getOutDate()<<" "<<
              item->getBackDate()<<" "<<
              item->getNeedJifen()<<" "<<
              item->getBookType()<<" "<<
              item->getBrower()<<" "<<
              item->isnotBrow1()<<endl;
        }
    }
    os.close();
}

Account *TOOL::getRootUser() const {
    return _root_user;
}

void TOOL::set_BOOK() {
    Clean;
    cout<<"1.查询图书"<<endl;
    cout<<"2.添加图书"<<endl;
    cout<<"3.删除图书"<<endl;
    cout<<"其他：返回"<<endl;
    cout<<"请选择：";
    int x;
    cin>>x;
    todo(2,x);
}

void TOOL::Insert_BOOK() {
    Clean;
    string name;
    string id;
    int needJifen;
    int type;
    cout<<"书名："<<endl;
    cout<<"编号："<<endl;
    cout<<"所需积分："<<endl;
    cout<<"类型："<<endl;
    cout<<"类型解释：\n\t0.文学创作类\n\t1.科技创新类\n\t2.美学艺术类\n\t3.计算机编程类\n\t4.乡村爱情类\n\t5.科幻小说类\n\t6.其他\n其他数字：暂未分类（后续增加自定义分类功能）"<<endl;
    gotoxy(6,1);
    cin>>name;
    name.insert(0,"《");
    name.insert(name.length(),"》");
    gotoxy(6,2);
    cin>>id;
    gotoxy(6,3);
    cin>>needJifen;
    gotoxy(6,4);
    cin>>type;
    BookList.push_back(new BOOK(
            name,
            id,
            getdate(),
            "0",
            "0",
            needJifen,
            type,
            "0",
            1
    ));
    write(Bookdb);
    gotoxy(1,20);
    cout<<"添加成功！按任意键返回上一页。";
    getch();
    set_BOOK();
}

void TOOL::Delete_BOOK() {
    Clean;
    string id;
    cout<<"请输入要删除图书的编号，输入*全部删除（若要删除某些图书，请在输入#书名）：";
    cin>>id;
    int num=0;
    if(id=="*"){
        num=BookList.size();
        BookList.erase(BookList.begin(), BookList.end());
    }
    else{
        if(id[0]=='#'){
            num=BNS[id].size();
            id.erase(id.begin());
            for(auto item:BNS[id]){
                auto iter=std::find(BookList.begin(), BookList.end(), BIS[id]);
                BookList.erase(iter);
                delete item;
            }
        }
        else{
            num=1;
            auto iter=std::find(BookList.begin(), BookList.end(), BIS[id]);
            BookList.erase(iter);
            delete BIS[id];
        }
    }
    write(Bookdb);
    cout<<"删除成功！共删除 "<<num<<" 本书"<<endl;
    getch();
    set_BOOK();
}

void TOOL::Set_User() {
    Clean;
    cout<<"1.查看用户数据库"<<endl;//黑心人，可以查看密码
    cout<<"2.增加用户"<<endl;
    cout<<"3.删除用户"<<endl;
    cout<<"4.修改用户密码"<<endl;
    cout<<"5.积分充值"<<endl;
    cout<<"6.用户权限设置"<<endl;
    cout<<"其他返回上一页"<<endl;
    cout<<"请选择：";
    int x;
    cin>>x;
    todo(3,x);

}
void TOOL::select_Account() {
    Clean;
    read(Accountdb,0);
    SetScreenSize(GetSystemMetrics(SM_CXSCREEN),GetSystemMetrics(SM_CYSCREEN));
    int r=60,c=120;
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
    cout<<"请输入用户名（输入*查询所有用户）：";
    gotoxy(2,4);
    //用户名 密码      身份证号        注册日期 最后登录日期 积分 用户权限 借阅次数
    cout<<"用户名\t密码\t身份证号\t注册时间  最后登录日期\t积分\t用户权限(1 admin 0 user)\t借阅次数";
    gotoxy(35,2);
    string user_name;
    cin>>user_name;
    if(user_name=="*"){
        int i=5;
        for(auto item:AccountList){
            gotoxy(2,i++);
            cout<<(*item);
        }
    }
    else{
        gotoxy(2,5);
        cout<<*ASS[user_name];
    }
    cout<<endl;
    for(int i=0;i<c;i++) cout<<"*";
    cout<<endl;
    cout<<"按任意键返回上一页...";
    getch();
    Show_Menu();
}
void TOOL::drop_User() {
    read(Accountdb,0);
    string sfz;
    while (true) {
        Clean;
        cout << "请输入欲删除用户的身份证：";
        cin >> sfz;
        if (ASS[sfz] == NULL) {
            cout<<"该用户不存在，按任意键继续";
            getch();
            continue;
        }
        break;
    }
    auto iter = std::find(AccountList.begin(), AccountList.end(), ASS[sfz]);
    AccountList.erase(iter);
    ASS[sfz]=NULL;
    write(Accountdb);
    read(Accountdb,0);
    cout<<"删除成功，按任意键返回上一页...";
    getch();
    Set_User();
}
void TOOL::update_password() {
    Clean;
    read(Accountdb,0);
    cout<<"请输入欲修改用户的身份证：";
    string sfz;
    cin>>sfz;
    cout<<"请输入欲修改用户的密码：";
    string password;
    cin>>password;
    ASS[sfz]->setUserPassword(password);
    write(Accountdb);
    read(Accountdb,0);
    cout<<"修改成功，按任意键返回上一页...";
    getch();
    Set_User();
}

void TOOL::Recharge() {
    read(Accountdb);
    string s;
    int jifen;
    while(true) {
        Clean;
        cout << "请输入欲充值身份证号：" << endl;
        cout << "请输入欲充值的积分数：" << endl;
        gotoxy(23, 1);
        cin >> s;
        gotoxy(23, 2);
        cin >> jifen;
        if (ASS[s] == NULL)cerr << "该用户不存在，请重新输入";
        else break;
        getch();
    }
    ASS[s]->setJifen(ASS[s]->getJifen()+jifen);
    write(Accountdb);
    read(Accountdb);
    cout<<"充值成功，按任意键返回上一页...";
    getch();
    Set_User();
}

void TOOL::set_user_root() {
    Clean;
    read(Accountdb);
    string s;
    int __ROOT;
    while(true) {
        Clean;
        cout << "请输入欲设置权限用户身份证号：" << endl;
        cout << "请输入欲设置权限特征值（0 普通用户 1管理员）：" << endl;
        gotoxy(28, 1);
        cin >> s;
        gotoxy(40, 2);
        cin >> __ROOT;
        if (ASS[s] == NULL)cerr << "该用户不存在，请重新输入";
        else if (ASS[s]->getSfz()==_root_user->getSfz()) cout<<"您无法给自己设置权限！";
        else if(ASS[s]->isRoot()==true) {
            cout<<"该用户为管理员，无法降权！\n若需降权，请输入越级管理密码:";
            string p;
            cin>>p;
            if(p==$_Root_Change_PassWord){
                break;
            }
            cout<<"越级管理密码错误"<<endl;
        }
        else break;
        getch();
    }
    ASS[s]->setRoot(__ROOT);
    write(Accountdb);
    read(Accountdb);
    cout<<"设置成功，按任意键返回上一页...";
    getch();
    Set_User();
}
