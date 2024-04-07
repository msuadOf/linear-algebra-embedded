#ifndef _DET_H
#include "libcapi.h"

typedef int det_num_t;
#define DET_NUM_FMT "%3d"

#define det_NULL 0
/* 行列式是什么？答得好，是数组，是二维数组 */
/* 其实和方阵一样 */
typedef struct det_t det_t;
struct det_t
{
    det_num_t *con;
    int order; /* 阶数 */
    void (*det_errorhandler)(det_t *this);
    void (*map)(det_t *this, det_num_t (*callback)(int row, int col));
};

det_t *det_create(det_num_t *con, int order);
void det_del(det_t *det);

det_num_t *det_byIndex(det_t *det, int row, int col);
// det_num_t det_getbyIndex(det_t *det, int row, int col);
void det_setbyIndex(det_t *det, int row, int col, det_num_t value);

void det_print(det_t *det);

det_t *det_createMinor(det_t *det, int delRow, int delCol);
det_num_t det_calc_laplace(det_t *det);

#define det_getbyIndex(det, row, col) (                                      \
    libcapi_printf("[debug]row=%d,col=%d,order=%d\n", row, col, det->order), \
    libcapi_assert(col <= det->order),                                       \
    libcapi_assert(row <= det->order),                                       \
    det->con[(row - 1) * (det->order) + (col - 1)])

#endif // !_DET_H