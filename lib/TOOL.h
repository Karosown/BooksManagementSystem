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
    //��ǰ�˺�Ϊ
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
    //��һ��������
//    vector <Administrator *> AdminList;
//    vector <User *> UserList;
    vector<Account *> AccountList;

    void write(string dir);

//    unordered_map<_Sfz,pair<_PassWord,_ROOT> > ammatch; ?????????????
    ~TOOL(){
        write(Accountdb);
    }
    //���ò��鼯��˼��
    unordered_map<_BOOK_NAME,vector<BOOK *> >BNS;
    //�Ż���
    unordered_map<_BOOK_ID,BOOK *>BIS;//�����鱾ID��BOOK������ϵ
    unordered_map<_Sfz,Account *>ASS;//�����û����֤���û���������ϵ
    unordered_map<_Sfz,vector<BOOK*> >ASB;//�����û����֤��ѯ�û�������Щ��
    TOOL(){
        read(Accountdb,0);
        read(Bookdb,1);
    }
    /**
     * �������
     * @param dir �ļ�Ŀ¼
     * @param flag ������ʽ
     */
    void   read(string dir,bool flag=0){
        ifstream is;//����������
        is.open(dir,ios::in);//���ļ� ios::in
        if(!flag){
            AccountList.erase(AccountList.begin(), AccountList.end());
            while(!is.eof()){//EOF
                string s;
                getline(is,s);//ͨ��getline��ȡһ�У���string����
                if(s[0]=='#')continue;//����ע�;���
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
        cout<<"��������Ҫ���ͼ��ı�ţ�ʱ��ֻ��Ϊ1���£���";
        string s;
        cin>>s;
        if (BIS[s]==NULL)cout<<"�Ȿ�鲻���ڻ�δ��⣬��ȴ�����������..."<<endl;
        else if (!BIS[s]->isnotBrow1())cout<<"�Ȿ�鱻�����ˣ��´������ɣ�";
        else{
            if(_root_user->getJifen()-BIS[s]->getNeedJifen()<0){
                cout<<"���Ļ��ֲ��������ֵ����ϵ����Ա�ֶ���ӣ����˳�ֵ���ܴ�����...��"<<endl;
            }
            else{
                BIS[s]->setBrower(_root_user->getSfz());
                string newdate=getdate();
                BIS[s]->setOutDate(newdate);
                BIS[s]->setisnotBrow(0);//�Ƿ���ͼ�����
                newdate[5]++;
                BIS[s]->setBackDate(newdate);
                _root_user->setJifen(_root_user->getJifen()-BIS[s]->getNeedJifen());
                _root_user->setJycs(_root_user->getJycs()+1);
                ASB[_root_user->getSfz()].push_back(BIS[s]);
                cout<<"���óɹ���"<<endl;
                cout<<"***********************"<<endl;
                cout<<"ͼ����Ϣ���£�"<<endl;
                cout<<"������"<<BIS[s]->getBookName()<<endl;
                cout<<"�鱾��ţ�"<<BIS[s]->getBookId()<<endl;
                cout<<"���ʱ�䣺"<<BIS[s]->getInDate()<<endl;
                cout<<"���ʱ�䣺"<<BIS[s]->getOutDate()<<endl;
                cout<<"�黹ʱ�䣺"<<BIS[s]->getBackDate()<<endl;
                cout<<"�����ˣ�"<<BIS[s]->getBrower()<<endl;
                cout<<"�ķѻ��֣�"<<BIS[s]->getNeedJifen()<<endl;
                cout<<"��ǰʣ�ࣺ"<<_root_user->getJifen()<<endl;
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
        cout<<"�����������...";
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
    static void gotoxy(int x,int y)//�������
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
        cout<<"�û� "<<_root_user->getUserName()<<" �����鼮";
        gotoxy(2,4);
        cout<<"����\t\t\t���\t\t���ʱ��\t�ϴν��ʱ��\t�黹ʱ��\t�������\t�������\t\t���½�����\t������";
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
            cout<<endl<<"��������Ҫ�黹���鱾���(����[exit()]����)��";
            string id;
            cin>>id;
            if(id=="exit()")Show_Menu();
            if(BIS[id]==NULL) cout<<"�Բ����Ȿ�黹û�����Ӵ�������������..."<<endl;
            else{
                BIS[id]->setisnotBrow(1);
                BIS[id]->setBackDate(getdate());
                auto iter=std::find(ASB[_root_user->getSfz()].begin(), ASB[_root_user->getSfz()].end(), BIS[id]);
                if (iter==ASB[_root_user->getSfz()].end()){
                    cout<<"��û�н������ͼ��Ӵ��������~"<<endl;
                    getch();
                    Back_book();
                }else{
                    ASB[_root_user->getSfz()].erase(iter);
                    write(Bookdb);
                    read(Bookdb,1);
                    cout<<"�黹�ɹ��������������..."<<endl;
                }

            }
        }
        else{
            cout<<"Ŀǰ��û������Ҫ��Ӵ~�������������..."<<endl;
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
 * ��������
 */
void Account::showme() {
    Clean;
    cout<<"******************************"<<endl;
    cout<<"*          ������Ϣ"<<endl;
    cout<<"*  �û�����"<<endl;
    cout<<"*  ���֤��"<<endl;
    cout<<"*  �û�Ȩ�ޣ�"<<endl;
    cout<<"*  ʣ����֣�"<<endl;
    cout<<"*  ע��ʱ�䣺"<<endl;
    cout<<"*  �ϴε�¼ʱ�䣺"<<endl;
    cout<<"*  ���Ĵ�����"<<endl;
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
    cout<<(this->isRoot()?"����Ա":"��ͨ�û�");TOOL::gotoxy(18,6);
    cout<<this->getJifen();TOOL::gotoxy(18,7);
    cout<<this->getRegedate();TOOL::gotoxy(18,8);
    cout<<this->getNewloginDate();TOOL::gotoxy(18,9);
    cout<<this->getJycs();
    getch();
    TOOL::getDemo()->Show_Menu();
}
ostream &operator<<(ostream &os, const BOOK &book) {
    os << book.book_name <<((book.book_name.length()>=22)?" ":(book.book_name.length()<=8?"\t\t":"\t"))<< book.book_id << "\t" << book.inDate << "\t"
       << (book.outDate=="0"?"��δ���":book.outDate) << "\t" << (book.backDate=="0"?"��δ���":book.backDate) << "\t" << book.needJifen << "\t\t"
            ;
    switch (book.book_type) {
        case def::WenXue:
            os<<"��ѧ������";
            break;
        case def::Keji:
            os<<"�Ƽ�������";
            break;
        case def::Arts:
            os<<"������Ʒ��";
            break;
        case def::Computer_Program:
            os<<"����������";
            break;
        case def::Love:
            os<<"��ѧ������";
            break;
        case def::SmallTalk:
            os<<"�ƻ�С˵��";
            break;
        case def::Ohter:
            os<<"����";
            break;
        default:
            os<<"��δ����";
            break;
    }
    if (book.Brower == "0") {
        os << "\t\t" << "��δ���" << "\t" << (book.isnotBrow == 1 ? "N" : "Y");
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
