#include <iostream>
#include <bits/stdc++.h> 
using namespace std;

// 线性链表的数据结构
typedef struct SqList {
	int value;
	SqList *next;
} *ListNode;

// 创建空表 
bool initNode(ListNode &listnode) {
	listnode = (ListNode) malloc(sizeof(SqList));
	if(!listnode) {
		cout << "分配失败" << endl;
		return false;
	}
	listnode->value = -1;			// ?
	listnode->next = NULL;
	return true;
}

// 给链表赋值 
ListNode setupList() {
	ListNode head;
	initNode(head);	// 创建一个空表
	ListNode listnode;
	listnode = head;		// 头部在这里 想不到吧！.nef 
	int value, count;
	cout << "请输入链表元素个数：" << endl;
	cin >> count;
	cout << "请输入链表元素：" << endl;
	for(int i=0; i<count; i++) {
		cin >> value;
		listnode->next = (ListNode) malloc(sizeof(SqList));
		listnode = listnode->next;
		listnode->value = value;
		listnode->next = NULL;
	}
	listnode->next = NULL;
	return head;
}

// 输出链表元素
void displayList(ListNode head) {
	ListNode listnode = head;
	while(listnode->next != NULL) {
		listnode = listnode->next;
		cout << listnode->value << " ";
	}
	cout << endl;
}

// 销毁链表
bool destroyList(ListNode &head) {
	ListNode listnode;
	while(head != NULL) {
		listnode = head;
		head = head->next;
		free(listnode);
	}
	head = NULL;
	return true;
}

// 清空链表
bool clearList(ListNode &head) {
	ListNode listnode, tmp = NULL;
	listnode = head->next;
	while(listnode != NULL) {
		tmp = listnode;
		listnode = listnode->next;
		free(tmp);
	}
	head->next = NULL;
	return 0;
}

// 判断链表为空
bool isEmptyList(ListNode head) {
	if(head != NULL && head->next == NULL)
		return true;
	else
		return false;
}

// 返回链表长度 
int listLength(ListNode listnode) {
	int length = 0;
	listnode = listnode->next;	// 头结点不算 
	while(listnode != NULL) {
		length++;
		listnode = listnode->next;
	}
	return length;
}

// 删除链表节点
void listNodeDelete(ListNode &head, int elem) {
	ListNode cur, pre;	// 当前节点、前驱节点
	cur = head->next;
	pre = head;
	while(cur != NULL) {
		if(cur->value == elem) {
			ListNode del = cur;
			pre->next = cur->next;
			cur = cur->next;
			free(del);
		}
		else {
			cur = cur->next;
			pre = pre->next;
		}
	} 
}

// 查找链表元素是否存在
bool listFind(ListNode head, int elem) {
	ListNode listnode = head->next;
	while(listnode != NULL) {
		if(listnode->value == elem)
			return true;
		else
			listnode = listnode->next;
	}
	return false;
}

// 链表插入排序，非递减版本 
bool listSortInc(ListNode &head) {
	// 1st 先判断是否是空表or只有一个元素 是则一定有序
	if(isEmptyList(head) || isEmptyList(head->next))
		return true;
	
	ListNode listnode = head->next->next;
	head->next->next = NULL;	//只保留首个数据节点，准备插入
	
	while(listnode != NULL) {
		ListNode tmp = listnode;		// 取出一个节点准备插入 
		listnode = listnode->next;
		
		ListNode pre = head;			// 准备遍历已排序列表 
		ListNode cur = head->next; 
		while(cur != NULL) {
			if(cur->value > tmp->value) { // 当前节点比待插入节点大 准备插入 pre->tmp->cur
				pre->next = tmp;
				tmp->next = cur;
				break;
			}
			else if(cur->next == NULL) {		// 到达尾部，插入尾部 
				cur->next = tmp;
				tmp->next = NULL;
				break; 
			}
			else {
				cur = cur->next;
				pre = pre->next;
			}
		}
	}
	return true;
}

// 链表插入排序，非递增版本 
bool listSortDec(ListNode &head) {
	// 1st 先判断是否是空表or只有一个元素 是则一定有序
	if(isEmptyList(head) || isEmptyList(head->next))
		return true;
	
	ListNode listnode = head->next->next;
	head->next->next = NULL;	//只保留首个数据节点，准备插入
	
	while(listnode != NULL) {
		ListNode tmp = listnode;		// 取出一个节点准备插入 
		listnode = listnode->next;
		
		ListNode pre = head;			// 准备遍历已排序列表 
		ListNode cur = head->next; 
		while(cur != NULL) {
			if(cur->value < tmp->value) { // 当前节点比待插入节点小 准备插入 pre->tmp->cur
				pre->next = tmp;
				tmp->next = cur;
				break;
			}
			else if(cur->next == NULL) {		// 到达尾部，插入尾部 
				cur->next = tmp;
				tmp->next = NULL;
				break; 
			}
			else {
				cur = cur->next;
				pre = pre->next;
			}
		}
	}
	return true;
}

// 2017 #4 


int main() {
	// Debug
	ListNode fuck = setupList();
	cout << "==========================" << endl;
	displayList(fuck);
	cout << "list length: " << listLength(fuck) << endl;
	bool fuck1 = listSortInc(fuck);
	displayList(fuck);
	cout << "list length: " << listLength(fuck) << endl;
	fuck1 = listSortDec(fuck);
	displayList(fuck);
	// Debug End
	return 0;
}
