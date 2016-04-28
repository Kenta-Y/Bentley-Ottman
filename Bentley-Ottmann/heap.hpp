//
//  heap.hpp
//  Bentley-Ottmann
//
//  Created by KentaYamagishi on 2016/04/25.
//  Copyright © 2016年 KentaYamagishi. All rights reserved.
//

#ifndef heap_hpp
#define heap_hpp

#include <stdio.h>

//element test.lf.y(Line_firstのy軸)を基準に並べている

void swap(element* a, element* b);
void insert_heap(element val,std::vector<element> &a, int* N);  //新しく値を挿入する関数
element deletemin(std::vector<element> &a, int *N);   //ヒープの最小値を取り除く関数
int check_heap(std::vector<element> &a,int n);    //ヒープ条件を満たしているかチェックする関数

#endif /* heap_hpp */
