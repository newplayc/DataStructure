#include<iostream>
using namespace std;
#include<string>
#include<map>
#include<vector>
#include<algorithm>
int* getNext(string s)
{
	int* Next = new int[s.length()];
	unsigned int i = 0;
	int j = -1;
	Next[i] = j;
	while (i <s.length()- 1) {
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
	if (*Root == nullptr)return;
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



class Solution {
public:
	vector<vector<int>> fourSum(vector<int>& nums, int target) {
		vector<vector<int>>ans;
		int len = nums.size();
		sort(nums.begin(), nums.end());
		for (int i = 0; i < len - 3; i++)
		{
			if (i != 0 && nums[i] == nums[i - 1])continue;
			for (int j = i + 1; j < len - 2; j++)
			{
				if (nums[j] == nums[j - 1])continue;

				int tar = target - nums[i] - nums[j];
				int s = j + 1;
				int d = len - 1;
				while (s < d) {
					int numv = nums[s] + nums[d];
					if (numv > tar) {
						    d--;
					}
					else if (numv < tar) {
						  s++;
					}
					else {
						vector<int>v;
						v.push_back(nums[i]);
						v.push_back(nums[j]);
						v.push_back(nums[s]);
						v.push_back(nums[d]);
						ans.push_back(v);
						for (++s; s < d && nums[s] == nums[s - 1]; ++s);
						for (--d; s < d && nums[d] == nums[d + 1]; --d);
					}

				}

			}
		}
		return ans;
	}
};




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
//TreeNode* T = nullptr;
//InsertBstTree(&T, 6);
//InsertBstTree(&T, 9);
//InsertBstTree(&T, 2);
//InsertBstTree(&T, 4);
//InsertBstTree(&T, 1);
//InsertBstTree(&T, 5);
//preOrderNoWhile(T);


	int wei[7] = { 5,1,3,6,11,2,4 };
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

	Solution S;
	vector<int>nums{ 2,2,2,2,2 };
	vector<vector<int>>ans;
	ans = S.fourSum(nums, 0);
	for (vector<int> a : ans)
	{
		for (int c : a)
		{
			cout << c << " ";
		}
		cout << endl;
	}
}


