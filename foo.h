//using pipo's TLP Control Driven Design
#include <iostream>
typedef unsigned char data_t;
#define N 100

//Top function
void diamond(data_t vec_in[N], data_t vec_out[N]);



//declaring sub-functions prototypes
//formal variable as parameters to the function
void funcA(data_t a1_in[N],data_t a1_out1[N],data_t a1_out2[N]);
void funcC(data_t a3_in[N],data_t a3_out[N]);
void funcB(data_t a2_in[N],data_t a2_out[N]);
void funcD(data_t a4_in[N],data_t a4_out1[N], data_t a4_out2[N]);


