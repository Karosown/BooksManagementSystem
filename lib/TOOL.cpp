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
    cout<<"*           ͼ�����ϵͳ           ";
    gotoxy(34,2);
    cout<<"*"<<endl;
    cout<<"*          1.�û���¼             ";
    gotoxy(34,3);
    cout<<"*"<<endl;
    cout<<"*          2.�û�ע��             ";
    gotoxy(34,4);
    cout<<"*"<<endl;
    cout<<"*          3.���ڱ�ϵͳ           ";
    gotoxy(34,5);
    cout<<"*"<<endl;
    cout<<"*          4.�˳�                ";
    gotoxy(34,6);    cout<<"*"<<endl;
    cout<<"*    ���������ѡ�񣺡� ��          ";
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
    cout<<"*           �û���¼";
    gotoxy(34,2);
    cout<<"*"<<endl;
    cout<<"*   ���֤��:";
    gotoxy(34,3);
    cout<<"*"<<endl;
    cout<<"*   �û�����:";
    gotoxy(34,4);    cout<<"*"<<endl;
    cout<<"**********************************"<<endl;
    cout<<"��û��ע����ȫ����д00000000ǰ��ע��";
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
        cout<<"���벻���Ϲ淶"<<endl;
        password="";
        gotoxy(14,4);
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 07);
        cout<<"\r";
        cout<<"*   �û�����:                       ";
        gotoxy(34,4);    cout<<"*"<<endl;
    }
    if (account=="00000000"&&password=="00000000")show_regesit(0);
    int _root=Login(account,password);
//    DEBUG(_root);
    if (_root) {
        //�Ż���
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
        cerr<<"�������֤����������Ƿ���ȷƥ�䣬���˺����벻������ϵ����Ա�����޸�"<<endl;
        getch();
        show_Login();
    }
}

void TOOL::show_regesit(int flag=0) {
    Clean;
    read(Accountdb,0);
    cout<<"**********************************"<<endl;
    cout<<"*           �û�ע��";
    gotoxy(34,2);
    cout<<"*"<<endl;
    cout<<"*      �û���:";
    gotoxy(34,3);
    cout<<"*"<<endl;
    cout<<"*      �û�����:";
    gotoxy(34,4);    cout<<"*"<<endl;
    cout<<"*      ���֤:";
    gotoxy(34,5);    cout<<"*"<<endl;
    cout<<"**********************************"<<endl;
    cout<<"ע������:�û�����4~6���ַ����ڣ�������#��ͷ��,�û�����������6���ַ�,�8��";
    string account,password;
    while(1){
        gotoxy(16,3);
        cin>>account;
        if(account[0]!='#'&&account.length()<=6&&account.length()>=4)break;
        gotoxy(1,8);
        cout<<"�û��������Ϲ淶";
        getch();
        show_regesit();
    }
    while(1){
        gotoxy(17,4);
        char ch;
        int len=0;
        while((ch=getch())&&ch!=13){
            //�˸��
            if(ch==8){
                //����Ļ�ϵ�*������8��ʱ
                if(0<len&&len<=8) cout<<"\b \b";
                //������
                if(len)password.erase(password.end()-1),len--;
                continue;
            }
            else password+=ch,len++;
            if (len<=8)cout<<"*";
        }
        if (password.length()>=6&&password.length()<=8)break;
        gotoxy(1,8);
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED);

        cout<<"���벻���Ϲ淶"<<endl;
        password="";
        gotoxy(17,4);
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 07);

        cout<<"\r";
        cout<<"*      �û�����:                         ";
        gotoxy(34,4);    cout<<"*"<<endl;
    }
    string sfz;
    while(1){
        gotoxy(15,5);
        cin>>sfz;
        gotoxy(1,8);
        if (sfz.length()==18&&Isdigit(sfz)&&sfz[0]>='1') {
//            if (ammatch.find(sfz)!=ammatch.end())cerr<<"��ǰ���֤��ע����˺ţ�";
            if (ASS.find(sfz)!=ASS.end())cerr<<"��ǰ���֤��ע����˺ţ�";
            else break;
        }
        else cout<<"���֤�����Ϲ淶"<<endl;
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED);
        gotoxy(16,5);
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 07 );
        cout<<"\r";
        cout<<"*      ���֤:                       ";
        gotoxy(34,5);    cout<<"*"<<endl;
    }
    regist(account,password,sfz);
    gotoxy(1,8);
    if(!flag){
        cout<<"ע��ɹ�������ǰ����¼��"<<endl;
        getch();
        show_Login();
    }else{
        cout<<"�û���ӳɹ���"<<endl;
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
    cout<<"����������������*��ѯ����ͼ�飩��";
    gotoxy(2,4);
    cout<<"����\t\t\t���\t\t���ʱ��\t�ϴν��ʱ��\t�黹ʱ��\t�������\t�������\t\t���½�����\t������";
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
        for(auto item:BNS["��"+book_name+"��"]){
            gotoxy(2,i++);
            cout<<(*item);
        }
    }
    cout<<endl;
    for(int i=0;i<c;i++) cout<<"*";
    cout<<endl;
    cout<<"�������������һҳ...";
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
        //��ʼ�˵�����
        case 0:
            switch (x) {
                //�û���¼
                case 1:
                    Clean;
                    show_Login();
                    break;
                    //�û�ע��
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
            //�˵�����
        case 1:
            switch (x) {
//                ���ز˵�
                case 0:
                    show_beginmenu();
                    break;
                case 1:
                    _root_user->showme();
                    break;
//                �鼮��ѯ
                case 2:
                    searchBook_view();
                    break;
//                ����ͼ��
                case 3:
                    Brow_book();
                    break;
//                �黹ͼ��
                case 4:
                    Back_book();
                    break;
//                �������
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
            //�����鼮����
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
            //�����û�����
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
    cout<<"*     ͼ�����ϵͳ-"+_root_user->getUserName()+"("+
          (this->_root_user->isRoot()==true?("����Ա"):("��ͨ�û�"))
          +")";
    gotoxy(40,2);
    cout<<"*"<<endl;
    cout<<"*   1.������Ϣ";
    gotoxy(40,3);
    cout<<"*"<<endl;
    cout<<"*   2.�鼮��ѯ";
    gotoxy(40,4);
    cout<<"*"<<endl;
    cout<<"*   3.����ͼ��";
    gotoxy(40,5);
    cout<<"*"<<endl;
    cout<<"*   4.�黹ͼ��";
    gotoxy(40,6);
    cout<<"*"<<endl;
    cout<<"*   5.�����ܰ�";
    gotoxy(40,7);
    cout<<"*"<<endl;
    if (this->_root_user->isRoot()){
        //����Ա�û�
        cout<<"*   6.�鼮����";
        gotoxy(40,8);
        cout<<"*"<<endl;
        cout<<"*   7.�û�����";
        gotoxy(40,9);
        cout<<"*"<<endl;
    }
    if (this->_root_user->isRoot())gotoxy(1,10);
    else gotoxy(1,8);
    cout<<"* ��ѡ���Ӧ���(0����):�� ��";
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
    cout<<"�۷��"<<endl;
    cout<<"����\t\t�û���\t\t�������"<<endl;
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
            //#���� ��� ���ʱ�� �ϴν��ʱ�� �黹ʱ�� ������� ������� ���½����� ������
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
    cout<<"1.��ѯͼ��"<<endl;
    cout<<"2.���ͼ��"<<endl;
    cout<<"3.ɾ��ͼ��"<<endl;
    cout<<"����������"<<endl;
    cout<<"��ѡ��";
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
    cout<<"������"<<endl;
    cout<<"��ţ�"<<endl;
    cout<<"������֣�"<<endl;
    cout<<"���ͣ�"<<endl;
    cout<<"���ͽ��ͣ�\n\t0.��ѧ������\n\t1.�Ƽ�������\n\t2.��ѧ������\n\t3.����������\n\t4.��尮����\n\t5.�ƻ�С˵��\n\t6.����\n�������֣���δ���ࣨ���������Զ�����๦�ܣ�"<<endl;
    gotoxy(6,1);
    cin>>name;
    name.insert(0,"��");
    name.insert(name.length(),"��");
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
    cout<<"��ӳɹ����������������һҳ��";
    getch();
    set_BOOK();
}

void TOOL::Delete_BOOK() {
    Clean;
    string id;
    cout<<"������Ҫɾ��ͼ��ı�ţ�����*ȫ��ɾ������Ҫɾ��ĳЩͼ�飬��������#��������";
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
    cout<<"ɾ���ɹ�����ɾ�� "<<num<<" ����"<<endl;
    getch();
    set_BOOK();
}

void TOOL::Set_User() {
    Clean;
    cout<<"1.�鿴�û����ݿ�"<<endl;//�����ˣ����Բ鿴����
    cout<<"2.�����û�"<<endl;
    cout<<"3.ɾ���û�"<<endl;
    cout<<"4.�޸��û�����"<<endl;
    cout<<"5.���ֳ�ֵ"<<endl;
    cout<<"6.�û�Ȩ������"<<endl;
    cout<<"����������һҳ"<<endl;
    cout<<"��ѡ��";
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
    cout<<"�������û���������*��ѯ�����û�����";
    gotoxy(2,4);
    //�û��� ����      ���֤��        ע������ ����¼���� ���� �û�Ȩ�� ���Ĵ���
    cout<<"�û���\t����\t���֤��\tע��ʱ��  ����¼����\t����\t�û�Ȩ��(1 admin 0 user)\t���Ĵ���";
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
    cout<<"�������������һҳ...";
    getch();
    Show_Menu();
}
void TOOL::drop_User() {
    read(Accountdb,0);
    string sfz;
    while (true) {
        Clean;
        cout << "��������ɾ���û������֤��";
        cin >> sfz;
        if (ASS[sfz] == NULL) {
            cout<<"���û������ڣ������������";
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
    cout<<"ɾ���ɹ����������������һҳ...";
    getch();
    Set_User();
}
void TOOL::update_password() {
    Clean;
    read(Accountdb,0);
    cout<<"���������޸��û������֤��";
    string sfz;
    cin>>sfz;
    cout<<"���������޸��û������룺";
    string password;
    cin>>password;
    ASS[sfz]->setUserPassword(password);
    write(Accountdb);
    read(Accountdb,0);
    cout<<"�޸ĳɹ����������������һҳ...";
    getch();
    Set_User();
}

void TOOL::Recharge() {
    read(Accountdb);
    string s;
    int jifen;
    while(true) {
        Clean;
        cout << "����������ֵ���֤�ţ�" << endl;
        cout << "����������ֵ�Ļ�������" << endl;
        gotoxy(23, 1);
        cin >> s;
        gotoxy(23, 2);
        cin >> jifen;
        if (ASS[s] == NULL)cerr << "���û������ڣ�����������";
        else break;
        getch();
    }
    ASS[s]->setJifen(ASS[s]->getJifen()+jifen);
    write(Accountdb);
    read(Accountdb);
    cout<<"��ֵ�ɹ����������������һҳ...";
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
        cout << "������������Ȩ���û����֤�ţ�" << endl;
        cout << "������������Ȩ������ֵ��0 ��ͨ�û� 1����Ա����" << endl;
        gotoxy(28, 1);
        cin >> s;
        gotoxy(40, 2);
        cin >> __ROOT;
        if (ASS[s] == NULL)cerr << "���û������ڣ�����������";
        else if (ASS[s]->getSfz()==_root_user->getSfz()) cout<<"���޷����Լ�����Ȩ�ޣ�";
        else if(ASS[s]->isRoot()==true) {
            cout<<"���û�Ϊ����Ա���޷���Ȩ��\n���轵Ȩ��������Խ����������:";
            string p;
            cin>>p;
            if(p==$_Root_Change_PassWord){
                break;
            }
            cout<<"Խ�������������"<<endl;
        }
        else break;
        getch();
    }
    ASS[s]->setRoot(__ROOT);
    write(Accountdb);
    read(Accountdb);
    cout<<"���óɹ����������������һҳ...";
    getch();
    Set_User();
}
