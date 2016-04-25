//
//  create_linesegment.hpp
//  Bentley-Ottmann
//
//  Created by KentaYamagishi on 2016/04/25.
//  Copyright © 2016年 KentaYamagishi. All rights reserved.
//

#ifndef create_linesegment_hpp
#define create_linesegment_hpp

#include <opencv2/opencv.hpp>

class Line_Segment{
private:
    cv::Point2i first_point;
    cv::Point2i end_point;
public:
    Line_Segment(int _firstx, int _firsty, int _endx, int _endy);
    cv::Point2i get_first_point();
    cv::Point2i get_end_point();
};

std::vector<Line_Segment> cleate_line();
void draw_line(std::vector<Line_Segment> line);
void draw_intersection(cv::Point2i intersection);
void draw_LineScanning(int y);

#endif /* create_linesegment_hpp */