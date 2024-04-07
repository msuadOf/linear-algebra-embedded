#include "det.h"
// 计算2x2行列式的值
static det_num_t det_2x2(det_t *det)
{
    det_num_t a = det_getbyIndex(det, 1, 1);
    det_num_t b = det_getbyIndex(det, 1, 2);
    det_num_t c = det_getbyIndex(det, 2, 1);
    det_num_t d = det_getbyIndex(det, 2, 2);
    return a * d - b * c;
}

// 计算3x3行列式的值
static det_num_t det_3x3(det_t *det)
{
    det_num_t a = det_getbyIndex(det, 1, 1);
    det_num_t b = det_getbyIndex(det, 1, 2);
    det_num_t c = det_getbyIndex(det, 1, 3);
    det_num_t d = det_getbyIndex(det, 2, 1);
    det_num_t e = det_getbyIndex(det, 2, 2);
    det_num_t f = det_getbyIndex(det, 2, 3);
    det_num_t g = det_getbyIndex(det, 3, 1);
    det_num_t h = det_getbyIndex(det, 3, 2);
    det_num_t i = det_getbyIndex(det, 3, 3);

    // 根据3x3行列式的计算公式计算行列式的值
    return a * (e * i - f * h) - b * (d * i - f * g) + c * (d * h - e * g);
}
// 创建一个行列式的子矩阵，删除了指定的行和列
 det_t *det_createMinor(det_t *det, int delRow, int delCol) {
    // 分配新行列式的内存
    int newOrder = det->order - 1;
    det_t *minor = det_create(NULL, newOrder);
    if (!minor) {
        return NULL;
    }

    // 复制数据到子矩阵，跳过要删除的行和列
    for (int row = 1; row <= newOrder; ++row) {
        for (int col = 1; col <= newOrder; ++col) {
            int srcRow = row + (row >= delRow ? 1 : 0);
            int srcCol = col + (col >= delCol ? 1 : 0);
            det_num_t value = det_getbyIndex(det, srcRow, srcCol);
            det_setbyIndex(minor, row, col, value);
        }
    }

    return minor;
}
// 递归计算行列式的值
det_num_t det_calc_laplace(det_t *det)
{
    if (det->order == 2) {
        return det_2x2(det);
    }  else {
        // 对于更高阶的行列式，这里使用一个简化的拉普拉斯展开方法
        det_num_t minorSum = 0;
        for (int i = 1; i <= det->order; ++i) {
            // 递归计算主子式的行列式值
            det_t* MinorDet=det_createMinor(det, 1, i);
            det_num_t minorDet_val = det_calc_laplace(MinorDet);
            det_del(MinorDet);
            // 根据i的奇偶性来确定正负号
            minorSum += ((i % 2 == 0) ? 1 : -1) * minorDet_val * det_getbyIndex(det, 1, i);
        }
        return minorSum;
    }
}


