#include <DxLib.h>

// �v���O������ WinMain ����n�܂�܂�
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	ChangeWindowMode(TRUE);	//�E�B���h�E���[�h�ɂ���
	SetGraphMode(800, 600, 32);	//�E�B���h�E�T�C�Y��ݒ肷��

	if (DxLib_Init() == -1)		// �c�w���C�u��������������
	{
		return -1;			// �G���[���N�����璼���ɏI��
	}
	SetDrawScreen(DX_SCREEN_BACK);	//����ʂ�`��Ώۂ�

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

	int GrHandle[24];//�摜 24�摜�ǂݍ���
	int x = 10;
	int y = 10;
	int v = 0;

	//�摜�̕����i3�~�S�@12�`�b�v�j�ǂݍ��� �΂߉摜�͎g��Ȃ�
	LoadDivGraph("Lilith1.png", 12, 3, 4, 20, 28, GrHandle);
	PlayMusic("bgm_maoudamashii_neorock71b . mp3", DX_PLAYTYPE_LOOP);
	//���C������
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
		// ��ʍ���ɕ`�悵�܂�(�wDrawGraph�x���g�p)
		//DrawGraph(x, y, GrHandle[v], FALSE);
		clsDx();
		printfDx("%d", chara.handlex);

		ScreenFlip();		//����ʂƕ\��ʂ̓���
		ClearDrawScreen();	//����ʂ̕`���S�ď���
	}

	// �ǂݍ��񂾉摜�̃O���t�B�b�N�n���h�����폜
	for(int i=0;i<12;i++) DeleteGraph(GrHandle[i]);

	DxLib_End();			// �c�w���C�u�����g�p�̏I������

	return 0;				// �\�t�g�̏I�� 
}

