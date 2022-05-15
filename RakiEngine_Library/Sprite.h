#pragma once
#include <memory>

#include "SpriteManager.h"
#include "NY_Camera.h"
#include "TexManager.h"

class Sprite
{
public:
	//�X�v���C�g�ꖇ�̏��
	std::unique_ptr<SpriteData> spdata;
	//uv�I�t�Z�b�g�n���h���i����𑝌������邱�Ƃŕ�������uv�l��K�p�\�j
	int uvOffsetHandle = 0;

public:
	//�X�v���C�g�����i���̐������ɋN���ł����H�j(�f�o�C�X�A�X�v���C�g�T�C�Y�A���\�[�X�ԍ��A�A���J�[�|�C���g�A�X�v���C�g�}�l�[�W���[�|�C���^)
	Sprite(XMFLOAT2 size,UINT resourceID, bool adjustResourceFlag = false,XMFLOAT2 anchor = { 0.0f,0.0f })
	{
		//�X�v���C�g����
		CreateSprite(size, anchor, resourceID, adjustResourceFlag, nullptr);
	};
	//�����Ȃ��i�ʂŏ������j
	Sprite();
	~Sprite();

	static void SetSpriteColorParam(float r, float g, float b, float a);

	/// <summary>
	/// �`��̂��ƂɂȂ�X�v���C�g�f�[�^����
	/// </summary>
	/// <param name="resourceID">�e�N�X�`���n���h��</param>
	/// <param name="sizeX">�`��T�C�Y</param>
	/// <param name="sizeY">�`��T�C�Y</param>
	/// <param name="reserveDrawCount">�`�悷�鐔</param>
	void Create(UINT resourceID);

	/// <summary>
	/// �X�v���C�g�𐶐����Auv�l������K�p
	/// </summary>
	/// <param name="divAllnum">��������</param>
	/// <param name="divX">x����������</param>
	/// <param name="divY">y����������</param>
	/// <param name="sizeX">�����T�C�Y</param>
	/// <param name="sizeY">�����T�C�Y</param>
	/// <param name="resourceID">�e�N�X�`���n���h��</param>
	void CreateAndSetDivisionUVOffsets(int divAllnum, int divX, int divY, int sizeX, int sizeY,UINT resourceID);

	//���_�C���X�^���X�f�[�^���X�V
	void InstanceUpdate();

	//�X�v���C�g�`��
	void Draw();

	void DrawSprite(float posX, float posY);

	void DrawExtendSprite(float x1, float y1, float x2, float y2);



private:
	static DirectX::XMFLOAT4 sprite_color;

	UINT sizeInsVB;

	UINT instanceDrawCount;

	//�e�N�X�`���̂��Ƃ̃T�C�Y
	XMFLOAT2 TEXTURE_DEFAULT_SIZE;

	//�����Y�H
	bool isCreated = false;

	//���_�o�b�t�@�̍Ċm�ۂ��K�v���H
	bool isVertexBufferNeedResize();

	//���_�o�b�t�@�̃T�C�Y�ύX�i�C���X�^���V���O�p�o�b�t�@�j
	void ResizeVertexInstanceBuffer(UINT newWidthSize);

	//�X�v���C�g�X�V�i�G���W���ŏ���ɂ��j
	void UpdateSprite();

	//�}���`�p�X���ʕ`��
	void DrawMPRender();

	bool IsCreated();

	//�X�v���C�g������(�f�o�C�X�A�X�v���C�g�T�C�Y�A�A���J�[�|�C���g�A�g�p���郊�\�[�X�ԍ��A���\�[�X�����t���O)
	void CreateSprite(XMFLOAT2 size, XMFLOAT2 anchor, UINT resourceID, bool adjustResourceFlag, uvAnimData* animData = nullptr);

};

///�V�A�X�v���C�g�����̎d��
///
/// �e�N�X�`���ԍ����w�肵�č쐬
/// ��
/// Update�͂��Ȃ�
/// ��
/// Draw()�ȊO�̕`��֐����Ă�
/// ��
/// ����ȏ�`�悵�Ȃ��^�C�~���O��Draw()�����s
/// 
/// �`��֐�
/// DrawSprite(x,y); �����A�ʏ�`��
/// 


