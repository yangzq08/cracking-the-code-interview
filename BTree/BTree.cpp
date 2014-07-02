//
//  main.cpp
//  BTree
//
//  Created by yangzhiqi on 14-6-16.
//  Copyright (c) 2014年 yangzhiqi. All rights reserved.
//

#include <iostream>
#include "Header.h"

using namespace std;

void pass_by_value(int* p)
{
    //Allocate memory for int and store the address in p
    p = new int;
}

void pass_by_reference(int*& p)
{
    p = new int;
}


int main(int argc, const char * argv[])
{
    /*
    int num = 0;
    int &ref = num;
    cout << ref << endl;
    ref = 1;
    cout << ref << endl;
    cout << num << endl;
    
    
    int* p1 = NULL;
    int* p2 = NULL;
    
    cout << p1 << endl;
    cout << p2 << endl;
    
    pass_by_value(p1); //p1 will still be NULL after this call
    pass_by_reference(p2); //p2 's value is changed to point to the newly allocate memory
    
    cout << p1 << endl;
    cout << p2 << endl;
    cout << *p2 << endl; //成功初始化
    */
    
    /*
     打印结果是：
     0x0
     0x0
     0x0
     0x100103ad0
     0
     */
    
    
    //queueForBTree q;
    //q.testQueueForBTree();
    
    //stackForBTree s;
    //s.testStackForBTree();
    
    BTree bb;
    bb.testBTree();
    
    //BSTree b;
    //b.testBSTree();
}

