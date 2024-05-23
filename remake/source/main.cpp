#include <tonc.h>


void setMode0() {
    // 화면 모드 0 및 BG0 활성화
    REG_DISPCNT = DCNT_MODE0 | DCNT_BG0;
    
    // BG0 컨트롤 설정 (16컬러 타일, 1번 캐릭터 블록, 31번 스크린 블록)
    tte_init_se_default(0, BG_CBB(0)|BG_SBB(31));

}

void setMode4() {
    REG_DISPCNT = DCNT_MODE4 | DCNT_BG2;
	m4_fill(BLD_BLACK);
}

int main()
{
    irq_init(NULL);
	irq_add(II_VBLANK, NULL);

	setMode0();

    
}