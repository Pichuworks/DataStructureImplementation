#include<bits/stdc++.h>
#include <iostream>

#define maxn 100 

using namespace std;

// �����ֵ���
typedef struct CSNode {
	int data;
	CSNode *firstchild;
	CSNode *nextsibling;
} *CSTree;

// Ĥ������ʦ*2
CSTree setupCSTree(CSTree &head) {
	int a, b;
	CSTree child, brother;
	cout << "������ " << head->data << " �ĺ��ӣ�-1��ʾΪ��" << endl;
	cin >> a;
	cout << "������ " << head->data << " ���ֵܣ�-1��ʾΪ��" << endl;
	cin >> b;
	if(a == -1)
		head->firstchild = NULL;
	else {
		child = (CSTree)malloc(sizeof(CSNode));
		child->data = a;
		head->firstchild = child;
		setupCSTree(head->firstchild);
	}
	if(b == -1)
		head->nextsibling = NULL;
	else {
		brother = (CSTree)malloc(sizeof(CSNode));
		brother->data = b;
		head->nextsibling = brother;
		setupCSTree(head->nextsibling);
	}
}

void initCSTree(CSTree &tree) {
	int root;
	cout << "��������ڵ�" << endl;
	cin >> root;
	tree = (CSTree)malloc(sizeof(CSNode));
	tree->data = root;
	tree->firstchild = NULL;
	tree->nextsibling = NULL;
	setupCSTree(tree);
}

// 2014 #5 �ú����ֵܱ�ʾ����������������������й��ж��ٴ��Լ����һ�������ͳ�Ա�� 
int cstree_high = 1;	// �����ֵ����ĸ߶� 
int num = 0;
void DFS1(CSTree tree, int high) {
	if(tree == NULL)
		return;
	if(tree->firstchild != NULL) {
		cstree_high = max(cstree_high, high+1);	// ���µݹ���һ��
		DFS1(tree->firstchild, high+1); 
	}
	if(tree->nextsibling != NULL) {
		cstree_high = max(cstree_high, high);	// �߶Ȳ���
		DFS1(tree->nextsibling, high); 
	}	
}

void DFS2(CSTree tree, int high) {
	if(tree == NULL)
		return;
	else if(high == cstree_high) {
		num++;
		cout << tree->data << " " << endl;
	}
	if(tree->firstchild != NULL)
		DFS2(tree->firstchild, high+1);
	if(tree->nextsibling != NULL)
		DFS2(tree->nextsibling, high);
}

void homeTree(CSTree tree) {
	DFS1(tree, 1);
	cout << "�����й��� " << cstree_high << " ��" << endl;
	DFS2(tree, 1);
	cout << "���һ�������� " << num << endl;
}

// 2012 �������ú����ֵ�����ṹ���д洢�����һ���㷨�������Ŀ�ȣ������н����������һ���ϵĽ���������
int widthCSTree(CSTree tree) {
	// ��α������ҳ������
	if(tree == NULL)
		 return 0;
	int width = 1;
	int width_tmp = 0;
	queue<CSTree> Q, Assist;		// Q���д溢�� Assist���д��ֵ�
	CSTree tmp;	//����ͷ
	Q.push(tree);	// ѹ������
	cout << "[debug] tree = " << tree->data << endl;
	while(!Q.empty()) {
		width_tmp = 0;
		int length = Q.size();	// Q��������һ��ĳ��� 
		width_tmp = length;
		cout << endl;
		cout << "[debug] length = " << length << endl;
		while(length--) {		// �����ֵܽڵ���� 
			tmp = Q.front();
			if(tmp->firstchild != NULL) {
				Q.push(tmp->firstchild);
				cout << "[debug Q.push] tmp = " << tmp->data << " , firstchild = " << tmp->firstchild->data << endl;
			}
			while(tmp->nextsibling != NULL) {
				Assist.push(tmp->nextsibling);
				cout << "[debug A.push] tmp = " << tmp->data << " , nextsibling = " << tmp->nextsibling->data << endl;
				tmp = tmp->nextsibling;
			}
			Q.pop();
		}
		width_tmp += Assist.size();	// �ò�Ŀ��:����+���ӵ��ֵ� 
		cout << "[debug] A.size = " << Assist.size() << " , width_tmp = " << width_tmp << endl;
		while(!Assist.empty()) {
			tmp = Assist.front();
			if(tmp->firstchild != NULL)
				Q.push(tmp->firstchild);	// ѹ�ֵܵĳ��ӽ����Ӷ��� 
			Assist.pop();	// ��ո�������Assist
		} 
		width = max(width,width_tmp);
		cout << "[debug] width now = " << width << endl;
	}
	return width;
}

// ������
// �������Ľڵ�ֵ��int���� -1��ʾ�ýڵ�Ϊ��
typedef struct BinaryTree {
	int val;
	BinaryTree *left;
	BinaryTree *right;
} *Tree;

// ���� 
void setupTree(Tree &tree) {
	int ch;
	cin >> ch;
	if(ch == -1)
		tree = NULL;
	else {
		tree = (Tree)malloc(sizeof(BinaryTree));
		tree->val = ch;
		cout << "���� " << ch << " �����ӽڵ�" << endl;
		setupTree(tree->left);
		cout << "���� " << ch << " �����ӽڵ�" << endl;
		setupTree(tree->right);
	} 
}

// �ݹ齨��ƽ������������ڵ�����м�ڵ�
// ����һ�ÿ����������������������ĸ߶Ȳ�ľ���ֵ������1
// ��������������������һ��ƽ������� 
Tree initBalanceTree(vector<int> &nums, int l, int r) {
	Tree root = (Tree) malloc(sizeof(BinaryTree));
	if(l <= r) {
		int mid = l + (r-l)/2;
		root->val = nums[mid];
		root->left = initBalanceTree(nums, l, mid-1);
		root->right = initBalanceTree(nums, mid+1, r);
	}
	else
		return NULL;
	return root;
}

// ��һ���������飬�����ɶ���������
// ����������������һ�ÿ����������Ǿ����������ʵĶ�������
// ��1�������������գ��������������н���ֵ��С�����ĸ�����ֵ��
// ��2�������������գ��������������н���ֵ���������ĸ�����ֵ��
// ��3����������Ҳ�ֱ�Ϊ������������
// ��4��û�м�ֵ��ȵĽڵ� 
void setupBinSortTree(Tree &tree) {
	int n;
	cout << "����������Ԫ�ظ���" << endl;
	cin >> n;
	cout << "����������Ԫ��" << endl; 
	vector<int> array(n);
	for(int i=0; i<n; i++) {
		cin >> array[i];
	}
	sort(array.begin(), array.end());	// �������� 
	if(array.size() == 0) {
		tree = NULL;
		return;
	}
	tree = initBalanceTree(array, 0, array.size()-1);	// �ݹ齨�� 
}

// ɾ��һ����
bool destroyTree(Tree &tree) {
	if(tree != NULL) {
		destroyTree(tree->left);
		destroyTree(tree->right);
		free(tree);
		tree = NULL;	// NullPointerException!
	}
	return true;
}

// �ݹ�������� ������ 
void recurPre(Tree tree) {
	if(tree != NULL) {
		cout << tree->val << " ";
		recurPre(tree->left);
		recurPre(tree->right);
	} 
}

// �ݹ�������� ����� 
void recurIn(Tree tree) {
	if(tree != NULL) {
		recurIn(tree->left);
		cout << tree->val << " ";
		recurIn(tree->right);
	} 
} 

// �ݹ������� ���Ҹ� 
void recurPost(Tree tree) {
	if(tree != NULL) {
		recurPost(tree->left);
		recurPost(tree->right);
		cout << tree->val << " ";
	} 
}

// �ݹ������ĸ߶�
int recurTreeHigh(Tree tree) {
	int high = 0;
	if(tree == NULL)
		high = 0;
	else
		high = max(recurTreeHigh(tree->left), recurTreeHigh(tree->right)) + 1;
	return high;
}

// 2013 #5 �ǵݹ������ĸ߶�
/*
back()�������һ��Ԫ��
empty()������п��򷵻���
front()���ص�һ��Ԫ��
pop()ɾ����һ��Ԫ��
push()��ĩβ����һ��Ԫ��
size()���ض�����Ԫ�صĸ���
pair<type,type> name;
*/ 
int treeHigh(Tree tree) {
	// ��α������ö��д�
	if(tree == NULL)
		return 0;
	queue< pair<Tree, int> > Q;	// ����һ�����У�����Ԫ��Ϊ���Ľڵ�����ĸ߶�
	Q.push(make_pair(tree, 1));		// �ȷ��Լ���ȥ
	pair<Tree, int> tmp_tree;
	int high = 1;
	while(!Q.empty()) {
		tmp_tree = Q.front();
		if(tmp_tree.first->left != NULL) {
			Q.push(make_pair(tmp_tree.first->left, tmp_tree.second+1));	// ѹ��������� 
		}
		if(tmp_tree.first->right != NULL) {
			Q.push(make_pair(tmp_tree.first->right, tmp_tree.second+1));	// ѹ��������� 
		}
		high = max(high, tmp_tree.second);
		Q.pop();
	}
	return high;
}

// 2015 #5 ��������·��
void longestPath(Tree tree) {
	// �ݹ�󷨺� ֱ�ӱ�����ͨ��treeHigh���������Ȼ��һ·��ȥ 
	if(tree != NULL) {
		cout << tree->val << " ";
		int left = treeHigh(tree->left);
		int right = treeHigh(tree->right);
		if(left > right)
			longestPath(tree->left);
		else
			longestPath(tree->right);
	} 
}

// 2016 #5 �ж��Ƿ�����ȫ������ 
bool isCompletedBinaryTree(Tree tree) {
	/*
		�����Ϊ�գ���ֱ�ӷ��ش� 
		�������Ϊ�գ�������������� 
		���һ��������Һ��Ӷ���Ϊ�գ���pop�ýڵ㣬�������Һ�������У� 
		�������һ����㣬����Ϊ�գ��Һ��Ӳ�Ϊ�գ������һ��������ȫ�������� 
		�������һ����㣬���Ӳ�Ϊ�գ��Һ���Ϊ�գ��������Һ��Ӷ�Ϊ�գ�
		��ýڵ�֮��Ķ����еĽ�㶼ΪҶ�ӽڵ㣻
		����������ȫ������������Ͳ�����ȫ��������
	*/
	if(tree == NULL)
		return false;
	queue<Tree> Q;
	Tree tmp;	// �������ͷ
	Q.push(tree);
	while(!Q.empty()) {
		tmp = Q.front();
		if(tmp->left != NULL && tmp->right != NULL) {	// ���Ҳ�Ϊ��
			Q.pop();
			Q.push(tmp->left);
			Q.push(tmp->right);
		}
		if(tmp->left == NULL && tmp->right != NULL) // ����Ҳ��գ�������ȫ������ 
			return false;
		if((tmp->left != NULL && tmp->right == NULL) || (tmp->left == NULL && tmp->right == NULL)) { // �󲻿��ҿ� ���� ����ȫ�� ��ʾ����ȫ��Ҷ�ӽ�㣬����ز�����ȫ������
			Q.pop();
			while(!Q.empty()) {
				tmp = Q.front();
				if(tmp->left != NULL || tmp->right != NULL)
					return false;
				Q.pop();
			}
			return true;
		}
	}
	return true;
}

// 2018 #5 �жϸ���������Ԫ�غͶ������Ĺ�ϵ
// �Ͳ�α������·��һ��������Ҫ��ס��ɳ��a, b�ĳ��� 
int twoElem(Tree tree) {
	int a, b;
	cout << "���������������Ԫ�أ�" << endl;
	cin >> a;
	cin >> b;
	int high_a = 0, high_b = 0;	// ����Ԫ�صĲ���
	if(tree == NULL)
		return -2;
	queue< pair<Tree, int> > Q;
	pair<Tree, int> tmp;
	Q.push(make_pair(tree, 1));
	while(!Q.empty()) {
		tmp = Q.front();
		if(tmp.first->val == a)
			high_a = tmp.second;
		if(tmp.first->val == b)
			high_b = tmp.second;
		if(tmp.first->left != NULL)
			Q.push(make_pair(tmp.first->left, tmp.second+1));
		if(tmp.first->right != NULL)
			Q.push(make_pair(tmp.first->right, tmp.second+1));
		Q.pop();
	}
	if(high_a == 0 && high_b == 0)
		return -2;
	if(high_a != 0 && high_b != 0)
		return abs(high_a - high_b);
	else
		return -1;
}

// ���������ɾ����xΪ�������� 
void deleteX(Tree &tree, int x) {
	if(tree != NULL) {
		if(tree->val == x) {
			destroyTree(tree);
			return;
		}
		else {
			deleteX(tree->left, x);
			deleteX(tree->right, x);
		}
	}
}

// 2017 922 #7 ����ÿ��Ԫ��ֵΪx�Ľ�㣬ɾȥ����Ϊ��������
void deleteTreeX(Tree &tree) {
	int x;
	cout << "������Ҫɾ���Ľڵ�X��" << endl;
	cin >> x;
	cout << "ɾ��ǰ������������" << endl;
	recurPre(tree);
	cout << endl;
	deleteX(tree, x);
	cout << "ɾ����������������" << endl;
	recurPre(tree);
	cout << endl;
}

// 2012 922 #8 ��ƽ����������ҵ�С��x����ӽ�x�Ľڵ㷵��ָ��,��Ҫ���÷ǵݹ��㷨ʵ����ʱ�临�Ӷ�T(n)=O(k)��
Tree fuckBalancedBinaryTree(Tree tree) {
	// �㷨˼�룺�����ǰ�ڵ����x��ȥ�������ң����С��x������Ҫ��������ȥ��
	// �����������ֵ����x˵����ǰ�ڵ������ӽ�x��С��x����ǰ�ڵ����������� 
	int x;
	cout << "��������ҽڵ�x:" << endl;
	cin >> x;
	if(tree == NULL)
		return NULL;
	Tree treenode = tree;
	while(treenode != NULL) {
		if(treenode->val >= x) {	// ��ǰ�ڵ�>=x
			if(treenode->left != NULL)	
				treenode = treenode->left;	// ������������ 
			else
				break;	// �ڵ㶼����X GG 
		}
		else if(treenode->val < x) {	// ��ǰ�ڵ�<x 
			if(treenode->right != NULL) {
				if(treenode->right->val > x)	// �������ڵ�>x ����ڵ���ӽ� 
					return treenode;
				else if(treenode->right->val < x)	// ����ڵ㲻����ӽ��� GG 
					treenode = treenode->right;
			}
		}
	}
	return NULL;
}

int main() {
	/*
	CSTree tree;
	initCSTree(tree);
	// homeTree(tree);
	cout << "[debug] widthCSTree = " << widthCSTree(tree) << endl;
	*/
	
	Tree tree = NULL;
	// cout << "������ڵ�" << endl;
	// setupTree(tree);
	setupBinSortTree(tree);
	// recurPre(tree);
	// cout << endl;
	// recurIn(tree);
	// cout << endl;
	// recurPost(tree);
	// cout << endl;
	// cout << "[�ݹ�]   ���ĸ߶��� " << recurTreeHigh(tree) << endl;
	// cout << "[�ǵݹ�] ���ĸ߶��� " << treeHigh(tree) << endl;
	// longestPath(tree);
	// cout << endl;
	// cout << isCompletedBinaryTree(tree) << endl;
	// cout << twoElem(tree) << endl;
	// deleteTreeX(tree);
	Tree fucktree;
	fucktree = fuckBalancedBinaryTree(tree);
	recurPre(fucktree);
	return 0;
}
