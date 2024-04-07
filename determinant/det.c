#include "det.h"
#include "libcapi.h"

static void det_map(struct det_t *det, det_num_t (*callback)(int row, int col))
{
    for (int i = 0; i < det->order; i++)
    {
        for (int j = 0; j < det->order; j++)
        {
            det_setbyIndex(det,i+1,j+1, callback(i + 1, j + 1) );
        }
    }
}
/* 入参要一个二维数组 */
det_t *det_create(det_num_t *con, int order)
{
    det_t *det = malloc(sizeof(det_t));
    unsigned int byte_size = sizeof(det_num_t) * (order) * (order);
    det->con = malloc(byte_size);
    if(con==det_NULL){
memset((void *)det->con, 0, byte_size);
    }
    else{
        memcpy((void *)det->con, (void *)con, byte_size);
    }
    det->order = order;

    /* 高级编程特性 */
    det->map = det_map;
    return det;
}

void det_del(det_t *det)
{
    free(det->con);
    free(det);
}
det_num_t* det_byIndex(det_t *det, int row, int col)
{
    // libcapi_printf("[debug]row=%d,col=%d,order=%d\n",row,col,det->order);
    libcapi_assert(col <= det->order);
    libcapi_assert(row <= det->order);
    return &(det->con[(row - 1) * (det->order) + (col - 1)]);
}
// det_num_t det_getbyIndex(det_t *det, int row, int col)
// {
//     libcapi_printf("[debug]row=%d,col=%d,order=%d\n",row,col,det->order);
//     libcapi_assert(col <= det->order);
//     libcapi_assert(row <= det->order);
//     return det->con[(row - 1) * (det->order) + (col - 1)];
// }
void det_setbyIndex(det_t *det, int row, int col,det_num_t value)
{
    // libcapi_printf("[debug]row=%d,col=%d,order=%d\n",row,col,det->order);
    libcapi_assert(col <= det->order);
    libcapi_assert(row <= det->order);
    det->con[(row - 1) * (det->order) + (col - 1)]=value;
}
void det_print(det_t *det)
{
    libcapi_printf("det[%d]:\n", (int)det->order);
    for (int i = 0; i < det->order; i++)
    {
        for (int j = 0; j < det->order; j++)
        {
            libcapi_printf(DET_NUM_FMT " ", det_getbyIndex(det, i + 1, j + 1));
        }
        libcapi_printf("%c", '\n');
    }
}