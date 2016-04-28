//
//  create_linesegment.cpp
//  Bentley-Ottmann
//
//  Created by KentaYamagishi on 2016/04/25.
//  Copyright © 2016年 KentaYamagishi. All rights reserved.
//

#include "create_linesegment.hpp"

cv::Mat img, tmp_img;

Line_Segment::Line_Segment(int _firstx, int _firsty, int _endx, int _endy){
    first_point = cv::Point2i(_firstx, _firsty);
    end_point = cv::Point2i(_endx, _endy);
}

cv::Point2i Line_Segment::get_first_point(){
    return first_point;
}

cv::Point2i Line_Segment::get_end_point(){
    return end_point;
}

std::vector<Line_Segment> cleate_line(){
    std::vector<Line_Segment> line;
    line.push_back(Line_Segment(100, 400, 300, 150));   // A
    line.push_back(Line_Segment(250, 450, 130, 100));   // B
    line.push_back(Line_Segment(200, 650, 400, 350));   // C
    line.push_back(Line_Segment(350, 330, 630, 220));   // D 1->350
    line.push_back(Line_Segment(410, 250, 500, 370));   // E
    line.push_back(Line_Segment(380, 120, 600, 150));   // F
    line.push_back(Line_Segment(430, 600, 650, 330));   // G
    
    return line;
}

void draw_line(std::vector<Line_Segment> line){
    img = cv::Mat::zeros(700, 700, CV_8UC3);
    
    for(int i = 0; i < line.size(); i++){
        cv::line(img, line[i].get_first_point(), line[i].get_end_point(), cv::Scalar(0,0,200), 2, 4);
        cv::circle(img, line[i].get_first_point(), 8, cv::Scalar(0,200,200), -1);
        cv::circle(img, line[i].get_end_point(), 8, cv::Scalar(0,200,200), -1);
    }
    cv::imshow("drawing", img);
    img.copyTo(tmp_img);
}

void draw_intersection(cv::Point2i intersection){
    cv::Mat img = tmp_img;
    cv::circle(img, intersection, 8, cv::Scalar(0, 200, 0), -1);    //緑色の円を描画
    cv::imshow("drawing", img);
    img.copyTo(tmp_img);
}

void draw_LineScanning(int y){
    cv ::Mat img;
    tmp_img.copyTo(img);
    if(y != 0) cv::line(img, cv::Point2i(0, y), cv::Point2i(700, y), cv::Scalar(200,200,0), 2, 4);
    cv::imshow("drawing", img);
}