#pragma once


//�V�[���ԍ���`
typedef enum {
    eScene_Title,   //�^�C�g�����
    eScene_Game,    //�Q�[�����
    // ----- �V�[���ǉ����͂����ɃV�[���ԍ��̐錾�����邱�ƁI ----- //
    editor, //�G�f�B�^�[�p

    eScene_None,    //����
} eScene;

//�V�[����ύX���邽�߂̃C���^�[�t�F�C�X�N���X
class ISceneChanger {
public:
    virtual ~ISceneChanger() = 0;
    virtual void ChangeScene(eScene NextScene) = 0;//�w��V�[���ɕύX����
    virtual void EndAplication() = 0;
};

