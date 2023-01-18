//simple fifo's design to check dataflow model (Control-driven TLP)
#include "foo.h"

//vec_in and vec_out are non-local memories

void diamond(data_t vec_in[N], data_t vec_out[N])
{
	data_t c1[N], c2[N], c3[N], c4[N];
#pragma HLS DATAFLOW
	funcA(vec_in, c1, c2);
	funcB(c1, c3); //funcC and funcD have no data dependencies bw them
	funcC(c2, c4);
	funcD(c3, c4, vec_out);

}

void funcA(data_t *in, data_t *out1, data_t *out2)
{
	#pragma HLS INLINE
	LOOP0:
	for(int i=0; i<N; i++)
	{
	#pragma HLS PIPELINE
		data_t t = in[i] * 3;
		out1[i] = t;
		out2[i] = t;
	}
}

void funcB(data_t *in, data_t *out)
{
#pragma HLS inline
Loop0:
  for (int i = 0; i < N; i++)
  {
#pragma HLS pipeline
    out[i] = in[i] + 25;
  }
}

void funcC(data_t *in, data_t *out)
{
#pragma HLS inline
Loop0:
  for (data_t i = 0; i < N; i++)
  {
#pragma HLS pipeline
    out[i] = in[i] * 2;
  }
}

void funcD(data_t *in1, data_t *in2, data_t *out)
{
#pragma HLS inline
Loop0:
  for (int i = 0; i < N; i++)
  {
#pragma HLS pipeline
    out[i] = in1[i] + in2[i] * 2;
  }
}


