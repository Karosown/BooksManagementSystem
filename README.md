# Banner

```
 ____  __.
|    |/ _|____ _______  ____  ______
|      < \__  \\_  __ \/  _ \/  ___/
|    |  \ / __ \|  | \(  <_> )___ \
|____|__ (____  /__|   \____/____  >
        \/    \/                 \/
```

居于Console的控制管理系统，使用C++|STL进行编写，适用于入门学生程序设计实践课程

# 项目要求

1. 实现用户登录以及用户注册功能

2. 管理员用户可执行用户管理（包括用户的增、删、改（积分充值和权限设置）、查）以及图书管理（增、删、查）

3. 所用用户都可进行个人资料查询、书本的借阅、归还功能

4. 结束排名实时查看，增加用户借书的活跃度

5. 拥有该系统的介绍界面

# 项目开发环境

1. 硬件环境：
   CPU型号：11th Gen Intel(R) Core(TM) i5-1135G7 @ 2.40GHz  2.42 GHz

2. 软件环境：

   操作系统：Windows 11

   编译环境：MinGW、G++14、CMake

   软件开发工具：Clion 2022 1.3

   类图设计工具：StartUML 5.0.2

   流程图设计工具：Typora - MarkDown Mermaid 0.11.18(Beta)

# 项目分析

## UML类图

![image-20221028103658641](http://7n.cdn.wzl1.top/typora/img/image-20221028103658641.png)

1. 管理员和用户具有相同属性，可以继承于同一个父类Account

2. TOOL工具类可以采取单例模式，所有工具函数写在类中，在主函数中，我们可以通过单例对象对每个功能进行单元测试

# 设计与实现

## 设计思路说明

（10分。用1）、2)、3)等序号的形式，列出自己负责的功能的设计思路。此括号内的内容如果出现在报告中，报告作废，总成绩为0分。）

### 前端界面制作

a) 

![img](http://7n.cdn.wzl1.top/typora/img/wps3.jpg)

由于是Console程序，考虑使用字符来对控制台进行美化，使用void gotoxy(int x,int y)函数来控制光标位置



b) 

![img](http://7n.cdn.wzl1.top/typora/img/wps4.jpg)

使用循环和gotoxy(x,y)函数进行最开始的进度条加载，奇偶性判断仅用于控制‘《’的输出个数

c) 

![img](http://7n.cdn.wzl1.top/typora/img/wps5.jpg)

密码遮蔽反回显设计

### 后端思路：

a) 将用户从数据文件中导入后，用vector容器存储，在唯一的TOOL对象中会有一个_root_user私有对象，用来表示当前用户，为了便于获取当前用户的对象，在导入的时候，我们也会以每个用户的身份证号码作为主键，建立一个以Account对象最为值的unordered_map容器，同理，我们也对每本书也设置了这样的unordered_map，也部分采用算法设计“并查集”的思想将每个用户所借用的书放到一个vector里面进行管理

b) 

![img](http://7n.cdn.wzl1.top/typora/img/wps6.jpg)

### 排序算法设计

本程序的排序算法采用的是C++自带的algorithm头文件中的sort函数，在日常开发中，sort函数已经可以满足绝大部分需求，在不同数据量时会采用不同的排序算法，比如快速排序、堆排序、插入排序、希尔排序等等。

c) unordered_map和map的选择

总所周知，unordered_map的底层实现时哈希表(Hash Table)，而map底层实现时红黑树（RBT），一个无序，一个有序。在查找层面上来说，unordered_map的平均时间复杂度时O(1)，最坏时间复杂度时O(n)；而map的底层红黑树是二叉搜索树，查找的时间复杂度为O(logn)，而插入和删除还需要对二叉树进行平衡操作。

d) Vector和list的选择

使用vector最开始只是为了方便在程序中进行存储，但后面仍然要erase，在这一点上来说，使用链表效率较高，在添加和删除上来说，使用list更有效率，但是在本程序并没有进行大量的删除和添加操作，所以仍然选用vector容器

## 功能单元测试

a) 大部分操作功能都被包装在TOOL类里面的，然而TOOL的对象是单例的，我们可以在main函数中通过TOOL的对象对每个功能进行单元测试

![img](http://7n.cdn.wzl1.top/typora/img/wps7.jpg) 

## 数据文件设计

本程序没有使用DBMS，但是有自身的数据库方案。

通过read(string dir,int flag)和write(string dir)对数据文件进行读入和写出操作

读入操作的原理是当文件读入输入流后，每次使用getline()函数读取一行到一个新字符串，如果行首为’#’代表注释文字，则跳过不读，每一行通过string类的find和substr函数对字符串进行处理，将数据中的空格做为分隔符，把每个文字分别存储到新的字符数组中，再通过其他对象的构造函数建立对象存放到vector和unordered_map容器中。

5) ![img](http://7n.cdn.wzl1.top/typora/img/wps8.jpg)

DEBUG调试设计



6) ![img](http://7n.cdn.wzl1.top/typora/img/wps9.jpg)

用户安全设计



密码采用反回显输出，在查询图书时，管理员端显示的借阅人时身份证号，而普通用户端显示的是用户名



  ![img](http://7n.cdn.wzl1.top/typora/img/wps10.jpg)

![img](http://7n.cdn.wzl1.top/typora/img/wps11.jpg) 

2. 功能模块图

![img](http://7n.cdn.wzl1.top/typora/img/wps12.jpg) 

1) 用户登录：输入账号密码后，根据用户的身份，登录后用户可使用的权限不同，菜单也不同

2) 用户注册：用户可以自定义用户名，并以自身的身份证号为账号进行注册，注册后即可登录
3) 关于本系统：对于本系统的一个介绍界面
4) 数据文件设计

根据对本项目的分析，设计的数据文件包含2个文件，Account.db文件是用户信息表，用于存储用户的相关信息；

表4.4 Account.db

| 字段名称      | 类型    | 长度 | 允许空 | 说明                        |
| ------------- | ------- | ---- | ------ | --------------------------- |
| User_name     | varchar | 6    | 否     | 用户名                      |
| User_password | varchar | 8    | 否     | 用户密码                    |
| Sfz           | char    | 18   | 否     | 用户身份证号，主键          |
| Regedate      | varchar | 10   | 否     | 用户注册时间                |
| Newlogin_date | varchar | 10   | 否     | 用户上次登录时间            |
| jifen         | int     | 10   | 否     | 用户积分                    |
| root          | char    | 1    | 否     | 用户权限：0普通用户 1管理员 |

表4.5 BOOK.db

| 字段名称  | 类型    | 长度 | 允许空 | 说明                                                         |
| --------- | ------- | ---- | ------ | ------------------------------------------------------------ |
| Book_name | string  | 255  | 否     | 书名                                                         |
| Book_id   | string  | 255  | 否     | 书本编号，主键                                               |
| inDate    | varchar | 10   | 否     | 入库时间                                                     |
| outDate   | varchar | 10   | 否     | 借用时间                                                     |
| backDate  | varchar | 10   | 否     | 归还时间                                                     |
| needjifen | Int     | 10   | 否     | 所需积分                                                     |
| Booktype  | Int     | 1    | 否     | 书籍类型0.文学创作类1.科技创新类2.美学艺术类3.计算机编程类4.乡村爱情类5.科幻小说类6.其他 其他数字：暂未分类 |
| isnotBrow | bool    | 1    | 否     | 是否没有被借阅，即是否在库                                   |

 

4. 详细设计

1） 借书功能的详细设计

（1） 流程图：

 

（2） 

![img](http://7n.cdn.wzl1.top/typora/img/wps13.jpg)

流程图说明：该流程开始后，先让用户输入打算借阅的图书编号，再判断这本书是否被存在，如果存在，则再判断是否被借阅，当且仅当该书存在且没有被借阅的条件下借阅成功，否则借阅失败，直接结束该流程。



2） 查书功能的详细设计

（1） 流程图：



![img](http://7n.cdn.wzl1.top/typora/img/wps14.jpg) 



（2） 流程图说明：当用户输入书名后，首先判断书名是否为通配符*，如果是，则把所有书籍都输出，不是，则判断该书是否存在，如果存在，则输出书名为该书的所有书籍，否则输出书籍查询为空

5. 实现

1） 借书功能的实现

（1） 运行效果图：



![img](http://7n.cdn.wzl1.top/typora/img/wps15.jpg) 



（2） 运行效果图说明：程序运行后，输入书籍编号即可借用

（3） 代码及注释：

```c++
void Brow_book(){

    Clean;//清屏

    read(Bookdb,1);//读入书籍数据

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

      write(Accountdb);//写出用户数据

      write(Bookdb);//写出书籍数据

      read(Accountdb,0);//读入用户数据

      read(Bookdb,1);//读入书籍数据

    }

    cout<<"按任意键返回...";

    getch();

    Show_Menu();

}
```



 

 

 

 

 

 

 

 

 

 

 

 

 

 

 

 

 

 

 

 

 

 

2） 查书功能的实现

（1） 运行效果图：![img](http://7n.cdn.wzl1.top/typora/img/wps16.jpg)

（2） 运行效果图说明：当用户输入书名后，首先判断书名是否为通配符*，如果是，则把所有书籍都输出，不是，则判断该书是否存在，如果存在，则输出书名为该书的所有书籍，否则输出书籍查询为空

（3） 代码及注释：

```cpp
void TOOL::searchBook_view(int flag=0) {
    read(Bookdb,1);
//书籍信息较长，调整屏幕大小
    SetScreenSize(GetSystemMetrics(SM_CXSCREEN),GetSystemMetrics(SM_CYSCREEN));
    int r=60,c=155;
    Clean; //清屏
//利用循环画出边框
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
    gotoxy(2,2);//移动光标
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
//判断是哪个功能调用的该函数，如果是在第一页调用的则回到第一页，如果是管理员在书籍设置界面调用的，则回到书籍设置界面
    if(!flag)Show_Menu();
    else set_BOOK();
}
```

# 总结

在本次课程设计的过程中，我掌握了UML类图的设计，一个项目的简单架构，对设计模式也有了一定深度的了解，特别是单例模式，加强了对STL容器的掌握程度，但美中不足之处是，在这次的作品中，只考虑了单线程的情况，在多线程的情况下也应该考虑线程锁以及线程优化问题，比如懒汉式单例模式就应该添加锁，避免两个线程在同时获取单例对象的时候，创建多个对象，同理也要在数据操作的地方也添加锁，避免用户脏读脏写，而且自制数据文件也有需要改进的地方，比如事务回滚之类的，也要想办法实现，数据读写过于暴力，当数据量大的情况下，容易出现系统卡死的情况，而且缓存设计不到位，重复从源数据文件中读写，脏读脏写等等都很容易产生。

目前程序未采用图形化开发，后期或将引入QT框架以及MySQL数据库进行项目重写。

# 参考文献

[1]  Stephen Prata,《C++ Primer Plus》,人民邮电出版社,2020年7月第1版

[2]  Thomas H. Cormen & Charles E. Leiserson  & Ronald L. Rivest & Clifford Stein,《算法导论》,机械工业出版社,2021年1月第1版

[3]  李煜东,《算法进阶指南》,河南电子音像出版社,2018年1月第1版

[4]  何海涛,《剑指Offer》,电子工业出版社,2011年11月第1版 & 2017年5月第2版