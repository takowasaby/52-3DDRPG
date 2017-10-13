#include "define.h"

char Key[256];

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {


	ChangeWindowMode(true/*option.WinMode*/);//ウィンドウモードで描画
							//SetGraphMode(WINDOW_X, WINDOW_Y, WINDOW_COLOR_BIT);	// 画面の大きさを変える(640*480の32bit)
	if (DxLib_Init() == -1) {
		return -1;
	}// DXライブラリを初期化処理,エラーが起きたら終了

	if (ChangeWindowMode(TRUE) != DX_CHANGESCREEN_OK || DxLib_Init() == -1) return -1; //初期化処理
	SetDrawScreen(DX_SCREEN_BACK);        //裏画面に設定

	Control_c control;

	while (!ProcessMessage() && !ClearDrawScreen() && !GetHitKeyStateAll(Key) && !Key[KEY_INPUT_ESCAPE]) {
		//↑ﾒｯｾｰｼﾞ処理         ↑画面をｸﾘｱ          ↑ｷｰﾎﾞｰﾄﾞ入力状態取得       ↑ESCが押されていない

		control.All();

		ScreenFlip();//裏画面を表画面に反映
	}

	DxLib_End();
	return 0;
}
