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

typedef struct element{
    cv::Point2i p1, p2;
    element *next;
} *elementptr;

typedef struct node{
    cv::Point v;
    struct node *lson, *rson;
} *nodeptr;

struct BothPoint{
    cv::Point2i first_point;
    cv::Point2i end_point;
};

int node_init();
int insert_point(datatype data);
int delete_point(datatype data);
int insert_element(datatype first, datatype end);

void treeInterval(nodeptr p, int x1, int x2, int y);
void sweep(elementptr head, nodeptr root);
void QuickSort(std::vector<BothPoint> &array, int begin, int end);
void sort_y(std::vector<Line_Segment> line);

#endif /* search_intersection_hpp */