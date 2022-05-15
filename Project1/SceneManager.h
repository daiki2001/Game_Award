#pragma once
#include "ISceneChanger.h"
#include "BaseScene.h"
#include "Raki_DX12B.h"
#include "Raki_WinAPI.h"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_win32.h"
#include "imgui/imgui_impl_dx12.h"

/// <summary>
/// �V�[���Ǘ��N���X�@�d�l
/// <para>�ڂ����� dixq.net/g/sp_06.html ���Q�Ƃ��邱��</para>
/// <para>�E�e�V�[���̃N���X�̃C���X�^���X�𐶐����A���݂̃V�[���̏����̂ݎ��s����</para>
/// <para>�E�g�p���́A���̃N���X�̃C���X�^���X��main�Ő����AInit�AUpdate�ADraw�A(�K�v�ɉ�����Finalize)�����s�����OK</para>
/// <para>�E�V�[���ύX���s���́A�e�N���X�̍X�V������ChangeScene(�����Fenum�Œ�`�����V�[���ԍ�)�֐������s���邱�ƂŁA</para>
/// <para>�@�O�V�[���̏I�����������s�A���V�[���̏������J�n����</para>
/// </summary>
class SceneManager : public ISceneChanger ,Task
{
private:
    //�V�[���̃|�C���^
    BaseScene *nowScene;
    //���̃V�[���Ǘ��ϐ�
	eScene mNextScene;

    bool isSceneEnd = false;

public:
    //�R���X�^���N�^
    SceneManager();
    ~SceneManager() {
    }
    void Initialize() override;//������
    void Finalize() override;//�I������
    void Update() override;//�X�V
    void Draw() override;//�`��

    // ���� nextScene �ɃV�[����ύX����
    void ChangeScene(eScene NextScene) override;

    void EndAplication() override;

    bool isEndApp() { return isSceneEnd; }

};

