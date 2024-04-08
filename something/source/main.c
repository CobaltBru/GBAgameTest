
#include <stdio.h>
#include <tonc.h>

// 정육면체 정점 정의
VECTOR cube_vertices[] = {
    {-30, -30, -30}, {30, -30, -30}, {30, 30, -30}, {-30, 30, -30},
    {-30, -30,  30}, {30, -30,  30}, {30, 30,  30}, {-30, 30,  30}
};

// 정육면체 면을 구성하는 정점 인덱스
u16 cube_faces[][4] = {
    {0, 1, 2, 3}, {1, 5, 6, 2}, {5, 4, 7, 6},
    {4, 0, 3, 7}, {3, 2, 6, 7}, {4, 5, 1, 0}
};

void draw_cube(VECTOR *vertices, int color) {
    int focalLength = 40; // 초점 거리
    int centerX = 120, centerY = 80; // 화면 중앙

    for(int i = 0; i < 6; i++) {
        for(int j = 0; j < 4; j++) {
            VECTOR *v1 = &vertices[cube_faces[i][j]];
            VECTOR *v2 = &vertices[cube_faces[i][(j + 1) % 4]];

            // Z값을 고려하여 3D 좌표를 2D 스크린 좌표로 변환
            int x1 = ((v1->x * focalLength) / (v1->z + focalLength + 100)) + centerX;
            int y1 = ((v1->y * focalLength) / (v1->z + focalLength + 100)) + centerY;
            int x2 = ((v2->x * focalLength) / (v2->z + focalLength + 100)) + centerX;
            int y2 = ((v2->y * focalLength) / (v2->z + focalLength + 100)) + centerY;

            // m3_line 함수를 사용하여 화면에 직선 그리기
            m3_line(x1, y1, x2, y2, color);
        }
    }
}

// 3D 벡터를 회전시키는 함수 (Y축, X축, Z축 순서)
void rotate_vector(VECTOR *v, int angleX, int angleY, int angleZ) {
    int s, c;
    VECTOR temp = *v;

    // Y축 회전
    s = lu_sin(angleY); c = lu_cos(angleY);
    temp.x = (v->x * c - v->z * s) >> 14;
    temp.z = (v->x * s + v->z * c) >> 14;

    // X축 회전
    s = lu_sin(angleX); c = lu_cos(angleX);
    v->y = (temp.y * c - temp.z * s) >> 14;
    v->z = (temp.y * s + temp.z * c) >> 14;

    // Z축 회전 (화면에 더 잘 표시되도록 추가)
    s = lu_sin(angleZ); c = lu_cos(angleZ);
    v->x = (temp.x * c - v->y * s) >> 14;
    v->y = (temp.x * s + v->y * c) >> 14;
}
// 메인 함수
int main() {
    REG_DISPCNT = DCNT_MODE3 | DCNT_BG2; // Mode 3 설정

    int angleX = 0, angleY = 0, angleZ = 0;

    while(1) {
        vid_vsync();
        m3_fill(CLR_BLACK); // 화면 클리어

        VECTOR rotated_vertices[8];
        for(int i = 0; i < 8; i++) {
            rotated_vertices[i] = cube_vertices[i];
            rotate_vector(&rotated_vertices[i], angleX, angleY, angleZ);
        }

        draw_cube(rotated_vertices, RGB15(31,31,31)); // 정육면체 그리기

        angleX += 0x68;
        angleY += 0x88;
        angleZ += 0x48;
    }
}