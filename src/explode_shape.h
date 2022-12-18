// 本头文件用于存储各种烟花爆炸模型的顶点
// float* vertices_arr[] 存储各个模型顶点数组的首地址
// int vertices_num[]  存储各个模型顶点数组的顶点数量
// 下标需要与 particle.h 中的 enum fireworktype { } 对应

#ifndef __EXPLODE_SHAPE_H__
#define __EXPLODE_SHAPE_H__

extern float* vertices_arr[];
extern int vertices_num[];
//int vertices_num[] = { 0, 0, 317 / 3, 500 / 3, 2000 / 3 };
#endif