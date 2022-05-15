#pragma once
#include <iostream>
#include <d3d12.h>
#include <d3dx12.h>
#include <DirectXMath.h>
#include <DirectXTex.h>
#include <d3dcompiler.h>
#include <wrl.h>

using namespace DirectX;
using namespace Microsoft::WRL;
using namespace std;

#pragma comment(lib, "d3d12.lib")
#pragma comment(lib, "d3dcompiler.lib")

//�X�v���C�g�p���f�����_�\����
typedef struct SpriteVertex
{
	XMFLOAT3 pos;
	XMFLOAT2 uv;
}SPVertex;

//�X�v���C�g�p�C���X�^���X�\���̕`�悷����̂��ꂼ��̍����f�[�^
typedef struct SpriteInstance
{
	XMMATRIX worldmat;	//���[���h�ϊ��s��
	XMFLOAT2 drawsize;	//�c����
	XMFLOAT4 uvOffset;	//uv�l
	XMFLOAT4 color;
};

//�萔�o�b�t�@�f�[�^�\����
typedef struct SpConstBufferData
{
	XMFLOAT4 color;//�F(rgba)
	XMMATRIX mat;
}SPConstBuffer;

//�X�v���C�g�ꖇ���̃f�[�^
typedef struct SpriteData
{
	//���_���W�i��_�݂̂ɂ��āA�W�I���g���ōׂ����R���g���[��������j
	SpriteVertex vertice;
	//�C���X�^���X�s��R���e�i�i�����f�[�^���i�[�F�A�t�B���ϊ������邵�A�����ɏc�����̃f�[�^����Ă����������j
	std::vector<SpriteInstance> insWorldMatrixes;

	ComPtr<ID3D12Resource> vertBuff;//���f���p���_�o�b�t�@
	D3D12_VERTEX_BUFFER_VIEW vbView;//���f���p���_�o�b�t�@�r���[

	ComPtr<ID3D12Resource> vertInsBuff;	//�C���X�^���X�p���_�o�b�t�@
	D3D12_VERTEX_BUFFER_VIEW vibView;	//�C���X�^���X�p���_�o�b�t�@�r���[

	ComPtr<ID3D12Resource> constBuff;//�萔�o�b�t�@
	UINT texNumber;//�}�l�[�W���[�ɕۑ����ꂽ���\�[�X�̔ԍ�

	XMFLOAT2 size;//�X�v���C�g�T�C�Y

	float rotation = 0.0f;//z����]�p
	XMFLOAT3 position = { 0.0f,0.0f,0.0f };//���W
	XMMATRIX matWorld;//���[���h�ϊ��s��

	XMFLOAT2 anchorPoint = { 0.0f,0.0f };//�A���J�[�|�C���g

	XMFLOAT2 screenPos = { 0.0f,0.0f };//�X�N���[�����W

	XMFLOAT4 color = { 1.0f,1.0f,1.0f,1.0f };

	//uv�I�t�Z�b�g�R���e�i
	std::vector<XMFLOAT4> uvOffsets;

	SpriteData()
	{

	}
	~SpriteData(){
		insWorldMatrixes.clear();
		insWorldMatrixes.shrink_to_fit();
	}

}SPData;

//�X�v���C�g���ʊǗ��N���X
//Winmain�ł�spritemanager�̎��̂�1�̂ݍ�邱�ƁI
class SpriteManager
{
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;

private:
	//�X�v���C�g�p�O���t�B�b�N�X�p�C�v���C���Z�b�g
	ComPtr<ID3D12PipelineState> pipelinestate;
	ComPtr<ID3D12RootSignature> rootsignature;

	//�}���`�p�X�G�t�F�N�g�p�O���t�B�N�X�p�C�v���C���Z�b�g
	ComPtr<ID3D12PipelineState> mpPipeline;
	ComPtr<ID3D12RootSignature> mpRootsig;

	SpriteManager(int window_width, int window_height) {
		//�r���[�|�[�g�s�񏉊���
		matViewport.r[0].m128_f32[0] = window_width / 2;
		matViewport.r[1].m128_f32[1] = -window_height / 2;
		matViewport.r[3].m128_f32[0] = window_width / 2;
		matViewport.r[3].m128_f32[1] = window_height / 2;
		//�p�C�v���C������
		CreateSpritePipeline();
	};
	SpriteManager() {};
	~SpriteManager() {};

public: 
	//���ʃr���[�|�[�g�s��
	XMMATRIX matViewport{};

	void CreateSpriteManager(ID3D12Device *dev, ID3D12GraphicsCommandList *cmd, int window_w, int window_h);
	//�X�v���C�g�̃O���t�B�b�N�X�p�C�v���C���𐶐�
	void CreateSpritePipeline();
	//�X�v���C�g���ʂ̃O���t�B�b�N�X�R�}���h���Z�b�g
	void SetCommonBeginDraw();
	//�}���`�p�X���\�[�X�`��p�O���t�B�N�X�R�}���h
	void SetCommonBeginDrawmpResource();

	//�C���X�^���X�擾
	static SpriteManager *Get() {
		static SpriteManager mgr;
		return &mgr;
	}

	//�`��ɕK�v�ȃ|�C���^
	ID3D12Device *dev;
	ID3D12GraphicsCommandList *cmd;

	//�R�s�[�R���X�g���N�^�A������Z�q������
	SpriteManager &operator=(const SpriteManager &obj) = delete;
	SpriteManager(const SpriteManager &obj) = delete;

};

