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
		int length = Q.size();
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
		width_tmp += Assist.size();	// �ò�Ŀ��
		cout << "[debug] A.size = " << Assist.size() << " , width_tmp = " << width_tmp << endl;
		while(!Assist.empty())
			Assist.pop();	// ��ո�������Assist
		width = max(width,width_tmp);
		cout << "[debug] width now = " << width << endl;
	}
	return width;
}

// ������
 

int main() {
	CSTree tree;
	initCSTree(tree);
	homeTree(tree);
	// cout << "[debug] widthCSTree = " << widthCSTree(tree) << endl;
	return 0;
}
