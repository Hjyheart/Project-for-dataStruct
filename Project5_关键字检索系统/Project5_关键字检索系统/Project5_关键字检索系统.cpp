/*名称：关键字检索系统
*概要：建立一个文本文件，文件名由用户用键盘输入，输入一个不含
空格的关键字，统计输出关键字在文本中的出现次数
*作者：洪嘉勇
*日期：2015.10.12
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cctype>
#include <utility>

using namespace std;

vector <pair<string, int> > Search;

/*----统计函数----*/
void Count(const string & temp){
	string word;
	char ch;
	/*--遍历统计--*/
	for (int i = 0; i < temp.length(); i++){
		//如果是字符就放入word
		if (isalpha(temp[i])){
			ch = temp[i];
			//都转化为小写
			ch = tolower(ch);
			word.push_back(ch);
			continue;
		}
		//容器为空的情况
		if (Search.empty()){
			Search.push_back(make_pair(word, 1));
			word.clear();
			continue;
		}
		else{
			//在容器中找到相同字符串
			for (int k = 0; k < Search.size(); k++){
				if (Search[k].first == word){
					Search[k].second++;
					word.clear();
					break;
				}
				//在容器中找不到相同字符串
				if (k == Search.size() - 1){
					Search.push_back(make_pair(word, 1));
					word.clear();
					break;
				}
			}
		}
	}
}

int main(){
	ofstream outFile;
	string fileName, temp, keyValue, originalValue;

	/*--输入--*/
	cout << "关键字检索系统" << endl << "请输入文件名：";
	cin >> fileName;
	outFile.open(fileName);
	cout << endl << "请输入一段英文：" << endl;
	//写入
	while (getline(cin, temp)){
		outFile << temp;
		Count(temp);
	}
	if (outFile.good())
		cout << "本段文本已经保存在文本文件\"" << fileName << "\"中。" << endl;
	outFile.close();

	/*--输出--*/
	ifstream inFile;
	inFile.open(fileName);

	cin.clear();
	cout << "请输入要检索的关键字(输入0退出程序):";
	cin >> keyValue;
	while (keyValue != "0"){
		originalValue = keyValue;
		cout << "显示源文件\"" << fileName << "\":" << endl;
		inFile.seekg(0);
		//读出
		while (inFile.good()){
			inFile >> temp;
			cout << temp << " ";
		}
		cout << endl;

		//大小写转化
		for (int i = 0; i < keyValue.length(); i++)
			keyValue[i] = tolower(keyValue[i]);
		//检索
		for (int i = 0; i < Search.size(); i++){
			//找到对应字符串
			if (Search[i].first == keyValue){
				cout << "在源文件中共检索到：" << Search[i].second << "个关键字"
					<< "\"" << originalValue << "\"" << endl;
				break;
			}
				//未找到对应字符串
				if (i == Search.size() - 1)
					cout << "源文件中未找到要求字段。" << endl;
		}
		cout << "请输入要检索的关键字：";
		cin >> keyValue;
	}
	inFile.close();
	return 0;
}