#include "define.h"

Data_c GData;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {


	ChangeWindowMode(true/*option.WinMode*/);//�E�B���h�E���[�h�ŕ`��
							//SetGraphMode(WINDOW_X, WINDOW_Y, WINDOW_COLOR_BIT);	// ��ʂ̑傫����ς���(640*480��32bit)
	if (DxLib_Init() == -1) {
		return -1;
	}// DX���C�u����������������,�G���[���N������I��

	if (ChangeWindowMode(TRUE) != DX_CHANGESCREEN_OK || DxLib_Init() == -1) return -1; //����������
	SetDrawScreen(DX_SCREEN_BACK);        //����ʂɐݒ�

	Control_c control;

	while (!ProcessMessage() && !ClearDrawScreen() && control.All()) {
		//��ү���ޏ���         ����ʂ�ر          

		ScreenFlip();//����ʂ�\��ʂɔ��f
	}

	DxLib_End();
	return 0;
}
