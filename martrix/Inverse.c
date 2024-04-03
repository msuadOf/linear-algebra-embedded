/* 作者：积石息土
链接：https://www.zhihu.com/question/519541655/answer/2378665834
来源：知乎
著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。

https://github.com/dianjixz/Morn
 */
int mMatrixInverse(MMatrix *mat,MMatrix *inv)
{
    int i,j,k;
    mException((INVALID_MAT(mat)),EXIT,"invalid input");
    int num = mat->row;mException((mat->col != num),EXIT,"invalid operate");
    
    double **data = (double **)mMalloc( num *sizeof(double *));
    double *pdata = (double * )mMalloc((num+num+3)*num*sizeof(double));
    for(j=0;j<num;j++)
    {
        data[j]=pdata+(num+num+3)*j;
        for(i=0;i<num;i++) data[j][i] = (double)(mat->data[j][i]);
        memset(data[j]+num,0,(num+3)*sizeof(double));data[j][num+j]=-1.0;
    }
    
    for(k=0;k<num;k++)
    {
        if(data[k][k]==0)
        {
            for(j=k+1;j<num;j++){if(data[j][k]!=0){double *buff = data[k]; data[k]=data[j]; data[j]=buff; break;}}
            if(j==num) {mFree(data);mFree(pdata);return 0;}
        }
        
        for(j=k+1;j<num;j++)
        {
            if(data[j][k]==0) continue;
            double w = data[j][k]/data[k][k];
            for(i=k+1;i<num+num;i+=4)
            {
                data[j][i  ]-=w*data[k][i  ];
                data[j][i+1]-=w*data[k][i+1];
                data[j][i+2]-=w*data[k][i+2];
                data[j][i+3]-=w*data[k][i+3];
            }
        }
    }

    MMatrix *p = inv;
    if((INVALID_POINTER(inv))||(inv == mat)) inv = mMatrixCreate(num,num+3,NULL);
    else mMatrixRedefine(inv,num,num+3,inv->data);
    
    for(j=num-1;j>=0;j--)for(k=num;k<num+num;k+=4)
    {
        data[j][k  ]=0-data[j][k  ];
        data[j][k+1]=0-data[j][k+1];
        data[j][k+2]=0-data[j][k+2];
        data[j][k+3]=0-data[j][k+3];
        for(i=j+1;i<num;i++)
        {
            data[j][k  ]-=data[j][i]*data[i][k  ];
            data[j][k+1]-=data[j][i]*data[i][k+1];
            data[j][k+2]-=data[j][i]*data[i][k+2];
            data[j][k+3]-=data[j][i]*data[i][k+3];
        }
        data[j][k  ] /= data[j][j];inv->data[j][k  -num] = (float)data[j][k  ];
        data[j][k+1] /= data[j][j];inv->data[j][k+1-num] = (float)data[j][k+1];
        data[j][k+2] /= data[j][j];inv->data[j][k+2-num] = (float)data[j][k+2];
        data[j][k+3] /= data[j][j];inv->data[j][k+3-num] = (float)data[j][k+3];
    }
    
    mFree(pdata);mFree(data);
    if(p!=inv){mObjectExchange(inv,mat,MMatrix);mMatrixRelease(inv);}
    inv->col=num;
    return 1;
}
