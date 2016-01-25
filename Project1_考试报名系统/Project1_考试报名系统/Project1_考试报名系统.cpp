/*名称：考试报名系统
*概要：编写一个考试报名系统，实现基本功能
*作者：洪嘉勇
*学号：1452822
*日期：2015.10.8
*/
#include <iostream>
#include <string>
#include <vector>
#include <utility>

#define  INFORMATION "请选择你要进行的操作（1为插入， 2为删除， 3为查找， 4为修改， 5为统计， 0为取消操作）" 
#define  ORDER_INSERT 1
#define  ORDER_DELETE 2
#define  ORDER_FIND   3
#define  ORDER_EDIT   4
#define  ORDER_COUNT  5
#define  ORDER_CANCEL 6

using namespace std;
/*----考生类----*/
struct Student{

	string name;      //姓名
	string category;  //类别
	string sex;       //性别
	int test_Number;  //考号
	int age;          //年龄

	Student *Pre;     //前指针
	Student *Next;    //后指针
};

/*----链表类----*/
class List{
private:
	Student *Head, *End;    //头指针 & 尾指针                      
	int List_Size;          //考生人数
public:
	List();
	~List();

	void add(const Student & stu);                  //添加考生
	void Insert();                                  //插入考生
	void Delete();                                  //删除考生
	void Edit();                                    //编辑考生
	void Count();                                   //统计考生
	void show();                                    //向用户展示目前所有考生及其情况
	void copy(Student * stu1, const Student & stu2);//拷贝考生

	Student * Find();                               //查找函数（无参）
	Student * Find(int pos);                        //查找函数（有参）
	Student * find(int pos);                        //查找函数（有参）
};
/*----拷贝函数----*/
void List::copy(Student * stu1, const Student & stu2){
	stu1->name = stu2.name;
	stu1->age = stu2.age;
	stu1->category = stu2.category;
	stu1->sex = stu2.sex;
	stu1->Pre = stu2.Pre;
	stu1->Next = stu2.Next;
	stu1->test_Number = stu2.test_Number;
}
/*----构造函数----*/
List::List(){
	Head = NULL;
	End = NULL;
	List_Size = 0;
}
/*----析构函数----*/
List::~List(){
	Student * p = Head;
	for (int i = 0; i < List_Size - 2; i++){
		p = p->Next;
	}
	for (int i = 0; i < List_Size - 2; i++){
		delete p->Next;
		p = p->Pre;
	}
	if (p->Next)
	    delete p->Next;
	delete p;
}
/*----展示函数----*/
void List::show(){
	Student *p = Head;

	cout << "考号    姓名    性别    年龄      类别" << endl;

	for (int i = 0; i < List_Size; i++){
		cout << p->test_Number << "       " << p->name << "     " << p->sex << "     " << p->age << "         "
			<< p->category << endl;
		if (p->Next)
		    p = p->Next;
	}
	cout << endl;
}
/*----添加函数----*/
void List::add(const Student & stu){
	Student *item = new Student;
	if (!item){
		cout << "fail" << endl;
		return;
	}
	copy(item, stu);

	List_Size++;
	//如果链表为空
	if (!Head){
		Head = item;
		End = item;
	}
	//如果链表不为空
	else{
		End->Next = item;
		item->Pre = End;
		item->Next = NULL;
		End = item;
	}
}
/*----插入函数----*/
void List::Insert(){
	Student *item = new Student;
	if (!item){
		cout << "fail" << endl;
		return;
	}
	int pos;

	cout << "输入你要插入的考生位置：";
	cin >> pos;
	//如果不是在队尾插入
	if (pos != List_Size + 1){
		Student *temp = find(pos);
		//容错操作
		while (!temp){
			cout << "对不起，没有找到您所要求插入的位置，请重新输入位置, 或者按0取消：";
			int pos2;
			cin >> pos2;
			if (pos2 == 0)
				return;
			temp = Find(pos2);
		}
		cout << "请依次输入考生的考号、姓名、性别、年龄及报考类别！" << endl;
		cin >> item->test_Number >> item->name >> item->sex >> item->age >> item->category;
		//如果前指针不为空
		if (temp->Pre != NULL){
			temp->Pre->Next = item;
			item->Pre = temp->Pre;
			item->Next = temp;
			temp->Pre = item;
		}
		//如果前指针为空
		else{
			item->Next = temp;
			item->Pre = NULL;
			temp->Pre = item;
			Head = item;
		}
	}
	else{
		cout << "请依次输入考生的考号、姓名、性别、年龄及报考类别！" << endl;
		cin >> item->test_Number >> item->name >> item->sex >> item->age >> item->category;
		//头指针为空
		if (!Head){
			Head = item;
			End = item;
		}
		//头指针不为空
		else{
			End->Next = item;
			item->Pre = End;
			item->Next = NULL;
			End = item;
		}
	}
	List_Size++;
}
/*----查找函数（无参）----*/
Student * List::Find(){
	int pos;
	Student *p = Head;

	cout << "请输入要查找的考生的考号：";
	cin >> pos;
	for (int i = 0; i < List_Size; i++){
		if (p->test_Number == pos)
			return p;
		if (p->Next)
			p = p->Next;
	}
	return NULL;
}
/*----查找函数（有参）----*/
Student * List::Find(int pos){
	Student *p = Head;

	for (int i = 0; i < List_Size; i++){
		if (p->test_Number == pos)
			return p;
		if (p->Next)
			p = p->Next;
	}
	return NULL;
}
Student * List::find(int pos){
	Student *p = Head;

	for (int i = 0; i < pos; i++){
		if (p->Next)
			p = p->Next;
	}
	return p;
}
/*----删除函数----*/
void List::Delete(){
	Student *temp;
	int pos;

	cout << "请输入要删除的考生考号:";
	cin >> pos;

	temp = Find(pos);
	//容错操作
	while (!temp){
		cout << "输入有误，请重新输入或者按0取消：";
		int pos2;
		cin >> pos2;
		if (pos2 == 0)
			return;
		temp = Find(pos2);
	}
	cout << "您要删除的考生信息为：" << "考号：" << temp->test_Number << "  名字:" << temp->name
		<< "  性别:" << temp->sex << "  年龄:" << temp->age << "  类别:" << temp->category << endl;
	//删除考生位于队列中间
	if (temp->Pre != NULL && temp->Next != NULL){
		temp->Pre->Next = temp->Next;
		temp->Next->Pre = temp->Pre;
		delete temp;
	}
	//删除考试位于队首
	if (temp->Pre == NULL && temp->Next != NULL){
		temp->Next->Pre = NULL;
		Head = temp->Next;
		delete temp;
	}
	//删除考生位于队尾
	if (temp->Pre != NULL && temp->Next == NULL){
		temp->Pre->Next = NULL;
		End = temp->Pre;
		delete temp;
	}
	List_Size--;
}
/*----编辑考生----*/
void List::Edit(){
	Student *temp;
	int pos;

	cout << "请输入要修改的考生的考号：";
	cin >> pos;

	temp = Find(pos);
	//容错操作
	while (!temp){
		cout << "请重新输入或者按0取消：";
		int pos2;
		cin >> pos2;
		if (pos2 == 0)
			return;
		temp = Find(pos2);
	}

	int chose;
	cout << "输入相应数字进行编辑,1:更改考号 2：更改姓名 3：更改性别 4：更改年龄 5:更改类别：";
	cin >> chose;
	while (chose > 5 || chose < 1){
		cout << "输入错误，按0取消或输入相应数字进行编辑,1:更改考号 2：更改姓名 3：更改性别 4：更改年龄 5:更改类别：";
		cin >> chose;
		if (chose == 0)
			return;
	}
	//新信息
	int new_Age;
	int new_Test_Number;
	string new_Name;
	string new_Sex;
	string new_Kind;
	//对应操作
	switch (chose){
	case 1:
		cout << "请输入新考号：";
		cin >> new_Test_Number;
		temp->test_Number = new_Test_Number;
		break;
	case 2:
		cout << "请输入新姓名:";
		cin >> new_Name;
		temp->name = new_Name;
		break;
	case 3:
		cout << "请输入新性别：";
		cin >> new_Sex;
		temp->sex = new_Sex;
		break;
	case 4:
		cout << "请输入新年龄:";
		cin >> new_Age;
		temp->age = new_Age;
		break;
	case 5:
		cout << "请输入新类别:";
		cin >> new_Kind;
		temp->category = new_Kind;
		break;
	default:
		break;
	}
}
/*----统计函数----*/
void List::Count(){
	cout << "总共" << List_Size << "考生" << endl;
	int boy_Num = 0, gir_Num = 0;      //男女生统计
	Student *p = Head;                 //临时指针
	vector <pair<string, int> > kind;  //类别统计容器
	vector <pair<int, int> > Age;      //年龄统计容器
	//扫描统计
	for (int i = 0; i < List_Size; i++){
		if (p->sex == "男")
			boy_Num++;
		else
			gir_Num++;
		if (kind.empty())
			kind.push_back(make_pair(p->category, 1));
		else{
			for (int k = 0; k < kind.size(); k++){
				if (kind[k].first == p->category){
					kind[k].second++;
					break;
				}
				if (k == kind.size() - 1){
					kind.push_back(make_pair(p->category, 1));
					break;
				}
			}
		}

		if (Age.empty())
			Age.push_back(make_pair(p->age, 1));
		else{
			for (int k = 0; k < Age.size(); k++){
				if (Age[k].first == p->age){
					Age[k].second++;
					break;
				}
				if (k == Age.size() - 1){
					Age.push_back(make_pair(p->age, 1));
					break;
				}
			}
		}

		if (p->Next != NULL)
			p = p->Next;
	}
	//输出
	cout << "共" << boy_Num << "个男生, 共" << gir_Num << "个女生" << endl;
	cout << "有以下几大类别" << endl;

	for (int i = 0; i < kind.size(); i++)
		cout << kind[i].first << ":" << kind[i].second << "人" << endl;

	cout << endl;

	cout << "有几大年龄段:" << endl;
	for (int i = 0; i < Age.size(); i++)
		cout << Age[i].first << ":" << Age[i].second << "人" << endl;
}

int main(){
	int amount, order;
	Student temp = { "", "", "", 0, 0, NULL, NULL };
	Student *p = NULL;
	List Test_System;

	cout << "首先请建立考生信息系统!" << endl << "请输入考生人数：";
	cin >> amount;
	//输入信息
	cout << "请依次输入考生的考号、姓名、性别、年龄及报考类别！" << endl;

	for (int i = 0; i < amount; i++){
		cin >> temp.test_Number >> temp.name >> temp.sex
			>> temp.age >> temp.category;
		//性别容错
		while (temp.sex != "男" && temp.sex != "女"){
			cout << endl << "性别错误， 重新输入性别(男 or 女):";
			cin >> temp.sex;
		}
		Test_System.add(temp);
	}
	//展示信息
	cout << "数据情况为：" << endl;
	Test_System.show();
	//选择操作
	cout << INFORMATION << endl
		<< "请选择你要进行的操作：";
	cin >> order;
	//循环输入
	while (order != ORDER_CANCEL){
		//根据参数order选择操作
		switch (order){
		case ORDER_INSERT:
			Test_System.Insert(); break;
		case ORDER_DELETE:
			Test_System.Delete(); break;
		case ORDER_FIND:
			p = Test_System.Find();
			if (p){
				cout << "考号    姓名    性别    年龄      类别" << endl;
				cout << p->test_Number << "       " << p->name << "     " << p->sex << "     " << p->age << "         "
					<< p->category << endl;
			}
			else
				cout << "查无此人！" << endl;
			break;
		case ORDER_EDIT:
			Test_System.Edit(); break;
		case ORDER_COUNT:
			Test_System.Count();
			break;
		default:
			break;
		}
		cout << "经操作后数据为：" << endl;
		Test_System.show();
		cin.get();
		//循环
		cout << INFORMATION << endl
			<< "请选择你要进行的操作：";
		cin >> order;
	}
	return 0;
}