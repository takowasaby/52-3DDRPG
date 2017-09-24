#pragma once
class Data_c; //��

class TextBox
{
private:
	//�E�B���h�E���[�h�Ɋւ���񋓑�
	enum WindowMode {
		readMode,	//�I���ł��Ȃ����b�Z�[�W�p
		pageMode,	//�㉺�őI���A���E�Ńy�[�W�ړ�
		scrollMode	//�X�N���[���ňړ�
	};
	WindowMode windowMode;

	Data_c* originalData;		// �f�[�^�N���X����ꗗ��ǂݍ��ޗp

	vector<string> message;	//���b�Z�[�W�i�[�z��
	int x, y, w, h, raw;	//���W�A�傫���A�s��
	int position; //�I���ʒu
	int topOfPage;	//�y�[�W�̐擪�̈ʒu

	bool isActivated;	//�A�N�e�B�u��Ԃ�
	bool isVisible;	//����Ԃ�
	bool isSelected;	//�I����Ԃ�

	//�L�[���͗p�ϐ�
	int key[256]; // 0:���͂���Ă��Ȃ� 1:���͂��ꂽ�u�� 2:���͂���Ă���
public:
	TextBox();
	~TextBox();

	void Update();	//�X�V
	void Draw();		//�`��
	void Activate();
	void InActivate();

	void LoadData(Data_c*);

	//�E�B���h�E�ҏW�p�֐�
	void SetWindowMode(WindowMode);
	void SetPositon(int,int);
	void SetSize(int,int,int);

	//���b�Z�[�W�ҏW�p�֐�
	void AddMessage(string);
	void SetMessage(string,int);

	string GetText(int);
};

