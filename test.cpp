#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<queue>
#include<stack>
#include<deque>
#include<cmath>
#include<cstdlib>
#include<unordered_map>
#include<unordered_set>
#include <cmath>

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
		int di[10] = {0};

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

		for (int i = 0; i < length; i++)
		{
			a[i] = fuzhu[i];
		}
		digit++;
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


void CreatGraph(Graph* G, int* N,const char* vex) {

	for (int i = 0; i < G->vexNum; i++) {
		G->vexs[i] = vex[i];
		for (int j = 0; j < G->vexNum; j++) {
			G->arcs[i][j] = *(N + i * G->vexNum + j);
			if (G->arcs[i][j] != 0	&& G->arcs[i][j]!=INT_MAX)
			{
				G->arcNum++;
			}
		}
	}
}


void DFS(Graph* G, int index, int* visit) {
	cout << G->vexs[index] << " ";
	visit[index] = 1;
	for (int i = 0; i < G->vexNum; i++) {
		if (G->arcs[index][i] !=0 &&G->arcs[index][i]!= INT_MAX&& visit[i] == 0) {
			DFS(G, i, visit);
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



int* findinDegree(Graph* G)
{
	int* INDegree = new int[G->vexNum];
	for (int i = 0; i < G->vexNum; i++) {
		INDegree[i] = 0;
	}
	for (int i = 0; i < G->vexNum; i++)
	{
		for (int j = 0; j < G->vexNum; j++)
		{
			if (G->arcs[i][j] != 0 &&G->arcs[i][j]!=INT_MAX)
			{
				INDegree[j] = INDegree[j] + 1;
			}
		}
	}
	return INDegree;
}

int* Tuopu(Graph* G)
{
	stack<int> s;
	int* in = findinDegree(G);
	int* Tuo = new int[G->vexNum];
	int index = 0;
	for (int i = 0; i < G->vexNum; i++)
	{
		if (in[i] == 0)
		{
			s.push(i);
		}
	}
	while (!s.empty())
	{
		int cur = s.top(); 
		s.pop();
		Tuo[index++] = cur;
		for (int i = 0; i < G->vexNum; i++)
		{
			if (G->arcs[cur][i] != 0&&G->arcs[cur][i] != INT_MAX)
			{
				in[i]--;
				if (in[i] == 0)
				{
					s.push(i);
				}
			}
		}
	}
	return Tuo;
}


int getindex(int* Tuo, int Len, int j)
{
	for (int i = 0; i < Len; i++) {
		if (Tuo[i] == j) {
			return i;
		}
	}
	return -1;
}


void keyPath(Graph* G)
{
	int* Tuo = Tuopu(G);
	int* early = new int[G->vexNum]{0};
	int* last = new int[G->vexNum]{0};
	for (int i = 0; i < G->vexNum; i++)
	{
		int max = 0;
		for (int j = 0; j < G->vexNum; j++)
		{
			if (G->arcs[j][Tuo[i]] > 0 && G->arcs[j][Tuo[i]] != INT_MAX)
			{
				int index = getindex(Tuo, G->vexNum, j);
				if (early[index] + G->arcs[j][Tuo[i]] > max)
				{
					max = early[index] +  G->arcs[j][Tuo[i]];
				}
			}
		}
		early[i] = max;
	}
	last[G->vexNum - 1] = early[G->vexNum - 1];
	for (int i = G->vexNum-2; i >=0 ; i--)
	{
		int min = INT_MAX;
		for (int j = 0; j < G->vexNum; j++) {
			if (G->arcs[Tuo[i]][j] > 0 && G->arcs[Tuo[i]][j] != INT_MAX) {
				int index = getindex(Tuo, G->vexNum, j);
				if (last[index] - G->arcs[Tuo[i]][j] < min)
				{
					min = last[index] - G->arcs[Tuo[i]][j];
				}
			}
		}
		last[i] = min;
	}
	for (int i = 0; i < G->vexNum; i++)
	{
		for (int j = 0; j < G->vexNum; j++) {
			if (G->arcs[i][j] != 0 && G->arcs[i][j] != INT_MAX)
			{
				int start = getindex(Tuo, G->vexNum, i);
				int end = getindex(Tuo, G->vexNum, j);
				if ((last[end] - G->arcs[i][j]) - early[start] == 0) {
					printf("start = %d end = %d\n", i, j);
				}
			}
		}
	}




}




void floyed(Graph* G)
{
	int** d = new int* [G->vexNum]; // 距离 
	int** p = new int* [G->vexNum]; // 前驱
	for (int i = 0; i < G->vexNum; i++)
	{
		d[i] = new int[G->vexNum];
		p[i] = new int[G->vexNum];
	}
	
	for (int i = 0; i < G->vexNum; i++)
	{
		for (int j = 0; j < G->vexNum; j++)
		{
			d[i][j] = G->arcs[i][j];
			if (G->arcs[i][j] != 0 && G->arcs[i][j] != INT_MAX)
			{		
				p[i][j] = i;
			}
			else {
				p[i][j] = -1;
			}
		}
	}
	for (int i = 0; i < G->vexNum; i++)
	{
		for (int j = 0; j < G->vexNum; j++)
		{
			for (int k = 0; k < G->vexNum; k++)
			{
				if (d[j][i] + d[i][k] < d[j][k])
				{
					d[j][k] = d[j][i] + d[i][k];
					p[j][k] = p[i][k];
				}
			}
		}
	}
	for (int i = 0; i < G->vexNum; i++)
	{
		for (int j = 0; j < G->vexNum; j++)
		{
			cout << d[i][j] << " ";

		}
		cout << endl;
	}
	cout << endl;

	for (int i = 0; i < G->vexNum; i++)
	{
		for (int j = 0; j < G->vexNum; j++)
		{
			cout << p[i][j] << " ";

		}
		cout << endl;
	}

}

int getMin(int* d, int* s, Graph* G) {
	int min = INT_MAX;
	int index;
	for (int i = 0; i < G->vexNum; i++) {
		if (!s[i] && d[i] < min) {
			min = d[i];
			index = i;
		}
	}
	return index;
}
void dijkstra(Graph* G, int index) {
	// 准备辅助数组
	int* s = (int*)malloc(sizeof(int) * G->vexNum);
	int* p = (int*)malloc(sizeof(int) * G->vexNum);
	int* d = (int*)malloc(sizeof(int) * G->vexNum);
	for (int i = 0; i < G->vexNum; i++)
	{
		if (G->arcs[index][i] != 0 && G->arcs[index][i] != INT_MAX)
		{
			d[i] = G->arcs[index][i];
			p[i] = index;
		}
		else
		{
			d[i] = INT_MAX;
			p[i] = -1;
		}
		if (i == index)
		{
			d[i] = 0;
			s[i] = 1;
		}
		else {
			s[i] = 0;
		}
		for (int i = 0; i < G->vexNum - 1; i++)
		{
			int  j = getMin(d, s, G);
			s[j] = 1;
			for (int c = 0; c < G->vexNum; c++)
			{
					if (!s[c]&&d[j] + G->arcs[j][c] < d[c])
					{
						d[c] = d[j] + G->arcs[j][c];
						p[c] = j;
			
					}
			}

		}
	}


}
//int main()
//{
//	Graph* G = IniGraph(9);
//	int N[9][9] = {0,6,4,5,INT_MAX,INT_MAX,INT_MAX,INT_MAX,INT_MAX ,
//					INT_MAX,0,INT_MAX,INT_MAX,1,INT_MAX,INT_MAX,INT_MAX,INT_MAX,
//					INT_MAX,INT_MAX,0,INT_MAX,1,INT_MAX,INT_MAX,INT_MAX,INT_MAX,
//					INT_MAX,INT_MAX,INT_MAX,0,INT_MAX,2,INT_MAX,INT_MAX,INT_MAX,
//					INT_MAX,INT_MAX,INT_MAX,INT_MAX,0,INT_MAX,9,7,INT_MAX,
//					INT_MAX,INT_MAX,INT_MAX,INT_MAX,INT_MAX,0,INT_MAX,4,INT_MAX,
//					INT_MAX,INT_MAX,INT_MAX,INT_MAX,INT_MAX,INT_MAX,0,INT_MAX,2,
//					INT_MAX,INT_MAX,INT_MAX,INT_MAX,INT_MAX,INT_MAX,INT_MAX,0,4,
//					INT_MAX,INT_MAX,INT_MAX,INT_MAX,INT_MAX,INT_MAX,INT_MAX,INT_MAX,0
//	};
//
//	CreatGraph(G, (int*)N, "abcdefghi");
//	int* viit = new int[9]{ 0 };
//	keyPath(G);
//}
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

vector<Node* >TuoPUSort(Graph1* Graphc)
{	
	//unordered_map<Node* , int>map;
	queue<Node*>qu;
	for (pair<int, Node*> p : Graphc->Nodes){	
		//map.insert(make_pair(p.second, p.first));
		if (p.second->in == 0){
			qu.push(p.second);
		}
    }

	vector<Node*>v;
	while (!qu.empty())
	{
		Node* N = qu.front();
		qu.pop();
		v.push_back(N);
		for (Node* o : N->nexts){
			o->in--;
			//map.insert(make_pair(o, o->in));
			if (o->in == 0)
			{
				qu.push(o);  
			}
		}
	}
	return v;
	
}

class Edgeo {
public:
	bool operator()(const Edge* a, const Edge* b)const
	{
		return a->weight < b->weight;
	}
};


unordered_set<Edge*>* Kri(Graph1* G)
{
	
	unordered_map<Node*, int> cmap;
	priority_queue<Edge*,vector<Edge*>,Edgeo> cqueue;
	for (Edge* E : G->Edges)
	{
		cqueue.push(E);
	}
	int i = 0;
	for (pair<int,Node*> s : G->Nodes)
	{
		cmap.insert(make_pair(s.second, i++));
	}
	unordered_set<Edge*> * v = new unordered_set<Edge*>();
	while (!cqueue.empty())
	{

		Edge* E = cqueue.top();
		cqueue.pop();
		if (cmap[E->From] != cmap[E->To])
		{
			v->insert(E);
			cmap[E->To] = cmap[E->From];
		}

	}
	return v;
}
//
//unordered_set<Edge*>* pri(Graph1* cGraph)
//{
//	unordered_set<Node*> NSet;
//	priority_queue<Edge*, vector<Edge*>, Edgeo> prio;
//	unordered_set<Edge*>* resu = new unordered_set<Edge*>();
//	for (pair<int, Node*> N : cGraph->Nodes)
//	{
//		if (NSet.find(N.second) == NSet.end())
//		{
//			NSet.insert(N.second);
//			for (Edge* E : N.second->Edges)
//			{
//				prio.push(E);
//			}
//		}
//		while (!prio.empty())
//		{
//			Edge* E = prio.top();
//			prio.pop();
//			if (NSet.find(E->To) == NSet.end())
//			{
//				NSet.insert(E->To);
//				resu->insert(E);
//				for (Edge* E : E->To->Edges)
//				{
//					prio.push(E);
//				}
//			}
//		}
//		return resu;
//
//
//	}
//}


//unordered_set<Edge*>* pri(Graph1* cGraph)
//{
//
//	unordered_set<Node*> NSet;
//	priority_queue<Edge*, vector<Edge*>, Edgeo> prio;
//	unordered_set<Edge*>* resu = new unordered_set<Edge*>();
//	for (pair<int, Node*> N : cGraph->Nodes)
//	{
//		if (NSet.find(N.second) == NSet.end())
//	  {
//		 NSet.insert(N.second);
//		 for (Edge* E :N.second->Edges)
//		 {
//			prio.push(E);
//		 }
//
//	  }
//
//		while (!prio.empty()) {
//			Edge* Ed = prio.top();
//			prio.pop();
//			Node* N = Ed->To;
//			if (NSet.find(N) == NSet.end())
//			{
//				resu->insert(Ed);
//				NSet.insert(N);
//				for (Edge* E : N->Edges)
//				{  
//					prio.push(E);
//				}
//			}
//		}
//	}
//	return resu;
//}


Node* selectedMin(unordered_map<Node*, int>* dis, unordered_set<Node*>* selectedNode)
{
	Node* l = nullptr;
	int Min = INT_MAX;
	for (pair<Node*, int> m : *dis)
	{
		if ((*selectedNode).find(m.first) == (*selectedNode).end() && m.second < Min)
		{
			Min = m.second;
			l = m.first;
		}
	}
	return l==nullptr? nullptr: l;
}


unordered_map<Node*, int>* djstra(Node* cNode)
{

	unordered_map<Node*, int >*dis = new unordered_map<Node*,int>;
	(*dis).insert(make_pair(cNode, 0));
	unordered_set<Node*>selectedNode;
	Node* m = selectedMin(dis, &selectedNode);

	while (m != nullptr)
	{   

		for (Edge* E : m->Edges)
		{
			Node* N = E->To;
			if ((*dis).find(N) == (*dis).end()) {
				(*dis).insert(make_pair(N, (*dis)[m] + E->weight));
			}
			(*dis).insert(make_pair(N, min((*dis)[N], (*dis)[m] + E->weight)));
		}
		selectedNode.insert(m);
		m = selectedMin(dis, &selectedNode);
	}

	return dis;

}



struct TreeN {
	int pass;
	int end;
	TreeN** T;
	TreeN() {
		pass = 0;
		end = 0;
		T = new TreeN*[26];
		for (int i = 0; i < 26; i++)
		{
			T[i] = nullptr;
		}
	}
};


class preTree {
private:
	TreeN* root;
public:
	preTree() {
		root = new TreeN;
	}
	void insert(string s) {
		TreeN* t = root;
		int c = s.size();
		int index;
		for (int i = 0; i < c; i++)
		{
			t->pass++;
			 index = s[i] - 'a';
			if (t->T[index] == nullptr)
			{
				t->T[index] = new TreeN();
			}
			t = t->T[index];
		}
		t->end++;
	}

	int Search(string  s)
	{
		TreeN* t = root;
		int index;
		int c = s.size();
		for (int i = 0; i < c; i++)
		{

			 index = s[i] - 'a';
			if (t->T[index] != nullptr) {
				t = t->T[index];
			}
			else {
				return 0;
			}
		}
		return t->end;
	}
	int preAs(string s)
	{
		TreeN* t = root;
		int index;		int c = s.size();
		for (int i = 0; i < c; i++)
		{

			 index = s[i] - 'a';
			if (t->T[index] != nullptr) {
				t = t->T[index];
			}
			else {
				return 0;
			}
		}
		return t->pass;



	}
	void delteback(TreeN* t)
	{     

		for (int i = 0; i < 26; i++) {
			if (t->T[i] != nullptr) {
				delteback(t->T[i]);
			}
		}
		delete t;
	}
	void  deletea(string s)
	{
		int c = s.size();
		if (Search(s) != 0){
			TreeN* t = root;

			for (int i = 0; i < c; i++){
				int index = s[i] - 'a';
				if (--t->pass == 0) {
					delteback(t);
				}
				t = t->T[index];
			}
			t->end--;
		}
	}
};


typedef struct time {
	int start;
	int end;
	time(int start, int end) {
		this->start = start;
		this->end = end;
	}
}time1;

class compt {
public:
	bool operator()(struct time& a, struct time& b)
	{
		return a.end < b.end;
	}
};


int cishu(vector<struct time>p, struct time a)
{
	sort(p.begin(), p.end(), compt());
	int result = 0;
	int c = p.size();
	for (int i = 0; i < c; i++) {
		if (a.start <= p[i].start &&a. end > p[i].end)
		{
			result++;
			a.start = p[i].end;
		}
	}
	return result;
}
 

typedef struct pro {
	int cost;
	int get;
	pro(int c, int g)
	{
		cost = c;
		get = g;
	}
}pro;


class  mn{
public:
	bool operator()(pro& p,pro& c)
	{	
		return p.cost < c.cost;
     }
};

class  mn1 {
public:
	bool operator()(pro& p, pro& c)
	{
		return p.cost > c.cost;
	}
};


int  HowMuch(vector<pro> p,int inm,int k)
{
	priority_queue<pro, vector<pro>, mn>coss;
	priority_queue<pro, vector<pro>, mn1>get;
	for (pro& pp : p)
	{
		coss.push(pp);
	}
	for (int i = 0; i < k; i++) {
		while (coss.top().cost <= inm) {
			get.push(coss.top());
			coss.pop();
		}
		if(!get.empty())
		inm += get.top().get;
            
	}
	return inm;
}

//       λ  
class MidNum
{

	priority_queue<int, vector<int>, less <int >> Big;
	priority_queue<int, vector<int>, greater<int>> small;
public:
	int num;
	MidNum() {
		num = 0;
	}
public:
	void insert(int in)
	{
		num++;
		if (Big.empty())
		{
			Big.push(in);
		}
		else {
			if (in <= Big.top())
			{
				Big.push(in);
			}
			else {
				small.push(in);
			}
			int v = Big.size() - small.size();
			if (abs(v) >= 2)
			{
				if (v > 0)
				{
					small.push(Big.top());
					Big.pop();
				}
				else {
					Big.push(small.top());
					small.pop();
				}

			}


		}

	}
	/*float GetMid()
	{
		if (num == 0)return -1;
		else if (num % 2 == 0) {
			return (Big.top() + small.top()) /2;
		}
		else {
			if (Big.size() > small.size()) {
				return Big.top();
			}
			return small.top();
		}
	}*/
};

bool Isvaild(int* Q, int s, int i)
{
	for (int k = 0; k < s; k++)
	{
		if (Q[k] == i || abs(Q[k] - i) == abs(k - s)) {
			return false;
		}
	}
	return true;
}
//}
//
//int process(int s, int* Q, int n)
//{
//	if (s == n) {
//		return 1;
//	}
//	string c;
//	c.push_back();
//	int res = 0;
//	for (int i = 0; i < n; i++) {
//		if (Isvaild(Q, s, i)) {
//			Q[s] = i;
//			res += process(s + 1, Q, n);
//		}
//	}
//	return res;
//}



int BitProcess(int limit, int col, int left, int right)
{
	if (col == limit)return 1;
	int pos = limit & ~(col | left | right);
	int res = 0;
	while (pos) {
		int ZRig = pos & (~pos + 1);
		pos = pos - ZRig;
		res += BitProcess(limit, col | ZRig, (left | ZRig) << 1, (right | ZRig) >> 1);
	}
	return res;
}

//  32λ
int NQueen(int n)
{
	/*if (n < 1)return 0;
	int* Q = new int[n];
	return process(0, Q, n);*/

	if (n < 1|| n>32)return 0;
	int limit = n == 32 ? -1 : (1 << n) - 1;
	return BitProcess(limit, 0, 0, 0);
}

typedef struct RecordNode
{
	Node* node;
	int distance;
	RecordNode(Node* n , int di)
	{
		node = n;
		distance = di;
	}

}RecordNode;

class Nodeheap {

public:

	Node** Nodes;
	int size;
	unordered_map<Node*, int> indexmap;
	unordered_map<Node*, int> distancemap;
	Nodeheap( int size1) {
		Nodes = new Node* [size1];
		this->size = 0;
	}
public:
	
	void AddorUpdateorIgnore(Node* n, int dis)
	{
		if (InHeap(n))
		{
			distancemap.insert(make_pair(n, min(distancemap[n], dis)));
			HeapInsert(n);
		}
		if (!IsEntered(n))
		{
			Nodes[size] = n;
			distancemap.insert(make_pair(n, dis));
			indexmap.insert(make_pair(n, size++));
			HeapInsert(n);

		}
	}

	void HeapInsert(Node* n)
	{
		int index = indexmap[n];
		while (distancemap[Nodes[index]] < distancemap[Nodes[(index - 1) / 2]])
		{
			myswap(index, (index - 1) / 2);
			index = (index - 1) / 2;
		}

	}

	RecordNode pop()
	{
		RecordNode  R = RecordNode(Nodes[0], distancemap[Nodes[0]]);
		myswap(0, size-1);
		indexmap.insert(make_pair(Nodes[size - 1], -1));
		distancemap.erase(Nodes[size - 1]);
		delete Nodes[size - 1];
		Nodes[--size] = nullptr;
		Headpify(0);
		return R;

	}

	void Headpify(int i)
	{
		int index = i;
		int left = index * 2 + 1;
		while (left < size)
		{
			int MoreSmall = left + 1 < size
				&&
				distancemap[Nodes[left + 1]] < distancemap[Nodes[left]] ? left + 1 : left;
			int FinS = distancemap[Nodes[index]] < distancemap[Nodes[MoreSmall]] ? index : MoreSmall;
			if (FinS == index)
			{
				break;
			}
			myswap(FinS, index);
			left = (FinS * 2) + 1;
		}


	}

	bool IsEmpty()
	{
		return size == 0;
	}

	bool IsEntered(Node* n)
	{
		return  indexmap.find(n) == indexmap.end();
	}

	bool InHeap(Node* n) {
		return IsEntered(n) && indexmap[n] != -1;
	}

	void myswap(int index1, int index2) {
		indexmap.insert(make_pair(Nodes[index1], index2));
		indexmap.insert(make_pair(Nodes[index2], index1));
		Node* t = Nodes[index1];
		Nodes[index1] = Nodes[index2];
		Nodes[index2] = t;
	}

};


unordered_map<Node*, int> * djsheap(Node* n)
{
	Nodeheap heap = Nodeheap(4);
	heap.AddorUpdateorIgnore(n, 0);
	unordered_map<Node*, int>* p = new unordered_map<Node*, int>;
	while (!heap.IsEmpty())
	{
		RecordNode min = heap.pop();
		for (Edge* E :  min.node->Edges)
		{
			Node* n = E->To;
			heap.AddorUpdateorIgnore(n, min.distance + E->weight);
		}
		p->insert(make_pair(min.node, min.distance));

	}
	return p;

}

void Hanprocess(int i,string star, string end, string other)
{
	if (i == 1)
		cout << i << " " << star << " " << end << endl;
	else {
		Hanprocess(i - 1, star, other, end);
		cout << i << " " << star << " " << end << endl;
		Hanprocess(i - 1, other, end, star);
	}


}

void hannuota(int n)
{
	if (n == 0)return;
	Hanprocess(n, "  ", "  ", "  ");
}

//charChildSequence

void pros(string *s, int i)
{
	if (i == (*s).size()) cout << *s<< " ";
	else{
		pros(s, i + 1);
		char  temp = (*s)[i];
		(*s)[i] = 0;
		pros(s, i + 1);
		(*s)[i] = temp;
	}

}

void Sequence(string s)
{
	pros(&s, 0);
}


//  ӡ ַ   ȫ       û   ظ 


void AllSequence(string s, int i, vector<string>&a)
{	
	int len = s.size();
		if (i == len) {
			a.push_back(s);
		}
	for (int j = i; j < len; j++) {
			swap(s[i], s[j]);
			AllSequence(s, i + 1, a);
			swap(s[i], s[j]);
	}
}

//  Ⱥ          {1  22  100  4};

int f(int a[], int i, int j);
int s(int a[], int i, int j)
{
	if (i == j)return 0;
	return min(f(a, i + 1, j), f(a, i, j - 1));
}

int f(int a[], int i, int j)
{
	if (i == j)return a[i];
	return max(a[i] + s(a, i + 1, j), a[j] + s(a, i, j - 1));
}

int WinScore(int arr[],int length)
{
	if (length == 0)return 0;

	return max(f(arr, 0, length - 1), s(arr, 0, length - 1));

}


int GetUnder(stack<int>& stack);

void Reserve(stack<int>& stack)
{
	   if (stack.empty())return;

		int under = GetUnder(stack);
		Reserve(stack);
		stack.push(under);
}


int GetUnder(stack<int>& stack)
{
	int cur = stack.top();
	stack.pop();
	if (stack.empty())return cur;
	else {

		int next = GetUnder(stack);
		stack.push(cur);
		return next;

	}
}


int processChar(int a[], int length, int i)
{
	if (i == length)return 1;
	if (a[i] == 0)return 0;

	if (a[i] == 1){
		int res = processChar(a, length, i + 1);
		if (i + 1 < length)
			res += processChar(a, length, i + 2);
		return res;
	}
	//if (a[i] == 2) {
	//	int res = processChar(a, length, i + 1);
	//	if (i + 1 < length && a[i + 1] < 7);
	//	res+=processChar(a, length, i + 2);
	//	return res;
	//}
	return processChar(a, length, i + 1);
}



int GetCharnum(int a[],int length)
{
	return processChar(a, length,0);
}   


double quickcheng(double x, long long N) {
	if (N == 0)
		return 0;

	double y = quickcheng(x, N / 2);
	return N % 2 == 0 ? y + y : y + y + x;
}

double myPow(double x, int n) {
	long long N = n;
	return quickcheng(x, N);
}

typedef struct stackst {
	int pre;
	int value;
	int back;
	
	stackst(int index, int val, int backindex)
	{
		pre = index;
		value = val;
		back = backindex;
	}
}stackst;
// 单调栈

class firststack {

private:
	stack<stackst * > container;
	vector<stackst* >contain;
public:
	void inputdata(int arr[] ,int len) 
	{
		for (int i = 0; i < len; i++) 
		{
			if (container.empty()) {
				stackst* s = new stackst(INT_MIN, arr[i], INT_MIN);
				container.push(s);
			}
			else
			{
				stackst* pre = nullptr;
				while (!container.empty() && container.top()->value < arr[i] )
				{
					pre = container.top();
					container.pop();
					pre->back = arr[i];
					if (!container.empty())
					{
						pre->pre = container.top()->value;
					}
					contain.push_back(pre);
				}
				stackst* s = new stackst(INT_MIN, arr[i], INT_MIN);
				container.push(s);
			}
	}
		stackst* pre = nullptr;
		while (!container.empty())
		{
			pre = container.top();
			container.pop();
			if (!container.empty())
			{
				pre->pre = container.top()->value;
			}
			contain.push_back(pre);
		}
	}
	void prin()
	{
		for (stackst* s : contain)
		{
			cout << s->pre << " " << s->value << " " << s->back << endl;
		}
	}
	
};

class Solution {
public:
	typedef struct maxo {
		int maxx;
		int index;
		maxo(int m, int i) {
			maxx = m;
			index = i;
		}
	}maxo;
	char* getadd(string s, int len)
	{
		char* sc = new char[len * 2 + 1];
		int index = 0;
		for (int i = 0; i < len * 2 + 1; i++)
		{
			sc[i] = (i & 1) == 1 ? s[index++] : '#';
		}
		return sc;

	}
	maxo manacher(string s)
	{
		int len = s.size();
		char* c = getadd(s, len);
		int* num = new int[len * 2 + 1];
		int R = -1;
		int C = -1;
		maxo res = maxo(INT_MIN, 0);
		for (int i = 0; i < len * 2 + 1; i++) {
			num[i] = R > i ? min(num[C * 2 - i], R - i) : 1;
			while (i + num[i] < len * 2 + 1 && i - num[i]>-1) {
				if (c[i + num[i]] == c[i - num[i]]) {
					num[i]++;
				}
				else {
					break;
				}
			}
			if (i + num[i] > R) {
				R = i + num[i];
				C = i;
			}
			if (num[i] > res.maxx) {
				res.maxx = num[i];
				res.index = i;
			}
		}
		return res;
	}
	string longestPalindrome(string s) {
		maxo m = manacher(s);
		return s.substr((m.index - (m.maxx - 1)) / 2, m.maxx - 1);
	}
};


vector<int> findAnagrams(string s, string p) {
	int lenp = p.size();
	int lens = s.size();
	if (lens < lenp) {
		return vector<int>();
	}
	vector<int>ans;
	vector<int>pcount(26, 0);
	for (int i = 0; i < lenp; i++) {
		pcount[p[i] - 'a']++;
	}

	for (int L = 0; L < lens - lenp + 1; L++)
	{
		vector<int>scount(26, 0);
		for (int R = L ; R < L + lenp; R++)
		{
			scount[s[R] - 'a']++;
		}
		if (scount == pcount) {
			ans.push_back(L);
		}
	}

	return ans;
}

vector<int>  findSubstring(string s, vector<string>& words) {
	int lens = s.size();
	int lenwords = words.size();
	int singlewordlen = words[0].size();
	if (lens < singlewordlen * lenwords) {
		return vector<int>();
	}
	vector<int>ans;
	unordered_map<string, int> wordsmap;
	for (int i = 0; i < lenwords; i++)
	{
		if (wordsmap.find(words[i]) == wordsmap.end()) {
			wordsmap.insert(make_pair(words[i], 1));
		}
		else {
			wordsmap[words[i]]++;
		}
	}
	int R = 0;
	unordered_map<string, int> smap;
	int flag = 0;
	for (int M = 0; M < singlewordlen; M++)
	{
		R = M;
		smap.clear();
		flag = 0;
		for (int L = M; L < lens - singlewordlen * lenwords + 1; L = L + singlewordlen)
		{
			if (flag == 0) {
				while (R <= L + singlewordlen * lenwords - singlewordlen)
				{
					string ss = s.substr(R, singlewordlen);
					if (smap.find(ss) == smap.end()) {
						smap.insert(make_pair(ss, 1));
					}
					else {
						smap[ss]++;
					}
					R = R + singlewordlen;

				}
				flag = 1;
			}
			else {
				if (R <= L + singlewordlen * lenwords - singlewordlen)
				{
					string ss = s.substr(R, singlewordlen);
					if (smap.find(ss) == smap.end()) {
						smap.insert(make_pair(ss, 1));
					}
					else {
						smap[ss]++;
					}
					R = R + singlewordlen;
				}
			}
			if (smap == wordsmap) {
				ans.push_back(L);
			}
			string ss = s.substr(L, singlewordlen);
			if (smap[ss] == 1)
			{
				smap.erase(ss);
			}
			else {
				smap[ss]--;
			}
		}
		if (singlewordlen == 1)
		{
			break;
		}
	}


	return ans;
}

	//int a[5] = { 1,2,3,4,5 };
	//cout << GetCharnum(a, 5);

	//cout << myPow(4, 5);


	//stack<int>s;
	//s.push(1); s.push(2); s.push(3);
	//Reserve(s);
	//while (!s.empty())
	//{
	//	cout << s.top();
	//	s.pop();
	//}

	//vector<string >a;
	//AllSequence("absb", 0, a);
	//for (string s : a)
	//{
	//	cout << s << endl;;
	//}


	//int a[4]{ 1, 2, 100, 4 };
	//cout << WinScore(a, 4);



	/*int v[4][3] = {
		{1,3,1},
		{2,4,2},
		{1,2,3},
		{4,3,4}
	};
	Graph1* G =   CreatMap(v,4);
	unordered_map<Node*, int>  *p =  djsheap(G->Nodes[1]);
	for (pair<Node*, int> c : *p)
	{
		cout << c.first->value << " " << c.second << endl;
	}*/

	//hannuota(3);


	//Sequence("abs");


	// 
	// 
	//BFS1(G->Nodes[1]);
	//cout << endl;
	// 
	// 
	//DFS(G->Nodes[1]);
	//cout << endl;
	// 
	//vector<Node*> b = TuoPUSort(G);
	//for (Node* n :b)
	//{
	//	cout << n->value << " " << n->in << endl;
	//}



	//K  㷨
	/* unordered_set<Edge*> *b =  Kri(G);
	 for (Edge* e : *b)
	 {	
		 cout << e->From->value << " " << e->To->value << endl;
	 }*/


	//   Ͻ ˹      
	//unordered_map<Node*, int>* c = djstra(G->Nodes[1]);
	//for (pair<Node*, int> m : *c)
	//{
	//	cout << m.first->value << " " << m.second << endl;
	// }


	//preTree p;
	//p.insert("abc");

	//p.insert("abc");

	//cout<<p.preAs("ab");


	//vector<struct time> p = { struct time(8,10),struct time(8,14),struct time(11,12),struct time(9,11) };
	//cout << cishu(p, struct time(8, 20));

	/*MidNum M;
	M.insert(1);
	M.insert(4);
	M.insert(10);
	M.insert(6);
	cout << M.GetMid();*/

     //cout << NQueen(4);

//}




//int main()
//{
	//string b{ "abacdc" };
	//KmpMtch(s, b, getNext(s));

	/*TreeNode *Ro;
	CreatTree(&Ro);
	//string s{ "abaccaba
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



int longestValidParentheses(string s) {
	int len = s.size();
	unordered_map<char, int> kuoMap;
	int o = 0;
	for (int i = 0; i < len; i++)
	{
		if (s[i] == '(' && o == 0)
		{
			kuoMap.insert(make_pair('(', i));
			o = 1;
		}
		else if (s[i] == ')')
		{
	

			if ( kuoMap.find(')') == kuoMap.end())
			{
				kuoMap.insert(make_pair(')', i));
			}
			else
			{
				kuoMap[')'] = i;
			}
		}
		
	}
	int maxlen = kuoMap[')'] - kuoMap['('];
	return maxlen;
}

int search(vector<int>& nums, int target) {
	int len = nums.size();
	int i = 0;
	while (i < len - 1 && nums[i] < nums[i + 1])
	{
		i++;
	}
	if (i >= len - 1)
	{
		vector<int>::iterator it = lower_bound(nums.begin(), nums.end(), target);
		if (it != nums.end()&& *it==target)
		{
			return it - nums.begin();
		}
		else {
			return -1;
		}
	}
	else {
		vector<int>::iterator it = lower_bound(nums.begin(), nums.begin() + i+ 1, target);
		if (it != nums.end()&&*it== target)
		{
			return it - nums.begin();
		}
		it = lower_bound(nums.begin() + i + 1, nums.end(),target);
		if (it != nums.end()&&*it ==target)
		{
			return it - nums.begin();
		}
		return -1;
	}
}

void AllSe(vector<string>& words, int i, vector<string>& res)
{
	int size = words.size();
	if (i == size) {
		string all;
		for (int c = 0; c < size; c++) {
			all += words[c];
		}
		res.push_back(all);
		return;
	}

	unordered_set<string> set;
	for (int j = i; j < size; j++) {
		if (set.find(words[j]) == set.end())
		{
			set.insert(words[j]);
			swap(words[i], words[j]);
			AllSe(words, i + 1, res);
			swap(words[i], words[j]);
		}
	}
}
//
//vector<int> searchRange(vector<int>& nums, int target) {
//	int len = nums.size();
//	if (len == 0)return vector<int> {-1, -1};
//	if (nums[0] > target || nums[len - 1] < target)return vector<int>{-1, -1};
//	vector<int>ans;
//	vector<int>::iterator it = lower_bound(nums.begin(), nums.end(), target);
//	if(*it != target)
//	{
//		return vector<int>{-1, -1};
//	}
//	else {
//		ans.push_back(it - nums.begin());
//		while ( ++it < nums.end()&& *it == target){}
//		ans.push_back(--it - nums.begin());
//	}
//
//}
//



bool isvaild(int h, int* Q, int l)
{
	for (int k = 0; k < h; k++)
	{
		if (Q[k] == l || abs(Q[k] - l) == abs(k - h))
		{
			return false;
		}
	}
	return true;
}

//void process(vector<vector<string>>& ans, int current, int* Q,const int n, vector<string>mcv)
//{
//	if (current == n)
//	{
//		ans.push_back(mcv);
//	}
//	for (int i = 0; i < n; i++)
//	{
//
//		string mc(n, '.');
//		if (isvaild(current, Q, i))
//		{
//			Q[current] = i;
//			mc[i] = 'Q';
//			mcv.push_back(mc);
//			process(ans, current + 1, Q, n, mcv);
//		}
//		else {
//			mcv.clear();
//			mcv.pop_back()
//		}
//	}
//}

int row[9] = { 0 };
int col[9] = { 0 };
int three[3][3] = { 0 };
int getnext(int x, int y)
{

	return  (~(row[x] | col[y] | three[x / 3][y / 3]) & (1 << 10) - 1);
}


bool DFS(vector<vector<char>>& board, int currentRow)
{
	if (currentRow == 8)
	{
		return true;
	}
	for (int j = 0; j < 9; j++)
	{
		if (board[currentRow][j] != '.')
		{
			int x = 1 << (board[currentRow][j] - '1');
			row[currentRow] |= x;
			col[j] |= x;
			three[currentRow / 3][j / 3] |= x;
		}
		else {
			int x = getnext(currentRow, j);
			if (x == 0) { return false; }
			while (x != 0)
			{
				int Zone = x & (~x + 1);
				x -= Zone;
				int in = 1;
				while (Zone != 1)
				{
					Zone >>= 1;
					in++;
				}
				board[currentRow][j] = in + '0';
				if (DFS(board, currentRow + 1)) {
					break;
				}
			}
		}
	}
	return false;
}


void solveSudoku(vector<vector<char>>& board) {
	DFS(board, 0);
}
//vector<vector<string>> solveNQueens(int n) {
//	int* Q = new int[n];
//	vector<vector<string>>ans;
//	vector<string>mcv;
//	process(ans, 0, Q, n, mcv);
//	return ans;
//}


string process(int n)
{
	string ans;
	if (n == 1)
		return "1";
	else
	{
		string s = process(n - 1);
		int len = s.size();

		int i = 0;
		while (i < len)
		{
			int l = 1;
			while (i + 1 < len && s[i] == s[i + 1])
			{
				l += 1;
				i++;
			}
			ans += l + '0';
			ans += s[i++];
		}
		return ans;
	}
}

string countAndSay(int n) {
	return process(n);
}

bool process(vector<vector<int>>& ans, vector<int> candidates, int target, int num, vector<int>ever, int index)
{
	if (num == target)
	{
		ans.push_back(ever);
		return true;
	}
	int len = candidates.size();
	for (int i = index; i < len; i++) {
		int nom = candidates[i];
		if (num + candidates[i] <= target)
		{
			ever.push_back(candidates[i]);
			vector<int> ::iterator it = candidates.begin();
			candidates.erase(it + i);
			if (!process(ans, candidates, target, num + nom, ever, i)) {
				ever.pop_back();
			}
			it = candidates.begin();
			candidates.insert(it + i, nom);
		}
		else {
			return false;
		}
	}
	return false;
}

template <typename V>
class Ele
{
public:
	V value;
	Ele(V v)
	{
		value = v;
	}
};

template<typename V>
class UnionFIndSet
{
public:

	unordered_map<V, Ele<V>*>elementmap;
	// 包裹map；

	unordered_map<Ele<V>*, Ele<V>*>fathermap;
	// 父亲map;

	unordered_map<Ele<V>*, int>sizemap;
	//大小map;
	UnionFIndSet(vector<V>&All)
	{
		for (V value : All)
		{
			Ele<V>* el = new Ele<V>(value);
			elementmap.insert(make_pair(value, el));
			fathermap.insert(make_pair(el, el));
			sizemap.insert(el, 1);

		}
	}
	Ele<V>* findHead(Ele<V>* element)
	{
		stack<Ele<V>* >path;
		while (element != fathermap[element]) {
			path.push(element);
			element = fathermap[element];
		}
		while (!path.empty())
		{
			fathermap.insert(make_pair(path.top(), element));
			path.pop();
		}
		return element;
	}


	bool isSameSet(V a, V b)
	{
		if (elementmap.find(a) != elementmap.end() && elementmap.find(b) != elementmap.end())
		{
			return findHead(elementmap[a]) == findHead(elementmap[b]);
		}
		return false;
	}
	void union1(V a, V b)
	{
		if (elementmap.find(a) != elementmap.end() && elementmap.find(b) != elementmap.end())
		{
			Ele<V>*af = findHead(elementmap[a]);
			Ele<V>*bf = findHead(elementmap[b]);
			if (af != bf) {
				Ele<V>* big = sizemap[af] >= sizemap[bf] ? af : bf;
				Ele<V>* small = big == af ? bf : af;
				fathermap.insert(make_pair(small, big));
				sizemap.insert(make_pair(big, sizemap[af] + sizemap[bf]));
				sizemap.erase(small);
			}
		}
	}
	



};

vector<vector<int>> combinationSum2(vector<int>& candidates, int target) {
	sort(candidates.begin(), candidates.end(), less<int>());
	if (candidates[0] > target)
	{
		return vector<vector<int>>();
	}
	vector<vector<int>> ans;
	vector<int> b;
	process(ans, candidates, target, 0, b, 0);
	return ans;
}


int firstMissingPositive(vector<int>& nums) {
	int len = nums.size();
	int i = 0;
	while (i<len)
	{
		if (nums[i] >= 1 && nums[i] <= len && nums[nums[i] - 1]!= nums[i])
		{
			swap(nums[i], nums[nums[i] - 1]);
		}
		else
			i++;
	}
	for (int i = 0; i < len; i++)
	{
		if (nums[i] != i + 1)
		{
			return i + 1;
		}
	}
	return len + 1;
}


int* water(vector<int>& height, int index, int len, int* a,int f)
{

	int l = index, r = index;
	int lmax = index, rmax = index;
	int flag = 0;
	if (f == 0)
	{
		if (index != 1 && height[index] == height[index - 1])
		{
			return a;
		}
		else if (index != 1 && height[index] < height[index - 1])
		{
			flag = 1;
			rmax = a[2];
			lmax = a[1];
		}
	}
	if (flag == 0)
	{
		while (l > 0 || r < len - 1)
		{
			if (l > 0)
			{
				if (height[--l] >= height[lmax])
				{
					lmax = l;
				}
			}
			if (r < len - 1)
			{
				if (height[++r] >= height[rmax])
				{
					rmax = r;
				}
			}
		}
	}
	a[0] = min(height[lmax], height[rmax]) - height[index];
	a[1] = lmax;
	a[2] = rmax;
	return a;
}

int trap(vector<int>& height) {
	int len = height.size();
	int ans = 0;
	int* a = new int[3]{-1};
	int flag = 0;
	for (int i = 1; i < len - 1; i++)
	{
		if (i - 1 == a[2])
		{
			flag = 1;
		}
		ans += water(height, i, len,a,flag)[0];
		flag = 1;
		cout << height[a[1]] << " " << height[i] << " " << height[a[2]]<<" " << a[0] << endl;
	}
	return ans;
}

string addStrings(string num1, string num2) {
	char arr[5];
	int R = 4;
	int len1 = num1.size() - 1;
	int len2 = num2.size() - 1;
	int jinwei = 0;
	while (len1 >= 0 && len2 >= 0)
	{
		int l1 = num1[len1] - '0';
		int l2 = num2[len2] - '0';
		int benwei = (l1 + l2 + jinwei) % 10;

		jinwei = (l1 + l2 + jinwei) / 10;

		arr[R--] = benwei + '0';
		len1--; len2--;
	}
	if (len1 < 0 && len2 >= 0)
	{
		while (len2 >= 0)
		{
			int l2 = num2[len2] - '0';
			int benwei = (l2 + jinwei) % 10;
			jinwei = (l2 + jinwei) / 10;
			arr[R--] = benwei + '0';
			len2--;
		}

	}
	else
	{
		while (len1 >= 0)
		{
			int l1 = num2[len2] - '0';
			int benwei = (l1 + jinwei) % 10;
			jinwei = (l1 + jinwei) / 10;
			arr[R--] = benwei + '0';
			len1--;
		}

	}
	string ans(arr,++R);
	return ans;
}


vector<vector<string>> groupAnagrams(vector<string>& strs) {
	int len = strs.size();
	vector<vector<string>>ans;
	unordered_map<string, int> umap;
	int index = 0;
	string temp;
	for (int i = 0; i < len; i++)
	{
		temp = strs[i];
		sort(strs[i].begin(), strs[i].end());
		if (umap.find(strs[i]) == umap.end())
		{
			ans.push_back(vector<string>{temp});
			umap.insert(make_pair(strs[i], index++));
		}
		else {
			ans[umap[strs[i]]].push_back(temp);
		}
	}
	return ans;
}

//53 
void maxSubArray(vector<int>& nums) {
	int len = nums.size();
	int * arr = new int[len];
	arr[0] = nums[0];
	for (int i = 1; i < len; i++){
		arr[i] = arr[i - 1] + nums[i];
	}
	for (int i = 0; i < len; i++) {
		cout << arr[i] << " ";
	}
}

//54

vector<int> spiralOrder(vector<vector<int>>& matrix) {
	int row = matrix.size();
	int col = matrix[0].size();
	int index = 0;
	vector<int> ans(row*col);
	int up = 0, down = row;
	int left = -1; int right = col;
	int CR = 0, CC = 0;
	int flag = 0;
	while (index < row * col)
	{
		if (flag == 0) {
			ans[index++] = matrix[CR][CC++];
			if (CC == right) {
				flag = 1;
				CC--;
				CR++;
				right--;
			}
		}
		if (flag == 1) {
			ans[index++] = matrix[CR++][CC];
			if (CR == down) {
				flag = 2;
				CR--;
				CC--;
				down--;
			}
		}
		if (flag == 2) {
			ans[index++] = matrix[CR][CC--];
			if (CC == left) {
				flag = 3;
				CC++;
				CR--;
				left++;
			}
		}
		if (flag == 3) {
			ans[index++] = matrix[CR--][CC];
			if (CR == up) {
				flag = 0;
				CR++;
				CC++;
				up++;
			}
		}

	}
	return ans;
}


//56

bool com(vector<int>& a, vector<int>& b)
{
	return a[0] < b[0];
}

vector<vector<int>> merge(vector<vector<int>>& intervals) {
	
	sort(intervals.begin(), intervals.end(), com);
	vector<vector<int>> ::iterator it = intervals.begin();
	vector<vector<int>> ans;
	int index = 0;
	while (it != intervals.end())
	{

		ans.push_back(*it);
		vector<vector<int>> ::iterator it1 = it + 1;
		while (it1 != intervals.end())
		{
			if ((*it1)[0] <= ans[index][0] && (*it1)[1] >= ans[index][0] || (*it1)[0] >= ans[index][0] && (*it1)[0] <= ans[index][1])
			{
				ans.at(index)[1] = max(ans.at(index)[1], (*it1)[1]);
				ans.at(index)[0] = min(ans.at(index)[0], (*it1)[0]);
				it1 = intervals.erase(it1);




			}
			else {
				it1++;
			}
		}
		it++;
		index++;
	}
	return ans;
}
//
//#include <iostream>
//#include <cmath>
//#define M_PI 3.1415
//using namespace std;
//
//double normal_pdf(double x, double mu, double sigma) {
//	double a = 1.0 / (sigma * sqrt(2 * M_PI));
//	double b = exp(-1.0 * pow(x - mu, 2) / (2 * pow(sigma, 2)));
//	return a * b;
//}
//
//void plot(double mu, double sigma) {
//	for (int i = 0; i < 30; i++) {
//		double x = mu - 3 * sigma + i * 0.2 * sigma;
//		double y = normal_pdf(x, mu, sigma) * 100;
//		for (int j = 0; j < y; j++) {
//			cout << "*";
//		}
//		cout << endl;
//	}
//}
//
//
//
//
//int main() {
//	i.front();
//	double mu = 170, sigma = 5;
//	plot(mu, sigma);
//
//	return 0;
//}

// 57
vector<vector<int>> insert(vector<vector<int>>& intervals, vector<int>& newInterval) {
	int len = intervals.size();
	int i = 0;
	while (i < len && intervals[i][0] < newInterval[0])
	{
		i++;
	}
	vector<vector<int>>::iterator it = intervals.begin() + i;
	intervals.insert(it, newInterval);
	int index = 0;
	int r = index + 1;
	int flag = 0;
	int com;
	while (index < len)
	{
		com = intervals[index][1];
		while (r < len && intervals[r][0] <= com)
		{
			com = max(intervals[r][1], com);
			r++;
			flag = 1;
		}
		if (flag == 1)
		{
			vector<vector<int>>::iterator it1 = intervals.begin();
			intervals[index][1] = com;
			intervals.erase(it1 + index + 1, it1 + r);
			break;
		}
		index = r;
		r++;
	}
	return intervals;
}

//58
int lengthOfLastWord(string s) {
	int len = s.size();
	if (len == 0)return 0;
	int j = len - 1;
	while (j >= 0 && s[j] == ' ')
	{
		j--;
	}
	int i = j;
	for ( i = j; i >= 0; i--)
	{
		if (s[i] == ' ') {
			break;
		}
	}

	return j - i;;
}
vector<vector<int>> generateMatrix(int n) {
	int i = 1;
	vector<vector<int>>matrix(n, vector<int>(n));
	int row = matrix.size();
	int col = matrix[0].size();
	int index = 0;
	int up = 0, down = row;
	int left = -1; int right = col;
	int CR = 0, CC = 0;
	int flag = 0;
	while (i <= row * col)
	{
		if (flag == 0) {
			matrix[CR][CC++] = i++;
			if (CC == right) {
				flag = 1;
				CC--;
				CR++;
				right--;
			}
		}
		else if (flag == 1) {
			matrix[CR++][CC] = i++;
			if (CR == down) {
				flag = 2;
				CR--;
				CC--;
				down--;
			}
		}
		else if (flag == 2) {
			matrix[CR][CC--] = i++;
			if (CC == left) {
				flag = 3;
				CC++;
				CR--;
				left++;
			}
		}
		else if (flag == 3) {
			matrix[CR--][CC] = i++;
			if (CR == up) {
				flag = 0;
				CR++;
				CC++;
				up++;
			}
		}

	}
	return matrix;
}


int process(int curx, int cury, int x, int y,vector<vector<int>>&ans)
{
	if (ans[curx][cury] != 0)return ans[curx][cury];
	if (curx == x && cury == y)
	{
		ans[curx][cury]  = 1;
		return ans[curx][cury];
	}
	if (cury == y)
	{
		ans[curx][cury] =  process(curx + 1, cury, x, y,ans);
		return ans[curx][cury];

	}
	if (curx == x)
	{
		ans[curx][cury] =  process(curx, cury + 1, x, y,ans);
		return ans[curx][cury];
	}
	ans[curx][cury] =  process(curx + 1, cury, x, y,ans) + process(curx, cury + 1, x, y,ans);
	return ans[curx][cury];
}

int uniquePaths(int m, int n) {
	vector<vector<int>> ans(m + 1, vector<int>(n + 1,0) );
	return process(1, 1, m, n, ans);
}

// 6 4
int process(int curx, int cury, int x, int y, vector<vector<int>>& grid, vector<vector<int>>& ans)
{
	if (ans[curx][cury] != -1)return ans[curx][cury];
	if (curx == x && cury == y)
	{
		ans[curx][cury] = grid[curx-1][cury-1];
		return ans[curx][cury];
	}
	if (cury == y)
	{
		ans[curx][cury] = process(curx + 1, cury, x, y, grid, ans) + grid[curx-1][cury-1];
		return ans[curx][cury];
	}
	if (curx == x)
	{
		ans[curx][cury] = process(curx, cury + 1, x, y, grid, ans) + grid[curx-1][cury-1];
		return ans[curx][cury];
	}
	ans[curx][cury] = min(process(curx + 1, cury, x, y, grid, ans), process(curx, cury + 1, x, y, grid, ans)) + grid[curx-1][cury-1];
	return ans[curx][cury];
}
int minPathSum(vector<vector<int>>& grid) {
	int x = grid.size();
	int y = grid[0].size();
	vector<vector<int>>ans(x + 1, vector<int>(y + 1, -1));
	return process(1, 1, x, y, grid, ans);

}
int countPairs(vector<int>& nums, int target) {
	sort(nums.begin(), nums.end());
	int ans = 0;
	int left = 0;
	int right = nums.size() - 1;
	while (left < right)
	{
		if (nums[left] + nums[right] < target) {
			ans += right - left;
			left++;
		}
		else {
			right--;
		}
	}
	return ans;
}


string addBinary(string a, string b) {
	int la = a.size();
	int lb = b.size();
	if (!la || !lb)
	{
		return la ? a : b;
	}
	int lla = la - 1;
	int llb = lb - 1;
	string ans;
	bool jin = false;
	while (lla >= 0 && llb >= 0)
	{
		if (a[lla] == '1' && b[llb] == '1' || a[lla] == '0' && b[llb] == '0')
		{
			if (jin)
			{
				ans.insert(ans.begin(), '1');
			}
			else
			{
				ans.insert(ans.begin(), '0');
			}
			if (a[lla] == '1')
			{
				jin = true;
			}
			else
			{
				jin = false;
			}
		}
		else {
			if (jin)
			{
				ans.insert(ans.begin(), '0');
			}
			else
			{
				ans.insert(ans.begin(), '1');
			}

		}

		lla--;
		llb--;
	}
	while (lla >= 0)
	{
		ans.insert(ans.begin(), a[lla]);
		lla--;
	}
	while (llb >= 0)
	{
		ans.insert(ans.begin(), a[llb]);
		llb--;
	}
	return ans;
}






void setZeroes(vector<vector<int>>& matrix) {
	int x = matrix.size();
	int y = matrix[0].size();
	int* row = new int[x] {1};
	int* col = new int[y] {1};
	for (int i = 0; i < x; i++)
	{
		for (int j = 0; j < y; j++)
		{
			row[i] = matrix[i][j] * row[i];
			col[j] = matrix[i][j] * col[j];
		}
	}
	for (int i = 0; i < x; i++)
	{
		cout << row[i];
	}
	for (int j = 0; j < y; j++)
	{
		cout << col[j];
	}
	for (int i = 0; i < x; i++)
	{
		for (int j = 0; j < y; j++)
		{
			if (row[i] == 0 && col[j] == 0)
			{
				matrix[i][j] = 0;
			}
		}
	}

}
void sortColors(vector<int>& nums) {
	int l = 0;
	int r = nums.size() - 1;
	int index = 0;
	while (index <= r)
	{
		if (nums[index] == 0)swap(nums[index++], nums[l++]);
		else if (nums[index] == 2)
		{
			if (nums[r] == 2) r--;
			else swap(nums[index], nums[r--]);
		}
		else index++;
	}
}
//string minWindow(string s, string t) {
//	unordered_map<char, int >tmap;
//	int  tlen = t.size();
//	int  slen = s.size();
//	for (int i = 0; i < tlen; i++)
//	{
//		if (tmap.find(t[i]) != tmap.end()) {
//			tmap[t[i]]++;
//		}
//		tmap.insert(make_pair(t[i], 1));
//	}
//}

void process(vector<vector<int>>& ans, int curnum, int k, int n, int pren, vector<int>vec)
{
	if (curnum == k) {
		ans.push_back(vec);
	}
	for (int i = pren + 1; i <= n; i++)
	{
		vec.push_back(i);
		process(ans, curnum + 1, k, n, i,vec );
		vec.pop_back();
	}
}
vector<vector<int>> combine(int n, int k) {
	vector<vector<int>> ans;
	vector<int >v;
	process(ans, 0, k, n, 0, v);
	return ans;
}
//vector<vector<int>> subsets(vector<int>& nums) {
//	int n = nums.size();
//	vector<vector<int>>ans;
//	int  bin = pow(2, n) - 1;
//	while (bin > 0)
//	{
//		vector<int>an;
//		for (int i = n - 1; i >= 0; i--)
//		{
//			if ((1 & (bin >> i)) == 1) {
//				an.push_back(nums[i]);
//			}
//		}
//		ans.push_back(an);
//		bin--;
//	}
//	return ans;
//}

bool process(bool** used, vector<vector<char>>& board, string word, int index, int cux, int cuy, int flag)
{
	int x = board.size();
	int y = board[0].size();
	if (index == word.size())return true;
	if (cux >= x || cux < 0 || cuy >= y || cuy < 0)return false;
	if (*(*(used + cux) + cuy))return false;
	if (board[cux][cuy] == word[index]) {
		*(*(used + cux) + cuy) = true;
		if (flag != 2 && process(used, board, word, index + 1, cux - 1, cuy, 1)) {
			return true;
		}
		if (flag != 1 && process(used, board, word, index + 1, cux + 1, cuy, 2)) {
			return true;
		}
		if (flag != 4 && process(used, board, word, index + 1, cux, cuy - 1, 3)) {
			return true;
		}
		if (flag != 3 && process(used, board, word, index + 1, cux, cuy + 1, 4)) {
			return true;
		}
		*(*(used + cux) + cuy) = false;
	}
	return false;

}
bool exist(vector<vector<char>>& board, string word)
{

	int x = board.size();
	int y = board[0].size();
	bool** used = new bool* [x];
	for (int i = 0; i < x; i++) {
		used[i] = new bool[y];
	}
	int index = 0;
	int w = word.size();
	if (x * y < w)
	{
		return false;
	}
	for (int i = 0; i < x; i++) {
		for (int j = 0; j < y; j++)
		{
			used[i][j] = false;
		}
	}
	for (int i = 0; i < x; i++)
	{
		for (int j = 0; j < y; j++)
		{
			if (board[i][j] == word[index])
			{
				if (process(used, board, word, index, i, j, -1))
					return true;
			}
			used[i][j] = false;
		}
	}
	return false;
}



ListNode* deleteDuplicates(ListNode* head) {
	ListNode* f = head->next;
	ListNode* s = new ListNode;
	s->next = head;
	while (f != nullptr)
	{
		if (f->val != s->next->val)
		{
			ListNode* pre = s->next;
			s->next = f;
			f = f->next;
			s = pre;
		}
		else {
			while (f != nullptr && f->val == s->next->val) {
				f = f->next;
			}
			s->next = f;
			f = f->next;
		}
	}
	return head;
}


int largestRectangleArea(vector<int>& heights) {
	int num = heights.size();
	int*  stack = new int[num];
	int top = -1;
	int index, area, ans = 0;
	for (int i = 0; i < num; i++)
	{
		if (top == -1) {
			stack[++top] = i;
		}
		else {
			while (top != -1 && heights[stack[top]] > heights[i]) {
				index = stack[top--];
				if (top == -1) {
					area = heights[index] * i;
				}
				else {
					area = heights[index] * (i - stack[top] - 1);
				}
				ans = max(ans, area);
			}
			stack[++top];
		}

	}
	while (top != -1) {
		index = stack[top--];
		if (top == -1) {
			area = heights[index] * num;
		}
		else {
			area = heights[index] * (num - 1 - stack[top]);
		}
		ans = max(ans, area);
	}
	return ans;
}


//int TreeN(int n)
//{
//	if (n < 0)return 0;
//	if (n == 0 || n == 1)return 1;
//	if (n == 2)return 2;
//	for (int left = 0; left <= n - 1; left++) {
//		int leftnum = TreeN(left);
//		int rightnum = TreeN(n - left - 1);
//		return leftnum * rightnum;
//	}
//
//}


int maximalRectangle(vector<vector<char>>& matrix)
{
	int x = matrix.size();
	int y = matrix[0].size();
	int hang[4][5];
	int lie[4][5];
	for (int i = 0; i < x; i++) {
		for (int j = 0; j < y; j++) {
			if (j == 0) {
				hang[i][j] = matrix[i][j];
			}
			else {
				hang[i][j] = matrix[i][j] == '0' ? 0 : matrix[i][j - 1] + 1;
			}
		}
	}
	for (int i = 0; i < y; i++) {
		for (int j = 0; j < x; j++) {
			if (j == 0) {
				lie[j][i] = matrix[j][i];
			}
			else {
				lie[j][i] = matrix[j][i] == '0' ? 0 : matrix[j - 1][i] + 1;
			}
		}
	}



	for (int i = 0; i < x; i++) {
		for (int j = 0; j < y; j++) {
			cout << hang[i][j] << " ";
		}
		cout << endl;
	}
	for (int i = 0; i < x; i++) {
		for (int j = 0; j < y; j++) {
			cout << lie[i][j] << " ";
		}
		cout << endl;
	}

	return 0;
}

////并查集
//template<typename V>
//class UnionFIndSet
//{
//public:
//	unordered_map<V, Ele<V>*>elementmap;
//	// 包裹map；
//
//	unordered_map<Ele<V>*, Ele<V>*>fathermap;
//	// 父亲map;
//
//	unordered_map<Ele<V>*, int>sizemap;
//	//大小map;
//	UnionFIndSet(vector<V>& All)
//	{
//		for (V value : All)
//		{
//			Ele<V>* el = new Ele<V>(value);
//			elementmap.insert(make_pair(value, el));
//			fathermap.insert(make_pair(el, el));
//			sizemap.insert(make_pair(el, 1));
//		}
//	}
//
//
//	Ele<V>* findHead(Ele<V>* element)
//	{
//		stack<Ele<V>* >path;
//		while (element != fathermap[element]) {
//			path.push(element);
//			element = fathermap[element];
//		}
//		while (!path.empty())
//		{
//			fathermap.insert(make_pair(path.top(), element));
//			path.pop();
//		}
//		return element;
//	}
//
//	bool isSameSet(V a, V b)
//	{
//		if (elementmap.find(a) != elementmap.end() && elementmap.find(b) != elementmap.end())
//		{
//			return findHead(elementmap[a]) == findHead(elementmap[b]);
//		}
//		return false;
//	}
//	void union1(V a, V b)
//	{
//		if (elementmap.find(a) != elementmap.end() && elementmap.find(b) != elementmap.end())
//		{
//			Ele<V>* af = findHead(elementmap[a]);
//			Ele<V>* bf = findHead(elementmap[b]);
//			if (af != bf) {
//				Ele<V>* big = sizemap[af] >= sizemap[bf] ? af : bf;
//				Ele<V>* small = big == af ? bf : af;
//				fathermap[small] = big;
//				sizemap[big] = sizemap[af] + sizemap[bf];
//				sizemap.erase(small);
//			}
//		}
//	}
//};



void process(vector<vector<int>>& ans, int now, vector<int>& nums, vector<int>v, unordered_set<int>&set)
{
	if (now == nums.size()) {
		ans.push_back(v);
		return;
	}
	process(ans, now + 1, nums, v, set);
	if (set.find(nums[now]) == set.end())
	{
		v.push_back(nums[now]);
		set.insert(nums[now]);
		process(ans, now + 1, nums, v, set);
	}


}
void process(vector<string>& ans, string s, int ji, int index, string temp)
{
	int lens = s.size();
	if (ji == 5 && index >= lens) {
		ans.push_back(temp);
		return;}
	if (index >= lens) {return;}
	if (ji != 1)temp += '.';
	string ss = s.substr(index, 3);
	int len = ss.size();
	if (len >= 1){process(ans, s, ji + 1, index + 1, temp + ss.substr(0, 1));}
	if (len >= 2)
	{
		if (ss[0] != '0')
		{
			process(ans, s, ji + 1, index + 2, temp + ss.substr(0, 2));
			if (len == 3 && stoi(ss) <= 255)
				process(ans, s, ji + 1, index + 3, temp + ss);
		}
	}

}


vector<string> restoreIpAddresses(string s) {
	vector<string>ans;
	process(ans, s, 1, 0, string());
	return ans;
}

	int prim(vector<vector<int> >& points, int start) {
		int n = points.size();
		int res = 0;

		// 1. 邻接矩阵
	    vector<vector<int> > g(n, vector<int>(n));	
		for (int i = 0; i < n; i++) {
			for (int j = i + 1; j < n; j++) {
				int dist = abs(points[i][0] - points[j][0]) + abs(points[i][1] - points[j][1]);
				g[i][j] = g[j][i] = dist;
			}
		}


		// 记录V中的点到Vnew的最近距离
		vector<int> lowcost(n, INT_MAX);
		// 记录V中的点是否加入到了Vnew
		vector<int> v(n);
		// lowcost 和 v 可以优化成一个数组

		// 2. 先将start加入到Vnew
		v[start] = 1;
		for (int i = 0; i < n; i++) {
			if (i == start) continue;
			lowcost[i] = g[i][start];
		}

		// 3. 遍历剩余若干个未加入到Vnew的节点
		for (int _ = 1; _ < n; _++) {
			// 找出此时V中，离Vnew最近的点
			int minIdx = -1;
			int minVal = INT_MAX;
			for (int j = 0; j < n; j++) {
				if (v[j] == 0 && lowcost[j] < minVal) {
					minIdx = j;
					minVal = lowcost[j];
				}
			}
			// 将最近的点加入Vnew
			v[minIdx] = 1;    
			res += minVal;

			// 更新集合V中剩余所有点的lowcost
			for (int j = 0; j < n; j++) {
				if (v[j] == 0 && g[j][minIdx] < lowcost[j]) {
					lowcost[j] = g[j][minIdx];
				}
			}
		}
		return res;

	}
	int minCostConnectPoints(vector<vector<int>>& points) {
		return prim(points, 0);
	}


class klset
{

	vector<int>parent;
	vector<int>rank;
	klset(int n) :parent(vector<int>(n)), rank(vector<int>(n)) {
		for (int i = 0; i < n; i++) {
			parent[i] = i;
		}
	}
	int findhead(int  x) {
		if (x != parent[x]) {
			parent[x] = findhead(parent[x]);
		}
		return x;
	}
	void merge(int x, int y) {
		int rootx = findhead(x);
		int rooty = findhead(y);
		if (rootx != rooty) {
			if (rank[rootx] < rank[rooty]) {
				swap(rootx, rooty);
			}
			parent[rooty] = rootx;
			if (rank[rootx] == rank[rooty]) rank[rootx] += 1;
		}

	}
	bool isSame(int x, int y) {
		return findhead(x) == findhead(y);
	}
};


int min1 = INT_MAX;
void process(vector<vector<int>>& saw, vector<vector<int>>& heights, int nowx, int nowy, int nownum, int dircetion) {
	int x = heights.size();
	int y = heights[0].size();
	if (nowx == x - 1 && nowy == y - 1) {
		saw[x - 1][y - 1] = 0;
		if (nownum > min1)return;
		if (dircetion == 1) {
			nownum = max(nownum, abs(heights[nowx][nowy] - heights[nowx - 1][nowy]));
		}
		else {
			nownum = max(nownum, abs(heights[nowx][nowy] - heights[nowx][nowy - 1]));
		}
		min1= nownum;
		return;
	}
	if (nowx != 0 || nowy != 0)
	{
		if (dircetion == 0) {
			nownum = max(nownum, abs(heights[nowx][nowy] - heights[nowx + 1][nowy]));
		}
		else if (dircetion == 1) {
			nownum = max(nownum, abs(heights[nowx][nowy] - heights[nowx - 1][nowy]));
		}
		else if (dircetion == 2) {
			nownum = max(nownum, abs(heights[nowx][nowy] - heights[nowx][nowy + 1]));
		}
		else {
			nownum = max(nownum, abs(heights[nowx][nowy] - heights[nowx][nowy - 1]));
		}
	}
	if (nownum >= min1) {
		return;
	}
	saw[0][0] = 1;
	if (nowx - 1 >= 0 && saw[nowx - 1][nowy] == 0) {
		saw[nowx - 1][nowy] = 1;
		process(saw, heights, nowx - 1, nowy, nownum, 0);
		saw[nowx - 1][nowy] = 0;
	}
	if (nowx + 1 < x && saw[nowx + 1][nowy] == 0) {
		saw[nowx + 1][nowy] = 1;
		process(saw, heights, nowx + 1, nowy, nownum, 1);
		saw[nowx + 1][nowy] = 0;
	}
	if (nowy - 1 >= 0 && saw[nowx][nowy - 1] == 0) {
		saw[nowx][nowy - 1] = 1;
		process(saw, heights, nowx, nowy - 1, nownum, 2);
		saw[nowx][nowy - 1] = 0;
	}
	if (nowy + 1 < y && saw[nowx][nowy + 1] == 0) {
		saw[nowx][nowy + 1] = 1;
		process(saw, heights, nowx, nowy + 1, nownum, 3);
		saw[nowx][nowy + 1] = 0;
	}
}

int minimumEffortPath(vector<vector<int>>& heights) {
	int x = heights.size();
	int y = heights[0].size();
	vector<vector<int>>ans(x, vector<int>(y));
	for (int i = 0; i < x; i++) {
		for (int j = 0; j < y; j++) {
			ans[i][j] = 0;
		}
	}
	process(ans, heights, 0, 0, 0, 0);
	return min1;
}






//
//vector<TreeNodem*> process(int start, int end)
//{
//	if (start > end)
//		return { nullptr };
//	vector<TreeNodem* >allTrees;
//
//	for (int i = start; i <= end; i++) {
//		vector<TreeNodem*>leftTrees = process(start, i - 1);
//		vector<TreeNodem*>rightTrees = process(i + 1, end);
//		for (auto& left : leftTrees) {
//			for (auto& right : rightTrees) {
//				TreeNodem* cutrTree = new TreeNodem(i);
//				cutrTree->left = left;
//				cutrTree->right = right;
//				allTrees.emplace_back(cutrTree);
//			}
//		}
//
//	}
//	return allTrees;
//}
//
//vector<TreeNodem*> generateTrees(int n) {
//	if (!n)return{};
//	return process(1, n);
//}



//int process1(int start, int end)
//{
//	if (start >= end)return 1;
//	int num = 0;
//	for (int i = start; i < end; i++)
//	{
//		int left = process1(start, i - 1);
//		int right = process1(i + 1, end);
//		num += left * right;
//	}
//	return num;
//
//}
//int numTrees(int n) {
//	return process1(1, n);
//}


int process(vector<int>& dp, vector<int>& dp1, int start, int end, int een, int flag)
{
	if (flag == 0 && dp[end] != 0)return dp[end];
	if (flag == 1 && dp1[start] != 0)return dp1[start];
	int num = 0;
	for (int i = start; i <= end; i++)
	{
		int left, right;
		dp[i] = process(dp, dp1, start, i - 1, een, 0);
		left = dp[i];

		dp1[i] = process(dp, dp1, i + 1, end, een, 1);
		right = dp1[i];
		num += left * right;
	}
	return num;

}
int numTrees(int n) {
	vector<int>dp(n + 1, 0);
	vector<int>dp1(n + 1, 0);
	dp[1] = 1;
	dp1[n] = 1;
	return process(dp, dp1, 1, n, n, 0);
}






bool isInterleave(string s1, string s2, string s3) {
	int n = s1.size();
	int m = s2.size();
	int l = s3.size();
	if (m + n != l) { return false; }
	vector<vector<bool>>dp(n + 1, vector<bool>(m + 1, false));
	for (int i = 1; i <= n; i++)
	{
		if (s1[i-1] != s3[i-1])break;
		dp[i][0] = true;
	}
	for (int i = 1; i <= m; i++)
	{
		if (s2[i-1] != s3[i-1])break;
		dp[0][i] = true;
	}
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= m; j++)
		{
			if (dp[i][j] == true)continue;
			if (dp[i - 1][j] == true || dp[i][j - 1] == true)
			{
				if (s1[i - 1] == s3[i + j - 1] || s2[j - 1] == s3[i + j - 1]) {
					dp[i][j] = true;
				}
			}
		}

	}
	return dp[n ][m ];
}

struct TreeNodem {
	int val;
	TreeNodem* left;
	TreeNodem* right;
	TreeNodem() : val(0), left(nullptr), right(nullptr) {}
	TreeNodem(int x) : val(x), left(nullptr), right(nullptr) {}
	TreeNodem(int x, TreeNodem* left, TreeNodem* right) : val(x), left(left), right(right) {}

};


void process(unordered_map<int, int>& umap,
	vector<int>& preorder, vector<int>& inorder,
	TreeNodem* root, int pb, int  ib, int ir)
{
	if (ib >= ir)return;
	int inorderindex = umap[root->val];
	if (inorderindex > ib)
	{
		TreeNodem* lroot = new TreeNodem(preorder[pb + 1]); root->left = lroot;
		process(umap, preorder, inorder, root->left, pb + 1, ib, inorderindex - 1);
	}
	if (inorderindex < ir)
	{
		int wei = inorderindex - ib + 1;
		TreeNodem* Rroot = new TreeNodem(preorder[pb + wei]);
		root->right = Rroot;
		process(umap, preorder, inorder, root->right, pb + wei, inorderindex + 1, ir);
	}
}
TreeNodem* buildTree(vector<int>& preorder, vector<int>& inorder) {
	TreeNodem* root = new TreeNodem(preorder[0]);
	int s = inorder.size();
	unordered_map<int, int>umap;
	for (int i = 0; i < s; i++)
	{
		umap[inorder[i]] = i;
	}
	process(umap, preorder, inorder, root, 0, 0, s - 1);
	return root;
}


void bst(TreeNodem** root, vector<int>& nums, int l, int R)
{
	if (l > R)return;
	int mid = (l + R + 1) >> 1;
	(*root)->val = nums[mid];
	if (l <= mid - 1)
	{
		TreeNodem* Nleft = new TreeNodem;
		(*root)->left = Nleft;
		bst(&Nleft, nums, l, mid - 1);
	}

	if (mid + 1 <= R)
	{
		TreeNodem* Nright = new TreeNodem;
		(*root)->right = Nright;
		bst(&Nright, nums, mid + 1, R);
	}
}
TreeNodem* sortedArrayToBST(vector<int>& nums) {
	TreeNodem* root = new TreeNodem;
	bst(&root, nums, 0, nums.size() - 1);
	return root;
}


void gettime()
{
	//time_t nowtime = time(0);
	//char buffer[30];
	//ctime_s(buffer, 30, &nowtime);
	//printf("%s" , buffer);

	time_t nowtime = time(0);
	struct tm p;
	localtime_s(&p, &nowtime);
	printf("%d/%d/%d %02d:%02d:%02d\n", 1900 + p.tm_year, 1 + p.tm_mon, p.tm_mday, p.tm_hour, p.tm_min, p.tm_sec);
	
}
void CreatTree(TreeNodem** Root)
{
	int ch;
	cin >> ch;
	if (ch != 0)
	{
		(*Root) = new TreeNodem;
		(*Root)->val = ch;
		CreatTree(&(*Root)->left);
		CreatTree(&(*Root)->right);

	}
	else
	{
		*Root = nullptr;
	}
}


int m = 0;
TreeNodem* DFS(TreeNodem* root)
{
	if (!root)return nullptr;
	TreeNodem* last = nullptr;
	last = DFS(root->left);
	TreeNodem* temp = root->right;
		if (root->left) {
			root->right = root->left;
		}
		if (last != nullptr)
		{
			if (last->right == nullptr)
			{
				last->right = temp;
			}
		}
		TreeNodem  * last2 = nullptr;
	last2 = DFS(temp);
	if (last2 != nullptr)
	last = last2;
	if (root->left)
		if (root->left->right == nullptr)
		{
			root->left->right = temp;
			m++;
		}
	if (!root->left && !temp) {
		root->left = nullptr;
		return root;
	}
	root->left = nullptr;
	return last;

}
void flatten(TreeNodem* root) {
	DFS(root);
}
void prem(TreeNodem* root)
{
	if (!root)return;
	cout << root->val;
	prem(root->left);
	prem(root->right);
}


bool isValid(string s) {
	stack<char>st;
	for (int i = 0; i < s.size(); i++)
	{
		if (s[i] == '(' || s[i] == '[' || s[i] == '{') {
			st.push(s[i]);
		}
		else
		{
			if (st.empty())return false;
			else
			{
				if (s[i] == ')' && st.top() != '(') { return false; }
				if (s[i] == ']' && st.top() != '[') { return false; }
				if (s[i] == '}' && st.top() != '{') { return false; }
				st.pop();
			}
		}
	}
	return s.empty();
}




int divide(int dividend, int divisor) {
	if (dividend==0)return 0;
	if (dividend == INT_MIN && divisor == -1)return INT_MAX;
	if (dividend == INT_MIN && divisor == 1)return INT_MIN;
	bool is = (dividend ^ divisor) < 0;
	dividend = abs(dividend);
	divisor = abs(divisor);
	int ans = 0;
	for (int i = 31; i >= 0; i--)
	{
		if (dividend >> i >= divisor)
		{
			ans += 1 << i;
			dividend -= divisor << i;
		}
	}
	return is ? -ans : ans;
}

vector<int> getRow(int rowIndex) {
	vector<int>v(rowIndex);
	v[0] = 1;
	int temp = 1;
	for (int i = 1; i < rowIndex; i++)
	{
		temp = 1;
		for (int j = 1; j <= i; j++)
		{
			if (j == i) { v[j] = 1; }
			else
			{
				int l = v[j];
				v[j] = v[j] + temp;
				temp = l;
			}

		}
	}
	return v;
}

int minimumTotal(vector<vector<int>>& triangle) {
	int size = triangle.size();
	vector<vector<int>>dp(size, vector<int>(size));
	for (int i = 1; i < size; i++)
	{
		for (int j = 0; j <= i; j++)
		{
			if (j == 0) {
				dp[i][j] = dp[i - 1][j] + triangle[i][j];
			}
			else
			{
				dp[i][j] = min(dp[i - 1][j], dp[i - 1][j - 1]) + triangle[i][j];
			}
		}
	}
	int ans = 1001;
	for (int i = 0; i < size; i++)
	{
		if (dp[size - 1][i] < ans)
		{
			ans = dp[size - 1][i];
		}
	}
	return ans;
}
int main()
{
	vector<vector<int>> train{ {2} ,{3,4},{6,5,7},{4,1,8,3} };
	cout<<minimumTotal(train);
}

