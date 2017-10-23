#include "define.h"

#define __STDC_WANT_LIB_EXT1__ 1

SaveLoad_c::SaveLoad_c() {
	FontTitleMain = CreateFontToHandle(NULL, 24, 1, DX_FONTTYPE_ANTIALIASING_EDGE_4X4, DX_CHARSET_DEFAULT);
	SE[DECISION] = LoadSoundMem("resource/sounds/SE/common/Decision1.ogg");
	SE[CANCEL] = LoadSoundMem("resource/sounds/SE/common/Cancel2.ogg");
	SE[CURSOR] = LoadSoundMem("resource/sounds/SE/common/Cursor2.ogg");
	SE[BUZZER] = LoadSoundMem("resource/sounds/SE/common/Buzzer1.ogg");
	TempScreen = MakeScreen(640, 480, FALSE);
}

SaveLoad_c::~SaveLoad_c() {
	DeleteFontToHandle(FontTitleMain);
	DeleteSoundMem(SE[DECISION]);
	DeleteSoundMem(SE[CANCEL]);
	DeleteSoundMem(SE[CURSOR]);
	DeleteSoundMem(SE[BUZZER]);
}

bool SaveLoad_c::SaveScreen(const int* Key, int* CharX, int* CharY, int* Status, const int StatusNum) {
	if (first == true) {
		first = false;
		Origin.CharX = CharX;
		Origin.CharY = CharY;
		Origin.Status = Status;
		Origin.StatusNum = StatusNum;
	}

	if (bright < 255) {
		bright = bright + 5;
		SetDrawBright(bright, bright, bright);
	}

	DrawFormatStringToHandle(40, 10, GetColor(255, 255, 255), FontTitleMain, "Slot 1");
	DrawFormatStringToHandle(40, 125, GetColor(255, 255, 255), FontTitleMain, "Slot 2");
	DrawFormatStringToHandle(40, 240, GetColor(255, 255, 255), FontTitleMain, "Slot 3");
	DrawFormatStringToHandle(40, 355, GetColor(255, 255, 255), FontTitleMain, "Slot 4");

	DrawFormatStringToHandle(5, Cursor, GetColor(255, 255, 255), FontTitleMain, "●");

	if (Key[KEY_INPUT_DOWN] == 1) {
		if (Cursor != 355) { Cursor = Cursor + 115; PlaySoundMem(SE[CURSOR], DX_PLAYTYPE_BACK); }
	}
	else if (Key[KEY_INPUT_UP] == 1) {
		if (Cursor != 10) { Cursor = Cursor - 115; PlaySoundMem(SE[CURSOR], DX_PLAYTYPE_BACK); }
	}
	else if (Key[KEY_INPUT_RETURN] == 1 || Key[KEY_INPUT_Z] == 1) {
		if (Cursor == 10) {
			PlaySoundMem(SE[DECISION], DX_PLAYTYPE_BACK);
			Save(1, Origin); //スロット1にセーブ
			GetDrawScreenGraph(0, 0, 640, 480, TempScreen);
			do {
				bright = bright - 5;
				SetDrawBright(bright, bright, bright);
				ClearDrawScreen();
				DrawGraph(0, 0, TempScreen, FALSE);
				ScreenFlip();
			} while (bright > 0);
			SetDrawBright(255, 255, 255);
			GData.SceneRequest(1, 1);//メニューに戻る
			return true;
		}
		else if (Cursor == 125) {
			PlaySoundMem(SE[DECISION], DX_PLAYTYPE_BACK);
			Save(2, Origin); //スロット2にセーブ
			GetDrawScreenGraph(0, 0, 640, 480, TempScreen);
			do {
				bright = bright - 5;
				SetDrawBright(bright, bright, bright);
				ClearDrawScreen();
				DrawGraph(0, 0, TempScreen, FALSE);
				ScreenFlip();
			} while (bright > 0);
			SetDrawBright(255, 255, 255);
			GData.SceneRequest(2, 3); //メニューに戻る
			return true;
		}
		else if (Cursor == 240) {
			PlaySoundMem(SE[DECISION], DX_PLAYTYPE_BACK);
			Save(3, Origin); //スロット3にセーブ
			GetDrawScreenGraph(0, 0, 640, 480, TempScreen);
			do {
				bright = bright - 5;
				SetDrawBright(bright, bright, bright);
				ClearDrawScreen();
				DrawGraph(0, 0, TempScreen, FALSE);
				ScreenFlip();
			} while (bright > 0);
			SetDrawBright(255, 255, 255);
			GData.SceneRequest(2, 3); //メニューに戻る
			return true;
		}
		else {
			PlaySoundMem(SE[DECISION], DX_PLAYTYPE_BACK);
			Save(4, Origin); //スロット4にセーブ
			GetDrawScreenGraph(0, 0, 640, 480, TempScreen);
			do {
				bright = bright - 5;
				SetDrawBright(bright, bright, bright);
				ClearDrawScreen();
				DrawGraph(0, 0, TempScreen, FALSE);
				ScreenFlip();
			} while (bright > 0);
			SetDrawBright(255, 255, 255);
			GData.SceneRequest(2, 3); //メニューに戻る
			return true;
		}
	}

	return false;
}

bool SaveLoad_c::LoadScreen(const int* Key, int* CharX, int* CharY, int* Status, const int StatusNum) {
	if (first == true) {
		first = false;
		Origin.CharX = CharX;
		Origin.CharY = CharY;
		Origin.Status = Status;
		Origin.StatusNum = StatusNum;

		FileCheck();
	}

	DrawFormatStringToHandle(40, 10, GetColor(255, 255, 255), FontTitleMain, "Slot 1");
	DrawFormatStringToHandle(40, 125, GetColor(255, 255, 255), FontTitleMain, "Slot 2");
	DrawFormatStringToHandle(40, 240, GetColor(255, 255, 255), FontTitleMain, "Slot 3");
	DrawFormatStringToHandle(40, 355, GetColor(255, 255, 255), FontTitleMain, "Slot 4");
	
	if (dataCheck[0] == 1) DrawFormatStringToHandle(260, 60, GetColor(255, 255, 255), FontTitleMain, "No Data");
	if (dataCheck[1] == 1) DrawFormatStringToHandle(260, 175, GetColor(255, 255, 255), FontTitleMain, "No Data");
	if (dataCheck[2] == 1) DrawFormatStringToHandle(260, 290, GetColor(255, 255, 255), FontTitleMain, "No Data");
	if (dataCheck[3] == 1) DrawFormatStringToHandle(260, 405, GetColor(255, 255, 255), FontTitleMain, "No Data");

	DrawFormatStringToHandle(5, Cursor, GetColor(255, 255, 255), FontTitleMain, "●");

	if (Key[KEY_INPUT_DOWN] == 1) {
		if (Cursor != 355) { Cursor = Cursor + 115; PlaySoundMem(SE[CURSOR], DX_PLAYTYPE_BACK); }
	}
	else if (Key[KEY_INPUT_UP] == 1) {
		if (Cursor != 10) { Cursor = Cursor - 115; PlaySoundMem(SE[CURSOR], DX_PLAYTYPE_BACK); }
	}
	else if (Key[KEY_INPUT_RETURN] == 1 || Key[KEY_INPUT_Z] == 1) {
		if (Cursor == 10) {
			if (dataCheck[0] == 0) {
				PlaySoundMem(SE[DECISION], DX_PLAYTYPE_BACK);
				Load(1, Origin); //スロット1をロード
				GetDrawScreenGraph(0, 0, 640, 480, TempScreen);
				do {
					bright = bright - 5;
					SetDrawBright(bright, bright, bright);
					ClearDrawScreen();
					DrawGraph(0, 0, TempScreen, FALSE);
					ScreenFlip();
				} while (bright > 0);
				SetDrawBright(255, 255, 255);
				GData.SceneRequest(2, 0); //ダンジョン探索へ
				return true;
			}
			else PlaySoundMem(SE[BUZZER], DX_PLAYTYPE_BACK);
		}
		else if (Cursor == 125) {
			if (dataCheck[1] == 0) {
				PlaySoundMem(SE[DECISION], DX_PLAYTYPE_BACK);
				Load(2, Origin); //スロット2をロード
				GetDrawScreenGraph(0, 0, 640, 480, TempScreen);
				do {
					bright = bright - 5;
					SetDrawBright(bright, bright, bright);
					ClearDrawScreen();
					DrawGraph(0, 0, TempScreen, FALSE);
					ScreenFlip();
				} while (bright > 0);
				SetDrawBright(255, 255, 255);
				GData.SceneRequest(2, 0); //ダンジョン探索へ
				return true;
			}
			else PlaySoundMem(SE[BUZZER], DX_PLAYTYPE_BACK);
		}
		else if (Cursor == 240) {
			if (dataCheck[2] == 0) {
				PlaySoundMem(SE[DECISION], DX_PLAYTYPE_BACK);
				Load(3, Origin); //スロット3をロード
				GetDrawScreenGraph(0, 0, 640, 480, TempScreen);
				do {
					bright = bright - 5;
					SetDrawBright(bright, bright, bright);
					ClearDrawScreen();
					DrawGraph(0, 0, TempScreen, FALSE);
					ScreenFlip();
				} while (bright > 0);
				SetDrawBright(255, 255, 255);
				GData.SceneRequest(2, 0); //ダンジョン探索へ
				return true;
			}
			else PlaySoundMem(SE[BUZZER], DX_PLAYTYPE_BACK);
		}
		else {
			if (dataCheck[3] == 0) {
				PlaySoundMem(SE[DECISION], DX_PLAYTYPE_BACK);
				Load(4, Origin); //スロット4をロード
				GetDrawScreenGraph(0, 0, 640, 480, TempScreen);
				do {
					bright = bright - 5;
					SetDrawBright(bright, bright, bright);
					ClearDrawScreen();
					DrawGraph(0, 0, TempScreen, FALSE);
					ScreenFlip();
				} while (bright > 0);
				SetDrawBright(255, 255, 255);
				GData.SceneRequest(2, 0); //ダンジョン探索へ
				return true;
			}
			else PlaySoundMem(SE[BUZZER], DX_PLAYTYPE_BACK);
		}
	}

	return false;
}

void SaveLoad_c::Save(const int SlotNum, OriginData_t Origin) {
	char filename[] = "0.save";
	snprintf(filename, 7, "%d.save", SlotNum);
	Data.saveCharX = *(Origin.CharX);
	Data.saveCharY = *(Origin.CharY);
	int i = 0;
	do {
		Data.savestatus[i] = Origin.Status[i];
		i++;
	} while (i <= Origin.StatusNum - 1);
	if (fopen_s(&sdfp, filename, "wb") == 0) {
		fwrite(&Data, sizeof(Data), 1, sdfp);
		fclose(sdfp);
	}
}

void SaveLoad_c::Load(const int SlotNum, OriginData_t Origin) {
	char filename[] = "0.save";
	snprintf(filename, 7, "%d.save", SlotNum);
	if (fopen_s(&sdfp, filename, "rb") == 0) {
		fread(&Data, sizeof(Data), 1, sdfp);
		fclose(sdfp);
		*(Origin.CharX) = Data.saveCharX;
		*(Origin.CharY) = Data.saveCharY;
		int i = 0;
		do {
			Origin.Status[i] = Data.savestatus[i];
			i++;
		} while (i <= Origin.StatusNum - 1);
	}
}

void SaveLoad_c::FileCheck(void) {
	if (fopen_s(&sdfp, "1.save", "rb") != 0) dataCheck[0] = 1;
	else fclose(sdfp);
	if (fopen_s(&sdfp, "2.save", "rb") != 0) dataCheck[1] = 1;
	else fclose(sdfp);
	if (fopen_s(&sdfp, "3.save", "rb") != 0) dataCheck[2] = 1;
	else fclose(sdfp);
	if (fopen_s(&sdfp, "4.save", "rb") != 0) dataCheck[3] = 1;
	else fclose(sdfp);
}