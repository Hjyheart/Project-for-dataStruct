/*名称：N皇后问题
*概要：编写一个程序输出N皇后的阵列
*作者：洪嘉勇
*日期：2015.10.10
*/
#include <iostream>
#include <string>

#define INFORMATION "现有N * N 的棋盘，放入N个皇后，要求所有皇后不在同一行，列和同一斜线上！"
#define INPUT "请输入皇后的个数（输入“0”退出程序）："

using namespace std;
/*----全局变量----*/
static int N;                   //皇后数量
static int solutionCount = 0;   //解决方案计数器
static int flag = 0;            //有误解标识
static int *nextLine;           //下一行可行位置队列
static int *queenPos;           //皇后位置记录队列

/*----打印函数----*/
void Print(){
	for (int i = 0; i < N; i++){
		for (int k = 0; k < N; k++){
			//在皇后对应位置输出“X”
			if (k == queenPos[i])
				cout << "X  ";
			else
				cout << "0  ";
		}
		cout << endl;
	}
	cout << endl << endl;
}

/*----数据存档函数----*/
void copy(int * Line){
	for (int i = 0; i < N; i++)
		Line[i] = nextLine[i];
}

/*----数据回溯函数----*/
void recopy(int *Line){
	for (int i = 0; i < N; i++)
		nextLine[i] = Line[i];
}

/*----设置下一行函数----*/
void setNextLine(int row){
	/*--判断是否已经到了最后一行--*/
	if (row == N)
		return;

	int dis;        //行距         
	memset(nextLine, 0, N * sizeof(int));
	/*--下一行的设置--*/
	for (int i = 0; i < row; i++){
		dis = row - i;
		//纵向设置下一行
		nextLine[queenPos[i]] = 1;
		//左斜下方设置下一行
		if (queenPos[i] - dis >= 0)
			nextLine[queenPos[i] - dis] = 1;
		//右斜下方设置下一行
		if (queenPos[i] + dis < N)
			nextLine[queenPos[i] + dis] = 1;
	}
}

/*----核心递归函数----*/
void solve(int row){
	/*--设置当前行队列--*/
	int *currentLine = new int[N];
	memset(currentLine, 0, N * sizeof(int));
	//数据备份
	copy(currentLine);
	/*--出解判断--*/
	if (row == N){
		//若有解调用打印函数
		Print();
		//将有解标识设置为“1”
		flag = 1;
		//解决方案加一
		solutionCount++;
		//返回上一层
		return;
	}
	/*--核心递归部分--*/
	for (int i = 0; i < N; i++){
		//判断对应位置是否可行
		if (currentLine[i] == 0){
			//记录皇后位置
			queenPos[row] = i;
			//设置下一行可行位置
			setNextLine(row + 1);
			//对下一行进行递归
			solve(row + 1);
			//递归返回之后，必须进行数据回溯
			recopy(currentLine);
		}
	}
	/*--内存释放--*/
	delete[] currentLine;
}

int main(){
	/*--用户界面--*/
	cout << INFORMATION << endl
		<< INPUT;
	cin >> N;
	//容错操作
	while (N < 0){
		cout << "N不可以小于零！！请重新输入：";
		cin >> N;
	}
	/*--循环部分--*/
	while (N != 0){
		//为指针关于N开空间并设置初始数据
		queenPos = new int[N];
		nextLine = new int[N];
		memset(nextLine, 0, N * sizeof(int));
		memset(queenPos, -1, N * sizeof(int));
		//对第一行进行单独操作（第一行为特殊情况，因为任何位置都可行）
		for (int i = 0; i < N; i++){
			//记录皇后位置
			queenPos[0] = i;
			//设置下一行
			setNextLine(1);
			//进入递归
			solve(1);
			//初始化nextLine，为下一次运作做准备
			memset(nextLine, 0, N * sizeof(int));
		}
		/*--输出界面--*/
		//无解情况
		if (!flag){
			cout << "没有解!" << endl;
		}
		//有解情况
		else{
			//输出解法个数
			cout << "共" << solutionCount << "种解法!" << endl;
			//数据初始化
			solutionCount = 0;
			flag = 0;
		}
		cout << INFORMATION << endl
			<< INPUT;
		cin >> N;
	}
	/*--内存释放--*/
	delete [] queenPos;
	delete [] nextLine;

	return 0;
}