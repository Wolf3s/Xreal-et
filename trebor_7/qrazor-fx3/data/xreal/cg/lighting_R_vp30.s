!!VP2.0
# NV_vertex_program generated by NVIDIA Cg compiler
# cgc version 1.2.1001, build date Mar 17 2004  10:58:07
# command line args: -profile vp30
# nv30vp backend compiling 'main' program
#vendor NVIDIA Corporation
#version 1.0.02
#profile vp30
#program main
#semantic main.matrix_model_view_projection
#semantic main.matrix_texture0
#semantic main.matrix_texture1
#semantic main.matrix_texture2
#semantic main.matrix_model
#var float4x4 matrix_model_view_projection :  : c[0], 4 : 1 : 1
#var float4x4 matrix_texture0 :  : c[4], 4 : 2 : 1
#var float4x4 matrix_texture1 :  : c[8], 4 : 3 : 1
#var float4x4 matrix_texture2 :  : c[12], 4 : 4 : 1
#var float4x4 matrix_model :  : c[16], 4 : 5 : 1
#var float4 IN.position : $vin.POSITION : ATTR0 : 0 : 1
#var float3 IN.normal : $vin.NORMAL : ATTR2 : 0 : 1
#var float4 IN.tex0 : $vin.TEXCOORD0 : ATTR8 : 0 : 1
#var float4 IN.tex1 : $vin.TEXCOORD1 : ATTR9 : 0 : 1
#var float4 main.position : $vout.POSITION : HPOS : -1 : 1
#var float3 main.normal : $vout.TEXCOORD0 : TEX0 : -1 : 1
#var float4 main.tex_diffuse : $vout.TEXCOORD1 : TEX1 : -1 : 1
#var float4 main.tex_light : $vout.TEXCOORD2 : TEX2 : -1 : 1
#var float4 main.tex_deluxe : $vout.TEXCOORD3 : TEX3 : -1 : 1
#const c[20] = 0 1 2 0
b0:
	DP4 o[HPOS].x, c[0], v[0];
	DP4 o[HPOS].y, c[1], v[0];
	DP4 o[HPOS].z, c[2], v[0];
	DP4 o[HPOS].w, c[3], v[0];
	DP3 o[TEX0].x, c[16].xyzx, v[2].xyzx;
	DP3 o[TEX0].y, c[17].xyzx, v[2].xyzx;
	DP3 o[TEX0].z, c[18].xyzx, v[2].xyzx;
	DP4 o[TEX1].x, c[4], v[8];
	DP4 o[TEX1].y, c[5], v[8];
	DP4 o[TEX1].z, c[6], v[8];
	DP4 o[TEX1].w, c[7], v[8];
	DP4 o[TEX2].x, c[8], v[9];
	DP4 o[TEX2].y, c[9], v[9];
	DP4 o[TEX2].z, c[10], v[9];
	DP4 o[TEX2].w, c[11], v[9];
	DP4 o[TEX3].x, c[12], v[9];
	DP4 o[TEX3].y, c[13], v[9];
	DP4 o[TEX3].z, c[14], v[9];
	DP4 o[TEX3].w, c[15], v[9];
END
# 19 instructions
# 0 temp registers
# End of program
