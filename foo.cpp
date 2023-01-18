
// © 17012023 Omer Tariq <omertariq@kaist.ac.kr>
//using PING PONG Buffers (PIPO Channel driven TLP)
//Note:“Vivado HLS supports pointers to pointers for synthesis but does not support them on the top-level interface, that is, as argument to the top-level function. If you use a pointer to pointer in multiple functions, Vivado HLS inlines all functions that use the pointer to pointer. Inlining multiple functions can increase run time.”
#include"foo.h"

void diamond(data_t vec_in[N], data_t vec_out[N])
{
	//instances of user-data type
	data_t a1[N], a2[N], a3[N], a4[N];


#pragma HLS DATAFLOW //linkage dependencies in parent-child functions
	funcA(vec_in, a1, a2);
	funcB(a1, a3);
	funcC(a2, a4);
	funcD(a3, a4, vec_out);
}


void funcA(data_t *in, data_t *out1, data_t *out2) //function parameters are pointers
{
	Loop0:
	for (int i=0; i<N; i++)
	{
#pragma HLS PIPELINE rewind
#pragma HLS UNROLL factor=2
		data_t t = in[i] * 3;
		out1[i] = t;
		out2[i] = t;
	}
}


void funcB(data_t *in, data_t *out)
{
	Loop0:
	for(int i=0; i<N; i++)
	{
#pragma HLS PIPELINE rewind
#pragma HLS UNROLL factor=2
		out[i] = in[i] + 25;
	}
}

void funcC(data_t *in, data_t *out)
{
	Loop0:
		for(int i=0; i<N; i++)
		{
	#pragma HLS PIPELINE rewind
	#pragma HLS UNROLL factor=2
			out[i] = in[i] * 2;
		}
}

void funcD(data_t *in1, data_t *in2, data_t *out)
{
	Loop0:
			for(int i=0; i<N; i++)
			{
		#pragma HLS PIPELINE rewind
		#pragma HLS UNROLL factor=2
				out[i] = in1[i] + in2[i] * 2;
			}
}
