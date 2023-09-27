#include<iostream>
using namespace std;
#include<string>
#include<map>
#include<vector>
int* getNext(string s)
{
	int* Next = new int[s.length()];
	int i = 0;
	int j = -1;
	Next[i] = j;
	while (i < s.length() - 1) {
		if (j == -1 || s[i] == s[j])
		{
			i++;
			j++;
			Next[i] = j;
		}
		else {
			j = Next[j];
		}
	}
	return Next;

}
void KmpMtch(string M, string s, int* Next)
{
	unsigned  int i = 0;
	unsigned int j = 0;
	while (i < M.length() && j < s.length()) {
		if (j == -1 || M[i] == s[j]) {
			i++;
			j++;
		}
		else {
			j = Next[j];
		}
	}
	if (j == s.length()) {
		cout << "successful" << endl;
	}
	else {
		cout << "fail" << endl;
	}


}


class TreeNode {
public:
	int data;
	int flag;
	int LFlag;
	int RFlag;
	TreeNode* Lchild;
	TreeNode* Rchild;
	TreeNode() :Lchild(nullptr), Rchild(nullptr),flag(0),LFlag(0),RFlag(0) {}
};


class QueueNode {
public:
	TreeNode* data;
	QueueNode* pre;
	QueueNode* next;
	QueueNode() :data(nullptr), pre(nullptr), next(nullptr) {}
};


class StackNode {
public:
	TreeNode* data;
	StackNode* next;
	StackNode(): data(nullptr),next(nullptr){}
};

StackNode* iniStack()
{
	StackNode* S = new StackNode;
	return S;
}

void enStack(StackNode* S,TreeNode* T)
{
	if (!S||!T)return;
	StackNode* N = new StackNode;
	N->data = T;
	N->next = S->next;
	S->next = N;
}
StackNode* deStack(StackNode* S)
{
	if (S->next == nullptr)return nullptr;
	StackNode* N = S->next;
	S->next = N->next;
	return N;
}
StackNode* GetTopStack(StackNode* s)
{
	if (s->next == nullptr) return nullptr;
	return s->next;

}
bool IsStackEmpty(StackNode* S)
{
	return  S->next == nullptr;
}
void CreatTree(TreeNode** Root)
{
	if (Root == nullptr)return;
	char ch;
	cin >> ch;
	if (ch != '#')
	{
		(*Root) = new TreeNode;
		(*Root)->data = ch;
		CreatTree(&(*Root)->Lchild);
		CreatTree(&(*Root)->Rchild);

	}
	else
	{
		Root = nullptr;
	}
}
void prePrint(TreeNode* Root)
{
	if (!Root)return;
	cout << Root->data << " ";
	prePrint(Root->Lchild);
	prePrint(Root->Rchild);
}

QueueNode* IniQueue()
{
	QueueNode* Head = new QueueNode;
	Head->next = Head;
	Head->pre = Head;
	return Head;
}

void enQueue(QueueNode* Head, TreeNode* Node)
{
	if (!Head || !Node)return;
	QueueNode* NewQueue = new QueueNode;
	NewQueue->data = Node;
	Head->pre->next = NewQueue;
	NewQueue->next = Head;
	NewQueue->pre = Head;
	Head->pre = NewQueue;
}

QueueNode* deQueue(QueueNode* Head)
{
	if (!Head)return nullptr;
	QueueNode* Node = Head->next;
	Head->next = Head->next->next;
	Head->next->pre = Head;
	return Node;
}
bool IsEmpty(QueueNode* Head)
{
	return Head->pre == Head;
}
void LevelOrder(TreeNode* Tree, QueueNode* Node)
{
	if (!Tree)return;
	enQueue(Node, Tree);
	while (!IsEmpty(Node)) {
		QueueNode* TD = deQueue(Node);
		cout << TD->data->data << " ";
		if (TD->data->Lchild) {
			enQueue(Node, TD->data->Lchild);
		}
		if (TD->data->Rchild) {
			enQueue(Node, TD->data->Rchild);
		}
	}
}
void preOrderNoWhile(TreeNode* T)
{
	TreeNode* Node = T;
	StackNode* N = iniStack();
	while (Node || !IsStackEmpty(N))
	{
		if (Node)
		{
			cout << Node->data;
			enStack(N, Node);
			Node = Node->Lchild;
		}
		else {
			Node = deStack(N)->data;
			Node = Node->Rchild;
		}
	}
}


void inorderNoWhile(TreeNode* T)
{
	TreeNode* Node = T;
	StackNode* N = iniStack();
	while (Node || !IsStackEmpty(N))
	{
		if (Node)
		{
			enStack(N, Node);
			Node = Node->Lchild;
		}
		else {
			Node = deStack(N)->data;
			cout << Node->data;
			Node = Node->Rchild;
		}
	}
}
void backorderNoWhile(TreeNode* T)
{
	
	TreeNode* Node = T;
	StackNode* N = iniStack();
	while (Node || !IsStackEmpty(N))
	{
		if (Node)
		{
			enStack(N, Node);
			Node = Node->Lchild;
		}
		else {
			TreeNode* top = GetTopStack(N)->data;
			if (top->Rchild && top->Rchild->flag==0)
			{
				top = top->Rchild;
				enStack(N, top);
				Node = top->Lchild;
			}
			else {
				top = deStack(N)->data;
				cout << top->data;
				top->flag = 1;
			}
		    }
	}
		
}

void InThreadTree(TreeNode* T, TreeNode** pre)
{
	if (T)
	{
		InThreadTree(T->Lchild, pre);
		if (T->Lchild == nullptr) 
		{
			T->LFlag = 1;
			T->Lchild = *pre;
		}
		if ( *pre != nullptr && (*pre)->Rchild == nullptr) 
		{
			(*pre)->RFlag = 1;
			(*pre)->Rchild = T;
		}
		*pre = T;

		InThreadTree(T->Rchild, pre);
	}
}
TreeNode* bstSearch(TreeNode* T,int data)
{
	if (T)
	{
		if (data < T->data) {
			bstSearch(T->Lchild, data);
		}
		else if (data > T->data) {
			bstSearch(T->Rchild, data);
		}
		else {
			return T;
		}


	}
	else {
		return NULL;
	}
}
void InsertBstTree(TreeNode** T,int data) {
	if (!*T){
		*T = new TreeNode;
		(*T)->data = data;
		return;
	}
	if (data>(*T)->data)
	{
		InsertBstTree((&(*T)->Rchild), data);
	}
	else if(data< (*T)->data){
		InsertBstTree((&(*T)->Lchild), data);
	}
	else {
		return;
	}

}



TreeNode* GetFirst(TreeNode* T)
{
	if (T->LFlag == 0)
	{
		T = T->Lchild;
	}
	return T;
}
TreeNode* GetNext(TreeNode* T)
{
	if (T->RFlag == 1)
		return T->Rchild;
	else{
		return GetFirst(T->Rchild);
        }
}
  
bool IsLoopStr(string s, int left, int right)
{
	if (s.length() < 2)return true;
	int i = left;
	int j = right;
	while (i < j) {
		if (s[i] == s[j])
		{
			i++;
			j--;
		}
		else {
			break;
		}
	}
	return i >= j;
}

int  merge(int* c, int L,int M, int R)
{
	int i =L, index = 0;
	int a[100];
	int j = M + 1;
	int ans = 0;
	while (i <= M && j <= R) {
		ans += c[i] <= c[j] ? (R- j + 1) *c[i] : 0;
		a[index++] = c[i] <= c[j] ? c[i++] : c[j++];
	}
	while (i <= M)
	{
		a[index++] = c[i++];
	}
	while (j <= R)
	{
		a[index++] = c[j++];
	}
	for (int i = 0; i < R - L + 1; i++)
	{
		c[L+i] = a[i];
	}
	return ans;
}

int poccess(int *a,int L,int R)
{
	if (L == R)  return 0;
	int M = L + ((R - L) >> 1);
	return poccess(a, L, M)+
	poccess(a, M + 1, R)+
	merge(a, L,M, R);
}
int SmallSum(int* a,int L,int R)
{
	return poccess(a, L, R);
}
vector<int> SortLR(int* a, int L, int R)
{
	vector<int> v;
	int i = L - 1;
	int j = R;
	while (L < j)
	{
		if (a[L] < a[R])
		{
			swap(a[L++], a[++i]);
		}
		else if(a[L]>a[R])
		{  
			swap(a[--j], a[L]);
		}
		else {
			L++;
		}
	}
	swap(a[R], a[j]);
	v.push_back(i+1); v.push_back(j);
	return v;
}

void QuickSort(int* a, int L, int R)
{
	if (L < R)
	{
		vector<int> b = SortLR(a, L, R);
		QuickSort(a, L, b[0]-1);
		QuickSort(a, b[1]+1, R);
	}

}
bool IsMatch(const char* s, const char* n)
{
	//if (*n == 0)return *s == 0;

	bool match = *s && (*s == *n || (*n == '.'));

	if (*(n + 1) == '*')
	{
		return IsMatch(s, n + 2) || IsMatch(++s, n);
	}
	else {
		return match && IsMatch(++s, ++n);
	}
}
bool IsMatch(string s, string n)
{
	return IsMatch(s.c_str(), n.c_str());
}




//class Solution {
//public:
//	vector<vector<int>> threeSum(vector<int>& nums) {
//		multimap<int, pair<int, int>> al; // target  nums[i]  i
//		int len = nums.size();
//		vector<vector<int>>ans;
//		for (int i = 0; i < len - 1; i++)
//		{
//			int sum = nums[i] + nums[i + 1];
//			int target = 0 - nums[i];
//			vector<int>ansc;
//			if (al.find(target) != al.end())
//			{
//				if (al.find(target)->second.second)
//				{
//					ansc.push_back(al.find(target)->second->first)
//						ansc.push_back(target - al.ifind(target)->second->first);
//				}
//			}
//			al.insert(sum, make_pair(nums[i], i));
//			ans.push_back(ansc);
//			vector<int>
//		}
//
//		return ans;
//	}
//};


int main()
{

	//string s{ "abaccababd" };
	//string b{ "abacdc" };
	//KmpMtch(s, b, getNext(s));

	/*TreeNode *Ro;
	CreatTree(&Ro);
	TreeNode* pre = nullptr;
	InThreadTree(Ro, &pre);

	pre->RFlag = 1;
	pre->Rchild = NULL;

	for (TreeNode* node = GetFirst(Ro); node != NULL; node = GetNext(node)) {
		cout << node->data << " ";
	}
	*/
	//prePrint(Ro);
	//preOrderNoWhile(Ro);
	//backorderNoWhile(Ro);

	//prePrint(Ro);
	/*QueueNode* Node = IniQueue();
	* 
	* 
	* 
	* 
	LevelOrder(Ro, Node);*/
	/*string s;
	cin >> s;
	while (s[0] != '#')
	{

		if (IsLoopStr(s)) {
			cout << "succ" << endl;
		}
		else {
			cout << "fail" << endl;
		}
		cin >> s;
		cin.get();

	}
*/



	/*int a[4] = { 1,8,6,2};
	QuickSort(a, 0,3);
	for (int i = 0; i<4; i++)
	{
		cout << a[i] << " ";
	}*/


	//bstTreeTset
	TreeNode* T = nullptr;
	InsertBstTree(&T, 6);
	InsertBstTree(&T, 9);
	InsertBstTree(&T, 2);
	InsertBstTree(&T, 4);
	InsertBstTree(&T, 1);
	InsertBstTree(&T, 5);
	preOrderNoWhile(T);

}


