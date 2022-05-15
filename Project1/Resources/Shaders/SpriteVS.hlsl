#include "Sprite.hlsli"

//�X�v���C�g�̓��͂�1���_�̂�
VSOutput main(float4 pos : POSITION, float2 uv : TEXCOORD,
matrix instanceMatrix : INSTANCE_WORLD_MAT,
float2 size : INSTANCE_DRAWSIZE,
float4 uvOffset : INSTANCE_UVOFFSET,
float4 color : INSTANCE_COLOR)
{
	VSOutput output;
    output.svpos = pos;
	output.uv = uv;
    output.ins_matrix = instanceMatrix;
    output.size = size;
    output.uvOffset = uvOffset;
    output.color = color;
	return output;
}