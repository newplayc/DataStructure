#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<queue>
#include<stack>
#include<unordered_map>
#include<unordered_set>
using namespace std;

int* getNext(string s)
{
	int* Next = new int[s.length()];
	int i = 0;
	int j = -1;
	int v = s.length();
	Next[i] = j;
	while (i < v- 1) {
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


void kmpMatch(string master, string sub, int* next) {
	int i = 0;
	int j = 0;
	int c = master.size();
	int v = sub.size();
	while (i < c && j < v) {
		if (j == -1 || master[i] == sub[j]) {
			i++;
			j++;
		}
		else {
			j = next[j];
		}
	}
	if (j == v) {
		printf("kmp match success.\n");
	}
	else {
		printf("kmp match fail.\n");
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
	TreeNode() :Lchild(nullptr), Rchild(nullptr), flag(0), LFlag(0), RFlag(0) {}
};
typedef struct HafuTreeNode
{
	int weight;
	int parent;
	int lchild;
	int rchild;

}HafuTreeNode;
typedef struct HafuTree
{
	HafuTreeNode* data;
	int length;
}HafuTree;

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
	StackNode() : data(nullptr), next(nullptr) {}
};

StackNode* iniStack()
{
	StackNode* S = new StackNode;
	return S;
}

void enStack(StackNode* S, TreeNode* T)
{
	if (!S || !T)return;
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
	int ch;
	cin >> ch;
	if (ch != 0)
	{
		(*Root) = new TreeNode;
		(*Root)->data = ch;
		CreatTree(&(*Root)->Lchild);
		CreatTree(&(*Root)->Rchild);

	}
	else
	{
		*Root = nullptr;
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
			if (top->Rchild && top->Rchild->flag == 0)
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
		if (*pre != nullptr && (*pre)->Rchild == nullptr)
		{
			(*pre)->RFlag = 1;
			(*pre)->Rchild = T;
		}
		*pre = T;

		InThreadTree(T->Rchild, pre);
	}
}
TreeNode* bstSearch(TreeNode* T, int data)
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
	return nullptr;
}
void InsertBstTree(TreeNode** T, int data) {
	if (!*T) {
		*T = new TreeNode;
		(*T)->data = data;
		return;
	}
	if (data > (*T)->data)
	{
		InsertBstTree((&(*T)->Rchild), data);
	}
	else if (data < (*T)->data) {
		InsertBstTree((&(*T)->Lchild), data);
	}
	else {
		return;
	}

}

HafuTree* InitializeHafuTree(int* weight, int length)
{
	HafuTree* T = new HafuTree;
	T->data = new HafuTreeNode[length * 2 - 1];
	T->length = length;

	for (int i = 0; i < length; i++)
	{
		T->data[i].weight = weight[i];
		T->data[i].parent = 0;
		T->data[i].lchild = -1;
		T->data[i].rchild = -1;
	}

	return T;
}
int* SearchTwoMin(HafuTree* Ha)
{
	int len = Ha->length;
	int min = INT_MAX, secondmin = INT_MAX;
	int minindex = -1, secondminindex = -1;
	for (int i = 0; i < len; i++)
	{
		if (Ha->data[i].parent == 0)
			if (Ha->data[i].weight < min)
			{
				min = Ha->data[i].weight;
				minindex = i;
			}
	}

	for (int i = 0; i < len; i++)
	{
		if (Ha->data[i].parent == 0)
			if (Ha->data[i].weight < secondmin && i != minindex) {
				secondmin = Ha->data[i].weight;
				secondminindex = i;
			}
	}
	int* TwoNum = new int[2];
	TwoNum[0] = minindex;
	TwoNum[1] = secondminindex;
	return TwoNum;
}
void CreatHafuTree(HafuTree* T)
{
	int len = T->length * 2 - 1;
	for (int i = T->length; i < len; i++)
	{
		int* c = SearchTwoMin(T);
		T->data[i].weight = T->data[c[0]].weight + T->data[c[1]].weight;
		T->data[i].lchild = c[0];
		T->data[i].rchild = c[1];
		T->data[i].parent = 0;
		T->data[c[0]].parent = i;
		T->data[c[1]].parent = i;
		T->length++;
	}
}
void PreOrderHafuTree(HafuTree* T, int index)
{
	if (index != -1) {
		cout << T->data[index].weight << " ";
		PreOrderHafuTree(T, T->data[index].lchild);
		PreOrderHafuTree(T, T->data[index].rchild);
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
	else {
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

int  merge(int* c, int L, int M, int R)
{
	int i = L, index = 0;
	int a[100];
	int j = M + 1;
	int ans = 0;
	while (i <= M && j <= R) {
		ans += c[i] <= c[j] ? (R - j + 1) * c[i] : 0;
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
		c[L + i] = a[i];
	}
	return ans;
}

int poccess(int* a, int L, int R)
{
	if (L == R)  return 0;
	int M = L + ((R - L) >> 1);
	return poccess(a, L, M) +
		poccess(a, M + 1, R) +
		merge(a, L, M, R);
}
int SmallSum(int* a, int L, int R)
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
		else if (a[L] > a[R])
		{
			swap(a[--j], a[L]);
		}
		else {
			L++;
		}
	}
	swap(a[R], a[j]);
	v.push_back(i + 1); v.push_back(j);
	return v;
}

void QuickSort(int* a, int L, int R)
{
	if (L < R)
	{
		vector<int> b = SortLR(a, L, R);
		QuickSort(a, L, b[0] - 1);
		QuickSort(a, b[1] + 1, R);
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
//	a			if (al.find(target)->second.second)
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
void swap(int*arr,int a, int b)
{
	int temp = arr[a];
	arr[a] = arr[b];
	arr[b] = temp;
}

void Heapinsert(int* a, int index)
{
	while (a[index] > a[(index - 1) / 2])
	{
		
		swap(a,index, (index - 1) / 2);
		index = (index - 1) / 2;
	}
}
void Heapify(int* a, int index, int heapsize)
{
	int left = index * 2 + 1;
	while (left < heapsize)
	{
		int MoreBig = left + 1 < heapsize && a[left + 1] > a[left] ? left + 1 : left;
		MoreBig = a[MoreBig] > a[index] ? MoreBig : index;
		if (MoreBig == index) {
			break;
		}
		swap(a, index, MoreBig);
		index = MoreBig;
		left = index * 2 + 1;
	}
}
void HeapSort(int* a, int length)
{
	if (a == nullptr)return;
	for (int i = 0; i < length; i++)
	{
		Heapinsert(a, i);
	}
	int heapsize = length;

	swap(a,0, --heapsize);

	while (heapsize > 0)
	{
		Heapify(a, 0, heapsize);

		swap(a,0, --heapsize);
	}
}
int GetDigit(int a);
int GetTimeDigit(int a, int t)
{
	int c = GetDigit(a);
	if (t > c)
	{
		return 0;
	}
	else {
		int ans = 0;
		while (t--) {

			ans = a % 10;
			a /= 10;
		}
		return ans;
	}

}
int GetDigit(int a)
{
	if (a == 0)return 1;
	int Di = 0;
	while (a > 0)
	{
		a /= 10;
		Di++;
	}
	return Di;
}
int GetMaxDigit(int *a,int length)
{
	int i = length;
	int Max = 0;
	for (int j = 0; j < length; j++)
	{
		int m = a[j];
		int c = 0;
		while (m > 0)
		{
			m /= 10;
			c++;
		}
		Max = max(Max, c);
	}
	return Max;
} 

void BarrSort(int* a,int length)
{
	int t = GetMaxDigit(a, length);
	int digit = 1;
	int* fuzhu = new int[length];
	for (int i = 0; i < t;i++) {
		int di[10] = { 0,0,0,0,0,0,0,0,0,0 };
		for (int j = 0; j < length; j++)
		{
			di[GetTimeDigit(a[j], digit)]++;
		}
		for (int i = 1; i < 10; i++) {
			di[i] = di[i] + di[i - 1];
		}
		for (int i = length-1; i >= 0; i--)
		{
			fuzhu[di[GetTimeDigit(a[i], digit)]-1] = a[i];
			di[GetTimeDigit(a[i], digit)]--;
		}
		digit++;
		for (int i = 0; i < length; i++)
		{
			a[i] = fuzhu[i];
		}
			
	}

}

struct ListNode {
	int val;
	ListNode* next;
	ListNode() : val(0), next(nullptr) {}
	ListNode(int x) : val(x), next(nullptr) {}
	ListNode(int x, ListNode* next) : val(x), next(next) {}
};

	ListNode* reverselist(ListNode* head, ListNode* tail, int k) {
		ListNode* t = head->next;
		ListNode* p;
		ListNode* r = t;
		ListNode* pre = tail;
		int i = 0;
		while (t && i < k) {
			p = t->next;
			t->next = pre;
			pre = t;
			t = p;
			i++;
		}
		head->next = pre;
		return r;
	}
	ListNode* reverseKGroup(ListNode* head, int k) {
		int i = 0;
		ListNode* t = new ListNode;
		ListNode* tail = nullptr;
		t->next = head;
		ListNode* p = t;
		int flag = 0;
		ListNode* ret = head;
		ListNode * not1 = nullptr;
		while (t) {
			t = t->next;
			i++;
			if (t) {
				not1 = t;
			}
			if (flag == 0 && i == k) {
				ret = t;
				flag = 1;
			}
			if (i == k + 1) {
				if (!t)
				tail = not1;
				else
				tail = t;


				p = reverselist(p, tail, k);
				i = 0;
			}
		}
		return ret;
	}


void headinsertcreatList(ListNode* head,int val) {
	ListNode* t = new ListNode(val);
	t->next = head->next;
	head->next = t;
}

void printLIst(ListNode* head) {
	ListNode* t = head;
	while (t) {
		cout << t->val << " ";
		t = t->next;

	}
}


int MaxWidthTree(TreeNode* root) {
	if (!root)return 0;
	queue<TreeNode*>q;
	q.push(root);
	TreeNode*  CurEnd = root;
	TreeNode*  NextEnd = nullptr;
	int cMax = 0;
	int Max = 0;
	while (!q.empty()) {
		TreeNode* t = q.front();
		q.pop();
		cMax++;
		if (t->Lchild != nullptr) {
			q.push(t->Lchild);
			NextEnd = t->Lchild;
		}
		if (t->Rchild != nullptr) {
			q.push(t->Rchild);
			NextEnd = t->Rchild;
		}
		if (t == CurEnd) {
			Max = max(Max, cMax);
			cMax = 0;
			CurEnd = NextEnd;
			NextEnd = nullptr;
		}
	}
	return Max;
}
int TreeDepth(TreeNode* T) {
	if (!T) { return 0; }
	int l = TreeDepth(T->Lchild);
	int R = TreeDepth(T->Rchild);
	return l >= R ? l + 1 : R + 1;
}



bool IsBST(TreeNode* T) {
	static int pre = INT_MIN;

	if (!T)return true;
	if (!IsBST(T->Lchild))return false;
	if (T->data <= pre)return false;
	pre = T->data;
	return IsBST(T->Rchild);
}

typedef struct ReturnData
{
	bool isU;
	int min;
	int max;
	bool IsBst;
	ReturnData(bool isU,int min,int max,bool is):isU(isU),min(min),max(max),IsBst(is){}
}ReturnData;
ReturnData ISBST(TreeNode* T)
{
	if (!T)return ReturnData(false, 0, 0, false);
	ReturnData lD = ISBST(T->Lchild);
	ReturnData RD = ISBST(T->Rchild);
	int min1 = T->data;
	int max1 = T->data;

	if (lD.isU) {
		min1 = min(min1, lD.min);
		max1 = max(max1, lD.max);
	}
	if (RD.isU) {
		min1 = min(min1, RD.min);
		max1 = max(max1, RD.max);
	}

	bool ISBst = true;
	if (lD.isU && (!lD.IsBst || lD.max >= T->data)) {
		ISBst = false;
	}
	if (RD.isU && (!RD.IsBst || RD.min <= T->data)) {
		ISBst = false;
	}

	return ReturnData(true,min1, max1,ISBst);
}


typedef struct ReType
{
	int height;
	bool IsB;
	ReType(int IsB,int hei):height(hei),IsB(IsB){}

}ReType;
ReType IsBala(TreeNode* T) {
	if (!T)return ReType(true, 0);
	ReType LD = IsBala(T->Lchild);
	ReType RD = IsBala(T->Rchild);

	int height = LD.height > RD.height ? LD.height + 1 : RD.height + 1;
	bool IsB = true;
	if (!LD.IsB || !RD.IsB) {
		IsB = false;
	}
	if (abs(LD.height - RD.height) > 1)
	{
		IsB = false;
	}
	return ReType(IsB, height);

}
struct Rep
{
	int height;
	int nodes;
	Rep(int h, int n) {
		height = h;
		nodes = n;
	}
};


Rep ISFULLBT(TreeNode* T) {
	if (!T)return Rep(0, 0);
	
	Rep LD = ISFULLBT(T->Lchild);
	Rep RD = ISFULLBT(T->Rchild);

	int height = LD.height > RD.height ? LD.height + 1 : RD.height + 1;
	int nodes = LD.nodes + RD.nodes + 1;

	return Rep(height, nodes);
}

typedef struct Graph {
	char* vexs;
	int** arcs;
	int vexNum;
	int arcNum;
}Graph;

Graph* IniGraph(int vexnum) 
{
	Graph* G = new Graph;
	G->vexs = new char[vexnum];
	G->arcs = new int* [vexnum];
	for (int i = 0; i < vexnum; i++)
	{
		G->arcs[i] = new int[vexnum];
	}
	G->vexNum = vexnum;
	G->arcNum = 0;
	return G;
}
void CreatGraph(Graph* G, int* N,char* vex) {
	
	for (int i = 0; i < G->vexNum; i++) {
		 G->vexs[i] = vex[i];
		for (int j = 0; j < G->vexNum; j++) {
			G->arcs[i][j] = *(N + i * G->vexNum + j);
			if (G->arcs[i][j] != 0)
			{
				G->arcNum++;
			}
		}
	}
	G->arcNum /= 2;
}

void DFS(Graph* G, int index, int* visit) {
	cout << G->vexs[index] << " ";
	visit[index] = 1;
	for (int i = 0; i < G->vexNum; i++) {
		if (G->arcs[index][i] == 1 && visit[i] == 0) {
			DFS(G,  i,  visit);
		}
	}
}

void BFS(Graph* G, int index, int* visit)
{
	queue<int> q;
	q.push(index);
	visit[index] = 1;
	while (!q.empty()) {
		int i = q.front();
		q.pop();
		cout << G->vexs[i] << " ";
		for (int j = 0; j < G->vexNum; j++) {
			if (G->arcs[i][j] == 1 && visit[j] == 0) {
				q.push(j);
				visit[j] = 1;
			}
		}
	}
}



struct Edge;
typedef struct Node {
public:

	int value;
	int in;
	int out;
	vector<Node*>nexts;
	vector<Edge*>Edges;
	Node(){}
	Node(int value) {
		this->value = value;
		in = 0;
		out = 0;
	}
}Node;

typedef struct Edge {
	int weight;
	Node *From;
	Node *To;
	Edge() {}
	Edge(int weight, Node* From, Node* To) {
		this->weight = weight;
		this->From = From;
		this->To = To;
	}
}Edge;

typedef struct Graph1 {
	unordered_map<int, Node*> Nodes;
	unordered_set<Edge*>Edges;
}Graph1;


Graph1* CreatMap(int p[4][3],int length) {
	Graph1* G = new Graph1;
	for (int i = 0; i < length; i++)
	{
		int  From = p[i][0];
		int To = p[i][1];
		int Weight = p[i][2];
		if (G->Nodes.find(From)== G->Nodes.end())
		{
			Node* t = new Node(From);
			G->Nodes.insert(make_pair(From,t));
		}
		if (G->Nodes.find(To) == G->Nodes.end()) {
			Node* t = new Node(To);
			G->Nodes.insert(make_pair(To,t));
		}
		Node* From1 = G->Nodes[From];
		Node* To1 =  G->Nodes[To];
		(*From1).out++;
		(*To1).in++;
		(*From1).nexts.push_back(To1);
		Edge* t = new  Edge(Weight, From1, To1);
		(*From1).Edges.push_back(t);
		G->Edges.insert(t);
	}
	return G;
}


void BFS1(Node * F)
{
	queue<Node*>q;
	unordered_set<Node*> set;
	q.push(F);
	set.insert(F);
	while (!q.empty())
	{
		Node* t = q.front();
		q.pop();
		cout <<  (*t).value;
		stack<Node*>stack;
		for (Node* N : (*t).nexts)
		{
			if (set.find(N) == set.end())
			{
				q.push(N);
				set.insert(N);
			}
		}
	}
}





void DFS(Node* s)
{
    unordered_set<Node*>set;
	stack<Node*>stack;
	cout << s->value;
	set.insert(s);
	stack.push(s);
	while(!stack.empty())
	{
		Node* cur = stack.top();
		stack.pop();
		for (Node* s : cur->nexts)
		{
			if (set.find(s) == set.end())
			{
				cout << s->value;
				stack.push(cur);
				stack.push(s);
				set.insert(s);
				break;
			}
		 }

	}

}
int main()
{
	int v[4][3] = {
		{1,3,1},
		{2,3,2},
		{2,4,3},
		{3,2,4}
	};
	Graph1* G =   CreatMap(v,4);
	//BFS1(G->Nodes[1]);
	DFS(G->Nodes[1]);
}




//int main()
//{

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
//TreeNode* T = nullptr;
//InsertBstTree(&T, 6);
//InsertBstTree(&T, 9);
//InsertBstTree(&T, 2);
//InsertBstTree(&T, 4);
//InsertBstTree(&T, 1);
//InsertBstTree(&T, 5);
//preOrderNoWhile(T);


	//int wei[7] = { 5,1,3,6,11,2,4 };
	//HafuTree* T = InitializeHafuTree(wei, 7);
	//CreatHafuTree(T);
	//PreOrderHafuTree(T, T->length - 1);


	//HeapSort
	//HeapSort(wei, 7);
	//for (int i : wei) {
	//	cout << i<<" ";
	//}


//	int a = 4;
//	cout << GetTimeDigit(a, 1);

	/*BarrSort(wei, 7);
	for (int i : wei) {
	cout << i<<" ";
    }*/

	//Solution S;
	//vector<int>nums{ 2,2,2,2,2 };
	//vector<vector<int>>ans;
	//ans = S.fourSum(nums, 0);
	//for (vector<int> a : ans)
	//{
	//	for (int c : a)
	//	{
	//		cout << c << " ";
	//	}
	//	cout << endl;
	//}


	//ListNode* head = new ListNode;
	//headinsertcreatList(head, 5);
	//headinsertcreatList(head, 4);
	//headinsertcreatList(head, 3);
	//headinsertcreatList(head, 2);
	//headinsertcreatList(head, 1);


	//ListNode* l  = reverseKGroup(head->next, 2);
	//printLIst(l);

		

	 //string s = "sadadas";
	 //string c = "das";
	 //kmpMatch(s, c, getNext(c));

 //   TreeNode* root = new TreeNode;
	//CreatTree(&root);


	//cout<<MaxWidthTree(root);
	//Rep R = ISFULLBT(root);
	//int e = R.height;
	//int v = R.nodes;
	//if (v == pow(2, e) - 1)
	//{
	//	cout << "s";
	//}
	//else {
	//	cout << "f";
	//}
	// 
	// 
	// 
	// 
//   int arcs[5][5] = {
//		0,1,1,1,0,
//		1,0,1,1,1,
//		1,1,0,0,0,
//		1,1,0,0,1,
//		0,1,0,1,0
//};
//
//
//   Graph* G = IniGraph(5);
//    CreatGraph(G, (int*)arcs,(char*)"ABCDE");
//    int* visit = new int[5];
//  for (int i = 0; i < 5; i++)
//  {
//	  visit[i] = 0;
//  }
//  //DFS(G,0, visit);
//  BFS(G, 0, visit);
//
//		
//
//
//}

//public class Edge {
//	public int weight;
//	public Node from;
//	public Node to;
//	public Edge(int weight, Node From, Node To)
//	{
//		this.weight = weight;
//		this.from = From;
//		this.to = To;
//	}
//
//}
//
//public class Node {
//	public int value;
//	public int in;
//	public int out;
//	public ArrayList<Node>nexts;
//	public ArrayList<Edge>edges;
//	public Node(int value) {
//		this.value = value;
//		in = 0;
//		out = 0;
//		nexts = new ArrayList<>();
//		edges = new ArrayList<>();
//	}
//
//
//}
//
//public class Graph {
//	public HashMap<Integer, Node>nodes;
//	public HashSet<Edge>edges;
//
//	public Graph() {
//		nodes = new HashMap<>();
//		edges = new HashSet<>();
//	}
//
//
//}