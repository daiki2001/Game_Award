#pragma once
#include "BaseScene.h"
#include "ISceneChanger.h"
#include "Sprite.h"
#include <string>

class Editor : public BaseScene
{
public: //���z�֐�
	Editor(ISceneChanger* changer);
	~Editor() override {};
	void Initialize() override; //�������������I�[�o�[���C�h�B
	void Finalize() override;   //�I���������I�[�o�[���C�h�B
	void Update() override;     //�X�V�������I�[�o�[���C�h�B
	void Draw() override;       //�`�揈�����I�[�o�[���C�h�B

private: //�萔
	static const std::string directoryPath; //�f�B���N�g���p�X

private: //�ÓI�����o�ϐ�
	static std::string fileName; //�t�@�C����

private: //�����o�֐�
	void Create();  //��������

	int SaveFile();
	int LoadFile();
	int Save(const char* fileName);

private: //�����o�ϐ�
	// �w�i�摜
	Sprite backSprite;

	bool isOpen; //�t�@�C���̓ǂݍ��݂�����Ă��邩�ǂ���
	bool isSave; //�Z�[�u�����ǂ���
	bool isLoad; //�ǂݍ��ݒ����ǂ���
};
