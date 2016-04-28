//
//  search_intersection.cpp
//  Bentley-Ottmann
//
//  Created by KentaYamagishi on 2016/04/25.
//  Copyright © 2016年 KentaYamagishi. All rights reserved.
//

#define DEMO
#include "search_intersection.hpp"

struct node nil;
nodeptr root;

int area(cv::Point2i q1, cv::Point2i q2, cv::Point2i q3){
    int ch = ((q1.x - q3.x) * (q2.y - q3.y) + (q2.x - q3.x) * (q3.y - q1.y));
    return ch;
}

int between(cv::Point2i p1, cv::Point2i p2, cv::Point2i p3){
    if(area(p1, p2, p3) != 0) return 0;
    
    if(p1.x != p2.x)
        return ((p1.x <= p3.x && p3.x <= p2.x) || (p1.x >= p3.x && p3.x >= p2.x));
    else
        return ((p1.y <= p3.y && p3.y <= p2.y) || (p1.y >= p3.y && p3.y >= p2.y));
}

int intersect(cv::Point2i a, cv::Point2i b, cv::Point2i c, cv::Point2i d){
    if(between(a, b, c) || between(a, b, d) || between(c, d, a) || between(c, d, b))
        return 1;
    else{
        int w,y;
        if(area(a, b, c) < 0) w = -1;
        else                  w = 1;
        if(area(c, d, a) < 0) y = -1;
        else                  y = 1;
        return ( (w * area(a, b, d) < 0) && (y * area(c, d, b) < 0));
    }
}


int node_init(){
    root = new node;
    if(root == NULL) return 0;
    root->fp = cv::Point2i(-10, -10);
    root->ep = cv::Point2i(-10, 710);
    root->rson = root->lson = &nil;
    
    return 1;
}

nodeptr insert_point(element data){
    nodeptr p, q = 0;
    p = root;
    while (p != &nil){
        q = p;
        //if(data.first_point == p->fp) return 0;
        if(area(q->fp, q->ep, data.lf) > 0) p = p->lson;
        else                                p = p->rson;
    }
    p = new node;
    if(p == NULL) return 0; //挿入失敗
    p->fp = data.lf;
    p->ep = data.le;
    p->lson = p->rson = &nil;
    p->parent = q;
    if(area(q->fp, q->ep, data.lf) > 0) q->lson = p;
    else                                q->rson = p;
    
    return p;   //挿入したデータの親を返す
}

nodeptr delete_point(element data){
    nodeptr f = 0, p, q, par;
    p = root;
    while(p != &nil){
        if(data.lf == p->ep && data.le == p->fp) break;
        f = p;
        if(area(f->fp, f->ep, data.le) > 0) p = p->lson;
        else                                p = p->rson;
    }
    
    par = f;
    if(p == &nil) return 0;
    
    if(p->lson == &nil || p->rson == &nil){ //子が１つ
        if(p->lson == &nil) q = p->rson;
        else                q = p->lson;
        if(f->lson == p)    f->lson = q;
        q->parent = f;
        return q;
    }else{                                  //子が2つ
        q = p->rson;
        f = q;
        while(q->lson != &nil){
            f = q;
            q = q->lson;
        }
        p->fp = q->fp;
        p->ep = q->ep;
        if(q == f){
            p->rson = q->rson;
            p->parent = par;
            return p;
        }
        else{
            f->lson = q->rson;
            f->parent = par;
            return f;
        }
    }

    return 0;
}
