Texture2D<float4> tex : register(t0);
SamplerState smp : register(s0);

cbuffer cbuff0 : register(b0)
{
	float4 color;
	matrix mat;
};

//�X�v���C�g�̓��͂�1���_�݂̂ɂ���

//�X�v���C�g�o�͍\����
struct VSOutput
{
	//���_���
	float4 svpos : SV_POSITION;	//���_���W
	float2 uv    : TEXCOORD;	//UV���W
	//�C���X�^���X���
    matrix ins_matrix : INSTANCE_WORLD_MAT;	//�C���X�^���V���O�p�ϊ��s��
    float2 size       : INSTANCE_DRAWSIZE;
    float4 uvOffset   : INSTANCE_UVOFFSET;
    float4 color      : INSTANCE_COLOR;
};

//�W�I���g���o�͍\����
struct GSOutput
{
    float4 pos : SV_POSITION;	//�o�͒��_���W
    float2 uv  : TEXCOORD;		//�o��UV�l
    matrix ins_matrix : INSTANCE_WORLD_MAT;
    float2 size       : INSTANCE_DRAWSIZE;
    float4 uvOffset : INSTANCE_UVOFFSET;
    float4 color : INSTANCE_COLOR;
};