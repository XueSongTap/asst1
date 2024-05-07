// Define vector unit width here
#define VECTOR_WIDTH 4

#ifndef CS149INTRIN_H_
#define CS149INTRIN_H_

#include <cstdlib>
#include <cmath>
#include "logger.h"

//*******************
//* Type Definition *
//*******************

extern Logger CS149Logger;
//这是一个通用的向量类型模板，其中包含了 VECTOR_WIDTH 个 T 类型的元素。
template <typename T>
struct __cs149_vec {
  T value[VECTOR_WIDTH];
};

// Declare a mask with __cs149_mask
//这是一个特殊的向量类型，其元素类型为布尔值 bool，用于表示向量中的每个元素的活动状态（即是否为有效数据）。
struct __cs149_mask : __cs149_vec<bool> {};
//__cs149_vec_float 和 __cs149_vec_int：这些宏定义了浮点数和整数类型的向量寄存器。
// Declare a floating point vector register with __cs149_vec_float
#define __cs149_vec_float __cs149_vec<float>

// Declare an integer vector register with __cs149_vec_int
#define __cs149_vec_int   __cs149_vec<int>

//***********************
//* Function Definition *
//***********************
//_cs149_init_ones(int first = VECTOR_WIDTH)：初始化一个掩码，其中前 first 个元素为1，其余元素为0。
// Return a mask initialized to 1 in the first N lanes and 0 in the others
__cs149_mask _cs149_init_ones(int first = VECTOR_WIDTH);
//_cs149_mask_not(__cs149_mask &maska)：返回掩码 maska 的逻辑非。
// Return the inverse of maska
__cs149_mask _cs149_mask_not(__cs149_mask &maska);
//_cs149_mask_or(__cs149_mask &maska, __cs149_mask &maskb)：返回两个掩码 maska 和 maskb 的逻辑或。
// Return (maska | maskb)
__cs149_mask _cs149_mask_or(__cs149_mask &maska, __cs149_mask &maskb);
//_cs149_mask_and(__cs149_mask &maska, __cs149_mask &maskb)：返回两个掩码 maska 和 maskb 的逻辑与。
// Return (maska & maskb)
__cs149_mask _cs149_mask_and(__cs149_mask &maska, __cs149_mask &maskb);

// Count the number of 1s in maska
//_cs149_cntbits(__cs149_mask &maska)：计算掩码 maska 中为1的位数。
int _cs149_cntbits(__cs149_mask &maska);

// Set register to value if vector lane is active
//  otherwise keep the old value
//_cs149_vset_float/__cs149_vset_int：根据掩码设置向量寄存器中的值，如果向量中的对应元素被激活，则设置为指定值，否则保持原值。
void _cs149_vset_float(__cs149_vec_float &vecResult, float value, __cs149_mask &mask);
void _cs149_vset_int(__cs149_vec_int &vecResult, int value, __cs149_mask &mask);
// For user's convenience, returns a vector register with all lanes initialized to value
__cs149_vec_float _cs149_vset_float(float value);
__cs149_vec_int _cs149_vset_int(int value);

// Copy values from vector register src to vector register dest if vector lane active
// otherwise keep the old value
//_cs149_vmove_float/__cs149_vmove_int：根据掩码从一个向量寄存器复制值到另一个向量寄存器。
void _cs149_vmove_float(__cs149_vec_float &dest, __cs149_vec_float &src, __cs149_mask &mask);
void _cs149_vmove_int(__cs149_vec_int &dest, __cs149_vec_int &src, __cs149_mask &mask);

// Load values from array src to vector register dest if vector lane active
//  otherwise keep the old value
//_cs149_vload_float/__cs149_vload_int：根据掩码从数组中加载值到向量寄存器。
void _cs149_vload_float(__cs149_vec_float &dest, float* src, __cs149_mask &mask);
void _cs149_vload_int(__cs149_vec_int &dest, int* src, __cs149_mask &mask);

// Store values from vector register src to array dest if vector lane active
//  otherwise keep the old value
//_cs149_vstore_float/__cs149_vstore_int：根据掩码将向量寄存器的值存储到数组中。
void _cs149_vstore_float(float* dest, __cs149_vec_float &src, __cs149_mask &mask);
void _cs149_vstore_int(int* dest, __cs149_vec_int &src, __cs149_mask &mask);

// Return calculation of (veca + vecb) if vector lane active
//  otherwise keep the old value
void _cs149_vadd_float(__cs149_vec_float &vecResult, __cs149_vec_float &veca, __cs149_vec_float &vecb, __cs149_mask &mask);
void _cs149_vadd_int(__cs149_vec_int &vecResult, __cs149_vec_int &veca, __cs149_vec_int &vecb, __cs149_mask &mask);

// Return calculation of (veca - vecb) if vector lane active
//  otherwise keep the old value
void _cs149_vsub_float(__cs149_vec_float &vecResult, __cs149_vec_float &veca, __cs149_vec_float &vecb, __cs149_mask &mask);
void _cs149_vsub_int(__cs149_vec_int &vecResult, __cs149_vec_int &veca, __cs149_vec_int &vecb, __cs149_mask &mask);

// Return calculation of (veca * vecb) if vector lane active
//  otherwise keep the old value
void _cs149_vmult_float(__cs149_vec_float &vecResult, __cs149_vec_float &veca, __cs149_vec_float &vecb, __cs149_mask &mask);
void _cs149_vmult_int(__cs149_vec_int &vecResult, __cs149_vec_int &veca, __cs149_vec_int &vecb, __cs149_mask &mask);

// Return calculation of (veca / vecb) if vector lane active
//  otherwise keep the old value
void _cs149_vdiv_float(__cs149_vec_float &vecResult, __cs149_vec_float &veca, __cs149_vec_float &vecb, __cs149_mask &mask);
void _cs149_vdiv_int(__cs149_vec_int &vecResult, __cs149_vec_int &veca, __cs149_vec_int &vecb, __cs149_mask &mask);


// Return calculation of absolute value abs(veca) if vector lane active
//  otherwise keep the old value
void _cs149_vabs_float(__cs149_vec_float &vecResult, __cs149_vec_float &veca, __cs149_mask &mask);
void _cs149_vabs_int(__cs149_vec_int &vecResult, __cs149_vec_int &veca, __cs149_mask &mask);

// Return a mask of (veca > vecb) if vector lane active
//  otherwise keep the old value
void _cs149_vgt_float(__cs149_mask &vecResult, __cs149_vec_float &veca, __cs149_vec_float &vecb, __cs149_mask &mask);
void _cs149_vgt_int(__cs149_mask &vecResult, __cs149_vec_int &veca, __cs149_vec_int &vecb, __cs149_mask &mask);

// Return a mask of (veca < vecb) if vector lane active
//  otherwise keep the old value
void _cs149_vlt_float(__cs149_mask &vecResult, __cs149_vec_float &veca, __cs149_vec_float &vecb, __cs149_mask &mask);
void _cs149_vlt_int(__cs149_mask &vecResult, __cs149_vec_int &veca, __cs149_vec_int &vecb, __cs149_mask &mask);

// Return a mask of (veca == vecb) if vector lane active
//  otherwise keep the old value
void _cs149_veq_float(__cs149_mask &vecResult, __cs149_vec_float &veca, __cs149_vec_float &vecb, __cs149_mask &mask);
void _cs149_veq_int(__cs149_mask &vecResult, __cs149_vec_int &veca, __cs149_vec_int &vecb, __cs149_mask &mask);

// Adds up adjacent pairs of elements, so
//  [0 1 2 3] -> [0+1 0+1 2+3 2+3]
//_cs149_hadd_float：对浮点数向量执行水平加法，即将相邻的元素相加。
void _cs149_hadd_float(__cs149_vec_float &vecResult, __cs149_vec_float &vec);

// Performs an even-odd interleaving where all even-indexed elements move to front half
//  of the array and odd-indexed to the back half, so
//  [0 1 2 3 4 5 6 7] -> [0 2 4 6 1 3 5 7]
//_cs149_interleave_float：对浮点数向量执行交错操作，即将奇数索引的元素移到前半部分，偶数索引的元素移到后半部分。\
void _cs149_interleave_float(__cs149_vec_float &vecResult, __cs149_vec_float &vec);

// Add a customized log to help debugging
void addUserLog(const char * logStr);

#endif
