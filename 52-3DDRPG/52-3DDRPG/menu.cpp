#include "define.h"

Menu_c::Menu_c()
{
}

Menu_c::~Menu_c()
{
}

void Menu_c::KeyUpdata(int Key[256])
{
	for (int i = 0; i < 256; i++) {
		mKey[i] = Key[i];
	}
}

void Menu_c::DrawGoal()
{
	int drawCount;

	for (int i = 0; i < EVENT_SIZE; i++) {
		drawCount += mData->GetEventFlag(mscenario, i);
	}

	printfDx("%s");
}

void Menu_c::MenuAll()
{
	clsDx();

	DrawLeft();
	DrawRight();
	DrawCursor();
	CheckKey();
}

void Menu_c::DrawBack()
{
}

void Menu_c::DrawLeft()
{
	printfDx("マップ");
	printfDx("ステータス");
	printfDx("装備");
	printfDx("アイテム");
	printfDx("ライブラリ");
	printfDx("セーブ");
	printfDx("オプション");
	printfDx("プレイ時間");
	printfDx("現在のシナリオ");
}

void Menu_c::DrawRight()
{
	drawCount = 0;

	printfDx("/nMode:%d, ", mode);
	printfDx("ItemType:%d, ", itemType);
	printfDx("SoubiType:%d, ", soubiType);
	printfDx("CChara:%d, ", chooseChara);
	printfDx("CItem:%d, ", chooseItem);
	printfDx("CSoubi:%d, ", chooseSoubi);
	printfDx("CSkill:%d, ", chooseSoubi);
	printfDx("YN:%d, ", YN);

	switch (depth) {
	case 0:
	case 1:
		switch (mode) {
		case map:
			DrawGoal();

			mscenario = mData->GetScenario();
			mdir = mData->GetDir();
			mx = mData->GetDungeonX();
			my = mData->GetDungeonY();
			for (int i = 0; i < MAP_SIZE_X; i++) {
				for (int j = 0; j < MAP_SIZE_Y; j++) {
					mwallType[i][j] = mData->GetWallType(i, j);
				}
			}

			int xLeft, yUp, size;
			size = 14;
			DrawBox(MENU_MAP_LEFT, MENU_MAP_UP, MENU_MAP_LEFT + 402, MENU_MAP_UP + 402, 0, TRUE);

			for (int i = 0; i < 25; i++) {
				for (int j = 0; j < 25; j++) {
					xLeft = MENU_MAP_LEFT + 1 + j * 16;
					yUp =  MENU_MAP_UP + 1 + i * 16;

					switch (mwallType[mx - 4 + j][my - 4 + i]) {
					case 1: DrawBox(xLeft, yUp, xLeft + size, yUp + size, GetColor(255, 255, 255), TRUE);	break;
					case 2: DrawBox(xLeft, yUp, xLeft + size, yUp + size, GetColor(255, 0, 0), TRUE);		break;
					case 3: DrawBox(xLeft, yUp, xLeft + size, yUp + size, GetColor(0, 255, 0), TRUE);		break;
					case 4: DrawBox(xLeft, yUp, xLeft + size, yUp + size, GetColor(0, 0, 255), TRUE);		break;
					}
				}
			}

			xLeft = MENU_MAP_LEFT + 1 + mx * 16;
			yUp = MENU_MAP_UP + 1 + my * 16;
			switch (mdir) {
			case 0:	DrawTriangle(xLeft, yUp + size, xLeft + size / 2, yUp, xLeft + size, yUp + size, GetColor(255, 255, 0), TRUE); break;
			case 1: DrawTriangle(xLeft, yUp, xLeft + size, yUp + size / 2, xLeft, yUp + size, GetColor(255, 255, 0), TRUE); break;
			case 2: DrawTriangle(xLeft, yUp, xLeft + size, yUp, xLeft + size / 2, yUp + size, GetColor(255, 255, 0), TRUE); break;
			case 3: DrawTriangle(xLeft + size, yUp, xLeft, yUp + size / 2, xLeft + size, yUp + size, GetColor(255, 255, 0), TRUE); break;
			}
			break;
		case status:
			for (int i = 0; i < CHARACTER_SIZE; i++) {
				if (mData->GetCharacterFlag(i)) {
					printfDx("/n%s ", mData->GetCharacterName(i));
					printfDx("HP:%d/%d ", mData->GetCharacterPoint(i, 0), mData->GetCharacterPoint(i, 2));
					printfDx("MP:%d/%d ", mData->GetCharacterPoint(i, 1), mData->GetCharacterPoint(i, 3));
					printfDx("STR:%d ", mData->GetCharacterPoint(i, 4));
					printfDx("VIT:%d ", mData->GetCharacterPoint(i, 5));
					printfDx("AGI:%d ", mData->GetCharacterPoint(i, 6));
					printfDx("INT:%d ", mData->GetCharacterPoint(i, 7));

					charaNum[drawCount] = i;
					drawCount++;
				}
			}
			break;
		case soubi:
			for (int i = 0; i < CHARACTER_SIZE; i++) {
				if (mData->GetCharacterFlag(i)) {
					printfDx("/n%s ", mData->GetCharacterName(i));
					printfDx("武器:%s, ", mData->GetSoubiText(mData->GetCharacterPoint(i, 9), 0));
					printfDx("アクセ:%s, ", mData->GetSoubiText(mData->GetCharacterPoint(i, 10), 0));

					charaNum[drawCount] = i;
					drawCount++;
				}
			}
			break;
		case item:
			printfDx("消耗品");
			printfDx("だいじなもの");
			break;
		case library:
			break;
		}
		break;
	case 2:
		switch (mode) {
		case map:
			break;
		case status:
			printfDx("/n%s ", mData->GetCharacterName(chooseChara));
			printfDx("HP:%d/%d ", mData->GetCharacterPoint(chooseChara, 0), mData->GetCharacterPoint(chooseChara, 2));
			printfDx("MP:%d/%d ", mData->GetCharacterPoint(chooseChara, 1), mData->GetCharacterPoint(chooseChara, 3));
			printfDx("STR:%d ", mData->GetCharacterPoint(chooseChara, 4));
			printfDx("VIT:%d ", mData->GetCharacterPoint(chooseChara, 5));
			printfDx("AGI:%d ", mData->GetCharacterPoint(chooseChara, 6));
			printfDx("INT:%d ", mData->GetCharacterPoint(chooseChara, 7));
			DrawGraph(480, 240, mData->GetCharacterPoint(chooseChara, 8), TRUE);

			for (int i = 0; i < SKILL_CODE_SIZE; i++) {
				if (mData->GetCharacterSkillCode(chooseChara, i) == -1) {
					printfDx("/n%s, ", mData->GetSkillText(mData->GetCharacterSkillCode(chooseChara, i), 0));
					skillNum[drawCount] = mData->GetCharacterSkillCode(chooseChara, i);
					drawCount++;
				}
			}
			
			printfDx("/n%s", mData->GetSkillText(skillNum[chooseSkill], 1));
			break;

		case soubi:
			printfDx("%s", mData->GetCharacterName(chooseChara));
			
			for (int i = 0; i < SOUBI_SIZE; i++) {
				if (mData->GetSoubiFlag(i) >= 1) {
					if (soubiType == mData->GetSoubiPoint(i, 1)) {
						if (i == mData->GetCharacterPoint(chooseChara, soubiType + 9)) printfDx("E.");
						printfDx("%s, ", mData->GetSoubiText(i, 0));
						soubiNum[drawCount] = i;
						drawCount++;
					}
				}
			}

			printfDx("/n%s", mData->GetSoubiText(soubiNum[chooseSoubi], 1));
			break;

		case item:
			printfDx("消耗品");
			printfDx("だいじなもの");

			for (int i = 0; i < ITEM_SIZE; i++) {
				if (mData->GetItemFlag(i) >= 1) {
					if (itemType == mData->GetItemPoint(i, 1)) {
						printfDx("%s, " ,mData->GetItemText(i, 0));
						itemNum[drawCount] = i;
						drawCount++;
					}
				}
			}

			printfDx("/n%s", mData->GetItemText(itemNum[chooseItem], 1));
			break;

		case library:
			break;
		}
	case 3:
		switch (mode) {
		case status:
			printfDx("/nこのスキルを使用しますか？");
			printfDx("はい　");
			printfDx("いいえ");
			break;
		case soubi:
			printfDx("/n%sを装備しますか？", mData->GetSoubiText(soubiNum[chooseSoubi], 0));
			printfDx("はい　");
			printfDx("いいえ");
			break;
		case item:
			printfDx("/nこのアイテムを使用しますか？");
			printfDx("はい　");
			printfDx("いいえ");
			break;
		}
	case 4: 
		switch (mode) {
		case status:
			printfDx("/nこのスキルを誰に使用しますか？");
			for (int i = 0; i < CHARACTER_SIZE; i++) {
				if (mData->GetCharacterFlag(i)) {
					printfDx("/n%s ", mData->GetCharacterName(i));
				}
			}
			break;
		case item:
			printfDx("/nこのアイテムを誰に使用しますか？");
			for (int i = 0; i < CHARACTER_SIZE; i++) {
				if (mData->GetCharacterFlag(i)) {
					printfDx("/n%s ", mData->GetCharacterName(i));
				}
			}
			break;
		}
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
			if (cursorY != limitDOWN) {
				cursorY += 20;
				mode++;
			}
			break;
		case 1:
			switch (mode) {
			case status:
				if (chooseChara != drawCount) {
					chooseChara++;
				}
				break;
			case soubi:
				if (chooseChara != drawCount) {
					chooseChara++;
				}
				break;
			}
			break;
		case 2:
			switch (mode) {
			case status:
				if (chooseSkill != drawCount) {
					chooseSkill++;
				}
				break;
			case soubi:
				if (chooseSoubi != drawCount) {
					chooseSoubi++;
				}
				break;
			case item:
				if (chooseItem != drawCount) {
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
			if (targetChara != drawCount) {
				targetChara++;
			}
			break;
		}
	}
	else if (mKey[KEY_INPUT_UP] == 1) {
		switch (depth) {
		case 0:
			if (cursorY != limitUP) {
				cursorY -= 20;
				mode--;
			}
			break;
		case 1:
			switch (mode) {
			case status:
				if (chooseChara != 0) {
					chooseChara--;
				}
				break;
			case soubi:
				if (chooseChara != 0) {
					chooseChara--;
				}
				break;
			}
			break;
		case 2:
			switch (mode) {
			case status:
				if (chooseSkill != 0) {
					chooseSkill--;
				}
				break;
			case soubi:
				if (chooseSoubi != 0) {
					chooseSoubi--;
				}
				break;
			case item:
				if (chooseItem != 0) {
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
			if (targetChara != 0) {
				targetChara--;
			}
			break;
		}
	}
	else if (mKey[KEY_INPUT_LEFT] == 1) {
		switch (depth) {
		case 0: break;
		case 1:
			switch (mode) {
			case soubi:
				if (soubiType != 0) {
					soubiType--;
				}
				break;
			case item:
				if (itemType != 0) {
					itemType--;
				}
				break;
			}
			break;
		case 2: 
		case 3:
		case 4: break;
		}
	}
	else if (mKey[KEY_INPUT_RIGHT] == 1) {
		switch (depth) {
		case 0: break;
		case 1: 
			switch (mode) {
			case soubi:
				if (soubiType != 1) {
					soubiType++;
				}
				break;
			case item:
				if (itemType != 1) {
					itemType++;
				}
				break;
			}
			break;
		case 2: 
		case 3:
		case 4: break;
		}
	}
	else if (mKey[KEY_INPUT_Z] == 1) {
		switch (mode) {
		case status:
			switch (depth) {
			case 0:
			case 1: 
			case 2: depth++; break;
			case 3: 
				if (YN == 0) {
					if (mData->GetSkillPoint(skillNum[chooseSkill], 6) == 0) {
						depth++;
					}
					else {
						UseSkill(skillNum[chooseSkill], -1);
					}
				}
				else {
					depth--;
				}
				break;
			case 4:
				UseSkill(itemNum[chooseSkill], targetChara);
				break;
			}
			break;
		case soubi:
			switch (depth) {
			case 0:
			case 1:
			case 2: depth++; break;
			case 3:
				if (YN == 0) {
					mData->SetCharacterPoint(charaNum[chooseChara], 9, soubiNum[chooseSoubi]);
				}
				else {
					depth--;
				}
				break;
			}
			break;
		case item:
			switch (depth) {
			case 0:
			case 1:
			case 2: depth++; break;
			case 3:
				if (YN == 0) {
					if (mData->GetItemPoint(itemNum[chooseItem], 6) == 0) {
						depth++;
					}
					else {
						UseItem(itemNum[chooseItem], -1);
					}
				}
				else {
					depth--;
				}
				break;
			case 4:
				UseItem(itemNum[chooseItem], targetChara);
				break;
			}
			break;
//		case library:
		case save:
			*mMode = 1;
			*mTitle_scene = 3;
			break;
		case option:
			*mMode = 1;
			*mTitle_scene = 4;
			break;
		}
	}
	else if (mKey[KEY_INPUT_X] == 1) {
		if (depth != 0) {
			depth--;
		}
	}
}

void Menu_c::UseItem(int num, int target)
{
	int x = 0;
	int y = 0;
	int effect1 = mData->GetItemPoint(num, 2);
	int effect2 = mData->GetItemPoint(num, 3);

	if (mData->GetItemPoint(num, 6) == 1) {
		for (int i = 0; i < CHARACTER_SIZE; i++) {
			if (mData->GetCharacterFlag(i) == 1) {
				x = mData->GetCharacterPoint(i, effect1 + 2);
				if (mData->GetItemPoint(num, 3) != -1) {
					y = mData->GetCharacterPoint(i, effect2 + 2);
				}

				x += mData->GetItemPoint(num, 4);
				if (effect1 <= 1 && x > mData->GetCharacterPoint(i, effect1)) {
					x = mData->GetCharacterPoint(i, effect1);
				}
				y += mData->GetItemPoint(num, 5);
				if (effect2 <= 1 && y > mData->GetCharacterPoint(i, effect2)) {
					y = mData->GetCharacterPoint(i, effect2);
				}

				mData->SetCharacterPoint(i, effect1 + 2, x);
				if (mData->GetItemPoint(num, 3) != -1) {
					mData->SetCharacterPoint(i, effect2 + 2, y);
				}
			}
		}
	} else {
		x = mData->GetCharacterPoint(target, effect1 + 2);
		if (mData->GetItemPoint(num, 3) != -1) {
			y = mData->GetCharacterPoint(target, effect2 + 2);
		}

		x += mData->GetItemPoint(num, 4);
		if (effect1 <= 1 && x > mData->GetCharacterPoint(target, effect1)) {
			x = mData->GetCharacterPoint(target, effect1);
		}
		y += mData->GetItemPoint(num, 5);
		if (effect2 <= 1 && y > mData->GetCharacterPoint(target, effect2)) {
			y = mData->GetCharacterPoint(target, effect2);
		}

		mData->SetCharacterPoint(target, effect1 + 2, x);
		if (mData->GetItemPoint(num, 3) != -1) {
			mData->SetCharacterPoint(target, effect2 + 2, y);
		}
	}
}

void Menu_c::WearSoubi(int num, int target, int part)
{
	mData->SetCharacterPoint(target, part + 9, num);
}

void Menu_c::UseSkill(int num, int target)
{
	int x = 0;
	int effect = mData->GetSkillPoint(num, 2);

	if (mData->GetSkillPoint(num, 6) == 1) {
		for (int i = 0; i < CHARACTER_SIZE; i++) {
			if (mData->GetCharacterFlag(i) == 1) {
				x = mData->GetCharacterPoint(i, effect + 2);

				x += mData->GetSkillPoint(num, 4);
				if (effect <= 1 && x > mData->GetCharacterPoint(i, effect)) {
					x = mData->GetCharacterPoint(i, effect);
				}

				mData->SetCharacterPoint(i, effect + 2, x);
			}
		}
	}
	else {
		x = mData->GetCharacterPoint(target, effect + 2);

		x += mData->GetSkillPoint(num, 4);
		if (effect <= 1 && x > mData->GetCharacterPoint(target, effect)) {
			x = mData->GetCharacterPoint(target, effect);
		}

		mData->SetCharacterPoint(target, effect + 2, x);
	}
}
