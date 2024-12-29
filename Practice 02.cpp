#include <graphics.h>
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    int x, y;
    int vx = 15, vy = 0;
    int g = 1;
    int r = 15;
    int p, vp;
    bool ballShot = false;
    bool ballVisible = true;
    int score = 0;
    int totalShots = 0;
    int targetLength, targetSpeed;
    bool inUpperLeft;

    initgraph(600, 800);
    setbkcolor(RGB(50, 50, 50));
    cleardevice();
    srand((unsigned int)time(NULL));

    targetLength = rand() % 100 + 20;
    targetSpeed = rand() % 5 + 2;
    p = rand() % (800 - targetLength);

    if (rand() % 2 == 0) {
        y = rand() % 100;
        vy = 0;
        inUpperLeft = true;
    }
    else {
        y = 600 + rand() % 100;
        vy = -30;
        inUpperLeft = false;
    }
    x = 0;

    while (totalShots < 10) {
        cleardevice();

        setfillcolor(RGB(255, 0, 0));
        solidrectangle(580, p, 580 + targetLength, p + 60);

        p = p + targetSpeed;
        if (p > 800 - 60 || p <= 0) {
            targetSpeed = -targetSpeed;
        }

        if (ballVisible) {
            setfillcolor(RGB(0, 255, 0));
            solidcircle(x, y, r);
        }

        if (GetAsyncKeyState(VK_SPACE) & 0x8000 && !ballShot && ballVisible) {
            ballShot = true;
            totalShots++;
            ballVisible = false;

            vx = 15;
            if (inUpperLeft) {
                vy = 0;
            }
            else {
                vy = -30;
            }
        }

        if (ballShot) {
            setfillcolor(RGB(0, 255, 0));
            solidcircle(x, y, r);

            x = x + vx;
            y = y + vy;
            vy = vy + g;

            if (y > 800) {
                ballShot = false;
                ballVisible = true;
                if (rand() % 2 == 0) {
                    y = rand() % 100;
                    vy = 0;
                    inUpperLeft = true;
                }
                else {
                    y = 600 + rand() % 100;
                    vy = -30;
                    inUpperLeft = false;
                }
                x = 0;
            }

            if (x + r >= 580 && x - r <= 580 + targetLength &&
                y + r >= p && y - r <= p + 60) {
                score++;
                ballShot = false;
                ballVisible = true;

                targetLength = rand() % 100 + 20;
                targetSpeed = rand() % 5 + 2;
                p = rand() % (800 - targetLength);
            }
        }

        settextstyle(20, 0, _T("Arial"));
        TCHAR score_text[50];
        _stprintf_s(score_text, _T("Score: %d/%d"), score, totalShots);
        settextcolor(RGB(255, 255, 255));
        outtextxy(10, 10, score_text);

        Sleep(40);
    }

    cleardevice();
    settextstyle(30, 0, _T("Arial"));
    TCHAR final_score[50];
    _stprintf_s(final_score, _T("Final Score: %d/%d"), score, totalShots);
    settextcolor(RGB(0, 255, 0));
    outtextxy(200, 400, final_score);

    _getch();
    closegraph();
    return 0;
}
