//
//  main.cpp
//  Bentley-Ottmann
//
//  Created by KentaYamagishi on 2016/04/25.
//  Copyright © 2016年 KentaYamagishi. All rights reserved.
//

#include <iostream>
#include <opencv2/opencv.hpp>
#include "create_linesegment.hpp"
#include "search_intersection.hpp"

extern elementptr head;
extern nodeptr root;

//int check_heap(int a[],int n);
//void insert(int val,int a[], int* N);
void swap(BothPoint* a, BothPoint* b);
//int deletemin(int a[], int *n);


//新しく値を挿入する関数
void insert(BothPoint val,std::vector<BothPoint> &a, int* N){
    int i;
    a.push_back(val);
    
    for(i=*N;i!=0;i=(i-1)/2){
        if(a[i].first_point.y<a[(i-1)/2].first_point.y)//親が子より大きい場合
            swap(&a[i],&a[(i-1)/2]);//関数呼びだし
    }
    (*N)++;
}
//値を入れ替える関数
void swap(BothPoint* a, BothPoint* b){
    BothPoint temp;
    temp=*a;
    *a=*b;
    *b=temp;
}
//ヒープの最小値を取り除く関数
int deletemin(std::vector<BothPoint> &a, int *N){
    BothPoint min=a[0];
    int i=1,j=i*2;
    a[0]=a[--(*N)];//末尾の要素をルートに持ってくる
    while(j<=(*N)){
        if(j+1<=(*N) && a[j-1].first_point.y > a[j].first_point.y) j++;
        if(a[i-1].first_point.y > a[j-1].first_point.y){//親が子より大きい値の場合
            //交換
            BothPoint temp=a[i-1];
            a[i-1] = a[j-1];
            a[j-1] = temp;
        }
        //数の更新
        i=j;
        j=i*2;
    }
    return min.first_point.y;
}

//ヒープ条件を満たしているかチェックする関数
int check_heap(std::vector<BothPoint> &a,int n){
    int i;
    for(i = 0; i < n; i++) {
        int left=2*i+1; // ループの内側に移動
        int right=2*i+2; // ループの内側に移動
        
        if(left >= n) {
            continue;
        }
        
        if(a[left].first_point.y < a[i].first_point.y) {
            return 0;
        }
        
        if(right >= n) {
            continue;
        }
        
        if(a[right].first_point.y < a[i].first_point.y) {
            return 0;
        }
    }
    return 1;
}

int main(){
    std::vector<BothPoint> heap;
    //int heap[MAX];
    int i,result;
    int n=0;
    int min;
    
    //関数呼び出し
    
    //初期設定
    //cv::namedWindow("drawing", CV_WINDOW_AUTOSIZE|CV_WINDOW_FREERATIO); //ウィンドウの初期化
    std::vector<Line_Segment> line; //線分の情報を格納するベクター
    line = cleate_line();  //線分の格納
    //draw_line(line);    //線分の描画
    //cv::waitKey(0);
    
    std::vector<BothPoint> both_p;
    for(int i = 0; i < line.size(); i++){
        BothPoint tmp1 = {line[i].get_first_point(),line[i].get_end_point()};
        BothPoint tmp2 = {line[i].get_end_point(),line[i].get_first_point()};
        both_p.push_back(tmp1);
        both_p.push_back(tmp2);
    }
    
    for(int i = 0; i < both_p.size(); i++)
        insert(both_p[i], heap, &n);
    
    for(i=0;i<n;i++){ // MAX -> n に変更
        printf("%d ",heap[i].first_point.y);
    }
    printf("\n");
    
    result=check_heap(heap,n); //関数呼びだし MAX -> n に変更
    if(result==1){
        printf("ヒープ条件を満たしています.\n");
    }else {
        printf("ヒープ条件を満たしていません\n");
    }
    
    /* なくなるまで最小値を取りだして表示 */
    while (n) {
        min=deletemin(heap,&n);//関数呼びだし
        printf("%d ",min);
    }
    printf("\n");
    
    return 0;
}