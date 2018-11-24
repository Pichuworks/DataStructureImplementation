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
