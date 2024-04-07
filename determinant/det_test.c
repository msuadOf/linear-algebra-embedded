#include <stdio.h>
#include "det.h"

int main(){
    printf("as\n");
    det_t* det=det_create(
        (det_num_t []){
            1,4,-1,4,
            2,2,2,3,
            3,-1,6,2,
            4,0,5,3
        },
        4
    );
    det_print(det);
    int a = det_calc_laplace(det);
    printf("a=%d\n",a);
    det_t* d=det_createMinor(det,1,2);
    det_print(d);
    det_del(det);
    return 0;
}