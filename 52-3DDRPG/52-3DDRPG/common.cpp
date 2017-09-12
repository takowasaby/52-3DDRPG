#include "define.h"

int UpdateKey(void) {
	char tmpKey[256];
	GetHitKeyStateAll(tmpKey);
	for (int i = 0; i < 256; i++) {
		if (tmpKey[i] != 0) {
			Key[i]++;
		}
		else {
			Key[i] = 0;
		}
	}
	return 0;
}

void nowLoading() {
	NLGraph = LoadGraph("resource/NOW LOADING.png");
	DrawGraph(0, 0, NLGraph, FALSE);
	ScreenFlip();
	DeleteGraph(NLGraph);
}