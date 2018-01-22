#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <string>
#include <cstring>
#include <iomanip>
#include <Windows.h>

using namespace std;
typedef  vector<vector<char> > VV;
//�ִ���
class heap {

public:
	heap() {}
	heap(int capacity) { data.resize(capacity); }
	~heap() {}
	//�ش� �ε����� ���� ���� 
	char get(int i) { return data[i]; }
	//Ʈ���� ���� �߰� 
	void insert(char item) {
		data.push_back(item);//���Ϳ� ������ �ֱ� 
		insert_arrange(size() - 1);//�켱������ ����  Ʈ�� ���� 
	}
	//Ʈ���� ��Ʈ ���� ���� 
	void deleteRoot() {
		data[0] = data[size() - 1];//��Ʈ ���� 
		data.pop_back();
		delete_arrange(0);//�켱������ ���� Ʈ�� ���� 
	}
	//�ڽ� ���� Ȯ�� 
	bool isLeaf(int i) {
		return getLeftCIndex(i) >= data.size();
	}
	//�׸񰳼� 
	int size() {
		return data.size();
	}
	//�θ��� �ε�����ȣ 
	int getPIndex(int i) { return (int)((i - 1) / 2); }
	//�����ڽ��ε��� ��ȣ 
	int getLeftCIndex(int i) { return i * 2 + 1; }
	//�������ڽ��ε��� ��ȣ 
	int getRightCIndex(int i) { return i * 2 + 2; }
	//�ش� ���� �ε����� ���� �˾ƺ��� 
	int getDepth(int i) { return (int)(log(i+1) / log(2.0)) + 1; }
private:
	vector<char> data;
	//swap 
	void swap(char& a, char& b) {
		char temp = a;
		a = b;
		b = temp;
	}
	//return a<b: 
	bool compare(char a, char b) {
		if (a >= 'A'&& a <= 'Z') lower(a);
		else if (a >= 'a'&& a <= 'z') upper(a);
		if (b >= 'A'&& b <= 'Z') lower(b);
		else if (b >= 'a'&& b <= 'z') upper(b);
		//return a > b;
		return a < b;
	}
	char lower(char& a) { return a += ('a' - 'A'); }
	char upper(char& a) { return a -= ('a' - 'A'); }
	//Ʈ���� ���� �߰��� �����ϴ� �Լ� 
	int insert_arrange(int startIndex) {
		int i = startIndex;
		while (getDepth(i)>1/*�ֻ����϶� ����*/) {
			char p = data[getPIndex(i)];
			char c = data[i];
			if (compare(p, c)) {
				swap(p, c);
				data[getPIndex(i)] = p;
				data[i] = c;
				i = getPIndex(i);
			}
			else break;
		}
		return i;
	}
	//Ʈ�� ��Ʈ ���� ���Ž� �����ϴ� �Լ� 
	void delete_arrange(int index) {
		int i = index;
		int lci = getLeftCIndex(i);
		int rci = getRightCIndex(i);
		char p = data[i];
		char lc = data[lci];
		char rc = data[rci];
		if(!isLeaf(i)){
			int ci = -1;
			char child;
			//���� �ڽ� �����ϱ� 
			if(rc==size()-1)
				ci = lci;
			else {
				if(!compare(lc, rc))//left�� Ŭ ��  
				ci = lci;
				else ci = rci; //right �� Ŭ �� 
			}
			child = data[ci]; //���� �ڽ� 
			// �켱������ ��߳��� ��� ��ü 
			if (compare(p, child)) {
				swap(p, child);
				data[i] = p;
				data[ci] = child;
				//����� �ڽĿ����� ���� ���� 
				delete_arrange(ci);
			}
		}
	}
	
};

//���� ������ �޾ƿ� ����� �����ϴ� �Լ� 
void readCommand(string cmd, heap& h) {
	bool isInput = false;
	for (int i = 0; i < cmd.size(); i++) {
		char c = cmd[i];
		if (!isInput && c == 'I')
			isInput = true;
		else if (!isInput && c == 'D')
			h.deleteRoot();
		else if (isInput&&c != ' ') {
			h.insert(c);
			isInput = false;
		}
		else if (c == ' ') continue;
		
	}
}
//print 1 ���� �Լ� ����
//rIndex is root index
void inOrder(heap h, int rIndex) {
	if (rIndex < h.size()) {
		inOrder(h, h.getLeftCIndex(rIndex));
		cout << setw(h.getDepth(rIndex)*3) << h.get(rIndex) << endl;
		inOrder(h, h.getRightCIndex(rIndex));
	}
}
//print 1 ���� �Լ� �� 
//print 3 ���� �Լ� ����

int sequenceOfNumbers(int n){
	if(n<1) return -1;
	return pow(2, n-1)-1;
}
int arrayX(int depth){
	return sequenceOfNumbers((int)((depth+2)/2)+1);
}
int arrayY(int depth){
	return arrayX(depth-1);
}

int sharpNumber(int depth, int totalDepth){
	if(depth==1) return -1;
	depth = totalDepth-depth+2;
	if(depth==2) return 0;
	return sequenceOfNumbers((int)((depth-2)/2)+1);
}

void hprint(int width, char d, char value, int x, int y , VV& printArray){
	printArray[x][y] = value;
	char c='#';
	for(int i = 0; i<width; i++){
		if(d=='l') 	printArray[x+i+1][y] =  c;
		else if(d=='r') printArray[x-i-1][y] =  c;
		else if(d=='d') printArray[x][y-i-1] =  c;
		else if(d=='u') printArray[x][y+i+1] =  c;
	}
}

void htree(heap h, int rIndex, char direction, int x, int y, VV& printArray){
	char dLeft, dRight;
	int newlx = x, newly = y, newrx = x, newry = y;
	int width = sharpNumber(h.getDepth(rIndex)+1, h.getDepth(h.size()-1));
	if(width<0) return ;
	switch(direction){
		case 'l': dLeft='u'; dRight='d'; newly = y-(width+1); newry = y+(width+1);  break;
		case 'r': dLeft='d'; dRight='u'; newly = y+(width+1); newry = y-(width+1);  break;
		case 'u': dLeft='r'; dRight='l'; newlx = x+(width+1); newrx = x-(width+1);  break;
		case 'd': dLeft='l'; dRight='r'; newlx = x-(width+1); newrx = x+(width+1);  break;
		case 'c': dLeft='l'; dRight='r'; newlx = x-(width+1); newrx = x+(width+1);  break;
	}
	if (rIndex < h.size()) {
		hprint(sharpNumber(h.getDepth(rIndex), h.getDepth(h.size()-1)), direction, h.get(rIndex), x, y, printArray);
		htree(h, h.getLeftCIndex(rIndex),dLeft ,  newlx, newly, printArray);
		htree(h, h.getRightCIndex(rIndex), dRight, newrx, newry, printArray);
	}
}
//print 3 ���� �Լ� �� 
void print1(heap h){
	cout << "==== print1 ====" <<endl<<endl;
	inOrder(h, 0);
	cout<<endl<<endl;
}
void print2(heap h) {
	int index = 0;
	int depth = h.getDepth(h.size()-1);
	cout << "==== print2 ====" <<endl<<endl;
	for (int i = 0; i < depth; i++) {
		index = pow(2, i) - 1;//�ش� ������ ���� �ε���  
		//���� ����� ��� 
		for (int p = 0; p < pow(2, depth-1 - i) - 1; p++)cout << (char)32; 
		for (int j = 0; j < pow(2, i); j++) {
			cout << h.get(index + j);//���� ��� 
			//���� ���� ����� ��� 
			for (int p = 0; p < pow(2, depth - i) - 1; p++)cout << (char)32;
			//�ش� ���� �ε����� �������̸� ������ 
			if (index + j == h.size() - 1) {
				cout << endl<< endl<< endl<< endl;
				return;
			}
			//�� �ִ��� �� ���纼��� ¥����  
			if ((i != depth - 1)) {
				if (h.getPIndex(index + j) != h.getPIndex(index + j + 1))
					cout << (char)32;
				else
					cout << (char)8;
			}
		}
		cout << endl<< endl;
	}
}

void print3(heap h){
	int depth = h.getDepth(h.size()-1);//�� ����
	//VV is vector<vector<char> >; ���� ����
	VV printArray(arrayX(depth), vector<char>(arrayY(depth), 0));
	int startX = arrayX(depth)/2;//������ǥ
	int startY = arrayY(depth)/2;
	//Ʈ���� ��Ʈ���� Ž���ϸ� VV�� ������
	htree(h, 0, 'c',startX, startY, printArray);
	//�� ��� �κ�
	cout << "==== print3 ====" <<endl<<endl;
	for(int i = 0; i< arrayY(depth); i++){
		for(int j = 0; j <arrayX(depth); j++){
			if(printArray[j][i]!=NULL)
				cout <<printArray[j][i]  ;
			else
				cout<< (char)32;
			cout << (char)32;
		}
		cout<<endl;
	}
}
int main() {
	heap h, h1;
	int b;

	string filePath = "input.txt";
	int size = 0;
	string cmd = "";
	// read File
	ifstream openFile(filePath.data());
	if (openFile.is_open()) {
		string s[2];
		int i = 0;
		while (getline(openFile, s[i])) i++;
		openFile.close();
		size = atoi(s[0].c_str());
		cmd = s[1];
	}
	readCommand(cmd, h);
	print1(h);
	print2(h);
	print3(h);
	return 0;
}
