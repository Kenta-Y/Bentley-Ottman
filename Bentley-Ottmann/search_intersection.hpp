//
//  search_intersection.hpp
//  Bentley-Ottmann
//
//  Created by KentaYamagishi on 2016/04/25.
//  Copyright © 2016年 KentaYamagishi. All rights reserved.
//

#ifndef search_intersection_hpp
#define search_intersection_hpp

#include <opencv2/opencv.hpp>
#include "create_linesegment.hpp"

typedef cv::Point2i datatype;

typedef struct node{
    cv::Point2i fp, ep;
    struct node *lson, *rson, *parent;
} *nodeptr;

struct element{
    cv::Point2i lf, le;
    struct node *IA, *IB;
};

int area(cv::Point2i q1, cv::Point2i q2, cv::Point2i q3);
int between(cv::Point2i p1, cv::Point2i p2, cv::Point2i p3);
int intersect(cv::Point2i a, cv::Point2i b, cv::Point2i c, cv::Point2i d);

int node_init();
nodeptr insert_point(element data);
nodeptr delete_point(element data);

#endif /* search_intersection_hpp */