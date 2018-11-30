#include <iostream>
#include <bits/stdc++.h> 
using namespace std;

// ������������ݽṹ
typedef struct SqList {
	int value;
	SqList *next;
} *ListNode;

// �����ձ� 
bool initNode(ListNode &listnode) {
	listnode = (ListNode) malloc(sizeof(SqList));
	if(!listnode) {
		cout << "����ʧ��" << endl;
		return false;
	}
	listnode->value = -1;			// ?
	listnode->next = NULL;
	return true;
}

// ������ֵ 
ListNode setupList() {
	ListNode head;
	initNode(head);	// ����һ���ձ�
	ListNode listnode;
	listnode = head;		// ͷ�������� �벻���ɣ�.nef 
	int value, count;
	cout << "����������Ԫ�ظ�����" << endl;
	cin >> count;
	cout << "����������Ԫ�أ�" << endl;
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

// �������Ԫ��
void displayList(ListNode head) {
	ListNode listnode = head;
	if(listnode->next == NULL) {
		cout << "����һ��������" << endl;
		return;
	}
	
	while(listnode->next != NULL) {
		listnode = listnode->next;
		cout << listnode->value << " ";
	}
	cout << endl;
}

// ��������
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

// �������
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

// �ж�����Ϊ��
bool isEmptyList(ListNode head) {
	if(head != NULL && head->next == NULL)
		return true;
	else
		return false;
}

// ���������� 
int listLength(ListNode listnode) {
	int length = 0;
	listnode = listnode->next;	// ͷ��㲻�� 
	while(listnode != NULL) {
		length++;
		listnode = listnode->next;
	}
	return length;
}

// ɾ������ڵ�
void listNodeDelete(ListNode &head, int elem) {
	ListNode cur, pre;	// ��ǰ�ڵ㡢ǰ���ڵ�
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

// ��������Ԫ���Ƿ����
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

// ����������򣬷ǵݼ��汾 
bool listSortInc(ListNode &head) {
	// 1st ���ж��Ƿ��ǿձ�orֻ��һ��Ԫ�� ����һ������
	if(isEmptyList(head) || isEmptyList(head->next))
		return true;
	
	ListNode listnode = head->next->next;
	head->next->next = NULL;	//ֻ�����׸����ݽڵ㣬׼������
	
	while(listnode != NULL) {
		ListNode tmp = listnode;		// ȡ��һ���ڵ�׼������ 
		listnode = listnode->next;
		
		ListNode pre = head;			// ׼�������������б� 
		ListNode cur = head->next; 
		while(cur != NULL) {
			if(cur->value > tmp->value) { // ��ǰ�ڵ�ȴ�����ڵ�� ׼������ pre->tmp->cur
				pre->next = tmp;
				tmp->next = cur;
				break;
			}
			else if(cur->next == NULL) {		// ����β��������β�� 
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

// ����������򣬷ǵ����汾 
bool listSortDec(ListNode &head) {
	// 1st ���ж��Ƿ��ǿձ�orֻ��һ��Ԫ�� ����һ������
	if(isEmptyList(head) || isEmptyList(head->next))
		return true;
	
	ListNode listnode = head->next->next;
	head->next->next = NULL;	//ֻ�����׸����ݽڵ㣬׼������
	
	while(listnode != NULL) {
		ListNode tmp = listnode;		// ȡ��һ���ڵ�׼������ 
		listnode = listnode->next;
		
		ListNode pre = head;			// ׼�������������б� 
		ListNode cur = head->next; 
		while(cur != NULL) {
			if(cur->value < tmp->value) { // ��ǰ�ڵ�ȴ�����ڵ�С ׼������ pre->tmp->cur
				pre->next = tmp;
				tmp->next = cur;
				break;
			}
			else if(cur->next == NULL) {		// ����β��������β�� 
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

// 2017 #4 �ϲ��ݼ�������*
bool mergeList2017() {
	ListNode list1 = setupList();
	ListNode list2 = setupList();
	// ����ʱ�����Ÿ����벻����.nef 
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

// 2017 #5 ѧ���ɼ�����*
void studentSort() {
	vector<int> student;
	int n;
	cout << "Student number?" << endl;
	cin >> n;
	cout << "Student #" << endl;
	for(int i=0; i<n; i++) {
		int tmp_score;
		cin >> tmp_score;
		student.push_back(tmp_score);	// ��β������һ������ 
	}
	
	// ���ÿ��ŵ�˼�� ǰ��ͬʱ���м�ɨ�� Ȼ�󽻻�
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

// 2016 #4 ɾ���ظ��ڵ�
void delNode() {
	ListNode head = setupList();
	ListNode listnode = head->next;
	while(listnode != NULL) {
		listNodeDelete(listnode, listnode->value);
		listnode = listnode->next; 
	}
	displayList(head);
}

// 2015 #4 �����ѡ������*
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

// 2013 #4 �����AB����Ľ��� ���ŵ��� * 
void unionList() {
	ListNode listA = setupList();
	ListNode listB = setupList();
	listSortInc(listA);
	listSortInc(listB);
	ListNode cur = listA->next;
	ListNode pre = listA;
	while(cur != NULL) {
		// ֻ��listB���д˽ڵ����ݣ�����listAû�б�Ľڵ�����ͬ���ݵĲŻᱣ�� 
		if(listFind(listB, cur->value) && !listFind(cur, cur->value)) {
			pre = pre->next;
			cur = cur->next;
		}
		else {	// ������ȫɾ�� 
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
