!!ARBfp1.0
# ARB_fragment_program generated by NVIDIA Cg compiler
# cgc version 1.2.1001, build date Mar 17 2004  10:58:07
# command line args: -profile arbfp1
#vendor NVIDIA Corporation
#version 1.0.02
#profile arbfp1
#program main
#semantic main.diffusemap
#semantic main.bumpmap
#semantic main.heightmap
#semantic main.specularmap
#semantic main.attenuationmap_xy
#semantic main.attenuationmap_z
#semantic main.attenuationmap_cube
#semantic main.view_origin
#semantic main.light_origin
#semantic main.light_color
#semantic main.bump_scale
#semantic main.height_scale
#semantic main.height_bias
#semantic main.specular_exponent
#var sampler2D diffusemap :  : texunit 0 : 1 : 1
#var sampler2D bumpmap :  : texunit 1 : 2 : 1
#var sampler2D heightmap :  : texunit 2 : 3 : 1
#var sampler2D specularmap :  : texunit 3 : 4 : 1
#var sampler2D attenuationmap_xy :  : texunit 4 : 5 : 1
#var sampler2D attenuationmap_z :  : texunit 5 : 6 : 1
#var samplerCUBE attenuationmap_cube :  : texunit 6 : 7 : 1
#var float3 view_origin :  : c[3] : 8 : 1
#var float3 light_origin :  : c[6] : 9 : 1
#var float3 light_color :  : c[0] : 10 : 1
#var float bump_scale :  : c[5] : 11 : 1
#var float height_scale :  : c[1] : 12 : 1
#var float height_bias :  : c[2] : 13 : 1
#var float specular_exponent :  : c[4] : 14 : 1
#var float4 IN.position : $vin.TEXCOORD0 : TEX0 : 0 : 1
#var float4 IN.tex_diffuse_bump : $vin.TEXCOORD1 : TEX1 : 0 : 1
#var float4 IN.tex_height_spec : $vin.TEXCOORD2 : TEX2 : 0 : 1
#var float4 IN.tex_atten_xy_z : $vin.TEXCOORD3 : TEX3 : 0 : 1
#var float4 IN.tex_atten_cube : $vin.TEXCOORD4 : TEX4 : 0 : 1
#var float3 IN.tangent : $vin.TEXCOORD5 : TEX5 : 0 : 1
#var float3 IN.binormal : $vin.TEXCOORD6 : TEX6 : 0 : 1
#var float3 IN.normal : $vin.TEXCOORD7 : TEX7 : 0 : 1
#var float4 main.color : $vout.COLOR : COL : -1 : 1
PARAM u3 = program.local[3];
PARAM u6 = program.local[6];
PARAM u0 = program.local[0];
PARAM u5 = program.local[5];
PARAM u1 = program.local[1];
PARAM u2 = program.local[2];
PARAM u4 = program.local[4];
PARAM c0 = {2, 0.5, 0, 0};
TEMP R0;
TEMP R1;
TEMP R2;
TEMP R3;
TEMP R4;
TEMP R5;
TEMP R6;
TEMP R7;
TEX R0.x, fragment.texcoord[2], texture[2], 2D;
TEX R1.xyz, fragment.texcoord[3], texture[4], 2D;
ADD R2.xyz, u3, -fragment.texcoord[0];
DP3 R2.w, fragment.texcoord[5], R2;
MOV R3.x, R2.w;
DP3 R2.w, fragment.texcoord[6], R2;
MOV R3.y, R2.w;
DP3 R2.x, fragment.texcoord[7], R2;
MOV R3.z, R2.x;
DP3 R2.x, R3, R3;
RSQ R2.x, R2.x;
MUL R3.xyz, R2.x, R3;
MOV R2.x, u2.x;
MAD R2.x, R0.x, u1.x, R2.x;
MAD R0.xy, R2.x, R3, fragment.texcoord[1].zwzz;
TEX R0.xyz, R0, texture[1], 2D;
TEX R4.xyz, fragment.texcoord[4], texture[6], CUBE;
ADD R0.xyz, R0, -c0.y;
MUL R0.xyz, R0, c0.x;
ADD R5.xyz, u6, -fragment.texcoord[0];
DP3 R0.w, fragment.texcoord[5], R5;
MOV R6.x, R0.w;
DP3 R0.w, fragment.texcoord[6], R5;
MOV R6.y, R0.w;
DP3 R0.w, fragment.texcoord[7], R5;
MOV R6.z, R0.w;
MOV R5.xy, R0;
MUL R0.x, R0.z, u5.x;
MOV R5.z, R0.x;
DP3 R0.x, R6, R6;
RSQ R0.x, R0.x;
DP3 R0.y, R5, R5;
RSQ R0.y, R0.y;
MUL R5.xyz, R0.y, R5;
MAD R7.xyz, R0.x, R6, R3;
MUL R6.xyz, R0.x, R6;
DP3_SAT R0.x, R5, R6;
MUL R0.xyz, u0, R0.x;
DP3 R0.w, R7, R7;
RSQ R0.w, R0.w;
MUL R7.xyz, R0.w, R7;
DP3_SAT R0.w, R5, R7;
POW R0.w, R0.w, u4.x;
MAD R5.xy, R2.x, R3, fragment.texcoord[1];
MAD R3.xy, R2.x, R3, fragment.texcoord[2].zwzz;
TEX R2, R5, texture[0], 2D;
TEX R3.xyz, R3, texture[3], 2D;
MUL R0.xyz, R2, R0;
MUL R3.xyz, R3, u0;
MOV R2.xyz, R0;
MAD R0.xyz, R3, R0.w, R2;
MOV R2.xyz, R0;
MUL R0.xyz, R2, R1;
MOV R1.x, fragment.texcoord[3].z;
MOV R1.y, c0.w;
TEX R1.xyz, R1, texture[5], 2D;
MOV R2.xyz, R0;
MUL R0.xyz, R2, R1;
MOV R2.xyz, R0;
MUL R0.xyz, R2, R4;
MOV R2.xyz, R0;
MOV result.color, R2;
END
# 62 instructions, 8 R-regs, 0 H-regs.
# End of program
