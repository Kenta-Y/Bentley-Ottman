//
//  search_intersection.cpp
//  Bentley-Ottmann
//
//  Created by KentaYamagishi on 2016/04/25.
//  Copyright © 2016年 KentaYamagishi. All rights reserved.
//

#define DEMO
#include "search_intersection.hpp"

struct element nil2;
struct node nil;
elementptr head;
nodeptr root;

int node_init(){
    root = new node;
    if(root == NULL) return 0;
    root->v.x = -1;
    root->rson = root->lson = &nil;
    
    return 1;
}

int insert_point(datatype data){
    nodeptr p, q = 0;
    p = root;
    while (p != &nil){
        q = p;
        if(data.x == p->v.x) return 0;
        if(data.x < p->v.x) p = p->lson;
        else                p = p->rson;
    }
    p = new node;
    if(p == NULL) return 0; //挿入失敗
    p->v = data;
    p->lson = p->rson = &nil;
    if(data.x < q->v.x) q->lson = p;
    else                q->rson = p;
    return 1;
}

int delete_point(datatype data){
    nodeptr f = 0, p, q;
    p = root;
    //while((p != &nil || data.x != p->v.x)){
    while(p != &nil){
        if(data.x == p->v.x) break;
        f = p;
        if(p->v.x > data.x) p = p->lson;
        else                p = p->rson;
    }
    if(p == &nil) return 0;
    if(p->lson == &nil || p->rson == &nil){
        if(p->lson == &nil) q = p->rson;
        else                q = p->lson;
        if(f->lson == p) f->lson = q;
    }else{
        q = p->rson;
        f = q;
        while(q->lson != &nil){
            f = q;
            q = q->lson;
        }
        p->v = q->v;
        if(q == f) p->rson = q->rson;
        else f->lson = q->rson;
    }
    return 1;
}

void treeInterval(nodeptr p, int x1, int x2, int y){
    if(p != &nil){
        if(p->v.x >= x1 && p->v.x <= x2){
            /*交点*/
            draw_intersection(cv::Point2i(p->v.x, y));    //緑色の円を描画
            std::cout << "(" << p->v.x << ", " << y << ") is intersection" << std::endl;
            treeInterval(p->lson, x1, x2, y);
            treeInterval(p->rson, x1, x2, y);
        }
        if(p->v.x <= x1) treeInterval(p->rson, x1, x2, y);
        if(p->v.x >= x2) treeInterval(p->lson, x1, x2, y);
    }
}

void sweep(elementptr head, nodeptr root){
    while(head != NULL){
#ifdef DEMO
        draw_LineScanning(head->p1.y);
        cv::waitKey(0);
#endif
        if(head->p1.y < head->p2.y) insert_point(head->p1);
        else if(head->p1.y > head->p2.y) delete_point(head->p2);
        else{
            if(head->p1.x < head->p2.x) treeInterval(root, head->p1.x, head->p2.x, head->p1.y);
            else                        treeInterval(root, head->p2.x, head->p1.x, head->p1.y);
        }
        head = head->next;
    }
}

int insert_element(datatype first, datatype end){
    static bool flg = false;
    
    if(!flg){
        head = new element;
        if(head == NULL) return 0; //挿入失敗
        head->p1 = first;
        head->p2 = end;
        head->next = &nil2;
        flg = true;
    }else{
        elementptr p = head, q = 0;
        while (p != &nil2){
            q = p;
            p = p->next;
        }
        p = new element;
        if(p == NULL) return 0; //挿入失敗
        p->p1 = first;
        p->p2 = end;
        p->next = &nil2;
        q->next = p;
    }
    return 1;
}

void QuickSort(std::vector<BothPoint> &array, int begin, int end){
    int i = begin;
    int j = end;
    int pivot;
    BothPoint temp;
    
    pivot = array[ ( begin + end ) / 2 ].first_point.y;  // 中央の値をpivotにする
    
    while(1){
        while( array[i].first_point.y < pivot ) ++i;   /* 枢軸以上の値が見つかるまで右方向へ進めていく */
        while( array[j].first_point.y > pivot ) --j;   /* 枢軸以下の値が見つかるまで左方向へ進めていく */
        if( i >= j )break;  // 軸がぶつかったらソート終了
        
        // 入れ替え
        temp = array[i];
        array[i] = array[j];
        array[j] = temp;
        i++;
        j--;
    }
    
    // 軸の左側をソートする
    if( begin < i - 1 ) QuickSort( array, begin, i - 1 );
    // 軸の右側をソートする
    if( j + 1 < end ) QuickSort( array, j + 1, end );
}

void sort_y(std::vector<Line_Segment> line){
    std::vector<BothPoint> both_p;
    for(int i = 0; i < line.size(); i++){
        BothPoint tmp1 = {line[i].get_first_point(),line[i].get_end_point()};
        BothPoint tmp2 = {line[i].get_end_point(),line[i].get_first_point()};
        both_p.push_back(tmp1);
        both_p.push_back(tmp2);
    }
    QuickSort(both_p, 0, (int)both_p.size()-1);
    
    for(int i = 0; i < both_p.size(); i++)
        insert_element(both_p[i].first_point, both_p[i].end_point);
}