#include <tonc.h>

int main()
{
    REG_DISPCNT = DCNT_MODE3 | DCNT_BG2;

    int ii, clk, oldclk;
    const int maxLine = 17;
    clk = 0;
    oldclk = 0;
    m3_fill(RGB15(12, 12, 14));

    m3_frame(12, 8, 228, 152, CLR_RED);
    while (1)
    {
        vid_vsync();
        key_poll();
        if (key_hit(KEY_RIGHT) && (clk <= maxLine-1))
        {
            clk++;
        }
        else if (key_hit(KEY_LEFT) && (clk >= 0))
        {
            clk--;
        }
        if (oldclk != clk)
        {
            for (ii = 1; ii < maxLine; ii++)
            {
                m3_line(12 + 11 * ii, 9, 12 + 11 * ii, 151, RGB15(12, 12, 14));
            }
            for (ii = 1; ii < clk; ii++)
            {
                m3_line(12 + 11 * ii, 9, 12 + 11 * ii, 151, CLR_LIME);
            }
            oldclk = clk;
        }

    }
}