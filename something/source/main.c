
#include <stdio.h>
#include <tonc.h>

// 선분을 그리는 함수
void draw_line(int x0, int y0, int x1, int y1, u16 color)
{
    m3_line(x0, y0, x1, y1, color);
}

// 삼각형 내부를 채우는 함수
void fill_triangle(int x0, int y0, int x1, int y1, int x2, int y2, u16 color)
{
    // y0, y1, y2를 정렬하여 y0 <= y1 <= y2 순서가 되도록 함
    if(y0 > y1) {
        SWAP(y0, y1);
        SWAP(x0, x1);
    }
    if(y1 > y2) {
        SWAP(y2, y1);
        SWAP(x2, x1);
    }
    if(y0 > y1) {
        SWAP(y0, y1);
        SWAP(x0, x1);
    }

    // 상단 삼각형 채우기
    int dy0 = y1 - y0;
    int dx0 = x1 - x0;
    int dy1 = y2 - y0;
    int dx1 = x2 - x0;

    float dxdy0 = dx0 / (float)dy0;
    float dxdy1 = dx1 / (float)dy1;

    float x02 = x0;
    float x01 = x0;
    
    for(int y=y0; y<y1; y++)
    {
        draw_line((int)x01, y, (int)x02, y, color);
        x01 += dxdy0;
        x02 += dxdy1;
    }

    // 하단 삼각형 채우기
    dy0 = y2 - y1;
    dx0 = x2 - x1;

    dxdy0 = dx0 / (float)dy0;
    x01 = x1;
    
    for(int y=y1; y<=y2; y++)
    {
        draw_line((int)x01, y, (int)x02, y, color);
        x01 += dxdy0;
        x02 += dxdy1;
    }
}

int main()
{
	
	REG_DISPCNT= DCNT_MODE3 | DCNT_BG2;

	// 삼각형의 꼭지점 좌표 설정
    int x0 = 0, y0 = 0;  // 꼭지점 1
    int x1 = 50, y1 = 0;  // 꼭지점 2
    int x2 = 50, y2 = 50;  // 꼭지점 3

    // 삼각형 색상 설정
    u16 color = CLR_YELLOW;  // 노란색

    // 삼각형 채우기
    fill_triangle(x0, y0, x1, y1, x2, y2, color);
	m3_rect(20, 20, 100, 60, RGB15(31, 0, 0)); // 시작점 (20, 20), 폭 100, 높이 60인 빨간색 사각형 그리기
    // 메인 루프
    while(1)
    {
        // 아무 작업도 하지 않음
    }
}
