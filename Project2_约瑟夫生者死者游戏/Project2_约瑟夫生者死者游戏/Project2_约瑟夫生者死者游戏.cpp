/*名称：约瑟夫生者死者游戏
*概要：编写一个约瑟夫生死环游戏的模拟程序
*作者：洪嘉勇
*学号：1452822
*日期：2015.10.9
*/
#include <iostream>

using namespace std;
/*----玩家结构体----*/
struct Player{
	int pos;               //玩家所处初始位置
	struct Player * Next;  //尾指针
};
/*----核心函数----*/
Player * solve(int n, int s, int m, int k){
	Player *p;                         //临时指针
	Player *Josephus = new Player[n];  //创建约瑟夫循环链表
	int count = 1;                     //计数器
	//约瑟夫环的初始化
	for (int i = 0; i < n; i++){
		Josephus[i].pos = i + 1;
		if (i != n - 1)
			Josephus[i].Next = &Josephus[i + 1];
		else
			Josephus[i].Next = &Josephus[0];
	}
	//寻找第一个位置，对s = 1进行特殊处理
	s--;
	if (s - 1 >= 0)
		p = &Josephus[s - 1];
	else
		p = &Josephus[n - 1];
	//将死者删除出链表，累加位置，直到达到人数要求
	while (n > k){
		for (int i = 0; i < m - 1; i++)
			p = p->Next;
		cout << "第" << count << "个死者的位置是:    " << p->Next->pos << endl;
		n--;
		count++;
		p->Next = p->Next->Next;
	}
	//为达到从小到大输出，移动指针
	while (p->pos < p->Next->pos)
		p = p->Next;
	p = p->Next;
	return p;
}

int main(){
	int N, S, M, K;
	Player *p;

	cout << "现有N人围成一圈， 从第S个人开始依次报数，报M的人出局，再由下一个人开始报数，如此循环，直到剩下K个人为止" << endl;

	cout << "请输入生死游戏的总人数N: ";
	cin >> N;
	//容错操作
	while (N < 2){
		cout << "至少需要两个人！请重新输入:";
		cin >> N;
	}

	cout << "请输入游戏开始的位置:    ";
	cin >> S;
	//容错操作
	while (S > N){
		cout << "错误的位置，请重新输入:";
		cin >> S;
	}

	cout << "请输入死亡数字M:         ";
	cin >> M;

	cout << "请输入剩余的生者人数K:   ";
	cin >> K;
	//容错操作
	while (K > N){
		cout << "错误的输入，请重新输入:";
		cin >> K;
	}
	//调用核心函数
	p = solve(N, S, M, K);
	//输出
	cout << "最后剩下:    " << K << "人" << endl;
	cout << "剩余的生者位置为:    ";

	for (int i = 0; i < K; i++){
		cout << p->pos << "    ";
		p = p->Next;
	}
	return 0;
}