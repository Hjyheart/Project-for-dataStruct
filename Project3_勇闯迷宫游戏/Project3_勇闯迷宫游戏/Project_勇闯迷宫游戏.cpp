#include <iostream>
#include <string>
#include <fstream>

using namespace std;

/*---保存中间过程的栈----*/
struct flag{
	int X;    //行坐标
	int Y;    //列坐标

	struct flag* Next; //下一步
};
/*---全局变量----*/
static char **map;       //地图指针
static int row, col;     //行， 列
static int en_X, en_Y;   //入口坐标
static int out_X, out_Y; //出口坐标
string commond;          //指令
flag *Head;              //解决方案

/*----展示函数----*/
void display(){
	bool search(int x, int y);
	cout << "      ";
	for (int i = 0; i <= col; i++)
		cout << "第" << i << "列" << "    ";
	cout << endl;
	for (int i = 0; i <= row; i++){
		cout << "第" << i << "行     ";
		for (int k = 0; k <= col; k++){
			if (!search(i, k) || (i == out_X && k == out_Y))
				cout << "X" << "        ";
			else
				cout << map[i][k] << "        ";
		}
		cout << endl << endl;
	}
}
/*----核心函数----*/
void solve(){
	bool toNext(int x, int y);
	/*--向上走--*/
	if (en_X - 1 >= 0 && map[en_X - 1][en_Y] == '0'){
		//调用探索函数，可行则跳出递归
		if (toNext(en_X - 1, en_Y))
			return;
		//该方向不可行执行出栈
		else{
			flag *p = Head->Next;
			delete p;
			Head->Next = NULL;
		}
	}
	/*--向下走--*/
	if (en_X + 1 <= row && map[en_X + 1][en_Y] == '0'){
		//调用探索函数，可行则跳出递归
		if (toNext(en_X + 1, en_Y))
			return;
		//该方向不可行执行出栈
		else{
			flag *p = Head->Next;
			delete p;
			Head->Next = NULL;
		}
	}
	/*--向左走--*/
	if (en_Y - 1 >= 0 && map[en_X][en_Y - 1] == '0'){
		//调用探索函数，可行则跳出递归
		if (toNext(en_X, en_Y - 1))
			return;
		//该方向不可行执行出栈
		else{
			flag *p = Head->Next;
			delete p;
			Head->Next = NULL;
		}
	}
	/*--向右走--*/
	if (en_Y + 1 <= col && map[en_X][en_Y + 1] == '0'){
		//调用探索函数，可行则跳出递归
		if (toNext(en_X, en_Y + 1))
			return;
		//该方向不可行执行出栈
		else{
			flag *p = Head->Next;
			delete p;
			Head->Next = NULL;
		}
	}
}
/*----递归函数----*/
bool toNext(int x, int y){
	bool search(int x, int y);
	/*--创建新节点，并入栈--*/
	flag *newWay = new flag, *p = Head;
	newWay->X = x;
	newWay->Y = y;
	newWay->Next = NULL;
	while (p && p->Next)
		p = p->Next;
	p->Next = newWay;
	/*--判断该点是否为终点--*/
	if (x == out_X && y == out_Y)
		return true;
	/*--向上试探--*/
	if (x - 1 >= 0 && map[x - 1][y] == '0' && search(x - 1, y)){
		//递归调用探索函数，可行则跳出递归
		if (toNext(x - 1, y))
			return true;
		//该方向不可行执行出栈
		else{
			flag * temp = newWay->Next;
			delete temp;
			newWay->Next = NULL;
		}
	}
	/*--向下试探--*/
	if (x + 1 <= row && map[x + 1][y] == '0' && search(x + 1, y)){
		//递归调用探索函数，可行则跳出递归
		if (toNext(x + 1, y))
			return true;
		//该方向不可行执行出栈
		else{
			flag * temp = newWay->Next;
			delete temp;
			newWay->Next = NULL;
		}
	}
	/*--向左试探--*/
	if (y - 1 >= 0 && map[x][y - 1] == '0' && search(x, y - 1)){
		//递归调用探索函数，可行则跳出递归
		if (toNext(x, y - 1))
			return true;
		//该方向不可行执行出栈
		else{
			flag * temp = newWay->Next;
			delete temp;
			newWay->Next = NULL;
		}
	}
	/*--向右试探--*/
	if (y + 1 <= col && map[x][y + 1] == '0' && search(x, y + 1)){
		//递归调用探索函数，可行则跳出递归
		if (toNext(x, y + 1))
			return true;
		//该方向不可行执行出栈
		else{
			flag * temp = newWay->Next;
			delete temp;
			newWay->Next = NULL;
		}
	}
	return false;
}
/*--搜索是否走过函数--*/
bool search(int x, int y){
	flag *p = Head;
	while (p && p->Next){
		if (p->X == x && p->Y == y)
			return false;
		p = p->Next;
	}
	return true;
}
/*--模式A选择函数--*/
void modeA(){
	int order;
	cout << "请选择地图(1, 2, 3):";
	cin >> order;
	while (order != 1 && order != 2 && order != 3){
		cout << "输入有误，重新输入:";
		cin >> order;
	}

	ifstream inFile1, inFile2, inFile3;
	inFile1.open("maze1.txt");
	inFile2.open("maze2.txt");
	inFile3.open("maze3.txt");
	if (!inFile1){
		cout << "文件1打开失败";
		return;
	}
	if (!inFile2){
		cout << "文件2打开失败";
		return;
	}
	if (!inFile3){
		cout << "文件3打开失败";
		return;
	}
	if (order == 1){
		map = new char*[3];
		for (int i = 0; i < 3; i++){
			map[i] = new char[3];
		}
		inFile1 >> en_X >> en_Y >> out_X >> out_Y;
		for (int i = 0; i < 3; i++){
			for (int k = 0; k < 3; k++)
				inFile1 >> map[i][k];
		}
		row = 2;
		col = 2;
	}
	if (order == 2){
		map = new char*[4];
		for (int i = 0; i < 4; i++){
			map[i] = new char[4];
		}
		inFile2 >> en_X >> en_Y >> out_X >> out_Y;
		for (int i = 0; i < 4; i++){
			for (int k = 0; k < 4; k++)
				inFile2 >> map[i][k];
		}
		row = 3;
		col = 3;
	}
	if (order == 3){
		map = new char*[5];
		for (int i = 0; i < 5; i++){
			map[i] = new char[5];
		}
		inFile3 >> en_X >> en_Y >> out_X >> out_Y;
		for (int i = 0; i < 5; i++){
			for (int k = 0; k < 5; k++)
				inFile3 >> map[i][k];
		}
		row = 4;
		col = 4;
	}
		Head = new flag;
		Head->X = en_X;
		Head->Y = en_Y;
		Head->Next = NULL;
		//出入口设置
		map[en_X][en_Y] = '0';
		map[out_X][out_Y] = '0';
		/*----调用核心函数寻找路径----*/
		solve();
		/*----输出----*/
		//迷宫无解
		if (Head->Next == NULL){
			cout << "此迷宫无解！" << endl;
			//释放内存
			delete[] map;
			delete Head;
		}
		//迷宫有解
		else{
			display();
			flag *p = Head;
			while (p){
				if (p->Next == NULL)
					cout << "(" << p->X << ", " << p->Y << ")";
				else
					cout << "(" << p->X << ", " << p->Y << ")->";
				p = p->Next;
			}
			cout << endl;
			//释放内存
			delete[] map;
			delete Head;
		}
}
/*--模式B选择函数--*/
void modeB(){
	string commondB = "Yes";
	while (commondB == "Yes"){
		/*----行和列的输入----*/
		cout << "请输入迷宫的大小（存在0行和0列）， 行:";
		cin >> row;
		cout << "列：";
		cin >> col;
		//检查输入是否有误
		while (row < 0 || col < 0){
			cout << "输入有误，行列必须非零！！请重新输入。\n";
			cout << "请输入迷宫的大小（存在0行和0列）， 行:";
			cin >> row;
			cout << "列：";
			cin >> col;
		}
		/*----入口的输入----*/
		cout << "请输入迷宫的入口坐标（存在0行和0列）, X:";
		cin >> en_X;
		cout << "Y:";
		cin >> en_Y;
		//检查输入是否有误
		while (en_X < 0 || en_X > col || en_Y < 0 || en_Y > row){
			cout << "入口坐标输入有误！！请根据迷宫大小正确输入。\n";
			cout << "请输入迷宫的入口坐标（存在0行和0列）, X:";
			cin >> en_X;
			cout << "Y:";
			cin >> en_Y;
		}
		/*----出口的输入----*/
		cout << "请输入迷宫的出口坐标（存在0行和0列）, X:";
		cin >> out_X;
		cout << "Y:";
		cin >> out_Y;
		//检查输入是否有误
		while (out_X < 0 || out_X > col || out_Y < 0 || out_Y > row){
			cout << "出口坐标输入有误！！请根据迷宫大小正确输入。\n";
			cout << "请输入迷宫的出口坐标（存在0行和0列）, X:";
			cin >> out_X;
			cout << "Y:";
			cin >> out_Y;
		}
		/*----地图和标记的初始化----*/
		cout << "现在请您自定义键入地图，其中\"#\"代表障碍物，\"0\"代表畅通的道路，非0键入我们都将视为障碍，出入口我们将强制设置为畅通\n";
		map = new char *[row + 1];
		for (int i = 0; i <= row; i++)
			map[i] = new char[col + 1];
		for (int i = 0; i <= row; i++)
			for (int k = 0; k <= col; k++)
				cin >> map[i][k];
		Head = new flag;
		Head->X = en_X;
		Head->Y = en_Y;
		Head->Next = NULL;
		//出入口设置
		map[en_X][en_Y] = '0';
		map[out_X][out_Y] = '0';
		/*----调用核心函数寻找路径----*/
		solve();
		/*----输出----*/
		//迷宫无解
		if (Head->Next == NULL){
			cout << "此迷宫无解！" << endl;
			//释放内存
			delete[] map;
			delete Head;
		}
		//迷宫有解
		else{
			display();
			flag *p = Head;
			while (p){
				if (p->Next == NULL)
					cout << "(" << p->X << ", " << p->Y << ")";
				else
					cout << "(" << p->X << ", " << p->Y << ")->";
				p = p->Next;
			}
			cout << endl;
			//释放内存
			delete[] map;
			delete Head;
		}
		cout << "Do you want to play again? input“Yes”or “No”:" << endl;
		cin >> commondB;
		while (commondB != "Yes" && commondB != "No"){
			cout << "输入有误" << endl;
			cout << "Do you want to play again? input“Yes”or “No”:" << endl;
			cin >> commondB;
		}
	}
	return;
}

int main(){

	cout << "************************************************************************" << endl;
	cout << "                          欢迎来到勇闯迷宫游戏                          " << endl;
	cout << "                            A--选择地图模式                             " << endl;
	cout << "                            B--自定义地图模式                           " << endl;
	cout << "                            E--退出游戏                                 " << endl;
	cout << "************************************************************************" << endl;

	cout << "请输入指令：";
	cin >> commond;

	while (commond != "E"){
		if (commond == "A")
			modeA();
		if (commond == "B")
			modeB();
		cout << "请输入指令：";
		cin >> commond;
	}
	return 0;
}