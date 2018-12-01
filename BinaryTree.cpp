#include<bits/stdc++.h>
#include <iostream>

#define maxn 100 

using namespace std;

// 孩子兄弟树
typedef struct CSNode {
	int data;
	CSNode *firstchild;
	CSNode *nextsibling;
} *CSTree;

// 膜拜王大师*2
CSTree setupCSTree(CSTree &head) {
	int a, b;
	CSTree child, brother;
	cout << "请输入 " << head->data << " 的孩子，-1表示为空" << endl;
	cin >> a;
	cout << "请输入 " << head->data << " 的兄弟，-1表示为空" << endl;
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
	cout << "请输入根节点" << endl;
	cin >> root;
	tree = (CSTree)malloc(sizeof(CSNode));
	tree->data = root;
	tree->firstchild = NULL;
	tree->nextsibling = NULL;
	setupCSTree(tree);
}

// 2014 #5 用孩子兄弟表示法构建二叉树，输出家谱中共有多少代以及最后一代人数和成员名 
int cstree_high = 1;	// 孩子兄弟树的高度 
int num = 0;
void DFS1(CSTree tree, int high) {
	if(tree == NULL)
		return;
	if(tree->firstchild != NULL) {
		cstree_high = max(cstree_high, high+1);	// 往下递归了一层
		DFS1(tree->firstchild, high+1); 
	}
	if(tree->nextsibling != NULL) {
		cstree_high = max(cstree_high, high);	// 高度不变
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
	cout << "家谱中共有 " << cstree_high << " 代" << endl;
	DFS2(tree, 1);
	cout << "最后一代人数有 " << num << endl;
}

// 2012 设树采用孩子兄弟链表结构进行存储，设计一个算法，求树的宽度（即具有结点数最多的那一层上的结点个数）。
int widthCSTree(CSTree tree) {
	// 层次遍历，找出最大宽度
	if(tree == NULL)
		 return 0;
	int width = 1;
	int width_tmp = 0;
	queue<CSTree> Q, Assist;		// Q队列存孩子 Assist队列存兄弟
	CSTree tmp;	//队列头
	Q.push(tree);	// 压进队列
	cout << "[debug] tree = " << tree->data << endl;
	while(!Q.empty()) {
		width_tmp = 0;
		int length = Q.size();
		width_tmp = length;
		cout << endl;
		cout << "[debug] length = " << length << endl;
		while(length--) {		// 所有兄弟节点入队 
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
		width_tmp += Assist.size();	// 该层的宽度
		cout << "[debug] A.size = " << Assist.size() << " , width_tmp = " << width_tmp << endl;
		while(!Assist.empty())
			Assist.pop();	// 清空辅助队列Assist
		width = max(width,width_tmp);
		cout << "[debug] width now = " << width << endl;
	}
	return width;
}

// 二叉树
 

int main() {
	CSTree tree;
	initCSTree(tree);
	homeTree(tree);
	// cout << "[debug] widthCSTree = " << widthCSTree(tree) << endl;
	return 0;
}
