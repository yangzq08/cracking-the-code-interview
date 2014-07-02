//
//  Header.h
//  BTree
//
//  Created by yangzhiqi on 14-6-16.
//  Copyright (c) 2014年 yangzhiqi. All rights reserved.
//

#ifndef BTree_Header_h
#define BTree_Header_h

#include "math.h"

using namespace std;

typedef struct node
{
    int data;
    node *lchild;
    node *rchild;
    node *parent; //添加parent方便向上查找
    node *next; //二叉树队列、栈
    
    int tag = 0; //后序遍历的标志，0为左标志，1为右标志
    
    
}node;

class linklistForBSTree
{
    friend class BSTree;
private:
    node *head;
public:
    linklistForBSTree();
    void printLinklist();
    bool isEmpty();
    int linkLength();
    bool insertList(node *t); //插入元素到第i个位置
};

linklistForBSTree::linklistForBSTree()
{
    head = NULL;
}

void linklistForBSTree::printLinklist()
{
    node *p = head;
    while(p)
    {
        cout << p->data << " ";
        p = p->next;
    }
    cout << endl;
}

bool linklistForBSTree::isEmpty()
{
    return head == NULL;
}

int linklistForBSTree::linkLength()
{
    int len = 0;
    node *p = head;
    while(p)
    {
        len = len + 1;
        p = p->next;
    }
    return len;
}

bool linklistForBSTree::insertList(node *t)
{
    //这里就直接实现插入到链表尾就好了。
    node *p = head;
    
    node *q = new node();
    /*
    q->data = t->data;
    q->next = NULL;
    //左右孩子的信息也需要存储
    q->lchild = t->lchild;
    q->rchild = t->rchild;
    q->parent = t->parent;
     */
    q = t;
    q->next = NULL;
    
    //如果是空链表
    if(p == NULL)
    {
        head = q;
        return true;
    }
    //不为空链表
    while(p->next)
    {
        p = p->next;
    }
    p->next = q;
    q->next = NULL;
    return true;
}

class stackForBTree
{
private:
    node *top;
public:
    stackForBTree();
    //~stackForBTree();
    void printStack();
    bool isEmpty();
    void push(node *t);
    node* pop();
    
    void testStackForBTree();
};

stackForBTree::stackForBTree()
{
    top = NULL;
}
/*
stackForBTree::~stackForBTree()
{
    cout << "stackForBTree destructor called" << endl;
}
*/
void stackForBTree::printStack()
{
    node *temp;
    temp = top;
    cout << "begin print stackForBTree elements" << endl;
    while(temp)
    {
        cout << temp->data << " ";
        temp = temp->next;
    }
    cout << endl;
}

bool stackForBTree::isEmpty()
{
    return top==NULL;
}

void stackForBTree::push(node *t)
{
    //cout << "pushing element " << t->data << " to stack" << endl;
    
    /*
     用这种方法，如果不加上top->next = NULL，在第二次test中先序遍历会出现420531-420531一直循环(正确结果是420531就结束了)
     奇怪的是，如果第一次test不跑层序遍历就成功。这说明层序遍历时遗留了next信息，导致这里next没有置NULL而直接使用遗留信息
     */
    /*
    if(isEmpty())
    {
        top = t;
        top->next = NULL;
    }
    else
    {
        node *newStackNode = new node();
        newStackNode = t;
        newStackNode->next = top;
        top = newStackNode;
    }
    */
    
    
    node *newStackNode = new node();
    newStackNode = t;
    newStackNode->next = top;
    top = newStackNode;

}

node* stackForBTree::pop()
{
    if(isEmpty())
    {
        cout << "empty stack" << endl;
        return NULL;
    }
    else
    {
        node *newStackNode = new node();
        newStackNode = top;
        top = top->next;
        //cout << "poping element " << newStackNode->data << " out of stack" << endl;
        return newStackNode;
    }
}

void stackForBTree::testStackForBTree()
{
    int a[] = {1,2,3,4,5,6};
    cout << "is the stack empty(1 yes, 0 no): " << isEmpty() << endl;
    
    int i;
    int len = sizeof(a)/sizeof(a[0]);
    node *stackNode = new node[len];
    for(i=0;i<len;i++)
    {
        stackNode[i].data = a[i];
        push(&stackNode[i]);
    }
    
    printStack();
    
    cout << "after poping element" << endl;
    pop();
    printStack();
}

class queueForBTree
{
private:
    node *front;
    node *rear;
public:
    queueForBTree();
    //~queueForBTree();
    void printQueue();
    bool isEmpty();
    void enQueue(node *t);
    node *deQueue();
    //friend void visit(node *t);
    
    void testQueueForBTree();
};

queueForBTree::queueForBTree()
{
    front = NULL;
    rear = NULL;
}
/*
queueForBTree::~queueForBTree()
{
    cout << "queueForBTree destructor called" << endl;
}
*/
void queueForBTree::printQueue()
{
    cout << "start printing queue element" << endl;
    
    node *p;
    p = front;
    if(isEmpty())
    {
        cout << "this is an empty queue" << endl;
        return;
    }
    
    while(p)
    {
        cout << p->data << " ";
        p = p->next;
    }
    
    cout << endl;
}

bool queueForBTree::isEmpty()
{
    if(front && rear) return false;
    else return true;
}

void queueForBTree::enQueue(node *t)
{
    cout << "start enqueue element " << t->data << " into rear" << endl;
    node *newNode = new node();
    newNode = t;
    //newmyNode->data = e;
    newNode->next = NULL; //入队即为队尾元素，next当置为NULL
    //空队列
    if(isEmpty())
    {
        front = newNode;
        rear = newNode;
        return;
        //delete newmyNode;
    }
    rear->next = newNode;
    rear = newNode;
}

node *queueForBTree::deQueue()
{
    if(isEmpty())
    {
        cout << "this is an empty queue" << endl;
        return NULL;
    }
    
    node *p;
    p = front;
    
    int temp = front->data;
    cout << "dequeue element " << temp << " out of queue" << endl;
    
    //只有一个元素
    if(rear == front)
    {
        front = NULL;
        rear = NULL;
        return p;
    }
    
    front = front->next;
    
    return p;
}

void queueForBTree::testQueueForBTree()
{
    cout << "is this queue for BTree empty?(1 yes, 0 no) " << isEmpty() << endl;
    
    node *arr = new node[5];
    int i=0;
    for(i=0;i<5;i++)
    {
        arr[i].data = i;
        enQueue(&arr[i]);
    }
    printQueue();
    
    node *out = deQueue();
    cout << "dequeue element is " << out->data << endl;
    
    printQueue();
    
}

/*--------------------------------------------------------------------------------------------------------
 
 --------------------------------------------------------------------------------------------------------
 
 --------------------------------------------------------------------------------------------------------
 
 --------------------------------------------------------------------------------------------------------
 
 --------------------------------------------------------------------------------------------------------
 
 ---------------------------------------------------------------------------------------------------------
 */

class BTree {
    friend class BSTree;
private:
    node *root;
public:
    BTree();
    //~BTree();
    void initBTree(); //构造空二叉树
    void destroyBTree(); //销毁二叉树
    void createBTree(char definition); //根据definition给出的二叉树定义构造二叉树
    void clearBTree(); //清空树
    bool isEmpty(); //判断是否为空树
    int getLength(node *t); //当前结点形成的子树的结点数目，root的话就是所有结点数目
    int getDepth2(); //返回完全二叉树的深度
    int getDepth(node *t); //递归求解深度
    //node *getRoot(); //返回二叉树的根结点
    void assign(node *t, int value); //给结点t赋值value
    node *getParent(node *child); //返回双亲结点，如果是root，返回空
    node *leftChild(node *parent);//返回左孩子结点
    node *rightChild(node *parent); //返回右孩子结点
    void insertChild(node *p, int LR, BTree &subtree);
    /*
     subtree为待插入的的子树，且其右子树为空
     LR=0，表示插入p的左子树，LR=1表示插入p的右子树
     p为待插入的结点
     插入后，原结点p的左/右子树称为subtree的右子树
     */
    void deleteChild(node *p, int LR); //根据LR的值判断到底删除p的左子树(LR=0)还是右子树(LR=1)
    //各种遍历的递归recursion版本
    void preOrderTraverse(node *t, void (*visit)(node *t)); //先序遍历,必须使用node *t，因为visit函数访问不到
    void inOrderTraverse(node *t, void (*visit)(node *t)); //中序遍历
    void postOrderTraverse(node *t, void (*visit)(node *t)); //后序遍历
    //各种遍历的非递归版本
    void preOrderTraverNoRecursion(node *t, void (*visit)(node *));
    void inOrderTraverNoRecursion(node *t, void (*visit)(node *));
    void postOrderTraverNoRecursion(node *t, void (*visit)(node *));
    
    void levelOrderTraverse(node *t, void (*visit)(node *t)); //层序遍历，借助队列
    friend void visit(node *t);
    BTree nodeCreateBTree(node *t);//一个结点形成一个树
    
    void insertBSTree(node *&t, int &elem); //实现BSTree的插入功能
    
    void getLeafDepth(node *t, int d); //得到叶子结点的深度
    bool isBalance(node *t); //判断树的当前结点是否平衡，平衡的定义：任意两个叶子节点的高度差不会超过1, t=root即为整数的平衡度
    
    bool checkBalance(node *t); //判断树是否为平衡二叉树
    void minHeightBTree(node *&t, int *a, int start, int end); //给定增序数组，实现插入二叉树最低高度，当前结点t处插入item
    
    node* findFirstCommonAncestor(node *p, node *q); //寻找两个结点的第一个共同祖先，不使用额外的结点存储
    bool father(node *parent, node *child); //判断parent是否为child的祖先，同一结点也算
    
    bool subtree(BTree *big, BTree *small); //判断small是不是big的subtree，big的结点数目为几百万量级，small为几百量级
    bool compare(node *p, node *q); //比较当前结点及以下是否匹配
    
    void printAllPathSumToGivenValue(int &item); //打印所有路径，data相加值为给定的value，不一定从root开始。
    void findPath(node *t, int &item); //当前结点一路向上是否有值
    void findPathWithoutParent(node *t, int &item, int *a, int level); //没有parent指针的情况下如何实现
    
    void testBTree();
};

BTree::BTree()
{
    root = NULL;
}
/*
BTree::~BTree()
{
    cout << "destructor called" << endl;
}
*/
void BTree::initBTree()
{
    root = NULL;
}

void BTree::destroyBTree()
{
    cout << "destroy btree" << endl;
    if(isEmpty())
    {
        cout << "already empty tree" << endl;
    }
    else
    {
        root = NULL;
    }
}

void BTree::createBTree(char definition)
{
    return;
}

void BTree::clearBTree()
{
    cout << "clear btree" << endl;
}

bool BTree::isEmpty()
{
    return root == NULL;
}

int BTree::getLength(node *t)
{
    if(t == NULL)
    {
        return 0;
    }
    else
    {
        return getLength(t->lchild) + getLength(t->rchild) + 1;
    }
}

int BTree::getDepth2()
{
    int length = getLength(root);
    return (int)log2(length+1) + 1;
}

int BTree::getDepth(node *t)
{
    int depth = 0;
    if(!t) //t为空
    {
        depth = 0;
        return depth;
    }
    if((!t->lchild) & (!t->rchild))
    {
        depth = 1;
    }
    else
    {
        if(getDepth(t->lchild) > getDepth(t->rchild))
        {
            depth = getDepth(t->lchild) + 1;
        }
        else
        {
            depth = getDepth(t->rchild) + 1;
        }
    }
    return depth;
}

void BTree::assign(node *t, int value)
{
    t->data = value;
}

//node * BTree::getParent(node *child); //返回双亲结点，如果是root，返回空
node* BTree::getParent(node *child)
{
    if(child == root)
    {
        return NULL; //是root
    }
    else
    {
        return child->parent;
    }
}
node* BTree::leftChild(node *parent)//返回左孩子结点
{
    return parent->lchild;
}

node* BTree::rightChild(node *parent) //返回右孩子结点
{
    return parent->rchild;
}
void BTree::insertChild(node *p, int LR, BTree &subtree)
{
    /*
     subtree为待插入的的子树，且其右子树为空
     LR=0，表示插入p的左子树，LR=1表示插入p的右子树
     p为待插入的结点
     插入后，原结点p的左/右子树称为subtree的右子树
     */
    node *temp = subtree.root->rchild;
    if(temp) //右子树如果不为空
    {
        cout << "subtree's right sub tree is not NULL, fail to insert" << endl;
        return;
    }
    
    node *newChild;
    if(LR == 0)
    {
        if(p->lchild)
        {
            newChild = p->lchild;
        
            subtree.root->rchild = newChild;
            newChild->parent = subtree.root;
        
            p->lchild = subtree.root;
            subtree.root->parent = p;
        }
        else
        {
            p->lchild = subtree.root;
            subtree.root->parent = p;
        }
    }
    else
    {
        if(p->rchild)
        {
            newChild = p->rchild;
        
            subtree.root->rchild = newChild;
            newChild->parent = subtree.root;
        
            p->rchild = subtree.root;
            subtree.root->parent = p;
        }
        else
        {
            p->rchild = subtree.root;
            subtree.root->parent = p;
        }
    }
    
}

void BTree::deleteChild(node *p, int LR)
{
    //根据LR的值判断到底删除p的左子树(LR=0)还是右子树(LR=1)
    if(LR == 0)
    {
        node *temp = p->lchild;
        delete []temp;
        p->lchild = NULL;
    }
    else
    {
        node *temp = p->rchild;
        delete []temp;
        p->rchild = NULL;
    }
}

void visit(node *t)
{
    cout << " " << t->data << " ";
}

void BTree::preOrderTraverse(node *t, void (*visit)(node *t))
{
    if(t)
    {
        visit(t);
        preOrderTraverse(t->lchild, visit);
        preOrderTraverse(t->rchild, visit);
    }
}

void BTree::preOrderTraverNoRecursion(node *t, void (*visit)(node *))
{
    /*
     1）root为当前结点；
     2）推当前结点rchild入栈，访问当前结点
     3）当前结点左孩子lchild不为空则取左孩子当前结点，重复第二步
     4）如果左孩子为空，判断
        - 栈为空，说明遍历结束
        - 栈不为空，pop栈顶元素，重复第二步
     */
    
    node *p;
    p = t;
    
    stackForBTree s;
    
    //int flag = 0;
    
    while(p)
    {
        if(p->rchild) s.push(p->rchild);
        visit(p);
        //cout << endl;
        if(p->lchild)
        {
            p = p->lchild;
        }
        else
        {
            if(s.isEmpty())
            {
                p = NULL;
                //flag = 1;
                //cout << "here stack is empty, flag = " << flag << endl;
            }
            else
            {
                p = s.pop();
            }
        }
    }
    //cout << "flag value is " << flag << endl;
    cout << endl;
}

void BTree::inOrderTraverse(node *t, void (*visit)(node *))
{
    if(t)
    {
        inOrderTraverse(t->lchild, visit);
        visit(t);
        inOrderTraverse(t->rchild, visit);
    }
}

void BTree::inOrderTraverNoRecursion(node *t, void (*visit)(node *))
{
    /*
     四个步骤：
     1）root为当前结点
     2）当前结点及之后的lchild左路径结点一路进栈
     3）pop栈顶并访问，取栈顶的rchild为当前结点
     4）回到第二步，直到当前结点为空，栈为空，遍历完成
     */
    
    int flag = 1;
    
    node *p;
    p = t;
    stackForBTree ss;
    
    //cout << "this is root data: " << p->data << endl;
    
    while(flag)
    {
        while(p)
        {
            ss.push(p);
            p = p->lchild;
        }
        if(ss.isEmpty())
        {
            flag = 0;
        }
        else
        {
            p = ss.pop();
            visit(p);
            p = p->rchild;
        }
    }
    
}

void BTree::postOrderTraverse(node *t, void (*visit)(node *))
{
    if(t)
    {
        postOrderTraverse(t->lchild, visit);
        postOrderTraverse(t->rchild, visit);
        visit(t);
    }
}

void BTree::postOrderTraverNoRecursion(node *t, void (*visit)(node *))
{
    /*
     后序遍历的困难在于需要知道当前结点的右子树是否已经遍历。
     若未访问右子树，应先访问右子树；
     若已访问右子树，则访问结点本身
     
     四个步骤：
     1）root为当前结点
     2）将当前结点及左路径上的结点一路进栈
     3）pop栈顶结点，
        - 如果结点是左标志，结点入栈，改为右标志，结点变为当前结点的rchild
        - 如果结点是右标志，访问该结点，并pop出栈顶元素为结点
     4）返回第二步，直至栈空，说明遍历完成。
     */
    
    node *p;
    p = t;
    
    stackForBTree s;
    //int flag = 1;
    
    //cout << "root tag is: " << p->tag << endl;
    
    do
    {
        while(p)
        {
            p->tag = 0;
            
            s.push(p);
            p = p->lchild;
        }
        int flag2 = 1;
        while(flag2 && (!s.isEmpty()))
        {
            p = s.pop();
            if(p->tag == 0) //说明右子树还没有访问过
            {
                p->tag = 1;
                s.push(p);
                //delete p;
                p = p->rchild;
                flag2 = 0;
            }
            else
            {
                visit(p);
                //p = s.pop();
            }
        }
        /*
        cout << " XX-----------XX" << endl;
        if(!p) cout << "this loop p is null" << endl;
        else cout << "this loop p data is: " << p->data << endl;
        if(s.isEmpty()) cout << "this loop stack is empty" << endl;
         */
    }while(!s.isEmpty());
    // ?????????????????????????????????????????
    //while(p || !s.isEmpty()); //正常打印之后又会无限循环，p走完一遍又存着root结点
    // ?????????????????????????????????????????
    //cout << "end of no recursion" << endl;
}

void BTree::levelOrderTraverse(node *t, void (*visit)(node *))
{
    queueForBTree q;
    node *p = t;
    q.enQueue(p);
    cout << "begin print in lever order " << endl;
    while(!q.isEmpty())
    {
        p = q.deQueue();
        visit(p);
        if(p->lchild)
        {
            q.enQueue(p->lchild);
        }
        if(p->rchild)
        {
            q.enQueue(p->rchild);
        }
        
    }
    cout << endl;
}

BTree BTree::nodeCreateBTree(node *t)
{
    BTree tre;
    tre.root = t;
    
    return tre;
}

void BTree::insertBSTree(node *&t, int &item)
{
    if(!t)
    {
        node *p = new node;
        p->data = item;
        p->lchild = NULL;
        p->rchild = NULL;
        t = p;
    }
    else if(t->data > item)
    {
        //cout << "insert to lchild" << endl;
        insertBSTree(t->lchild, item);
    }
    else
    {
        //cout << "insert to rchild" << endl;
        insertBSTree(t->rchild, item);
    }
    
}

int num = 0, dep[100];
void BTree::getLeafDepth(node *t, int d)
{
    if(t == NULL) return;
    
    getLeafDepth(t->lchild, d+1);
    
    if((t->lchild == NULL) && (t->rchild == NULL))
    {
        dep[num] = d;
        num++;
    }
    
    getLeafDepth(t->rchild, d+1);
}

bool BTree::isBalance(node *t)
{
    //空树
    if(t == NULL) return true;
    
    int max, min;
    int i;
    
    getLeafDepth(root, 0);
    
    max = dep[0];
    min = dep[0];
    for(i=0;i<num;i++)
    {
        if(dep[i]>max) max = dep[i];
        if(dep[i]<min) min = dep[i];
    }
    if(max-min > 1)
        return false;
    else
        return false;
}

bool BTree::checkBalance(node *t)
{
    //从root还是比较左右孩子的深度
    node *p = t;
    if(p == NULL)
        return true;
    
    int left_depth = getDepth(p->lchild);
    int right_depth = getDepth(p->rchild);
    if((left_depth-right_depth > 1) || (right_depth-left_depth > 1))
    {
        cout << "find unbalanced node, data is: " << p->data << endl;
        return false;
    }
    else
    {
        return checkBalance(p->lchild) && checkBalance(p->rchild);
    }
    
}

void BTree::minHeightBTree(node *&t, int *a, int start, int end)
{
    /*
     为了保证minimal height，必须对数组进行处理。
     方法就是不断的递归取数组的中间值（因为已经是增序），小于的为左子树，大于的为右子树
     有点类似排序里面的划分，或者是二分操作。
     
     本质上其实类似于二叉搜索树，比根大的放右边，比根小的放左边，关键是元素选择使用二分操作
     
     验证方法：1）层序遍历，判断入队顺序；2）中序遍历应该为有序数组（就是原数组）
     */
    
    /*
    for(int i=start;i<=end;i++)
    {
        cout << a[i] << " ";
    }
    */
    int mid = (start + end) / 2;
    cout << "mid value is " << mid+1 << endl; //这里可以看到是如何二分选择元素值的。
    
    node *p = new node();
    p->data = a[mid];
    p->lchild = NULL;
    p->rchild = NULL;
    
    t = p;
    
    if(start <= mid-1)
        minHeightBTree(t->lchild, a, start, mid-1);
    if(mid+1 <= end)
        minHeightBTree(t->rchild, a, mid+1, end);
    
}

bool BTree::father(node *parent, node *child)
{
    if(parent == NULL || child == NULL) return false;
    if(parent == child) return true;
    else
    {
        return father(parent->lchild, child) || father(parent->rchild, child);
    }
}

node* BTree::findFirstCommonAncestor(node *p, node *q)
{
    /*
     //想太简单，单纯的以为两个结点在同一层
    if(p->parent == q->parent)
    {
        cout << "find first common ancestor" << endl;
        return p->parent;
    }
    else
    {
        //return findFirstCommonAncestor(p->parent, q->parent);
        
    }
     */
    if(p == NULL || q == NULL)
    {
        cout << "given node is null" << endl;
        return NULL;
    }
    node *ancestor = root;
    while(ancestor)
    {
        bool b1,b2;
        b1 = father(ancestor->lchild,p);
        b2 = father(ancestor->lchild,q);
        if(b1 && b2)
        {
            //还可以继续往下找
            ancestor = ancestor->lchild;
        }
        else
        {
            b1 = father(ancestor->rchild,p);
            b2 = father(ancestor->rchild,q);
            if(b1 && b2)
            {
                ancestor = ancestor->rchild;
            }
            else
            {
                cout << "find first common ancestor, value is: " << ancestor->data << endl;
                return ancestor;
            }
        }
    }
    return root;
}

bool BTree::compare(node *p, node *q)
{
    if(q == NULL) return true;
    if(p == NULL) return false;
    
    if(p->data == q->data)
    {
        bool b1 = compare(p->lchild,q->lchild);
        bool b2 = compare(p->rchild,q->rchild);
        return b1 && b2;
    }
    else
    {
        return false;
    }
}

bool BTree::subtree(BTree *big, BTree *small)
{
    /*
     big的结点数为百万量级，small的结点数为百量级
     如何判断small是否为big的子树
     
     暴力法：
     先在big里找到small的根结点，然后匹配左右子树
     注意可能有多个结点与small值相同
     */
    
    bool result;
    result = compare(big->root,small->root);
    if(result)
    {
        return true;
    }
    else
    {
        bool b1 = compare(big->root->lchild, small->root);
        bool b2 = compare(big->root->rchild, small->root);
        return b1 || b2;
    }
}

void BTree::findPath(node *t, int &item)
{
    if(t == NULL)
    {
        cout << "empty node" << endl;
        return;
    }
    node *p = t;
    linklistForBSTree l;
    l.insertList(p);
    int sum = 0;
    while(p)
    {
        sum = sum + p->data;
        if(sum == item)
        {
            cout << "find one path" << endl;
            l.printLinklist();
        }
        else
        {
            p = p->parent;
            l.insertList(p);
        }
    }
    if(t->lchild)
    {
        findPath(t->lchild, item);
    }
    if(t->rchild)
    {
        findPath(t->rchild, item);
    }
}

void BTree::findPathWithoutParent(node *t, int &item, int *a, int level)
{
    if(t == NULL)
    {
        //cout << "empty node" << endl;
        return;
    }
    a[level] = t->data;
    
    int sum = 0;
    for(int i=level;i>-1;i--)
    {
        sum = sum + a[i];
        if(sum == item)
        {
            cout << "find one path" << endl;
            for(int j=level;j>=i;j--)
            {
                cout << a[j] << " ";
            }
            cout << endl;
        }
    }
    
    int *a1 = new int[level+2];
    int *a2 = new int[level+2];
    
    //cout << level << " level length of a1 is " << sizeof(a)/sizeof(a[0]) << endl;
    
    //copy parent level value
    for(int i=0;i<=level;i++)
    {
        a1[i] = a[i];
        a2[i] = a[i];
    }
    findPathWithoutParent(t->lchild, item, a1, level+1);
    findPathWithoutParent(t->rchild, item, a2, level+1);
    
    /*
    cout << "after find path" << endl;
    for(int i=0;i<sizeof(a1)/sizeof(a1[0]);i++)
    {
        cout << a1[i] << " ";
    }
    cout << endl;
    cout << " ------------------" << endl;
    
    //考虑叶子结点到叶子结点情况
    
    int *merge1 = new int[2*level + 3];
    int *merge2 = new int[2*level + 3];
    for(int i=level+1;i>-1;i--)
    {
        merge1[i] = a2[i];
        merge2[i] = a1[i];
    }
    int k = level+1;
    for(int i=level+2;i<2*level+3;i++)
    {
        merge1[i] = a1[k];
        merge2[i] = a2[k];
        k = k - 1;
    }
    int sum1 = 0;
    int sum2 = 0;
    int len = sizeof(merge1)/sizeof(merge1[0]);
    cout << "start print merge array" << endl;
    for(int i=2*level + 2;i>-1;i--)
    {
        cout << merge1[i] << " ";
    }
    cout << endl;
    for(int i=2*level + 2;i>-1;i--)
    {
        cout << merge2[i] << " ";
    }
    cout << endl;
    for(int i=2*level + 2;i>-1;i--)
    {
        sum1 = sum1 + merge1[i];
        sum2 = sum2 + merge2[i];
        //cout << "sum1 = " << sum1 << " sum2 = " << sum2 << endl;
        if(sum1 == item)
        {
            cout << "find one path" << endl;
            for(int j=len-1;j>=i;j--)
            {
                cout << merge1[j] << " ";
            }
            cout << endl;
        }
        if(sum2 == item)
        {
            cout << "find one path" << endl;
            for(int j=len-1;j>=i;j--)
            {
                cout << merge2[j] << " ";
            }
            cout << endl;
        }
    }
    */
}

void BTree::printAllPathSumToGivenValue(int &item)
{
    /*
     如果存在指向存在parent的指针，那么遍历此树，对每个结点一路向上累加。
     */
    //findPath(root, item);
    
    /*
     如果不存在parent的指针，为了保证能够遍历到每条路径，求和依然是从下到上的。
     在二叉树从上到下的查找过程中，数组保存中间结果，从后向前累加实现从下到上的求和
     然后将该层的中间结果存入到该结点的左右孩子，也就是下一层结点，继续递归
     
     -----------------------------------------------------------------
     这里有个问题就是，所有的路径是否包括从叶子结点到叶子结点的路径？？？？？
     findPathWithoutParent里面是没有考虑到这种情况的。
     考虑进来的话该如何做呢？修改一下递归。
     在对结点lchild和rchild递归后，所得的数组a1和a2合并一下再寻找结果。----->尝试后发现有致命问题，尾递归，无法走之后的步
     
     想到的解决方法：修改输入
     findPathWithoutParent(lchild, a1, rchild, a2, item, level);
     第一步：实现lchild路径里是否存在路径；
     第二步：rchild和lchild的路径合并，注意是root为桥，然后计算是否存在路径
     这样就能计算出来了，思路如此，尚未实现。lchild=root的话rchild直接取为NULL就好了
     -----------------------------------------------------------------
     */
    int *a = new int[1];
    
    findPathWithoutParent(root, item, a, 0);
}

void BTree::testBTree()
{
    int a[] = {80,52,30,44,22,74,73,114,150,85,11,170};
    //int a[] = {80,52,30,43,12,74,65,114,150,101,6,5};
    //int a[] = {1,2,3,4,5,6,7,8,9};
    int b[] = {80,53,114,150,101};
    int len = sizeof(a)/sizeof(a[0]);
    int len_b = sizeof(b)/sizeof(b[0]);
    int i;
    
    cout << "begin test leafNode balance and tree balance" << endl;
    for(i=0;i<len;i++)
    {
        insertBSTree(root, a[i]);
    }
    inOrderTraverNoRecursion(root, visit);
    cout << endl;
    
    bool result1 = checkBalance(root);
    bool result2 = isBalance(root);
    cout << "tree balance? " << result1 << endl;
    cout << "leaf node balance? " << result2 << endl;
    /*
    cout << "begin test findAllPathToGivenValue" << endl;
    

    int item = 132;
    printAllPathSumToGivenValue(item);
    
    cout << "-----------------------------------------------------------------" << endl;
    
    cout << "begin test subtree" << endl;
    
    BTree b1, b2;
    b1.root = NULL;
    b2.root = NULL;

    for(i=0;i<len;i++)
    {
        b1.insertBSTree(b1.root, a[i]);
    }
    b1.inOrderTraverse(b1.root, visit);
    cout << endl;
    cout << b1.getDepth(b1.root) << endl;
    
    for(i=0;i<len_b;i++)
    {
        b2.insertBSTree(b2.root, b[i]);
    }
    b2.inOrderTraverse(b2.root, visit);
    cout << endl;
    cout << b2.getDepth(b2.root) << endl;
    cout << endl;
    
    bool result = subtree(&b1, &b2);
    cout << result << endl;
    */
    
    /*
    root = NULL;
    
    cout << "begin test minHeight BTree" << endl;
    
    minHeightBTree(root, a, 0, len-1);
    
    //levelOrderTraverse(root, visit);
    inOrderTraverNoRecursion(root, visit);
    cout << endl;
    cout << "depth is:" << getDepth(root) << endl;
    
    node *ancestor;
    node *p = root, *q = root;
    p = p->rchild->rchild->rchild;
    q = q->rchild->lchild;
    cout << "node p value is: " << p->data << " node q value is: " << q->data << endl;
    ancestor = findFirstCommonAncestor(p, q);
    */

    
    /*
    cout << "begin test BSTree" << endl;
    
    node *temp = new node;
    temp->data = a[0];
    temp->lchild = NULL;
    temp->rchild = NULL;
    
    root = temp;
    
    int i;
    for(i=1;i<len;i++)
    {
        insertBSTree(root, a[i]);
    }
    //cout << "root lchild " << root->lchild->data << endl;
    inOrderTraverNoRecursion(root, visit);
    cout << endl;
    
    bool isBalance;
    isBalance = checkBalance(root);
    cout << "root balance? " << isBalance << endl;
    isBalance = checkBalance(root->lchild);
    cout << "root->lchild balance? " << isBalance << endl;
    isBalance = checkBalance(root->rchild);
    cout << "root->rchild balance? " << isBalance << endl;
     
     */

    /*
    int a[] = {0,1,2,3,4,5,6};
    node *begin = new node();
    begin->data = a[0];
    begin->lchild = NULL;
    begin->rchild = NULL;
    begin->parent = NULL;
    
    root = begin;
    
    int len = sizeof(a)/sizeof(a[0]);
    cout << len << endl;
    node *newNode = new node[len];
    BTree *newBTree = new BTree[len+1];
    int i;
    a[0] = 7;
    for(i=0;i<len;i++)
    {
        newNode[i].data = a[i];
        newNode[i].lchild = NULL;
        newNode[i].rchild = NULL;
        newNode[i].parent = NULL;
        newBTree[i] = nodeCreateBTree(&newNode[i]);
    }
    
    
    int LR;
    for(i=0;i<len;i++)
    {
        if(i%2==0)
        {
            LR = 0;
        }
        else
        {
            LR = 1;
        }
        cout << "this time insert root's position is(0 is left, 1 right): " << LR << endl;
        insertChild(root, LR, newBTree[i]);
    }
    
    
    cout << "node number of tree is: " << getLength(root) << endl;
    cout << "tree depth is: " << getDepth(root) << endl;
    
    cout << "testing what the tree is" << endl;
    cout << "this is root: " << root->data << endl;
    cout << "this is root left child: " << root->lchild->data << endl;
    cout << "this is root right child: " << root->rchild->data << endl;
    
    cout << "pre order traverse" << endl;
    preOrderTraverse(root, visit);
    cout << endl;
    cout << "pre order traverse with no recursion" << endl;
    preOrderTraverNoRecursion(root, visit);
    cout << endl;
    
    cout << "in order traverse" << endl;
    inOrderTraverse(root, visit);
    cout << endl;
    cout << "in order traverse with no recursion" << endl;
    inOrderTraverNoRecursion(root, visit);
    cout << endl;
    
    cout << "post order traverse" << endl;
    postOrderTraverse(root, visit);
    cout << endl;
    cout << "post order traverse with no recursion" << endl;
    postOrderTraverNoRecursion(root, visit);
    cout << endl;
    
    cout << "level order travers" << endl;
    levelOrderTraverse(root, visit);
    
    cout << "----------------the end of first test---------------" << endl;
    
    //上面都是一个结点为一棵树，现在将其中的一些变为2~3个结点的树
    node *anew = new node();
    anew->data = 100;
    anew->lchild = NULL;
    anew->rchild = NULL;
    anew->parent = NULL;
    
    node *anew2 = new node();
    anew2->data = 200;
    anew2->lchild = NULL;
    anew2->rchild = NULL;
    anew2->parent = NULL;
    
    newBTree[7] = nodeCreateBTree(anew);
    newBTree[7].root->lchild = anew2;
    newBTree[7].root->rchild = NULL;
    anew2->parent = newBTree[7].root;
    
    LR = 0;
    cout << "this time insert root's position is(0 is left, 1 right): " << LR << endl;
    insertChild(root, LR, newBTree[7]);
    
    cout << "node number of tree is: " << getLength(root) << endl;
    cout << "tree depth is: " << getDepth(root) << endl;
    
    cout << "testing what the tree is" << endl;
    cout << "this is root: " << root->data << endl;
    cout << "this is root left child: " << root->lchild->data << endl;
    cout << "this is root right child: " << root->rchild->data << endl;
    
    cout << "pre order traverse" << endl;
    preOrderTraverse(root, visit);
    cout << endl;
    cout << "pre order traverse with no recursion" << endl;
    preOrderTraverNoRecursion(root, visit);
    cout << endl;
    
    cout << "in order traverse" << endl;
    inOrderTraverse(root, visit);
    cout << endl;
    cout << "in order traverse with no recursion" << endl;
    inOrderTraverNoRecursion(root, visit);
    cout << endl;
    
    cout << "post order traverse" << endl;
    postOrderTraverse(root, visit);
    cout << endl;
    cout << "post order traverse with no recursion" << endl;
    postOrderTraverNoRecursion(root, visit);
    cout << endl;
    
    cout << "level order travers" << endl;
    levelOrderTraverse(root, visit);
     */

}

// --------------------------------------------------------------------------------------------------------------------

// --------------------------------------------------------------------------------------------------------------------

// --------------------------------------------------------------------------------------------------------------------

// Binary Search Tree 左子树结点值 < 根节点值 < 右子树结点值
class BSTree{
private:
    node *root;
public:
    bool findBSTree(node *t, int &elem); //查找给定值item的元素
    void insertBSTree(node *&t, int &item); //插入值为item的结点
    void insertBSTreeTest(node **t, int &item);
    bool deleteBSTree(node *&t, int &item); //删除值为item的结点，t为当前结点，t->data不一定等于item
    void inOrderTraverse(node *t, void (*visit)(node *));
    int getDepth(node *t); //计算当前结点的深度
    
    void insertBSTreeWithNode(node *&t, node *ins); //插入ins到当前结点t出
    
    linklistForBSTree* generateDepthLinklist(); //同一深度的搜索树结点生成一个链表，总共有Depth个链表
    
    node* findNextNode(node *t); //寻找给定结点的下一个（中序后继）结点
    
    void testBSTree();
};

bool BSTree::findBSTree(node *t, int &elem)
{
    node *p = t;
    if(!p)
    {
        return false;
    }
    if(p->data == elem)
    {
        cout << "find the node" << endl;
        return true;
    }
    else if(p->data > elem)
    {
        return findBSTree(p->lchild, elem);
    }
    else
    {
        return findBSTree(p->rchild, elem);
    }
    
}

void BSTree::insertBSTreeTest(node **t, int &item)
{
    if(!(*t))
    {
        node *p = new node;
        p->data = item;
        p->lchild = NULL;
        p->rchild = NULL;
        *t = p;
        //cout << "build up new node, value = " << t->data << endl;
    }
    else if((*t)->data > item)
    {
        /*
         cout << "calling lchild function, current node data is " << t->data << " current item is: " << item << endl;
         bool judge;
         if(t->lchild) judge = false;
         else judge = true;
         cout << "is current->lchild null?(0: no, 1: yes)" << judge << endl;
         */
        insertBSTreeTest(&(*t)->lchild, item);
        
    }
    else
    {
        //cout << "calling rchild function, current node data is " << t->data << " current item is: " << item << endl;
        insertBSTreeTest(&(*t)->rchild, item);
    }

}
void BSTree::insertBSTree(node *&t, int &item)
{
    /*--------------------------------------------------------------------------------------------------------------------
     注意：这里为何参数要写成 node *&t。
     
     在实际操作中，如果直接定义node *t，在递归调用t->lchild时发现值虽然赋上了，但是t->lchild没有存入到t的信息里，导致不断被覆盖
     
     在此猜测，可能是因为node本身就是指针变量，调用函数时如果要使用到母参数的关系或者要与母参数产生联系，必须这样定义，才能传递进去
     
     这也就解释了为何中序等其他三种遍历递归时可以只用node *t，因为它只需要访问它的child去了，无须再跟当前结点产生任何联系
     
     --------------------------------------------------------------------------------------------------------------------*/
    if(!t)
    {
        node *p = new node;
        p->data = item;
        p->lchild = NULL;
        p->rchild = NULL;
        t = p;
        //cout << "build up new node, value = " << t->data << endl;
    }
    else if(t->data > item)
    {
        /*
        cout << "calling lchild function, current node data is " << t->data << " current item is: " << item << endl;
        bool judge;
        if(t->lchild) judge = false;
        else judge = true;
        cout << "is current->lchild null?(0: no, 1: yes)" << judge << endl;
         */
        insertBSTree(t->lchild, item);
        
    }
    else
    {
        //cout << "calling rchild function, current node data is " << t->data << " current item is: " << item << endl;
        insertBSTree(t->rchild, item);
    }
    
}

bool BSTree::deleteBSTree(node *&t, int &item)
{
    //删除值为item的结点，t为当前结点，t的值不一定是item
    if(t == NULL) return false;
    
    
    if(t->data == item)
    {
        node *p = new node;
        if((!t->lchild) && (!t->rchild)) //叶子结点
        {
            p = t;
            t = NULL;
            delete p;
            return true;
        }
        else if((t->lchild) && (!t->rchild)) //左孩子存在，右孩子不存在
        {
            p = t;
            t = t->lchild;
            //t->lchild = NULL;
            delete p;
            return true;
        }
        else if((!t->lchild) && (t->rchild)) //左孩子不存在，右孩子存在
        {
            p = t;
            t = t->rchild;
            //t->rchild = NULL;
            delete p;
            return true;
        }
        else //左右孩子都在
        {
            /*
             处理的原则：删除结点后仍然保持二叉搜索树中序序列的有序性
             比较好的方式是将结点的中序前件移到该结点的位置，然后直接调用删除该中序前件，中序前件的位置由左孩子顶替
             因为该中序前件一定是单支结点，否则中序前件就不是它了，还得往下找
             */
            p = t;
            /*寻找中序前件：左孩子的右子树，也就是左子树的最右边
             分两种情况：
                情况一：当前结点的左孩子的右子树为空，左孩子即为中序前件
                情况二：当前结点的左孩子的右子树不为空，一路循环下去找最右边
             */
            if(p->lchild->rchild == NULL)
            {
                t->data = t->lchild->data;
                //递归方法
                delete p;
                return deleteBSTree(t->lchild, t->lchild->data);
                
                //非递归方法
                /*
                p = t->lchild;
                t->lchild = t->lchild->lchild;
                delete p;
                return true;
                 */
                
            }
            else
            {
                node *p2 = p->lchild;
                //p = p->lchild;
                while(p2->rchild)
                {
                    p = p2;
                    p2 = p2->rchild;
                }
                
                t->data = p2->data;
                //递归方法
                //return deleteBSTree(p->rchild, p2->data); //为何一定要使用p->rchild,或者p都行
                //return deleteBSTree(p2, p2->data); //为何使用p2就无法删除？？？？
                
                //非递归方法
                
                p->rchild = p->rchild->lchild;
                //delete p2;
                return true;
                
                
            }
            
            
        }
    }
    else if(t->data > item)
    {
        return deleteBSTree(t->lchild, item);
    }
    else
    {
        return deleteBSTree(t->rchild, item);
    }
    
}

void BSTree::inOrderTraverse(node *t, void (*visit)(node *))
{
    if(t)
    {
        inOrderTraverse(t->lchild, visit);
        visit(t);
        inOrderTraverse(t->rchild, visit);
    }
}

void BSTree::insertBSTreeWithNode(node *&t, node *ins)
{
    if(!t)
    {
        t = ins;
    }
    else if(t->data > ins->data)
    {
        insertBSTreeWithNode(t->lchild, ins);
    }
    else
    {
        insertBSTreeWithNode(t->rchild, ins);
    }
}

int BSTree::getDepth(node *t)
{
    if(t == NULL)
        return 0;
    else
    {
        if(getDepth(t->lchild) > getDepth(t->rchild))
            return getDepth(t->lchild) + 1;
        else
            return getDepth(t->rchild) + 1;
    }
}

linklistForBSTree* BSTree::generateDepthLinklist()
{
    int depth = getDepth(root);
    linklistForBSTree *L =  new linklistForBSTree[depth];
    
    //先处理root结点。
    L[0].insertList(root);
    
    //cout << L[0].isEmpty() << endl;
    
    int pre = 0;
    while((!L[pre].isEmpty()) && pre < depth)
    {
        cout << "current is linklist " << pre << endl;
        int cur = pre + 1;
        node *p;
        p = L[pre].head;
        while(p)
        {
            if(p->lchild)
                L[cur].insertList(p->lchild);
            if(p->rchild)
                L[cur].insertList(p->rchild);
            p = p->next;
        }
        pre = cur;
    }
    
    /*
    for(int i=0;i<depth;i++)
    {
        cout << "this is depth " << i << endl;
        L[i].printLinklist();
    }
     */
    
    return L;
}

node* BSTree::findNextNode(node *t)
{
    /*
     中序后继的情况有如下：
     1）没有右子树，分三种情况：
        如果是parent->lchild，后继就是parent；
        如果是parent->rchild，并且是上溯结点的左子树，上溯结点即为后继
        没有parent或者是parent->rchild但不是上溯结点的左子树，说明是尾结点，后继为NULL
     
     2）有右子树，分析当前节点的右孩子，两种情况
        如果node->rchild->lchild == NULL 那么右孩子即为后继结点
        如果不为NULL，右孩子的左子树一路下去最左边的那个就是后继结点
     */
    
    //右子树存在的情况
    if(t->rchild)
    {
        if(t->rchild->lchild == NULL)
        {
            cout << "situation 1: rchild exists, rchild->lchild = NULL" << endl;
            return t->rchild;
        }
        else
        {
            cout << "situation 2: rchild->lchild exists, find the left most lchild along the way" << endl;
            node *p = t->rchild;
            while(p->lchild)
            {
                p = p->lchild;
            }
            return p;
        }
    }
    else //右子树为空
    {
        if(t->parent == NULL) //root结点，无parent，无rchild
        {
            cout << "situation 3: root node, no parent, no rchild" << endl;
            return NULL;
        }
        else if(t->parent->lchild == t) //是parent的左孩子
        {
            cout << "situation 4: rchild not exist, parent's lchild" << endl;
            return t->parent;
        }
        else //有parent，且是parent的右孩子，分两种情况
        {
            node *p1 = t->parent;
            node *p2 = p1->parent;
            while((p2->lchild != p1) && (p2 != NULL)) //一直上溯找左子树，直到root结点
            {
                p1 = p2;
                p2 = p2->parent;
            }
            if(p2 == NULL)
            {
                cout << "situation 5: rchild not exist, parent's rchild, not ancestor's left child tree" << endl;
                return NULL;
            }
            else
            {
                cout << "situation 6: rchild not exist, parent's rchild, is ancestor's left child tree" << endl;
                return p2;
            }
        }
    }
}


void BSTree::testBSTree()
{
    int a[] = {80,52,30,43,12,74,65,114,150,101};
    int len = sizeof(a)/sizeof(a[0]);
    
    cout << "begin test BSTree" << endl;
    
    
    int i;
    
    root = NULL;
    
    for(i=0;i<len;i++)
    {
        //insertBSTreeTest(&root, a[i]);
        insertBSTree(root, a[i]);
    }
    
    /*
    node *temp = new node;
    temp->data = a[0];
    temp->lchild = NULL;
    temp->rchild = NULL;
    
    node *newNode = new node[len];
    
    root = temp;
    
    for(i=1;i<len;i++)
    {
        
        newNode[i].data = a[i];
        newNode[i].lchild = NULL;
        newNode[i].rchild = NULL;
        insertBSTreeWithNode(root, &newNode[i]);
    }
     */
    
    inOrderTraverse(root, visit);
    
    cout << endl;
    
    cout << "current depth is " << getDepth(root) << endl;
    
    
    
    deleteBSTree(root, a[0]);
    
    inOrderTraverse(root, visit);
    cout << "new root data is: " << root->data << endl;
    
    linklistForBSTree *L;
    L = generateDepthLinklist();
    
    for(i=0;i<getDepth(root);i++)
    {
        cout << "this is depth " << i << endl;
        L[i].printLinklist();
    }
    
}



#endif
