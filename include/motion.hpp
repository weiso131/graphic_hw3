#ifndef MOTION_HPP
#define MOTION_HPP
typedef struct motion {
    float rx;
    float ry;
    float rz;
    
    float sx;
    float sy;
    float sz;
    
    float tx;
    float ty;
    float tz;
    int speed_num; //決定當前子動作的完成度，數字越大越慢完成
} Motion;
#endif