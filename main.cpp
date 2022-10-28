#include "lib/TOOL.cpp"

void draw();

using namespace std;

int main(){
    system("title 图书管理系统");
    draw();
    Clean;
    TOOL* tool=TOOL::getDemo();
    tool->show_beginmenu();
    delete tool;
    return 0;
}

void draw() {
    TOOL::gotoxy(30,10);
    cout<<"\t\t欢迎使用本图书管理系统"<<endl;
    cout<<"\t\t\t\tTo 2022 Powered By WuZongLin www.wzl1.top";
    TOOL::gotoxy(25,11);
    for (int i = 0; i <= 100; ++i) {
        TOOL::gotoxy(30,12);
        int j;
        for (j = 0; j <= i; j+=3) {
            cout<<"<";
            if ((j&1))cout<<"<";
        }
        TOOL::gotoxy(78,12);
        if (j>100)j=100;
        cout<<j<<"%";
        cout<<"\r";
        _sleep(50);
    }
}
