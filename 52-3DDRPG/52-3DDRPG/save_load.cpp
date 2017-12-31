#include "define.h"

#define __STDC_WANT_LIB_EXT1__ 1

SaveLoad_c::SaveLoad_c() :
	end(0)
{
	FontTitleMain = CreateFontToHandle(NULL, 24, 1, DX_FONTTYPE_ANTIALIASING_EDGE_4X4, DX_CHARSET_DEFAULT);
	SE[DECISION] = LoadSoundMem("resource/sounds/SE/common/Decision1.ogg");
	SE[CANCEL] = LoadSoundMem("resource/sounds/SE/common/Cancel2.ogg");
	SE[CURSOR] = LoadSoundMem("resource/sounds/SE/common/Cursor2.ogg");
	SE[BUZZER] = LoadSoundMem("resource/sounds/SE/common/Buzzer1.ogg");
	TempScreen = MakeScreen(640, 480, FALSE);
	textBox = new TextBox;
	FileCheck();
	for (int i = 0; i < 4; i++) {
		if (dataCheck[i] != 1) LoadTime(i);
	}
}

SaveLoad_c::~SaveLoad_c() {
	DeleteFontToHandle(FontTitleMain);
	DeleteSoundMem(SE[DECISION]);
	DeleteSoundMem(SE[CANCEL]);
	DeleteSoundMem(SE[CURSOR]);
	DeleteSoundMem(SE[BUZZER]);
	delete textBox;
}

bool SaveLoad_c::SaveScreen(const int* Key) {
	/*
	if (first == true) {
		first = false;
		
		Origin.CharX = CharX;
		Origin.CharY = CharY;
		Origin.Status = Status;
		Origin.StatusNum = StatusNum;
		
		FileCheck();
	}
	*/

	if (bright < 255 && end == 0) {
		bright = bright + 5;
		SetDrawBright(bright, bright, bright);
	}

	for (int i = 0; i < 4; i++) {
		textBox->DrawWindow(0, 120 * i, 640, 120);
		if (Cursor == i) {
			DrawFormatStringToHandle(40, 10 + (120 * i), GetColor(255, 191, 0), FontTitleMain, "Slot %d", i + 1);
			if (dataCheck[i] == 1) DrawFormatStringToHandle(260, 60 + 120 * i, GetColor(255, 191, 0), FontTitleMain, "No Data");
			else {
				DrawFormatStringToHandle(100, 45 + 120 * i, GetColor(255, 191, 0), FontTitleMain, "プレイ時間　%2d:%2d:%2d", drawCount[i][3], drawCount[i][2], drawCount[i][1]);
				DrawFormatStringToHandle(100, 75 + 120 * i, GetColor(255, 191, 0), FontTitleMain, "セーブ時刻　%4d/%2d/%2d %2d:%2d:%2d", drawDate[i].Year, drawDate[i].Mon, drawDate[i].Day, drawDate[i].Hour, drawDate[i].Min, drawDate[i].Sec);
			}
		}
		else {
			DrawFormatStringToHandle(40, 10 + (120 * i), GetColor(255, 255, 255), FontTitleMain, "Slot %d", i + 1);
			if (dataCheck[i] == 1) DrawFormatStringToHandle(260, 60 + 120 * i, GetColor(255, 255, 255), FontTitleMain, "No Data");
			else {
				DrawFormatStringToHandle(100, 45 + 120 * i, GetColor(255, 255, 255), FontTitleMain, "プレイ時間　%2d:%2d:%2d", drawCount[i][3], drawCount[i][2], drawCount[i][1]);
				DrawFormatStringToHandle(100, 75 + 120 * i, GetColor(255, 255, 255), FontTitleMain, "セーブ時刻　%4d/%2d/%2d %2d:%2d:%2d", drawDate[i].Year, drawDate[i].Mon, drawDate[i].Day, drawDate[i].Hour, drawDate[i].Min, drawDate[i].Sec);
			}
		}
	}
	/*
	DrawFormatStringToHandle(40, 10, GetColor(255, 255, 255), FontTitleMain, "Slot 1");
	DrawFormatStringToHandle(40, 125, GetColor(255, 255, 255), FontTitleMain, "Slot 2");
	DrawFormatStringToHandle(40, 240, GetColor(255, 255, 255), FontTitleMain, "Slot 3");
	DrawFormatStringToHandle(40, 355, GetColor(255, 255, 255), FontTitleMain, "Slot 4");
	
	DrawFormatStringToHandle(5, Cursor, GetColor(255, 255, 255), FontTitleMain, "●");
	*/
	if (Key[KEY_INPUT_DOWN] == 1) {
		if (Cursor != 3) { Cursor++; PlaySoundMem(SE[CURSOR], DX_PLAYTYPE_BACK); }
	}
	else if (Key[KEY_INPUT_UP] == 1) {
		if (Cursor != 0) { Cursor--; PlaySoundMem(SE[CURSOR], DX_PLAYTYPE_BACK); }
	}
	else if (Key[KEY_INPUT_RETURN] == 1 || Key[KEY_INPUT_Z] == 1) {
		PlaySoundMem(SE[DECISION], DX_PLAYTYPE_BACK);
		Save(Cursor + 1);
		end = 1;
		/*
		if (Cursor == 0) {
			PlaySoundMem(SE[DECISION], DX_PLAYTYPE_BACK);
			Save(1); //スロット1にセーブ
			GetDrawScreenGraph(0, 0, 640, 480, TempScreen);
			do {
				bright = bright - 5;
				SetDrawBright(bright, bright, bright);
				ClearDrawScreen();
				DrawGraph(0, 0, TempScreen, FALSE);
				ScreenFlip();
			} while (bright > 0);
			SetDrawBright(255, 255, 255);
			GData.SceneBackRequest();
			return true;
		}
		else if (Cursor == 1) {
			PlaySoundMem(SE[DECISION], DX_PLAYTYPE_BACK);
			Save(2); //スロット2にセーブ
			GetDrawScreenGraph(0, 0, 640, 480, TempScreen);
			do {
				bright = bright - 5;
				SetDrawBright(bright, bright, bright);
				ClearDrawScreen();
				DrawGraph(0, 0, TempScreen, FALSE);
				ScreenFlip();
			} while (bright > 0);
			SetDrawBright(255, 255, 255);
			GData.SceneBackRequest();
			return true;
		}
		else if (Cursor == 2) {
			PlaySoundMem(SE[DECISION], DX_PLAYTYPE_BACK);
			Save(3); //スロット3にセーブ
			GetDrawScreenGraph(0, 0, 640, 480, TempScreen);
			do {
				bright = bright - 5;
				SetDrawBright(bright, bright, bright);
				ClearDrawScreen();
				DrawGraph(0, 0, TempScreen, FALSE);
				ScreenFlip();
			} while (bright > 0);
			SetDrawBright(255, 255, 255);
			GData.SceneBackRequest();
			return true;
		}
		else {
			PlaySoundMem(SE[DECISION], DX_PLAYTYPE_BACK);
			Save(4); //スロット4にセーブ
			GetDrawScreenGraph(0, 0, 640, 480, TempScreen);
			do {
				bright = bright - 5;
				SetDrawBright(bright, bright, bright);
				ClearDrawScreen();
				DrawGraph(0, 0, TempScreen, FALSE);
				ScreenFlip();
			} while (bright > 0);
			SetDrawBright(255, 255, 255);
			GData.SceneBackRequest();
			return true;
		}
		*/
	}
	if (end == 1) {
		if (bright > 0) {
			bright -= 5;
			SetDrawBright(bright, bright, bright);
		}
		else {
			SetDrawBright(255, 255, 255);
			GData.SceneRequest(2, 3);
			return true;
		}
	}

	return false;
}

bool SaveLoad_c::LoadScreen(const int* Key) {
	/*
	if (first == true) {
		first = false;
		
		Origin.CharX = CharX;
		Origin.CharY = CharY;
		Origin.Status = Status;
		Origin.StatusNum = StatusNum;

		FileCheck();
	}
	*/

	if (bright < 255 && end == 0) {
		bright = bright + 5;
		SetDrawBright(bright, bright, bright);
	}

	for (int i = 0; i < 4; i++) {
		textBox->DrawWindow(0, 120 * i, 640, 120);
		if (Cursor == i) {
			DrawFormatStringToHandle(40, 10 + (120 * i), GetColor(255, 191, 0), FontTitleMain, "Slot %d", i + 1);
			if (dataCheck[i] == 1) DrawFormatStringToHandle(260, 60 + 120 * i, GetColor(255, 191, 0), FontTitleMain, "No Data");
			else {
				DrawFormatStringToHandle(100, 45 + 120 * i, GetColor(255, 191, 0), FontTitleMain, "プレイ時間　%2d:%2d:%2d", drawCount[i][3], drawCount[i][2], drawCount[i][1]);
				DrawFormatStringToHandle(100, 75 + 120 * i, GetColor(255, 191, 0), FontTitleMain, "セーブ時刻　%4d/%2d/%2d %2d:%2d:%2d", drawDate[i].Year, drawDate[i].Mon, drawDate[i].Day, drawDate[i].Hour, drawDate[i].Min, drawDate[i].Sec);
			}
		}
		else {
			DrawFormatStringToHandle(40, 10 + (120 * i), GetColor(255, 255, 255), FontTitleMain, "Slot %d", i + 1);
			if (dataCheck[i] == 1) DrawFormatStringToHandle(260, 60 + 120 * i, GetColor(255, 255, 255), FontTitleMain, "No Data");
			else {
				DrawFormatStringToHandle(100, 45 + 120 * i, GetColor(255, 255, 255), FontTitleMain, "プレイ時間　%2d:%2d:%2d", drawCount[i][3], drawCount[i][2], drawCount[i][1]);
				DrawFormatStringToHandle(100, 75 + 120 * i, GetColor(255, 255, 255), FontTitleMain, "セーブ時刻　%4d/%2d/%2d %2d:%2d:%2d", drawDate[i].Year, drawDate[i].Mon, drawDate[i].Day, drawDate[i].Hour, drawDate[i].Min, drawDate[i].Sec);
			}
		}
	}

	/*
	DrawFormatStringToHandle(40, 10, GetColor(255, 255, 255), FontTitleMain, "Slot 1");
	DrawFormatStringToHandle(40, 125, GetColor(255, 255, 255), FontTitleMain, "Slot 2");
	DrawFormatStringToHandle(40, 240, GetColor(255, 255, 255), FontTitleMain, "Slot 3");
	DrawFormatStringToHandle(40, 355, GetColor(255, 255, 255), FontTitleMain, "Slot 4");
	
	if (dataCheck[0] == 1) DrawFormatStringToHandle(260, 60, GetColor(255, 255, 255), FontTitleMain, "No Data");
	if (dataCheck[1] == 1) DrawFormatStringToHandle(260, 175, GetColor(255, 255, 255), FontTitleMain, "No Data");
	if (dataCheck[2] == 1) DrawFormatStringToHandle(260, 290, GetColor(255, 255, 255), FontTitleMain, "No Data");
	if (dataCheck[3] == 1) DrawFormatStringToHandle(260, 405, GetColor(255, 255, 255), FontTitleMain, "No Data");

	DrawFormatStringToHandle(5, Cursor, GetColor(255, 255, 255), FontTitleMain, "●");
	*/
	if (Key[KEY_INPUT_DOWN] == 1) {
		if (Cursor != 3) { Cursor++; PlaySoundMem(SE[CURSOR], DX_PLAYTYPE_BACK); }
	}
	else if (Key[KEY_INPUT_UP] == 1) {
		if (Cursor != 0) { Cursor--; PlaySoundMem(SE[CURSOR], DX_PLAYTYPE_BACK); }
	}
	else if (Key[KEY_INPUT_X] == 1) {
		end = 2;
	}
	else if (Key[KEY_INPUT_RETURN] == 1 || Key[KEY_INPUT_Z] == 1) {
		PlaySoundMem(SE[DECISION], DX_PLAYTYPE_BACK);
		Load(Cursor + 1);
		end = 1;
		/*
		if (Cursor == 10) {
			if (dataCheck[0] == 0) {
				PlaySoundMem(SE[DECISION], DX_PLAYTYPE_BACK);
				Load(1); //スロット1をロード
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
				Load(2); //スロット2をロード
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
				Load(3); //スロット3をロード
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
				Load(4); //スロット4をロード
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
		*/
	}
	if (end != 0) {
		if (bright > 0) {
			bright -= 5;
			SetDrawBright(bright, bright, bright);
		}
		else if (end == 1) {
			SetDrawBright(255, 255, 255);
			GData.SceneRequest(1, 1);
			return true;
		}
		else if (end == 2) {
			SetDrawBright(255, 255, 255);
			GData.SceneRequest(1, 2);
			return true;
		}
	}

	return false;
}

void SaveLoad_c::Save(const int SlotNum) {
	char filename[] = "0.save";
	snprintf(filename, 7, "%d.save", SlotNum);
	
	//Data.scenario = GData.GetScenario();
	for (int i = 0; i < 5; i++) {
		Data.stage[i] = GData.GetStageNum(i);
		Data.dungeonX[i] = GData.GetDungeonXNum(i);
		Data.dungeonY[i] = GData.GetDungeonYNum(i);
		Data.dir[i] = GData.GetDirNum(i);
		Data.room[i] = GData.GetRoomNum(i);
		for (int j = 0; j < 128; j++) {
			Data.flag[i][j] = GData.GetFlagNum(i, j);
		}
	}
	GData.GetCount(Data.playCount);
	GetDateTime(&Data.dateData);

	if (fopen_s(&sdfp, filename, "wb") == 0) {
		fwrite(&Data, sizeof(Data), 1, sdfp);
		fclose(sdfp);
	}
}

void SaveLoad_c::Load(const int SlotNum) {
	char filename[] = "0.save";
	snprintf(filename, 7, "%d.save", SlotNum);
	for (int i = 0; i < 5; i++) {
		GData.DeleteData(i);
	}
	if (fopen_s(&sdfp, filename, "rb") == 0) {
		fread(&Data, sizeof(Data), 1, sdfp);
		fclose(sdfp);

	//	GData.SetScenario(Data.scenario);
		for (int i = 0; i < 5; i++) {
			GData.SetStageNum(i, Data.stage[i]);
			GData.SetDungeonXNum(i, Data.dungeonX[i]);
			GData.SetDungeonYNum(i, Data.dungeonY[i]);
			GData.SetDirNum(i, Data.dir[i]);
			GData.SetRoomNum(i, Data.room[i]);
			for (int j = 0; j < 128; j++) {
				GData.SetFlagNum(i, j, Data.flag[i][j]);
			}
			/*
			if (dataCheck[SlotNum - 1] == 1) {
				GData.SetFlagNum(i, 0, 1);
			}
			*/
		}
		GData.SetCount(Data.playCount);
	}
}

void SaveLoad_c::LoadTime(const int index)
{
	char filename[] = "0.save";
	snprintf(filename, 7, "%d.save", index + 1);
	if (fopen_s(&sdfp, filename, "rb") == 0) {
		fread(&Data, sizeof(Data), 1, sdfp);
		fclose(sdfp);

		for (int i = 0; i < 4; i++) {
			drawCount[index][i] = Data.playCount[i];
		}
		drawDate[index] = Data.dateData;
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