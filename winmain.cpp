#include <DxLib.h>

// プログラムは WinMain から始まります
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	ChangeWindowMode(TRUE);	//ウィンドウモードにする
	SetGraphMode(800, 600, 32);	//ウィンドウサイズを設定する

	if (DxLib_Init() == -1)		// ＤＸライブラリ初期化処理
	{
		return -1;			// エラーが起きたら直ちに終了
	}
	SetDrawScreen(DX_SCREEN_BACK);	//裏画面を描画対象へ

	struct player {
	public:
		int count=0;
		int handlex=1;
		int handley = 1;
		int img = -1;
		int x=0;
		int y=0;
	};

	player chara;
	chara.img=LoadGraph("chara.png", true);

	int GrHandle[24];//画像 24画像読み込む
	int x = 10;
	int y = 10;
	int v = 0;

	//画像の分割（3×４　12チップ）読み込み 斜め画像は使わない
	LoadDivGraph("Lilith1.png", 12, 3, 4, 20, 28, GrHandle);
	PlayMusic("bgm_maoudamashii_neorock71b . mp3", DX_PLAYTYPE_LOOP);
	//メイン処理
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0) {
		if ((CheckHitKey(KEY_INPUT_LEFT) && CheckHitKey(KEY_INPUT_UP)) ||
			(CheckHitKey(KEY_INPUT_LEFT) && CheckHitKey(KEY_INPUT_DOWN)) ||
			(CheckHitKey(KEY_INPUT_RIGHT) && CheckHitKey(KEY_INPUT_UP)) ||
			(CheckHitKey(KEY_INPUT_RIGHT) && CheckHitKey(KEY_INPUT_DOWN))) {

			if (CheckHitKey(KEY_INPUT_LEFT) && CheckHitKey(KEY_INPUT_UP)) {
				chara.count++;
				//chara.handlex = chara.count % 20 / 10 * 2+3;
				chara.handlex = ((chara.count / 10) & 3) - (((chara.count / 10) & 3) + 1) / 4 * 2+3;
				chara.handley = 2;
			}
			else if (CheckHitKey(KEY_INPUT_LEFT) && CheckHitKey(KEY_INPUT_DOWN)) {
				chara.count++;
				//chara.handlex = chara.count % 20 / 10 * 2+3;
				chara.handlex = ((chara.count / 10) & 3) - (((chara.count / 10) & 3) + 1) / 4 * 2+3;
				chara.handley = 0;
			}
			else if (CheckHitKey(KEY_INPUT_RIGHT) && CheckHitKey(KEY_INPUT_UP)) {
				chara.count++;
				//chara.handlex = chara.count % 20 / 10 * 2+3;
				chara.handlex = ((chara.count / 10) & 3) - (((chara.count / 10) & 3) + 1) / 4 * 2+3;
				chara.handley = 3;
			}
			else if (CheckHitKey(KEY_INPUT_RIGHT) && CheckHitKey(KEY_INPUT_DOWN)) {
				chara.count++;
				//chara.handlex = chara.count % 20 / 10 * 2+3;
				chara.handlex = ((chara.count / 10) & 3) - (((chara.count / 10) & 3) + 1) / 4 * 2+3;
				chara.handley = 1;
			}
		}
		else {



			if (CheckHitKey(KEY_INPUT_UP) == 1) {
				chara.count++;
				//chara.handlex = chara.count % 20 / 10 * 2;
				chara.handlex = chara.count/10 % 4;
				if (chara.count/10 % 4 == 3) {
					chara.handlex = 1;
				}
				chara.handley = 3;
			}
			if (CheckHitKey(KEY_INPUT_DOWN) == 1) {
				chara.count++;
				//chara.handlex = chara.count % 20 / 10 * 2;
				chara.handlex = chara.count/10 % 4;
				if (chara.count /10% 4 == 3) 
					chara.handlex = 1;
				
				chara.handley = 0;
			}
			if (CheckHitKey(KEY_INPUT_LEFT) == 1) {
				chara.count++;
				//chara.handlex = chara.count % 20 / 10 * 2;
				chara.handlex = ((chara.count / 10) & 3) - (((chara.count / 10) & 3) + 1) / 4 * 2;
				chara.handley = 1;
			}
			if (CheckHitKey(KEY_INPUT_RIGHT) == 1) {
				chara.count++;
				//chara.handlex = chara.count % 20 / 10 * 2;
				chara.handlex = ((chara.count / 10) & 3) - (((chara.count / 10) & 3) + 1) / 4 * 2;
				chara.handley = 2;
			}
		}
		if (CheckHitKey(KEY_INPUT_UP) == 1) 
			chara.y--;
		if (CheckHitKey(KEY_INPUT_DOWN) == 1) 
			chara.y++;
		if (CheckHitKey(KEY_INPUT_LEFT) == 1) 
			chara.x--;
		if (CheckHitKey(KEY_INPUT_RIGHT) == 1) 
			chara.x++;

		DrawRectGraph(chara.x,chara.y,32*chara.handlex,64*chara.handley,32,64,chara.img,true,false);
		// 画面左上に描画します(『DrawGraph』を使用)
		//DrawGraph(x, y, GrHandle[v], FALSE);
		clsDx();
		printfDx("%d", chara.handlex);

		ScreenFlip();		//裏画面と表画面の入替
		ClearDrawScreen();	//裏画面の描画を全て消去
	}

	// 読み込んだ画像のグラフィックハンドルを削除
	for(int i=0;i<12;i++) DeleteGraph(GrHandle[i]);

	DxLib_End();			// ＤＸライブラリ使用の終了処理

	return 0;				// ソフトの終了 
}

