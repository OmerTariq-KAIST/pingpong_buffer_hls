############################################################
## This file is generated automatically by Vitis HLS.
## Please DO NOT edit it.
## Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
############################################################
open_project foo
set_top diamond
add_files foo.cpp
add_files foo.h
add_files -tb foo_test.cpp
add_files -tb result.golden.dat
open_solution "solution1" -flow_target vivado
set_part {xczu7ev-ffvc1156-2-e}
create_clock -period 10 -name default
config_export -format ip_catalog -output /media/omer/52A00DEFA00DDA7D/KAIST/MS-PhD/Projects/Vitis_HLS_Projects/My_Projects/Tutorials/foo -rtl verilog
#source "./foo/solution1/directives.tcl"
csim_design
csynth_design
cosim_design
export_design -rtl verilog -format ip_catalog -output /media/omer/52A00DEFA00DDA7D/KAIST/MS-PhD/Projects/Vitis_HLS_Projects/My_Projects/Tutorials/foo
