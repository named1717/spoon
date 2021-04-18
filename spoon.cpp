#define _CRT_SECURE_NO_WARNINGS
#include <bangtal.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <windows.h>

SceneID scene[5];
ObjectID icon13, icon14, coinn, endgame[4], omt[4];
long coin[6] = { 5000, 10000, 3000, 7000, 20000, 50000 };
long mycoin[6] = { 0,0,0,0,0,0 };
TimerID timer1, timer2, timer3, timer4, timer5, timer6;
int pocket = 200000;
ObjectID trade[12], soccer[3];
int track;
SoundID sound3;
ObjectID menu[5], buy[4], animal[4], note[4];
int ma[4] = { 0,0,0,0 };
int toto[3] = { 0,0,0 };
int matoto[4] = { 0,0,0,0 };
int started = 0;
int crc;
int endingcheck = 0;

void endcheck() {
	for (int i = 0; i < 6; i++) {
		track += coin[i] * mycoin[i];
	}
	track += pocket;
	if (track >= 20000000 && endingcheck == 0) {
		showMessage("축하합니다.\n 게임을 클리어하셨습니다.");
		endingcheck = 1;
		for (int i = 0; i < 4; i++) {
			showObject(endgame[i]);
			showObject(omt[i]);
		}
	}
	track = 0;
}
void showasset() {
	for (int i = 0; i < 6; i++) {
		track += coin[i] * mycoin[i];
	}
	track += pocket;
	printf("남은 현금은 %d입니다.\n", pocket);
	printf("현재 자산은 %d입니다.\n", track);
	track = 0;
}
void marelocate() {
	for (int i = 0;i < 4;i++) {
		ma[i] = 0;
		locateObject(animal[i], scene[3], 0, 320 - i * 80);
	}
}
void cashmatoto() {
	for (int i = 0;i < 4;i++) {
		matoto[i] = 0;
	}
}
void movemal() {
	for (int i = 0; i < 4; i++) {
		int moving = int(rand() % (40 - (i * 5)));
		ma[i] += moving + 20;
		locateObject(animal[i], scene[3], ma[i], 320 - i * 80);
		if (ma[i] > 1200) { crc = i; break; }
	}
	if (ma[crc] > 1200) {
		started = 0;
		stopTimer(timer5);
		setTimer(timer4, 50);
		startTimer(timer4);
		if (crc == 0) {
			pocket += matoto[crc] * 100000;
			showMessage("말이 이겼습니다.");
		}
		else {
			pocket += matoto[crc] * 50000 * (crc + 1) * (crc + 1);
			if (crc == 1) {
				showMessage("소가 이겼습니다.");
			}
			else if (crc == 2) {
				showMessage("개가 이겼습니다.");
			}
			else {
				showMessage("양이 이겼습니다.");
			}
		}
		cashmatoto();
		marelocate();
		printf("남은 현금은 %d입니다.\n", pocket);
		crc = 0;
	}
}
void cashtoto() {
	for (int i = 0; i < 3; i++) {
		toto[i] = 0;
	}
}
void iconchange(int x, int y) {
	char buff[50], bufff[50];
	sprintf(buff, "Images/epl%d.png", x);
	sprintf(bufff, "Images/epl%d.png", y);
	setObjectImage(icon13, buff);
	setObjectImage(icon14, bufff);
}
void checkdelist(int i) {
	if (coin[i] <= 500) {
		coin[i] = 10000;
		mycoin[i] = 0;
		char buf[50];
		sprintf(buf, "코인 %d가 상장폐지되었습니다.", i + 1);
		showMessage(buf);
	}
}
void pricecheck() {
	for (int i = 0; i < 6; i++) {
		printf("코인 %d의 가격은 %d입니다.", i + 1, coin[i]);
	}
}
void pricechange() {
	for (int i = 0; i < 6;i++) {
		int random = int(rand() % 2);
		int changerate = int(rand() % 50);
		int plusbonus = int(rand() % 30);
		if (random == 0) {
			coin[i] += coin[i] * (changerate + plusbonus) / 100;
		}
		else {
			coin[i] -= coin[i] * changerate / 100;
			checkdelist(i);
		}
		printf("코인 %d의 가격은 %d입니다.\n", i + 1, coin[i]);
	}
}
ObjectID makeobj(const char* image, SceneID scene, int x, int y, bool shown) {
	ObjectID object = createObject(image);
	locateObject(object, scene, x, y);
	if (shown) {
		showObject(object);
	}
	return object;
}
void mousecallback(ObjectID object, int x, int y, MouseAction action) {
	int temp = floor(object / 2.0001);
	int temp2 = object - 31;
	int temp3 = object - 35;
	int temp4 = object % 2;
	if (object % 2 == 1 && object < 13) {
		if (pocket >= coin[temp]) {
			pocket -= coin[temp];
			mycoin[temp]++;
			showasset();
		}
		else {
			showMessage("잔액이 부족합니다.");
		}
	}
	else if (object % 2 == 0 && object < 13) {
		if (mycoin[temp] >= 1) {
			pocket += coin[temp];
			mycoin[temp]--;
			showasset();
		}
		else {
			showMessage("보유한 코인이 없습니다.");
		}
	}
	else if (object == 15 || object == 19 || object == 23 || object == 27) {
		enterScene(scene[1]);
	}
	else if (object == 16 || object == 20 || object == 24 || object == 28) {
		enterScene(scene[2]);
	}
	else if (object == 17 || object == 21 || object == 25 || object == 29) {
		enterScene(scene[3]);
	}
	else if (object == 18 || object == 22 || object == 26 || object == 30) {
		enterScene(scene[4]);
	}
	else if (object == 31 || object == 32 || object == 33 || object == 34) {
		if (started == 0) {
			if (pocket >= 50000) {
				pocket -= 50000;
				matoto[temp2]++;
				showasset();
			}
			else {
				showMessage("잔액이 부족합니다.");
			}
		}
		else {
			showMessage("이미 경주가 시작되었습니다.");
		}
	}
	else if (object == 35 || object == 36 || object == 37) {
		if (pocket >= 10000) {
			pocket -= 10000;
			toto[temp3]++;
			showasset();
		}
		else {
			showMessage("잔액이 부족합니다.");
		}
	}
	else if (object == 42) {
		showMessage("코인 거래소 입니다.\n 10초마다 가격이 변동됩니다.\n 코인가격이 500원 밑이면 상장폐지되어 보유코인이 사라집니다.");
	}
	else if (object == 43) {
		showMessage("토토입니다.\n 40초마다 한 경기가 진행됩니다.\n 배당은 승무패 각각 3배입니다.");
	}
	else if (object == 44) {
		showMessage("경마장입니다.\n 한 경기가 끝난 후 50초마다 한 경기가 진행되며\n 배당은 말 2배, 소 4배, 개 9배, 양 16배입니다.");
	}
	else if (object == 45) {
		showMessage("동전을 주우시면 1000원을 얻습니다.");
	}
	else if (object == 46) {
		pocket += 1000;
		int i = int(rand() % 1160) + 40;
		int y = int(rand() % 550);
		locateObject(coinn, scene[4], i, y);
		showasset();
	}
	else if (temp4 == 1 && object >= 47) {
		endGame();
	}
	else if (temp4 == 0 && object >= 47) {
		for (int i = 0; i < 4; i++) {
			hideObject(endgame[i]);
			hideObject(omt[i]);
		}
	}
}
void timercallback(TimerID timer) {
	if (timer == timer1) {
		system("cls");
		pricechange();
		showasset();
		setTimer(timer1, 10);
		startTimer(timer1);
	}
	else if (timer == timer2) {
		int plag = int(rand() % 6);
		int tempa = int(rand() % 6);
		int tempb = int(rand() % 100);
		char buf[50];
		sprintf(buf, "Images/%d.%d.png", tempa + 1, plag);
		switch (plag) {
		case 0: coin[tempa] += coin[tempa] * 2; showImageViewer(buf);
		case 1: coin[tempa] -= coin[tempa] * 3 / 4; showImageViewer(buf);
		case 2: for (int i = 0; i < 6; i++) { coin[i] += coin[i] * 3 / 10; }; showImageViewer("Images/0.2.png");
		case 3: for (int i = 0; i < 6; i++) { coin[i] -= coin[i] * 2 / 10; }; showImageViewer("Images/0.3.png");
		}
		pricecheck();
		showasset();
		setTimer(timer2, 240 + tempb);
		startTimer(timer2);
	}
	else if (timer == timer3) {
		int a, b, c;
		c = int(rand() % 100);
		do {
			a = int(rand() % 20);
			b = int(rand() % 20);
		} while (a == b);
		iconchange(a, b);
		if (c > 66) {
			showMessage("축구 결과 A팀 승리!");
			pocket += toto[0] * 30000;
			cashtoto();
		}
		else if (34 <= c <= 66) {
			showMessage("축구 결과 무승부!");
			pocket += toto[1] * 30000;
			cashtoto();
		}
		else {
			showMessage("축구 결과 B팀 승리!");
			pocket += toto[2] * 30000;
			cashtoto();
		}
		showasset();
		setTimer(timer3, 40);
		startTimer(timer3);
	}
	else if (timer == timer4) {
		showMessage("경마 경주가 시작됩니다.");
		started = 1;
		setTimer(timer5, 2);
		startTimer(timer5);
	}
	else if (timer == timer5) {
		setTimer(timer5, 0.75);
		startTimer(timer5);
		movemal();
	}
	else if (timer == timer6) {
		endcheck();
		setTimer(timer6, 0.4);
		startTimer(timer6);
	}
}
int main() {
	setGameOption(GameOption::GAME_OPTION_MESSAGE_BOX_BUTTON, false);
	setGameOption(GameOption::GAME_OPTION_INVENTORY_BUTTON, false);
	scene[1] = createScene("거래소", "Images/배경1.png");
	scene[2] = createScene("토토", "Images/배경2.png");
	scene[3] = createScene("경마", "Images/배경3.png");
	scene[4] = createScene("재무", "Images/배경4.png");
	timer1 = createTimer(10.0f);
	timer2 = createTimer(180.0f);
	timer3 = createTimer(40.5f);
	timer4 = createTimer(51.5f);
	timer5 = createTimer(0.5f);
	timer6 = createTimer(0.4f);
	sound3 = createSound("kygo.mp3");
	for (int i = 0; i < 6; i++) {
		trade[i] = makeobj("Images/buy.png", scene[1], 800, 410 - 75 * i, true);
		trade[i + 6] = makeobj("Images/sell.png", scene[1], 1000, 410 - 75 * i, true);
	}
	icon13 = makeobj("Images/epl0.png", scene[2], 350, 300, true);
	icon14 = makeobj("Images/epl1.png", scene[2], 830, 300, true);
	scaleObject(icon13, 0.33f);
	scaleObject(icon14, 0.33f);
	for (int i = 1; i < 5; i++) {
		menu[1] = makeobj("Images/menu1.png", scene[i], 107, 600, true);
		menu[2] = makeobj("Images/menu2.png", scene[i], 334, 600, true);
		menu[3] = makeobj("Images/menu3.png", scene[i], 561, 600, true);
		menu[4] = makeobj("Images/menu4.png", scene[i], 788, 600, true);
	}
	for (int i = 0; i < 4; i++) {
		char temp[50];
		sprintf(temp, "Images/buy%d.png", i + 1);
		buy[i] = makeobj(temp, scene[3], 154 + i * 282, 0, true);
	}
	for (int i = 0; i < 3; i++) {
		char tempp[50];
		sprintf(tempp, "Images/soccer%d.png", i + 1);
		soccer[i] = makeobj(tempp, scene[2], 205 + i * 358, 60, true);
	}
	animal[0] = makeobj("Images/horse.png", scene[3], 0, 320, true);
	animal[1] = makeobj("Images/cow.png", scene[3], 0, 240, true);
	animal[2] = makeobj("Images/dog.png", scene[3], 0, 160, true);
	animal[3] = makeobj("Images/sheep.png", scene[3], 0, 80, true);
	for (int i = 0; i < 4; i++) {
		note[i] = makeobj("Images/note.png", scene[i + 1], 1015, 600, true);
	}
	coinn = makeobj("Images/coin.png", scene[4], 400, 60, true);
	for (int i = 1; i < 5; i++) {
		endgame[i - 1] = makeobj("Images/end.png", scene[i], 400, 343, false);
		omt[i - 1] = makeobj("Images/omt.png", scene[i], 785, 343, false);
	}
	showasset();
	playSound(sound3, true);
	showTimer(timer1);
	startTimer(timer1);
	startTimer(timer2);
	startTimer(timer3);
	startTimer(timer4);
	startTimer(timer6);
	setTimerCallback(timercallback);
	setMouseCallback(mousecallback);
	showMessage("이십만원을 가지고 이천만원을 만드셔야합니다.\n 콘솔창을 함께 띄워주세요");
	startGame(scene[1]);
}