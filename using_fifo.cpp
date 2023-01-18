//using fifo's (Control-driven TLP)
#include "foo.h"
#define WORD 16

//to link C dependencies
extern "C"{
void diamond(vec_16_words *vec_in, vec_16_words *vec_out, int size)
{
	//define the interfaces for input and output
#pragma HLS INTERFACE m_axi port=vec_in depth=32
#pragma HLS INTERFACE m_axi port=vec_out depth=32

	hls::stream<vec_16_words> c0, c1, c2, c3, c4, c5; //each 64 byte vector
	assert(size%16==0); //assertion added for size variable (completely divided by 16)


	//sub-functions wit interlinked dependencies calling into parent function
#pragma HLS DATAFLOW
	load(vec_in, c0, size);
	compute_A(c0, c1, c2, size);
	compute_B(c1, c3, size);
	compute_C(c2, c4, size);
	compute_D(c3, c4, c5, size);
	store(c5, vec_out, size);
}

}


void load(vec_16_words *in, hls::stream<vec_16_words>& out, int size ) //64 byte vector
{
	Loop_LD:
	for (int i=0; i<size; i++)
	{
#pragma HLS PERFORMANCE target_ti=32 // ti=target transaction interval
#pragma HLS LOOP_TRIPCOUNT max=32 //reporting
		out.write(in[i]);
	}
}

void compute_A(hls::stream<vec_16_words>& in, hls::stream<vec_16_words>& out1, hls::stream<vec_16_words>& out2, int size)
{
	Loop_A:
	for(int i=0; i<size; i++)
	{
#pragma HLS PERFORMANCE target_ti=32 // ti=target transaction interval
#pragma HLS LOOP_TRIPCOUNT max=32 //reporting
		vec_16_words t = in.read();
		out1.write(t * 3);
		out2.write(t * 3);
	}
}

void compute_B(hls::stream<vec_16_words>& in, hls::stream<vec_16_words>& out, int size)
{
	Loop_B:
	for(int i=0; i<size; i++)
		{
	#pragma HLS PERFORMANCE target_ti=32 // ti=target transaction interval
	#pragma HLS LOOP_TRIPCOUNT max=32 //reporting
			out.write(in.read() + 25);
		}

}
void compute_C(hls::stream<vec_16_words>& in, hls::stream<vec_16_words>& out, int size)
{
	Loop_C:
		for(data_t i=0; i<size; i++)
			{
		#pragma HLS PERFORMANCE target_ti=32 // ti=target transaction interval
		#pragma HLS LOOP_TRIPCOUNT max=32 //reporting
				out.write(in.read() * 2);
			}
}
void compute_D(hls::stream<vec_16_words>& in1, hls::stream<vec_16_words>& in2, hls::stream<vec_16_words>& out, int size)
{
	Loop_D:
	  for (data_t i = 0; i < size; i++)
	  {
	    #pragma HLS performance target_ti=32
	    #pragma HLS LOOP_TRIPCOUNT max=32
	    out.write(in1.read() + in2.read());
	  }

}
void store(hls::stream<vec_16_words>& in, vec_16_words *out, int size)
{
	Loop_ST:
	for(int i=0; i<size; i++)
	{
#pragma HLS performance target_ti=32
#pragma HLS LOOP_TRIPCOUNT max=32
		out[i] = in.read();

	}

}

