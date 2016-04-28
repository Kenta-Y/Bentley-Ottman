//
//  heap.cpp
//  Bentley-Ottmann
//
//  Created by KentaYamagishi on 2016/04/25.
//  Copyright © 2016年 KentaYamagishi. All rights reserved.
//

#include "search_intersection.hpp"
#include "create_linesegment.hpp"
#include "heap.hpp"

//値を入れ替える関数
void swap(element* a, element* b){
    element temp;
    temp=*a;
    *a=*b;
    *b=temp;
}

//新しく値を挿入する関数
void insert_heap(element val,std::vector<element> &a, int* N){
    int i;
    a.push_back(val);
    
    for(i=*N;i!=0;i=(i-1)/2){
        if(a[i].lf.y<a[(i-1)/2].lf.y)//親が子より大きい場合
            swap(&a[i],&a[(i-1)/2]);//関数呼びだし
    }
    (*N)++;
}

//ヒープの最小値を取り除く関数
element deletemin(std::vector<element> &a, int *N){
    element min=a[0];
    int i=1,j=i*2;
    a[0] = a[--(*N)];//末尾の要素をルートに持ってくる
    while(j<=(*N)){
        if(j+1<=(*N) && a[j-1].lf.y > a[j].lf.y) j++;
        if(a[i-1].lf.y > a[j-1].lf.y){//親が子より大きい値の場合
            //交換
            element temp=a[i-1];
            a[i-1] = a[j-1];
            a[j-1] = temp;
        }
        //数の更新
        i=j;
        j=i*2;
    }
    a.pop_back();
    return min;
}

//ヒープ条件を満たしているかチェックする関数
int check_heap(std::vector<element> &a,int n){
    int i;
    for(i = 0; i < n; i++) {
        int left=2*i+1; // ループの内側に移動
        int right=2*i+2; // ループの内側に移動
        
        if(left >= n) continue;
        if(a[left].lf.y < a[i].lf.y) return 0;
        if(right >= n) continue;
        if(a[right].lf.y < a[i].lf.y) return 0;
    }
    return 1;
}