#include <iostream>
#include <string>
#include <stack>

using namespace std;

/*----节点结构体和树类----*/
struct Node{
	char data;
	Node * leftChild;
	Node * rightChild;
};

class Tree{
private:
	Node * root;
	static int count;
public:
	Tree() :root(NULL){}
	Tree(const string s){ root = buildTree(s); }
	Node* buildTree(const string s);
	Node* create();
	Node* getRoot();

	void PostOrder(Node* node);
	void Inorder(Node* node);
};

int Tree::count = 0;

/*----创建树的节点----*/
Node* Tree::create(){
	Node* p = new Node();
	p->data = ' ';
	p->leftChild = NULL;
	p->rightChild = NULL;
	return p;
}

/*----获取根树----*/
Node* Tree::getRoot(){
	return root;
}

/*----生成树----*/
Node* Tree::buildTree(const string s){
	stack <char> operate;
	stack <Node *> node;
	stack <char> operate2;
	stack <Node *> node2;
	string p = "";
	Node * treeNode;
	char ch;

	for (int k = 0; k < s.length(); k++){
		//将（）里的内容单独作为一个表达式调用自身去处理
		if (s[k] == '('){
			k++;
			while (s[k] != ')'){
				p = p + s[k];
				k++;
			}
			node.push(buildTree(p));
			p.clear();
			continue;
		}
		//数字直接做叶子节点
		else{
			if (s[k] - '0' >= 0 && s[k] - '0' <= 9){
				treeNode = create();
				treeNode->data = s[k];

				node.push(treeNode);
			}
			//遇到运算符
			else if (s[k] == '*' || s[k] == '/' || s[k] == '+' || s[k] == '-'){
				if (!operate.empty() && (s[k] == '+' || s[k] == '-')){
					if (operate.top() == '+' || operate.top() == '-'){
						treeNode = create();
						treeNode->data = operate.top();
						treeNode->rightChild = node.top();
						node.pop();
						treeNode->leftChild = node.top();
						node.pop();

						node.push(treeNode);

						operate.pop();
						operate.push(s[k]);
					}
					else{
						//对连乘连除的处理
						while (!operate.empty() && (operate.top() == '*' || operate.top() == '/')){
							node2.push(node.top());
							node.pop();
							operate2.push(operate.top());
							operate.pop();
						}
						node2.push(node.top());
						node.pop();
						while (!operate2.empty())
						{
							treeNode = create();
							treeNode->data = operate2.top();
							operate2.pop();
							treeNode->leftChild = node2.top();
							node2.pop();
							treeNode->rightChild = node2.top();
							node2.pop();

							node2.push(treeNode);
						}
						node.push(node2.top());
						operate.push(s[k]);
						node2.pop();
					}
				}
				else
					operate.push(s[k]);
			}
		}
	}


	while (!operate.empty() && (operate.top() == '*' || operate.top() == '/')){
		node2.push(node.top());
		node.pop();
		operate2.push(operate.top());
		operate.pop();
	}
	node2.push(node.top());
	node.pop();
	while (!operate2.empty())
	{
		treeNode = create();
		treeNode->data = operate2.top();
		operate2.pop();
		treeNode->leftChild = node2.top();
		node2.pop();
		treeNode->rightChild = node2.top();
		node2.pop();

		node2.push(treeNode);
	}
	node.push(node2.top());
	node2.pop();

	while (!operate.empty())
	{

		node2.push(node.top());
		node.pop();
		operate2.push(operate.top());
		operate.pop();
	}
	node2.push(node.top());
	node.pop();
	while (!operate2.empty())
	{
		treeNode = create();
		treeNode->data = operate2.top();
		operate2.pop();
		treeNode->leftChild = node2.top();
		node2.pop();
		treeNode->rightChild = node2.top();
		node2.pop();

		node2.push(treeNode);
	}
	node.push(node2.top());
	node2.pop();

	return node.top();
}

/*---后后序遍历----*/
void Tree::PostOrder(Node* node){
	if (node != NULL){
		PostOrder(node->leftChild);
		PostOrder(node->rightChild);
		cout << node->data;
	}
}

/*----前序遍历----*/
void Tree::Inorder(Node* node){
	if (node != NULL){
		cout << node->data;
		Inorder(node->leftChild);
		Inorder(node->rightChild);
	}
}

int main(){
	string centerString;

	cout << "请输入表达式：";
	cin >> centerString;

	Tree tree(centerString);

	cout << "波兰表达式：";
	tree.Inorder(tree.getRoot());
	cout << endl;

	cout << "中缀表达式：";
	cout << centerString << endl;

	cout << "逆波兰表达式：";
	tree.PostOrder(tree.getRoot());
	cout << endl;
	return 0;
}