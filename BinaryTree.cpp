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
		int length = Q.size();	// Q现在是上一层的长子 
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
		width_tmp += Assist.size();	// 该层的宽度:长子+长子的兄弟 
		cout << "[debug] A.size = " << Assist.size() << " , width_tmp = " << width_tmp << endl;
		while(!Assist.empty()) {
			tmp = Assist.front();
			if(tmp->firstchild != NULL)
				Q.push(tmp->firstchild);	// 压兄弟的长子进孩子队列 
			Assist.pop();	// 清空辅助队列Assist
		} 
		width = max(width,width_tmp);
		cout << "[debug] width now = " << width << endl;
	}
	return width;
}

// 二叉树
// 二叉树的节点值是int类型 -1表示该节点为空
typedef struct BinaryTree {
	int val;
	BinaryTree *left;
	BinaryTree *right;
} *Tree;

// 建树 
void setupTree(Tree &tree) {
	int ch;
	cin >> ch;
	if(ch == -1)
		tree = NULL;
	else {
		tree = (Tree)malloc(sizeof(BinaryTree));
		tree->val = ch;
		cout << "输入 " << ch << " 的左子节点" << endl;
		setupTree(tree->left);
		cout << "输入 " << ch << " 的右子节点" << endl;
		setupTree(tree->right);
	} 
}

// 递归建立平衡二叉树，根节点就是中间节点
// 它是一棵空树或它的左右两个子树的高度差的绝对值不超过1
// 并且左右两个子树都是一棵平衡二叉树 
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

// 给一个有序数组，建立成二叉排序树
// 二叉排序树或者是一棵空树，或者是具有下列性质的二叉树：
// （1）若左子树不空，则左子树上所有结点的值均小于它的根结点的值；
// （2）若右子树不空，则右子树上所有结点的值均大于它的根结点的值；
// （3）左、右子树也分别为二叉排序树；
// （4）没有键值相等的节点 
void setupBinSortTree(Tree &tree) {
	int n;
	cout << "请输入数组元素个数" << endl;
	cin >> n;
	cout << "请输入数组元素" << endl; 
	vector<int> array(n);
	for(int i=0; i<n; i++) {
		cin >> array[i];
	}
	sort(array.begin(), array.end());	// 有序数组 
	if(array.size() == 0) {
		tree = NULL;
		return;
	}
	tree = initBalanceTree(array, 0, array.size()-1);	// 递归建树 
}

// 删除一颗树
bool destroyTree(Tree &tree) {
	if(tree != NULL) {
		destroyTree(tree->left);
		destroyTree(tree->right);
		free(tree);
		tree = NULL;	// NullPointerException!
	}
	return true;
}

// 递归先序遍历 根左右 
void recurPre(Tree tree) {
	if(tree != NULL) {
		cout << tree->val << " ";
		recurPre(tree->left);
		recurPre(tree->right);
	} 
}

// 递归中序遍历 左根右 
void recurIn(Tree tree) {
	if(tree != NULL) {
		recurIn(tree->left);
		cout << tree->val << " ";
		recurIn(tree->right);
	} 
} 

// 递归后序遍历 左右根 
void recurPost(Tree tree) {
	if(tree != NULL) {
		recurPost(tree->left);
		recurPost(tree->right);
		cout << tree->val << " ";
	} 
}

// 递归求树的高度
int recurTreeHigh(Tree tree) {
	int high = 0;
	if(tree == NULL)
		high = 0;
	else
		high = max(recurTreeHigh(tree->left), recurTreeHigh(tree->right)) + 1;
	return high;
}

// 2013 #5 非递归求树的高度
/*
back()返回最后一个元素
empty()如果队列空则返回真
front()返回第一个元素
pop()删除第一个元素
push()在末尾加入一个元素
size()返回队列中元素的个数
pair<type,type> name;
*/ 
int treeHigh(Tree tree) {
	// 层次遍历，用队列存
	if(tree == NULL)
		return 0;
	queue< pair<Tree, int> > Q;	// 定义一个队列，队列元素为树的节点和它的高度
	Q.push(make_pair(tree, 1));		// 先放自己进去
	pair<Tree, int> tmp_tree;
	int high = 1;
	while(!Q.empty()) {
		tmp_tree = Q.front();
		if(tmp_tree.first->left != NULL) {
			Q.push(make_pair(tmp_tree.first->left, tmp_tree.second+1));	// 压左子树入队 
		}
		if(tmp_tree.first->right != NULL) {
			Q.push(make_pair(tmp_tree.first->right, tmp_tree.second+1));	// 压右子树入队 
		}
		high = max(high, tmp_tree.second);
		Q.pop();
	}
	return high;
}

// 2015 #5 输出树的最长路径
void longestPath(Tree tree) {
	// 递归大法好 直接暴力，通过treeHigh算最长子树，然后一路下去 
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

// 2016 #5 判断是否是完全二叉树 
bool isCompletedBinaryTree(Tree tree) {
	/*
		如果树为空，则直接返回错 
		如果树不为空：层序遍历二叉树 
		如果一个结点左右孩子都不为空，则pop该节点，将其左右孩子入队列； 
		如果遇到一个结点，左孩子为空，右孩子不为空，则该树一定不是完全二叉树； 
		如果遇到一个结点，左孩子不为空，右孩子为空；或者左右孩子都为空；
		则该节点之后的队列中的结点都为叶子节点；
		该树才是完全二叉树，否则就不是完全二叉树；
	*/
	if(tree == NULL)
		return false;
	queue<Tree> Q;
	Tree tmp;	// 保存队列头
	Q.push(tree);
	while(!Q.empty()) {
		tmp = Q.front();
		if(tmp->left != NULL && tmp->right != NULL) {	// 左右不为空
			Q.pop();
			Q.push(tmp->left);
			Q.push(tmp->right);
		}
		if(tmp->left == NULL && tmp->right != NULL) // 左空右不空，不是完全二叉树 
			return false;
		if((tmp->left != NULL && tmp->right == NULL) || (tmp->left == NULL && tmp->right == NULL)) { // 左不空右空 或者 左右全空 表示后面全是叶子结点，否则必不是完全二叉树
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

// 2018 #5 判断给定的两个元素和二叉树的关系
// 和层次遍历求最长路径一样，就是要记住这沙雕a, b的长度 
int twoElem(Tree tree) {
	int a, b;
	cout << "请输入给定的两个元素：" << endl;
	cin >> a;
	cin >> b;
	int high_a = 0, high_b = 0;	// 两个元素的层数
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

// 先序遍历，删除以x为根的子树 
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

// 2017 922 #7 对于每个元素值为x的结点，删去以它为根的子树
void deleteTreeX(Tree &tree) {
	int x;
	cout << "请输入要删除的节点X：" << endl;
	cin >> x;
	cout << "删除前先序遍历结果：" << endl;
	recurPre(tree);
	cout << endl;
	deleteX(tree, x);
	cout << "删除后先序遍历结果：" << endl;
	recurPre(tree);
	cout << endl;
}

// 2012 922 #8 在平衡二叉树中找到小于x且最接近x的节点返回指针,，要求用非递归算法实现且时间复杂度T(n)=O(k)。
Tree fuckBalancedBinaryTree(Tree tree) {
	// 算法思想：如果当前节点大于x，去左子树找，如果小于x，则需要到右子树去找
	// 如果右子树的值大于x说明当前节点就是最接近x且小于x，否当前节点跳到右子树 
	int x;
	cout << "请输入查找节点x:" << endl;
	cin >> x;
	if(tree == NULL)
		return NULL;
	Tree treenode = tree;
	while(treenode != NULL) {
		if(treenode->val >= x) {	// 当前节点>=x
			if(treenode->left != NULL)	
				treenode = treenode->left;	// 到左子树搜索 
			else
				break;	// 节点都大于X GG 
		}
		else if(treenode->val < x) {	// 当前节点<x 
			if(treenode->right != NULL) {
				if(treenode->right->val > x)	// 右子树节点>x 这个节点最接近 
					return treenode;
				else if(treenode->right->val < x)	// 这个节点不是最接近的 GG 
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
	// cout << "输入根节点" << endl;
	// setupTree(tree);
	setupBinSortTree(tree);
	// recurPre(tree);
	// cout << endl;
	// recurIn(tree);
	// cout << endl;
	// recurPost(tree);
	// cout << endl;
	// cout << "[递归]   树的高度是 " << recurTreeHigh(tree) << endl;
	// cout << "[非递归] 树的高度是 " << treeHigh(tree) << endl;
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
