#include "define.h"

Menu_c::Menu_c() :
	depth(0),
	mode(0), mscenario(0),
	mdir(0), mx(0), my(0),
	drawCount(0),
	itemType(0), soubiType(0),
	chooseChara(0), chooseItem(0), chooseSoubi(0), chooseSkill(0),
	YN(0), targetChara(0),
	windowH(0), windowW(0), menuScreen(0),
	row(0), stringX(0), stringY(0),
	xLeft(0), yUp(0)
{
	colorW = GetColor(255, 255, 255);
	colorY = GetColor(255, 191, 0);
	LoadWindow();

	se[cursor] = LoadSoundMem("resource/sounds/SE/room/cursor.mp3");
	ChangeVolumeSoundMem(64, se[cursor]);
	se[decision] = LoadSoundMem("resource/sounds/SE/room/decision.mp3");
	ChangeVolumeSoundMem(64, se[decision]);
	se[bubu] = LoadSoundMem("resource/sounds/SE/other/bubu.mp3");
	ChangeVolumeSoundMem(64, se[bubu]);

	for (int i = 0; i < CHARACTER_SIZE; i++) {
		charaNum[i] = -1;
	}
	for (int i = 0; i < ITEM_SIZE; i++) {
		itemNum[i] = -1;
	}
	for (int i = 0; i < SOUBI_SIZE; i++) {
		soubiNum[i] = -1;
	}
	for (int i = 0; i < SKILL_SIZE; i++) {
		skillNum[i] = -1;
	}

	textBox = new TextBox;
}
Menu_c::~Menu_c()
{
	delete textBox;
}

void Menu_c::KeyUpdate(int Key[256])
{
	for (int i = 0; i < 256; i++) {
		mKey[i] = Key[i];
	}
}

void Menu_c::DrawGoal()
{
	int drawCount;

	for (int i = 0; i < EVENT_SIZE; i++) {
		drawCount += GData.GetEventFlag(mscenario, i);
	}

	printfDx("%s");
}

void Menu_c::MenuAll()
{
	clsDx();

	DrawLeft();
	DrawRight();
	//	DrawCursor();
//	if (eventList->getCallEventFlag() == 0) {
//		CheckKey();
//	}
	CheckKey();
	/*
	printfDx("\nMode:%d, ", mode);
	printfDx("ItemType:%d, ", itemType);
	printfDx("SoubiType:%d, ", soubiType);
	printfDx("CChara:%d, ", chooseChara);
	printfDx("CItem:%d, ", chooseItem);
	printfDx("CSoubi:%d, ", chooseSoubi);
	printfDx("CSkill:%d, ", chooseSoubi);
	printfDx("YN:%d, ", YN);
	printfDx("targetChara:%d, ", targetChara);
	printfDx("drawCount:%d, ", drawCount);
	printfDx("depth:%d, ", depth);
	*/
}

void Menu_c::DrawBack()
{
}
void Menu_c::DrawLeft()
{
	textBox->DrawWindow(56, 40, 104, 280);
	textBox->DrawWindow(56, 320, 104, 120);

	row = 40;
	stringX = 65;
	stringY = 50;

	if (mode == 0) DrawFormatString(stringX, stringY + row * 0, colorY, "マップ");
	else DrawFormatString(stringX, stringY + row * 0, colorW, "マップ");

	if (mode == 1) DrawFormatString(stringX, stringY + row * 1, colorY, "ステータス");
	else DrawFormatString(stringX, stringY + row * 1, colorW, "ステータス");

	if (mode == 2) DrawFormatString(stringX, stringY + row * 2, colorY, "装備");
	else DrawFormatString(stringX, stringY + row * 2, colorW, "装備");

	if (mode == 3) DrawFormatString(stringX, stringY + row * 3, colorY, "アイテム");
	else DrawFormatString(stringX, stringY + row * 3, colorW, "アイテム");

	if (mode == 4) DrawFormatString(stringX, stringY + row * 4, colorY, "タイトル");
	else DrawFormatString(stringX, stringY + row * 4, colorW, "タイトル");

	if (mode == 5) DrawFormatString(stringX, stringY + row * 5, colorY, "セーブ");
	else DrawFormatString(stringX, stringY + row * 5, colorW, "セーブ");

	if (mode == 6) DrawFormatString(stringX, stringY + row * 6, colorY, "オプション");
	else DrawFormatString(stringX, stringY + row * 6, colorW, "オプション");

	row = 50;
	stringX = 65;
	stringY = 330;

	DrawFormatString(stringX, stringY + row * 0, colorW, "プレイ時間");

	GData.GetCount(count);
	DrawFormatString(stringX + 5, stringY + 25, colorW, "%2d:%2d:%2d", count[3], count[2], count[1]);


	DrawFormatString(stringX, stringY + row * 1, colorW, "シナリオ");
	DrawFormatString(stringX + 25, stringY + row * 1 + 25, colorW, "%d", GData.GetScenario());
}
void Menu_c::DrawRight()
{
	drawCount = 0;
	/*	for (int i = 0; i < CHARACTER_SIZE; i++) {
	charaNum[i] = -1;
	}
	for (int i = 0; i < ITEM_SIZE; i++) {
	itemNum[i] = -1;
	}
	for (int i = 0; i < SOUBI_SIZE; i++) {
	soubiNum[i] = -1;
	}
	for (int i = 0; i < SKILL_SIZE; i++) {
	skillNum[i] = -1;
	}
	*/
	switch (depth) {
	case 0:
	case 1:
		switch (mode) {
		case map:
			//			DrawGoal	
			textBox->DrawWindow(160, 40, 424, 400);

			mscenario = GData.GetScenario();
			mdir = GData.GetDir();
			mx = GData.GetDungeonX();
			my = GData.GetDungeonY();
			for (int i = 0; i < MAP_SIZE_X; i++) {
				for (int j = 0; j < MAP_SIZE_Y; j++) {
					mwallType[i][j] = GData.GetWallType(i, j);
				}
			}

			//		DrawBox(MENU_MAP_LEFT, MENU_MAP_UP, MENU_MAP_LEFT + (MENU_MAP_SIZE + 2) * MAP_SIZE_X + 2, MENU_MAP_UP + (MENU_MAP_SIZE + 2) * MAP_SIZE_Y + 2, 0, TRUE);

			for (int i = 0; i < 25; i++) {
				for (int j = 0; j < 25; j++) {
					xLeft = MENU_MAP_LEFT + 2 + j * (MENU_MAP_SIZE + 2);
					yUp = MENU_MAP_UP + 2 + i * (MENU_MAP_SIZE + 2);

					switch (mwallType[j][i]) {
					case 1: DrawBox(xLeft, yUp, xLeft + MENU_MAP_SIZE, yUp + MENU_MAP_SIZE, GetColor(255, 255, 255), TRUE);	break;
					case 2: DrawBox(xLeft, yUp, xLeft + MENU_MAP_SIZE, yUp + MENU_MAP_SIZE, GetColor(0, 0, 255), TRUE);		break;
					case 3: DrawBox(xLeft, yUp, xLeft + MENU_MAP_SIZE, yUp + MENU_MAP_SIZE, GetColor(0, 255, 0), TRUE);		break;
					case 4: DrawBox(xLeft, yUp, xLeft + MENU_MAP_SIZE, yUp + MENU_MAP_SIZE, GetColor(255, 0, 0), TRUE);		break;
					}
				}
			}

			xLeft = MENU_MAP_LEFT + 2 + mx * (MENU_MAP_SIZE + 2);
			yUp = MENU_MAP_UP + 2 + my * (MENU_MAP_SIZE + 2);
			switch (mdir) {
			case 0:	DrawTriangle(xLeft, yUp + MENU_MAP_SIZE, xLeft + MENU_MAP_SIZE / 2, yUp, xLeft + MENU_MAP_SIZE, yUp + MENU_MAP_SIZE, GetColor(255, 0, 0), TRUE); break;
			case 1: DrawTriangle(xLeft, yUp, xLeft + MENU_MAP_SIZE, yUp + MENU_MAP_SIZE / 2, xLeft, yUp + MENU_MAP_SIZE, GetColor(255, 0, 0), TRUE); break;
			case 2: DrawTriangle(xLeft, yUp, xLeft + MENU_MAP_SIZE, yUp, xLeft + MENU_MAP_SIZE / 2, yUp + MENU_MAP_SIZE, GetColor(255, 0, 0), TRUE); break;
			case 3: DrawTriangle(xLeft + MENU_MAP_SIZE, yUp, xLeft, yUp + MENU_MAP_SIZE / 2, xLeft + MENU_MAP_SIZE, yUp + MENU_MAP_SIZE, GetColor(255, 0, 0), TRUE); break;
			}
			break;
		case status:

			textBox->DrawWindow(160, 40, 424, 400);

			row = 100;
			stringX = 190;
			stringY = 80;

			for (int i = 0; i < CHARACTER_SIZE; i++) {
				if (GData.GetCharacterFlag(i)) {

					if (chooseChara == i && depth == 1) DrawFormatString(stringX, stringY + row * i, colorY, "%s HP:%d/%d MP:%d/%d \nSTR:%d VIT:%d AGI:%d INT:%d",
						GData.GetCharacterName(i).c_str(), GData.GetCharacterStatus(i, 0, 1), GData.GetCharacterStatus(i, 0, 0),
						GData.GetCharacterStatus(i, 1, 1), GData.GetCharacterStatus(i, 1, 0), GData.GetCharacterStatus(i, 2, 1),
						GData.GetCharacterStatus(i, 3, 1), GData.GetCharacterStatus(i, 4, 1), GData.GetCharacterStatus(i, 5, 1));
					else DrawFormatString(stringX, stringY + row * i, colorW, "%s HP:%d/%d MP:%d/%d \nSTR:%d VIT:%d AGI:%d INT:%d",
						GData.GetCharacterName(i).c_str(), GData.GetCharacterStatus(i, 0, 1), GData.GetCharacterStatus(i, 0, 0),
						GData.GetCharacterStatus(i, 1, 1), GData.GetCharacterStatus(i, 1, 0), GData.GetCharacterStatus(i, 2, 1),
						GData.GetCharacterStatus(i, 3, 1), GData.GetCharacterStatus(i, 4, 1), GData.GetCharacterStatus(i, 5, 1));

					drawCount++;
					charaNum[drawCount - 1] = i;
				}
			}

			break;
		case soubi:
			textBox->DrawWindow(160, 40, 424, 400);

			row = 100;
			stringX = 190;
			stringY = 80;

			for (int i = 0; i < CHARACTER_SIZE; i++) {
				if (GData.GetCharacterFlag(i)) {
					DrawFormatString(stringX, stringY + row * drawCount, colorW, "%s ", GData.GetCharacterName(i).c_str());

					if (chooseChara == i && soubiType == 0 && depth == 1 && GData.GetCharacterSoubi(i, 0) == -1) DrawFormatString(stringX + 100, stringY + row * i, colorY, "武器:");
					else if (GData.GetCharacterSoubi(i, 0) == -1) DrawFormatString(stringX + 100, stringY + row * i, colorW, "武器:");
					else if (chooseChara == i && soubiType == 0 && depth == 1) DrawFormatString(stringX + 100, stringY + row * i, colorY, "武器:\n%s", GData.GetSoubiText(GData.GetCharacterSoubi(i, 0), 0).c_str());
					else DrawFormatString(stringX + 100, stringY + row * i, colorW, "武器:\n%s", GData.GetSoubiText(GData.GetCharacterSoubi(i, 0), 0).c_str());

					if (chooseChara == i && soubiType == 1 && depth == 1 && GData.GetCharacterSoubi(i, 1) == -1) DrawFormatString(stringX + 220, stringY + row * i, colorY, "アクセ:");
					else if (GData.GetCharacterSoubi(i, 1) == -1)DrawFormatString(stringX + 220, stringY + row * i, colorW, "アクセ:");
					else if (chooseChara == i && soubiType == 1 && depth == 1) DrawFormatString(stringX + 220, stringY + row * i, colorY, "アクセ:\n%s", GData.GetSoubiText(GData.GetCharacterSoubi(i, 1), 0).c_str());
					else DrawFormatString(stringX + 220, stringY + row * i, colorW, "アクセ:\n%s", GData.GetSoubiText(GData.GetCharacterSoubi(i, 1), 0).c_str());

					drawCount++;
					charaNum[drawCount - 1] = i;
				}
			}
			break;
		case item:
			textBox->DrawWindow(160, 40, 424, 40);
			textBox->DrawWindow(160, 80, 424, 360);

			stringX = 175;
			stringY = 50;

			if (itemType == 0 && depth == 1) DrawFormatString(stringX, stringY + row * 0, colorY, "消耗品");
			else DrawFormatString(stringX, stringY + row * 0, colorW, "消耗品");
			if (itemType == 1 && depth == 1) DrawFormatString(stringX + 210, stringY + row * 0, colorY, "だいじなもの");
			else DrawFormatString(stringX + 210, stringY + row * 0, colorW, "だいじなもの");
			break;
		case title:
			textBox->DrawWindow(160, 40, 424, 400);
			break;
		default:
			textBox->DrawWindow(160, 40, 424, 400);
			break;
		}
		break;
	case 2:
		switch (mode) {
		case map:
			break;
		case status:
			textBox->DrawWindow(160, 40, 424, 200);
			textBox->DrawWindow(160, 240, 424, 160);
			textBox->DrawWindow(160, 400, 424, 40);

			row = 30;
			stringX = 175;
			stringY = 60;

			DrawFormatString(stringX, stringY + row * 0, colorW, "%s ", GData.GetCharacterName(chooseChara).c_str());
			DrawFormatString(stringX, stringY + row * 1, colorW, "HP:%d/%d ", GData.GetCharacterStatus(chooseChara, 0, 1), GData.GetCharacterStatus(chooseChara, 0, 0));
			DrawFormatString(stringX, stringY + row * 2, colorW, "MP:%d/%d ", GData.GetCharacterStatus(chooseChara, 1, 1), GData.GetCharacterStatus(chooseChara, 1, 0));
			DrawFormatString(stringX, stringY + row * 3, colorW, "STR:%d ", GData.GetCharacterStatus(chooseChara, 2, 1));
			DrawFormatString(stringX + 100, stringY + row * 3, colorW, "VIT:%d ", GData.GetCharacterStatus(chooseChara, 3, 1));
			DrawFormatString(stringX, stringY + row * 4, colorW, "AGI:%d ", GData.GetCharacterStatus(chooseChara, 4, 1));
			DrawFormatString(stringX + 100, stringY + row * 4, colorW, "INT:%d ", GData.GetCharacterStatus(chooseChara, 5, 1));
			DrawGraph(480, 240, GData.GetCharacterImage(chooseChara), TRUE);

			row = 20;
			stringX = 175;
			stringY = 255;

			for (int i = 0; i < SKILL_SIZE; i++) {
				skillNum[i] = -1;
				if (GData.GetCharacterSkillCode(chooseChara, i) == 1) {
					if (chooseSkill == drawCount) {
						DrawFormatString(stringX, stringY + row * drawCount, colorY, "%s", GData.GetSkillText(i, 0).c_str());
						DrawFormatString(stringX + 300, stringY + row * drawCount, colorY, "消費MP:%d", GData.GetSkillPoint(i, 1));
					}
					else {
						DrawFormatString(stringX, stringY + row * drawCount, colorW, "%s", GData.GetSkillText(i, 0).c_str());
						DrawFormatString(stringX + 300, stringY + row * drawCount, colorW, "消費MP:%d", GData.GetSkillPoint(i, 1));
					}
					drawCount++;
					skillNum[drawCount - 1] = i;
				}
			}

			stringX = 175;
			stringY = 412;
			if (skillNum[chooseSkill] != -1) {
				DrawFormatString(stringX, stringY + row * 0, colorW, "%s", GData.GetSkillText(skillNum[chooseSkill], 1).c_str());
			}
			break;

		case soubi:

			textBox->DrawWindow(160, 40, 424, 40);
			textBox->DrawWindow(160, 80, 424, 320);
			textBox->DrawWindow(160, 400, 424, 40);

			stringX = 175;
			stringY = 50;

			DrawFormatString(stringX, stringY + row * 0, colorW, "%s", GData.GetCharacterName(chooseChara).c_str());

			row = 20;
			stringX = 175;
			stringY = 95;

			for (int i = 0; i < SOUBI_SIZE; i++) {
				soubiNum[i] = -1;
				if (GData.GetSoubiPoint(i, 5) >= 1) {
					if (soubiType == GData.GetSoubiPoint(i, 1)) {
						if (i != GData.GetCharacterSoubi(0, soubiType)
							&& i != GData.GetCharacterSoubi(1, soubiType)
							&& i != GData.GetCharacterSoubi(2, soubiType)
							&& i != GData.GetCharacterSoubi(3, soubiType)) {
							if (drawCount == chooseSoubi) {
								DrawFormatString(stringX, stringY + row * drawCount, colorY, "%s", GData.GetSoubiText(i, 0).c_str());
								DrawFormatString(stringX + 300, stringY + row * drawCount, colorY, "X%d", GData.GetSoubiPoint(i, 5));
							}
							else {
								DrawFormatString(stringX, stringY + row * drawCount, colorW, "%s", GData.GetSoubiText(i, 0).c_str());
								DrawFormatString(stringX + 300, stringY + row * drawCount, colorW, "X%d", GData.GetSoubiPoint(i, 5));
							}
							drawCount++;
							soubiNum[drawCount - 1] = i;
						}
					}
				}
			}

			stringX = 175;
			stringY = 412;

			if (soubiNum[chooseSoubi] != -1) {
				DrawFormatString(stringX, stringY + row * 0, colorW, "%s", GData.GetSoubiText(soubiNum[chooseSoubi], 1).c_str());
			}
			break;

		case item:
			textBox->DrawWindow(160, 40, 424, 81);
			textBox->DrawWindow(160, 80, 424, 320);
			textBox->DrawWindow(160, 400, 424, 40);

			stringX = 175;
			stringY = 50;

			if (itemType == 0) DrawFormatString(stringX, stringY + row * 0, colorY, "消耗品");
			else DrawFormatString(stringX, stringY + row * 0, colorW, "消耗品");
			if (itemType == 1) DrawFormatString(stringX + 210, stringY + row * 0, colorY, "だいじなもの");
			else DrawFormatString(stringX + 210, stringY + row * 0, colorW, "だいじなもの");

			row = 20;
			stringX = 175;
			stringY = 95;

			for (int i = 0; i < ITEM_SIZE; i++) {
				itemNum[i] = -1;
				if (GData.GetItemPoint(i, 8) >= 1) {
					if (itemType == GData.GetItemPoint(i, 1)) {
						if (drawCount == chooseItem) {
							DrawFormatString(stringX, stringY + row * drawCount, colorY, "%s", GData.GetItemText(i, 0).c_str());
							DrawFormatString(stringX + 300, stringY + row * drawCount, colorY, "X%d", GData.GetItemPoint(i, 8));
						}
						else {
							DrawFormatString(stringX, stringY + row * drawCount, colorW, "%s", GData.GetItemText(i, 0).c_str());
							DrawFormatString(stringX + 300, stringY + row * drawCount, colorW, "X%d", GData.GetItemPoint(i, 8));
						}
						drawCount++;
						itemNum[drawCount - 1] = i;
					}
				}
			}

			stringX = 175;
			stringY = 412;

			if (itemNum[chooseItem] != -1) {
				DrawFormatString(stringX, stringY + row * 0, colorW, "%s", GData.GetItemText(itemNum[chooseItem], 1).c_str());
			}
			break;

		case title:
			break;
		}
		break;
	case 3:
		DrawGraph(0, 0, menuScreen, TRUE);
		switch (mode) {
		case status:
			textBox->DrawWindow(220, 140, 324, 80);
			textBox->DrawWindow(460, 220, 80, 64);

			stringX = 230;
			stringY = 170;

			DrawFormatString(stringX, stringY + row * 0, colorW, "このスキルを使用しますか？");

			row = 25;
			stringX = 470;
			stringY = 230;

			if (YN == 0) DrawFormatString(stringX, stringY + row * 0, colorY, "はい　");
			else DrawFormatString(stringX, stringY + row * 0, colorW, "はい　");

			if (YN == 1) DrawFormatString(stringX, stringY + row * 1, colorY, "いいえ");
			else DrawFormatString(stringX, stringY + row * 1, colorW, "いいえ");
			break;
		case soubi:
			textBox->DrawWindow(220, 140, 324, 80);
			textBox->DrawWindow(460, 220, 80, 64);

			stringX = 230;
			stringY = 170;

			DrawFormatString(stringX, stringY + row * 0, colorW, "%sを装備しますか？", GData.GetSoubiText(soubiNum[chooseSoubi], 0).c_str());

			row = 25;
			stringX = 470;
			stringY = 230;

			if (YN == 0) DrawFormatString(stringX, stringY + row * 0, colorY, "はい　");
			else DrawFormatString(stringX, stringY + row * 0, colorW, "はい　");

			if (YN == 1) DrawFormatString(stringX, stringY + row * 1, colorY, "いいえ");
			else DrawFormatString(stringX, stringY + row * 1, colorW, "いいえ");
			break;
		case item:
			textBox->DrawWindow(220, 140, 324, 80);
			textBox->DrawWindow(460, 220, 80, 64);

			stringX = 230;
			stringY = 170;

			DrawFormatString(stringX, stringY + row * 0, colorW, "このアイテムを使用しますか？");

			row = 25;
			stringX = 470;
			stringY = 230;

			if (YN == 0) DrawFormatString(stringX, stringY + row * 0, colorY, "はい　");
			else DrawFormatString(stringX, stringY + row * 0, colorW, "はい　");

			if (YN == 1) DrawFormatString(stringX, stringY + row * 1, colorY, "いいえ");
			else DrawFormatString(stringX, stringY + row * 1, colorW, "いいえ");
			break;
		}
		break;
	case 4:
		DrawGraph(0, 0, menuScreen, TRUE);
		switch (mode) {
		case status:
			textBox->DrawWindow(220, 140, 324, 80);
			textBox->DrawWindow(460, 220, 80, 128);

			stringX = 230;
			stringY = 170;

			DrawFormatString(stringX, stringY + row * 0, colorW, "このスキルを誰に使用しますか？");

			row = 25;
			stringX = 470;
			stringY = 230;

			for (int i = 0; i < CHARACTER_SIZE; i++) {
				if (GData.GetCharacterFlag(i)) {
					if (targetChara == drawCount) DrawFormatString(stringX, stringY + row * drawCount, colorY, "%s ", GData.GetCharacterName(i).c_str());
					else DrawFormatString(stringX, stringY + row * drawCount, colorW, "%s ", GData.GetCharacterName(i).c_str());

					drawCount++;
				}
			}
			break;
		case item:
			textBox->DrawWindow(220, 140, 324, 80);
			textBox->DrawWindow(460, 220, 80, 128);

			stringX = 230;
			stringY = 170;

			DrawFormatString(stringX, stringY + row * 0, colorW, "このアイテムを誰に使用しますか？");

			row = 25;
			stringX = 470;
			stringY = 230;

			for (int i = 0; i < CHARACTER_SIZE; i++) {
				if (GData.GetCharacterFlag(i)) {
					if (targetChara == drawCount) DrawFormatString(stringX, stringY + row * drawCount, colorY, "%s ", GData.GetCharacterName(i).c_str());
					else DrawFormatString(stringX, stringY + row * drawCount, colorW, "%s ", GData.GetCharacterName(i).c_str());

					drawCount++;
				}
			}
			break;
		}
		break;
	case 5:
		DrawGraph(0, 0, menuScreen, TRUE);
		textBox->DrawWindow(220, 140, 324, 80);

		stringX = 230;
		stringY = 170;

		DrawFormatString(stringX, stringY + row * 0, colorW, "MPが足りません！");
		break;
	}
}

void Menu_c::DrawCursor()
{
	DrawTriangle(cursorX - 5, cursorY - 3, cursorX + 5, cursorY, cursorX - 5, cursorY + 3, GetColor(255, 255, 255), TRUE);
}

void Menu_c::CheckKey()
{
	if (mKey[KEY_INPUT_DOWN] == 1) {
		switch (depth) {
		case 0:
			if (mode < 6) {
				mode++;
			}
			break;
		case 1:
			switch (mode) {
			case status:
				if (chooseChara < drawCount - 1) {
					chooseChara++;
				}
				break;
			case soubi:
				if (chooseChara < drawCount - 1) {
					chooseChara++;
				}
				break;
			}
			break;
		case 2:
			switch (mode) {
			case status:
				if (chooseSkill < drawCount - 1) {
					chooseSkill++;
				}
				break;
			case soubi:
				if (chooseSoubi < drawCount - 1) {
					chooseSoubi++;
				}
				break;
			case item:
				if (chooseItem < drawCount - 1) {
					chooseItem++;
				}
				break;
			}
			break;
		case 3:
			if (YN != 1) {
				YN++;
			}
			break;
		case 4:
			if (targetChara < drawCount - 1) {
				targetChara++;
			}
			break;
		}
		GMusic.ReserveSound(se[cursor], DX_PLAYTYPE_BACK);
	}
	else if (mKey[KEY_INPUT_UP] == 1) {
		switch (depth) {
		case 0:
			if (mode > 0) {
				mode--;
			}
			break;
		case 1:
			switch (mode) {
			case status:
				if (chooseChara > 0) {
					chooseChara--;
				}
				break;
			case soubi:
				if (chooseChara > 0) {
					chooseChara--;
				}
				break;
			}
			break;
		case 2:
			switch (mode) {
			case status:
				if (chooseSkill > 0) {
					chooseSkill--;
				}
				break;
			case soubi:
				if (chooseSoubi > 0) {
					chooseSoubi--;
				}
				break;
			case item:
				if (chooseItem > 0) {
					chooseItem--;
				}
				break;
			}
			break;
		case 3:
			if (YN != 0) {
				YN--;
			}
			break;
		case 4:
			if (targetChara > 0) {
				targetChara--;
			}
			break;
		}
		GMusic.ReserveSound(se[cursor], DX_PLAYTYPE_BACK);
	}
	else if (mKey[KEY_INPUT_LEFT] == 1) {
		switch (depth) {
		case 0: break;
		case 1:
			switch (mode) {
			case soubi:
				if (soubiType > 0) {
					soubiType--;
				}
				break;
			case item:
				if (itemType > 0) {
					itemType--;
				}
				break;
			}
			break;
		case 2:
		case 3:
		case 4: break;
		}
		GMusic.ReserveSound(se[cursor], DX_PLAYTYPE_BACK);
	}
	else if (mKey[KEY_INPUT_RIGHT] == 1) {
		switch (depth) {
		case 0: break;
		case 1:
			switch (mode) {
			case soubi:
				if (soubiType < 1) {
					soubiType++;
				}
				break;
			case item:
				if (itemType < 1) {
					itemType++;
				}
				break;
			}
			break;
		case 2:
		case 3:
		case 4: break;
		}
		GMusic.ReserveSound(se[cursor], DX_PLAYTYPE_BACK);
	}
	else if (mKey[KEY_INPUT_Z] == 1) {
		switch (mode) {
		case status:
			switch (depth) {
			case 0:
				depth++;
				break;
			case 1:
				depth++;
				break;
			case 2:
				if (skillNum[chooseSkill] != -1) {
					if (GData.GetSkillPoint(skillNum[chooseSkill], 6) == 0) {
						DeleteGraph(menuScreen);
						SaveDrawScreen(0, 0, 640, 480, "resource/MenuScreen.bmp");
						menuScreen = LoadGraph("resource/MenuScreen.bmp");
						depth++;
					}
				}
				else {
					//ブー
				}
				break;
			case 3:
				if (YN == 0) {
					if (GData.GetSkillPoint(skillNum[chooseSkill], 6) == 0) {
						depth++;
					}
					else {
						if (UseSkill(skillNum[chooseSkill], -1, chooseChara) == FALSE) {
							depth = 5;
						}
					}
				}
				else {
					YN = 0;
					depth--;
				}
				break;
			case 4:
				if (UseSkill(skillNum[chooseSkill], targetChara, chooseChara) == FALSE) {
					depth = 5;
				}
				else {
					YN = 0;
					targetChara = 0;
					depth = 2;
				}
				break;
			case 5:
				depth = 2;
				break;
			}
			break;
		case soubi:
			switch (depth) {
			case 0:
				depth++;
				break;
			case 1:
				depth++;
				break;
			case 2:
				if (soubiNum[chooseSoubi] != -1) {
					DeleteGraph(menuScreen);
					SaveDrawScreen(0, 0, 640, 480, "resource/MenuScreen.bmp");
					menuScreen = LoadGraph("resource/MenuScreen.bmp");
					depth++;
				}
				break;
			case 3:
				if (YN == 0) {
					GData.SetCharacterSoubi(charaNum[chooseChara], soubiType, soubiNum[chooseSoubi]);
					YN = 0;
					depth = 2;
				}
				else {
					YN = 0;
					depth--;
				}
				break;
			}
			break;
		case item:
			switch (depth) {
			case 0:
				depth++;
				break;
			case 1:
				depth++;
				break;
			case 2:
				if (itemNum[chooseItem] != -1) {
					if (GData.GetItemPoint(itemNum[chooseItem], 7) == 0) {
						DeleteGraph(menuScreen);
						SaveDrawScreen(0, 0, 640, 480, "resource/MenuScreen.bmp");
						menuScreen = LoadGraph("resource/MenuScreen.bmp");
						depth++;
					}
					else {
						//ブー
					}
				}
				break;
			case 3:
				if (YN == 0) {
					if (GData.GetItemPoint(itemNum[chooseItem], 6) == 0) {
						depth++;
					}
					else {
						UseItem(itemNum[chooseItem], -1);
					}
				}
				else {
					YN = 0;
					depth--;
				}
				break;
			case 4:
				UseItem(itemNum[chooseItem], targetChara);
				YN = 0;
				targetChara = 0;
				depth = 2;
				break;
			}
			break;
		case title:
			GData.SceneRequest(1, 2);

			break;
		case save:
			GData.SceneRequest(1, 3);
			break;
		case option:
			GData.SceneRequest(1, 5);
			break;
		}
		GMusic.ReserveSound(se[decision], DX_PLAYTYPE_BACK);
	}
	else if (mKey[KEY_INPUT_X] == 1) {
		switch (depth) {
		case 0:
			GData.SceneBackRequest();
			mode = 0;
			break;
		case 1:
			itemType = 0;
			soubiType = 0;
			chooseChara = 0;
			depth--;
			break;
		case 2:
			chooseItem = 0;
			chooseSoubi = 0;
			chooseSkill = 0;
			depth--;
			break;
		case 3:
			YN = 0;
			depth--;
			break;
		case 4:
			targetChara = 0;
			depth--;
			break;
		case 5:
			YN = 0;
			targetChara = 0;
			depth = 2;
			break;
		}
		GMusic.ReserveSound(se[decision], DX_PLAYTYPE_BACK);
	}
	else if (mKey[KEY_INPUT_V] == 1) {
		if (mode == soubi && depth == 1) {
			GData.SetCharacterSoubi(charaNum[chooseChara], soubiType, -1);
		}
		GMusic.ReserveSound(se[decision], DX_PLAYTYPE_BACK);
	}
	else if (mKey[KEY_INPUT_C] == 1) {
		GData.SceneBackRequest();
		mode = 0;
		GMusic.ReserveSound(se[decision], DX_PLAYTYPE_BACK);
	}

}

void Menu_c::UseItem(int num, int target)
{
	if (num != -1) {
		int x = 0;
		int y = 0;
		int effect1 = GData.GetItemPoint(num, 2);
		int effect2 = GData.GetItemPoint(num, 3);

		if (effect1 < 7 && effect2 < 7 && GData.GetCharacterState(target, 0) == 0) {
			if (GData.GetItemPoint(num, 6) == 1) {
				for (int i = 0; i < CHARACTER_SIZE; i++) {
					if (GData.GetCharacterFlag(i) == 1) {
						x = GData.GetCharacterStatus(i, effect1 - 1, 1);
						if (GData.GetItemPoint(num, 3) != -1) {
							y = GData.GetCharacterStatus(i, effect2 - 1, 1);
						}

						x += GData.GetItemPoint(num, 4);
						if (effect1 <= 1 && x > GData.GetCharacterStatus(i, effect1, 0)) {
							x = GData.GetCharacterStatus(i, effect1 - 1, 0);
						}
						y += GData.GetItemPoint(num, 5);
						if (effect2 <= 1 && y > GData.GetCharacterStatus(i, effect2, 0)) {
							y = GData.GetCharacterStatus(i, effect2 - 1, 0);
						}

						GData.SetCharacterStatus(i, effect1 - 1, x, 1);
						if (GData.GetItemPoint(num, 3) != -1) {
							GData.SetCharacterStatus(i, effect2 - 1, y, 1);
						}
					}
				}
			}
			else {
				x = GData.GetCharacterStatus(target, effect1 - 1, 1);
				if (GData.GetItemPoint(num, 3) != -1) {
					y = GData.GetCharacterStatus(target, effect2 - 1, 1);
				}

				x += GData.GetItemPoint(num, 4);
				if (effect1 <= 1 && x > GData.GetCharacterStatus(target, effect1 - 1, 0)) {
					x = GData.GetCharacterStatus(target, effect1 - 1, 0);
				}
				y += GData.GetItemPoint(num, 5);
				if (effect2 <= 1 && y > GData.GetCharacterStatus(target, effect2 - 1, 0)) {
					y = GData.GetCharacterStatus(target, effect2 - 1, 0);
				}

				GData.SetCharacterStatus(target, effect1 - 1, x, 1);
				if (GData.GetItemPoint(num, 3) != -1) {
					GData.SetCharacterStatus(target, effect2 - 1, y, 1);
				}
			}

			GData.CalcItemFlag(num, -1);
		}
		else if (GData.GetCharacterState(target, 0) == 1) {
			GData.ChangeCharacterState(target, 0);
			GData.SetCharacterStatus(target, 0, 1, GData.GetCharacterStatus(target, 0, 0));
			GData.CalcItemFlag(num, -1);
		}
		else {
			//ブー
		}
	}
}
void Menu_c::WearSoubi(int num, int target, int part)
{
	if (num != -1) {
		GData.SetCharacterSoubi(target, part, num);
	}
}
bool Menu_c::UseSkill(int num, int target, int user)
{
	if (num != -1) {
		int x = 0;
		int mp = GData.GetCharacterStatus(user, 1, 1);
		int effect = GData.GetSkillPoint(num, 2);
		if (mp < GData.GetSkillPoint(num, 1)) {
			return FALSE;
		}

		if (effect < 7 && GData.GetCharacterState(target, 0) == 0) {
			if (GData.GetSkillPoint(num, 6) == 1) {
				for (int i = 0; i < CHARACTER_SIZE; i++) {
					if (GData.GetCharacterFlag(i) == 1) {
						x = GData.GetCharacterStatus(i, effect - 1, 1);

						x += GData.GetSkillPoint(num, 4);
						if (effect <= 1 && x > GData.GetCharacterStatus(i, effect - 1, 0)) {
							x = GData.GetCharacterStatus(i, effect - 1, 0);
						}

						GData.SetCharacterStatus(i, effect - 1, x, 1);
					}
				}
			}
			else {
				x = GData.GetCharacterStatus(target, effect - 1, 1);

				x += GData.GetSkillPoint(num, 4);
				if (effect <= 1 && x > GData.GetCharacterStatus(target, effect - 1, 0)) {
					x = GData.GetCharacterStatus(target, effect - 1, 0);
				}

				GData.SetCharacterStatus(target, effect - 1, x, 1);
			}
			mp -= GData.GetSkillPoint(num, 1);
			GData.SetCharacterStatus(user, 3, mp, 1);
		}
		else if (GData.GetCharacterState(target, 0) == 1) {
			GData.ChangeCharacterState(target, 0);
			GData.SetCharacterStatus(target, 0, 1, GData.GetCharacterStatus(target, 0, 0));
			mp -= GData.GetSkillPoint(num, 1);
			GData.SetCharacterStatus(user, 3, mp, 1);
		}
		else {
			//ブー
		}

		return TRUE;
	}
}

void Menu_c::LoadWindow()
{
	windowH = LoadGraph("resource/window/window_H.png");
	windowW = LoadGraph("resource/window/window_W.png");
}
