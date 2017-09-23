#pragma once

#include "DxLib.h"

#include "control.h"
#include "data.h"
#include "dungeon.h"
#include "ECharaData.h"
#include "EDrawSetting.h"
#include "EQueueData.h"
#include "Event.h"
#include "fps.h"
#include "option.h"
#include "TextBox.h"
#include "title.h"
#include <math.h>
#include <map>
#include <vector>
#include <string>

const int EVENT_MODE_DEFAULTSIZE = 1;
const int EVENT_MODE_RESIZE = 2;
const int EVENT_MODE_COMPLETE = 4;

const int EVENT_ACTION_POSITION = 1;
const int EVENT_ACTION_OPACITY = 2;
const int EVENT_ACTION_SCALE = 4;
const int EVENT_ACTION_TEXT = 8;
const int EVENT_ACTION_TURN = 16;
const int EVENT_ACTION_LIGHT = 32;
const int EVENT_ACTION_DARK = 64;
const int EVENT_ACTION_TEXTCLEAR = 128;
const int EVENT_ACTION_WAIT = 256;
const int EVENT_ACTION_END =512;

//TextBox�֘A�̐錾------------------------------------
//�E�B���h�E���[�h�Ɋւ���񋓑�
enum WindowMode {
	readMode,	//�I���ł��Ȃ����b�Z�[�W�p
	pageMode,	//�㉺�őI���A���E�Ńy�[�W�ړ�
	scrollMode	//�X�N���[���ňړ�
};
//-------------------------------------------------------