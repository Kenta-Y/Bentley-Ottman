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
#include "heap.hpp"

extern nodeptr root;
extern struct node nil;

cv::Point2i cross_point(cv::Point2i p1, cv::Point2i p2, cv::Point2i p3, cv::Point2i p4){
    int x, y, tmp;
    tmp = (p3.y*p4.x-p3.x*p4.y) * (p2.x-p1.x) - (p1.y*p2.x-p1.x*p2.y)*(p4.x-p3.x);
    x = tmp / ((p2.y-p1.y)*(p4.x-p3.x) - (p2.x-p1.x)*(p4.y-p3.y));
    tmp = (p3.y*p4.x-p3.x*p4.y)*(p2.y-p1.y) - (p1.y*p2.x-p1.x*p2.y)*(p4.y-p3.y);
    y = tmp / ((p2.y-p1.y)*(p4.x-p3.x) - (p2.x-p1.x)*(p4.y-p3.y));
    
    return cv::Point2i(x, y);
}

std::vector<cv::Point2i> inter;

void search(nodeptr L1, nodeptr L2, std::vector<element> &heap, int *N){
    
    //bool check = intersect(L1->fp, L1->ep, L2->fp, L2->ep);
    if(intersect(L1->fp, L1->ep, L2->fp, L2->ep) == 1){     //交点がある場合
        bool check = false;
        //std::cout << "foo" << parent_node->fp << ", " << parent_node->ep << ", " << parent_node->lson->fp << ", " << parent_node->lson->ep << std::endl;
        cv::Point2i cross = cross_point(L1->fp, L1->ep, L2->fp, L2->ep);
        
        for(int i = 0; i < inter.size(); i++){
            if(cross == inter[i]){
                check = true;
                break;
            }
        }
        
        if(!check && L1->ep != L2->ep){
            inter.push_back(cross);
            draw_intersection(cross);
            std::cout << "draw: " << cross << std::endl;
            std::cout << "foo" << L1->fp << ", " << L1->ep << ", " << L2->fp << ", " << L2->ep << std::endl;
            
            //２本の線分を４本に分割してヒープに挿入
            element linea[4], lineb[4];
            
            //linea[0] = {L1->fp, cross};
            lineb[0] = {cross, L1->fp};
            //linea[1] = {L2->fp, cross};
            lineb[1] = {cross, L2->fp};
            
            linea[2] = {cross, L1->ep};
            lineb[2] = {L1->ep, cross};
            linea[3] = {cross, L2->ep};
            lineb[3] = {L2->ep, cross};
            
            for(int i = 0; i < 4; i++){
                if(i > 1)
                    insert_heap(linea[i], heap, N);
                
                insert_heap(lineb[i], heap, N);
    //            heap.push_back(linea[i]);
    //            heap.push_back(lineb[i]);
            }
            
            //上の2つは2分探索木にも挿入
            insert_point(linea[0]);
            insert_point(linea[1]);
            
    //        element cross_val;
    //        cross_val.lf = cv::Point2i(cross.x, cross.y);
    //        cross_val.le = cv::Point2i(-10, -10);
    //        cross_val.IA = L1;
    //        cross_val.IB = L2;
    //        insert_heap(cross_val, heap, N);
        }
    }
}

int main(){
    std::vector<element> heap;
    int n=0;
    
//    line.push_back(Line_Segment(100, 400, 300, 150));   // A
//    line.push_back(Line_Segment(250, 450, 130, 100));   // B
//    line.push_back(Line_Segment(350, 330, 630, 220));   // D
//    line.push_back(Line_Segment(410, 250, 500, 370));   // E
    
    //関数呼び出し
    //cv::Point2i A = {300,150}, B = {100, 400}, C = {130,100}, D = {250, 450}, CRS = {350, 350};
    //cv::Point2i A = {350,330}, B = {630, 220}, C = {410,250}, D = {500, 370}, CRS = {350, 350};
//    int ck = intersect(B, A, D, C);
//    if(ck == 1)
//        CRS = cross_point(A, B, C, D);
    
//    std::cout << ck;
    
    cv::waitKey(0);
    
    //初期設定
    cv::namedWindow("drawing", CV_WINDOW_AUTOSIZE|CV_WINDOW_FREERATIO); //ウィンドウの初期化
    std::vector<Line_Segment> line; //線分の情報を格納するベクター
    line = cleate_line();  //線分の格納
    draw_line(line);    //線分の描画
    //draw_intersection(CRS);
    cv::waitKey(0);
    
    std::vector<element> both_p;
    for(int i = 0; i < line.size(); i++){
        element tmp1 = {line[i].get_first_point(), line[i].get_end_point(), &nil, &nil};
        element tmp2 = {line[i].get_end_point(), line[i].get_first_point(), &nil, &nil};
        both_p.push_back(tmp1);
        both_p.push_back(tmp2);
    }
    
    for(int i = 0; i < both_p.size(); i++)
        insert_heap(both_p[i], heap, &n);
    
    for(int i=0;i<n;i++){ // MAX -> n に変更
        printf("%d ",heap[i].lf.y);
    }
    printf("\n");
    
    if(!check_heap(heap, (int)heap.size())) printf("ヒープ条件を満たしていません\n"); //例外処理
    
    node_init();
    
    while(n != 0){
        // a:ヒープから最小要素を取り出す
        element min = deletemin(heap,&n); //ヒープから最小要素の削除
        
//        if(min.IA != &nil && min.IB != &nil){   //d:線分の交点を発見
//            std::cout << "ccc" << std::endl;
//            cv::Point2i tmp_fp = min.IA->fp, tmp_ep = min.IA->ep;
//            min.IA->fp = min.IB->fp;
//            min.IA->ep = min.IB->ep;
//            min.IB->fp = tmp_fp;
//            min.IB->ep = tmp_ep;
  
//            nodeptr tmp;
//            tmp = min.IA;
//            min.IA = min.IB;
//            min.IB = tmp;
            
        //}else if(min.lf.y < min.le.y){  // b:線分の上端を発見
        if(min.lf.y < min.le.y){  // b:線分の上端を発見
        
            std::cout << "aaa" << std::endl;
            nodeptr parent_node = insert_point(min);  //2分探索木へ挿入
            
            //交点確認
//            if(parent_node->lson != &nil){
//                search(parent_node, parent_node->lson, heap, &n);
//            }
//            if(parent_node->rson != &nil){
//                search(parent_node, parent_node->rson, heap, &n);
//            }
            if(parent_node->parent != &nil)
                search(parent_node, parent_node->parent, heap, &n);
            
        }else if(min.lf.y > min.le.y){  //c:線分の下端を発見
            
            std::cout << "ddd" << std::endl;
            nodeptr parent_node = delete_point(min);  //2分探索木から削除
            if(parent_node != 0){
                //交点確認
    //            if(parent_node->lson != &nil){
    //                search(parent_node, parent_node->lson, heap, &n);
    //            }
    //            else if(parent_node->rson != &nil){
    //                search(parent_node, parent_node->rson, heap, &n);
    //            }
                if(parent_node->parent != &nil)
                    search(parent_node, parent_node->parent, heap, &n);
            }
        }
        
        std::cout << n << std::endl;
        //std::cout << min.lf.y << std::endl;
        draw_LineScanning(min.lf.y);
        cv::waitKey(0);
    }
    
    cv::waitKey(0);
    /* なくなるまで最小値を取りだして表示 */
//    while (n) {
//        int min = deletemin(heap,&n);//関数呼びだし
//        printf("%d ",min);
//    }
//    printf("\n");
    
    return 0;
}