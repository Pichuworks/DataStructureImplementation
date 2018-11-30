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
	if(listnode->next == NULL) {
		cout << "这是一个空链表。" << endl;
		return;
	}
	
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

// 2017 #4 合并递减单链表*
bool mergeList2017() {
	ListNode list1 = setupList();
	ListNode list2 = setupList();
	// 输入时候先排个序，想不到吧.nef 
	listSortInc(list1);
	listSortInc(list2);
	ListNode pre = list1;
	ListNode cur = list1->next;
	ListNode tmp = NULL;
	ListNode cur2 = list2->next;
	list2->next = NULL;
	while(cur != NULL && cur2 != NULL) {
		if(cur2->value < cur->value) {
			if(cur2->value != pre->value) {
				cout << "[DEBUG] cur: " << cur->value << " cur2: " << cur2->value << ", merge" << endl;
				tmp = cur2;
				cur2 = cur2->next;
				pre->next = tmp;
				tmp->next = cur;
			}
			else {
				cout << "[DEBUG] cur: " << cur->value << " cur2: " << cur2->value << ", skip 1" << endl;
				pre = pre->next;
				cur = cur->next;
				cur2 = cur2->next;
			}
		}
		else {
			cout << "[DEBUG] cur: " << cur->value << " cur2: " << cur2->value << ", skip 2" << endl;
			pre = pre->next;
			cur = cur->next;
		}
	}
	if(cur == NULL && cur2 != NULL) {
		while(cur2 != NULL) {
			if(pre->value == cur2->value) {
				cout << "[DEBUG] pre: " << pre->value << " cur2: " << cur2->value << ", skip" << endl;
				cur2 = cur2->next;
			}
			else
				break;
		}
		if(cur2 != NULL)
			cout << "[DEBUG] pre: " << pre->value << " cur2: " << cur2->value << ", merge" << endl;
		pre->next = cur2;
	}
	displayList(list1);
	return true;
}

// 2017 #5 学生成绩调整*
void studentSort() {
	vector<int> student;
	int n;
	cout << "Student number?" << endl;
	cin >> n;
	cout << "Student #" << endl;
	for(int i=0; i<n; i++) {
		int tmp_score;
		cin >> tmp_score;
		student.push_back(tmp_score);	// 在尾部加入一个数据 
	}
	
	// 利用快排的思想 前后同时向中间扫描 然后交换
	int begin = 0;
	int end = n-1;
	while(begin < end) {
		while(begin < end && student[begin] >= 60) begin++;
		while(begin < end && student[end] < 60) end--;
		if(begin > end) break;
		int swap = student[begin];
		student[begin] = student[end];
		student[end] = swap;
		begin++;
		end--;
	}
	
	cout << "sort result" << endl;
	for(int i=0; i<n; i++) {
		cout << student[i] << " ";
	}
	cout << endl;
}

// 2016 #4 删除重复节点
void delNode() {
	ListNode head = setupList();
	ListNode listnode = head->next;
	while(listnode != NULL) {
		listNodeDelete(listnode, listnode->value);
		listnode = listnode->next; 
	}
	displayList(head);
}

// 2015 #4 链表简单选择排序*
void simpleSelSort() {
	ListNode head = setupList();
	ListNode node = head->next;
	while(node != NULL) {
		ListNode min = node;
		ListNode cur = node->next;
		while(cur != NULL) {
			if(min->value > cur->value)
				min = cur;
			cur = cur->next;
		}
		int tmp = node->value;
		node->value = min->value;
		min->value = tmp;
		node = node->next;
	}
	displayList(head);
}

// 2014 #4 [1 3 5 7 8 4 6 2]
void fuckEvenList() {
	ListNode listnode = setupList();
	ListNode even = NULL;
	initNode(even);
	ListNode cur = listnode->next;
	ListNode pre = listnode;
	int flag = 0;
	while(cur != NULL) {
		flag++;
		if(flag%2 == 1) {
			cur = cur->next;
			pre = pre->next;
			continue;
		}
		else {
			pre->next = cur->next;
			cur->next = even->next;
			even->next = cur;
			cur = pre->next;
			continue;
		}
	}
	pre->next = even->next;
	displayList(listnode);
}

// 2013 #4 求递增AB链表的交集 并排倒序 * 
void unionList() {
	ListNode listA = setupList();
	ListNode listB = setupList();
	listSortInc(listA);
	listSortInc(listB);
	ListNode cur = listA->next;
	ListNode pre = listA;
	while(cur != NULL) {
		// 只有listB中有此节点数据，而且listA没有别的节点有相同数据的才会保留 
		if(listFind(listB, cur->value) && !listFind(cur, cur->value)) {
			pre = pre->next;
			cur = cur->next;
		}
		else {	// 其他的全删了 
			ListNode tmp = cur;
			pre->next = cur->next;
			cur = cur->next;
			free(tmp);
		}
	}
	listSortDec(listA);
	displayList(listA);
}

int main() {
	/*
	// Optn Debug
	ListNode fuck = setupList();
	cout << "==========================" << endl;
	displayList(fuck);
	cout << "list length: " << listLength(fuck) << endl;
	listSortInc(fuck);
	displayList(fuck);
	cout << "list length: " << listLength(fuck) << endl;
	listSortDec(fuck);
	displayList(fuck);
	
	// ExamQstn 
	mergeList2017();
	studentSort();
	delNode();
	simpleSelSort();
	fuckEvenList();
	*/
	unionList();
	return 0;
}
