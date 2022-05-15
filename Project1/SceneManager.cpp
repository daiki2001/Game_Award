#include "SceneManager.h"
#include "GameScene.h"
#include "Title.h"
#include "Editor.h"

//Raki_DX12B         *SceneManager::dx12b  = nullptr;
//NY_Object3DManager *SceneManager::objmgr = nullptr;
//SpriteManager      *SceneManager::spmgr  = nullptr;

SceneManager::SceneManager() :mNextScene(eScene_None) {

    //����O������V�[���͂����Œ�`
    nowScene = (BaseScene*)new Editor(this);
    Initialize();
}

void SceneManager::Initialize()
{
    //�V�[���̏�����
	nowScene->Initialize();
}

void SceneManager::Finalize()
{
    //�V�[���̏I��
    delete nowScene;
}

void SceneManager::Update()
{
    if (mNextScene != eScene_None) {    //���̃V�[�����Z�b�g����Ă�����
        delete nowScene;//���݂̃V�[���̏I�����������s
        switch (mNextScene) {       //�V�[���ɂ���ď����𕪊�
        case eScene_Title:        //���̉�ʂ����j���[�Ȃ�
            nowScene = (BaseScene*)new Title(this);
            break;//�ȉ���
        case eScene_Game:
            nowScene = (BaseScene*)new GameScene(this);
            break;
            // ----- �V�[����ǉ�����Ƃ��́A��̂悤��enum�ɒ�`�����萔�ŕ��򂳂��āAnowScene�ɊY���V�[����new�Ő������邱�� ----- //
        case editor:
            nowScene = (BaseScene*)new GameScene(this);
            break;

        }
        mNextScene = eScene_None;    //���̃V�[�������N���A
        nowScene->Initialize();    //�V�[����������
    }

    nowScene->Update(); //�V�[���̍X�V
}

void SceneManager::Draw()
{
    //���݃V�[���̕`�揈�������s
    nowScene->Draw();
}

void SceneManager::ChangeScene(eScene NextScene)
{
    //���̃V�[���ԍ����Z�b�g
    mNextScene = NextScene;
}

void SceneManager::EndAplication()
{
    isSceneEnd = true;
}


