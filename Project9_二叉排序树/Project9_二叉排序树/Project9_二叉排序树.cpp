#include <iostream>
#include <vector>

using namespace std;

struct Node{ 
	int data;               //保存的数据
	Node * leftChild;       //左子树
	Node * rightChild;      //右子树
};

class Tree{
private:
	Node * root;                          //根节点
public:
	Tree() :root(NULL){};                 //默认构造函数
	~Tree();                              //析构函数

	void one_BuildTree();                 //生成二叉排序树
	void two_Insert();                    //插入节点
	void three_Find();                    //查找节点

	void destroy(Node *p);                //摧毁节点
	void build(Node *p, Node *current);   //生成二叉排序树辅助函数
	void Print(Node *node);               //打印
	void search(int number, Node *node);  //查找辅助函数

	Node * create();                      //创建空节点
};

/*---析构函数---*/
Tree::~Tree(){
	destroy(root);
}
/*---摧毁节点---*/
void Tree::destroy(Node *p){
	if (p->leftChild)
		destroy(p->leftChild);
	if (p->rightChild)
		destroy(p->rightChild);
	delete p;
}
/*---创建空节点---*/
Node * Tree::create(){
	Node *p = new Node();

	p->data = 0;
	p->leftChild = NULL;
	p->rightChild = NULL;

	return p;
}
/*---生成二叉排序树---*/
void Tree::one_BuildTree(){
	vector <int> que;
	int key, flag = 0;
	cout << "Please input key to create Bsort_Tree(end with 0):" << endl;
	cin >> key;
	while (key != 0){
		for (int i = 0; i < que.size(); i++){
			if (que[i] == key){
				cout << "The input key<" << key << "> is have in!" << endl;
				flag = 1;
				break;
			}
		}
		if (!flag)
			que.push_back(key);
		flag = 0;
		cin >> key;
	}

	root = create();
	if (!root){
		cout << "内存分配失败！" << endl;
		return;
	}
	root->data = que[0];

	for (int i = 1; i < que.size(); i++){
		Node *p = create();
		if (!p){
			cout << "内存分配失败" << endl;
			return;
		}
		p->data = que[i];
		build(p, root);
	}

	cout << "Bsort_Tree is:" << endl;
	Print(root);
	cout << endl << endl;
}
/*---插入节点---*/
void Tree::two_Insert(){
	int num;
	cout << "Please input  key which inserted: ";
	cin >> num;

	Node *p = create();
	if (!p){
		cout << "内存分配失败！" << endl;
		return;
	}
	p->data = num;

	build(p, root);

	cout << "Bsort_Tree is:" << endl;
	Print(root);
	cout << endl << endl;
}
/*---查找节点---*/
void Tree::three_Find(){
	int num;
	cout << "Please input key which searched: ";
	cin >> num;

	search(num, root);
}
/*---生成二叉树辅助函数---*/
void Tree::build(Node *p, Node *current){
	if (p->data > current->data){
		if (!current->rightChild){
			current->rightChild = p;
			return;
		}
		build(p, current->rightChild);
	}
	if (p->data < current->data){
		if (!current->leftChild){
			current->leftChild = p;
			return;
		}
		build(p, current->leftChild);
	}
	if (p->data == current->data)
		cout << p->data << " have in！";
}
/*---打印---*/
void Tree::Print(Node *node){
	Node *p = node;
	if (p->leftChild)
		Print(p->leftChild);
	cout << p->data << " -> ";
	if (p->rightChild)
		Print(p->rightChild);
}
/*---查找辅助函数---*/
void Tree::search(int number, Node *node){

	if (number < node->data){
		if (!node->leftChild){
			cout << number << " is not exist!" << endl;
			return;
		}
		search(number, node->leftChild);
	}
	if (number > node->data){
		if (!node->rightChild){
			cout << number << " is not exist!" << endl;
			return;
		}
		search(number, node->rightChild);
	}
	if (number == node->data){
		cout << number << " is exist." << endl;
		if (node->leftChild)
			cout << "It's leftChild is " << node->leftChild->data << endl;
		if (node->rightChild)
			cout << "It's rightChild is " << node->rightChild->data << endl;
	}
}

int main(){
	cout << "**                           二叉排序树                           **" << endl;
	cout << "====================================================================" << endl;
	cout << "**                         1 --- 建立二叉排序树                   **" << endl;
	cout << "**                         2 --- 插入元素                         **" << endl;
	cout << "**                         3 --- 查询元素                         **" << endl;
	cout << "**                         4 --- 退出程序                         **" << endl;
	cout << "====================================================================" << endl;
	
	int order;
	Tree tree;

	cout << "Please select: ";
	cin >> order;
	while (order != 4){
		switch (order){
		case 1:
			tree.one_BuildTree();
			break;
		case 2:
			tree.two_Insert();
			break;
		case 3:
			tree.three_Find();
			break;
		default:
			cout << "输入有误" << endl;
		}
		cout << "Please select: ";
		cin >> order;
	}
	return 0;
}