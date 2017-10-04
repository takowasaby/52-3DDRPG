#include "define.h"

char Key[256];

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {

<<<<<<< HEAD
	ChangeWindowMode(false);//ã‚¦ã‚£ãƒ³ãƒ‰ã‚¦ãƒ¢ãƒ¼ãƒ‰ã§æç”»
							//SetGraphMode(WINDOW_X, WINDOW_Y, WINDOW_COLOR_BIT);	// ç”»é¢ã®å¤§ãã•ã‚’å¤‰ãˆã‚‹(640*480ã®32bit)
=======
	ChangeWindowMode(true/*option.WinMode*/);//ƒEƒBƒ“ƒhƒEƒ‚[ƒh‚Å•`‰æ
							//SetGraphMode(WINDOW_X, WINDOW_Y, WINDOW_COLOR_BIT);	// ‰æ–Ê‚Ì‘å‚«‚³‚ğ•Ï‚¦‚é(640*480‚Ì32bit)
>>>>>>> master
	if (DxLib_Init() == -1) {
		return -1;
	}// DXƒ‰ƒCƒuƒ‰ƒŠ‚ğ‰Šú‰»ˆ—,ƒGƒ‰[‚ª‹N‚«‚½‚çI—¹

	if (ChangeWindowMode(TRUE) != DX_CHANGESCREEN_OK || DxLib_Init() == -1) return -1; //‰Šú‰»ˆ—
	SetDrawScreen(DX_SCREEN_BACK);        //— ‰æ–Ê‚Éİ’è

	Control_c control;

	while (!ProcessMessage() && !ClearDrawScreen() && !GetHitKeyStateAll(Key) && !Key[KEY_INPUT_ESCAPE]) {
		//ªÒ¯¾°¼Şˆ—         ª‰æ–Ê‚ğ¸Ø±          ª·°ÎŞ°ÄŞ“ü—Íó‘Ôæ“¾       ªESC‚ª‰Ÿ‚³‚ê‚Ä‚¢‚È‚¢

		control.All();

		ScreenFlip();//— ‰æ–Ê‚ğ•\‰æ–Ê‚É”½‰f
	}

	DxLib_End();
	return 0;
}
