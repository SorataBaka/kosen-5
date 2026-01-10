/*
  コンパイル方法（Linux）：
    $ gcc line.c -lncursesw -lm -o line
  実行方法：
    $ ./line
    $ ./line 計算回数n
    $ ./line サイズdx  サイズdy
    $ ./line サイズdx  サイズdy  計算回数n
  キー操作：
    Q		終了
    + -		計算回数変更
    H J K L 等	線分サイズ変更
    Space 等 	再計算
*/
#include <ncurses.h>
#include <locale.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <stdio.h>  // <-- for FILE I/O
#include <string.h> // <-- for strcpy

WINDOW *win = NULL;

//========================= Plot macro =========================
#define Plot(x, y, c)               \
    do                              \
    {                               \
        if (win)                    \
            mvwaddch(win, y, x, c); \
    } while (0)
//==============================================================

//===================== Line draw functions ====================
void SlowDrawLine1(int x1, int y1, int dx, int dy, char c)
{
    double m = (double)dy / (double)dx;
    int x, y;
    for (x = 0; x <= dx; x++)
    {
        y = (int)round(m * x);
        Plot(x1 + x, y1 + y, c);
    }
}

void SlowDrawLine2(int x1, int y1, int dx, int dy, char c)
{
    double m = (double)dy / (double)dx;
    int x, y;
    for (x = 0; x <= dx; x++)
    {
        y = m * x + 0.5;
        Plot(x1 + x, y1 + y, c);
    }
}

void FastDrawLineDDA1(int x1, int y1, int dx, int dy, char c)
{
    double m = (double)dy / (double)dx;
    int x, y = 0;
    double e = 0.0;
    for (x = 0; x <= dx; x++)
    {
        Plot(x1 + x, y1 + y, c);
        e += m;
        if (e >= 0.5)
        {
            y++;
            e -= 1.0;
        }
    }
}

void FastDrawLineDDA2(int x1, int y1, int dx, int dy, char c)
{
    int x, y = 0;
    int e = 0;
    for (x = 0; x <= dx; x++)
    {
        Plot(x1 + x, y1 + y, c);
        e += dy;
        if (2 * e >= dx)
        {
            y++;
            e -= dx;
        }
    }
}

void FastDrawLineDDA3(int x1, int y1, int dx, int dy, char c)
{
    int x, y = 0;
    int dx2 = 2 * dx;
    int dy2 = 2 * dy;
    int e = 0;
    for (x = 0; x <= dx; x++)
    {
        Plot(x1 + x, y1 + y, c);
        e += dy2;
        if (e >= dx)
        {
            y++;
            e -= dx2;
        }
    }
}

void FastDrawLineDDA4(int x1, int y1, int dx, int dy, char c)
{
    int x, y = 0;
    int dy2 = 2 * dy;
    int e = dy2;
    for (x = 0; x <= dx; x++)
    {
        Plot(x1 + x, y1 + y, c);
        if (e >= dx)
        {
            y++;
            e += dy2 - 2 * dx;
        }
        else
        {
            e += dy2;
        }
    }
}

void FastDrawLineBA(int x1, int y1, int dx, int dy, char c)
{
    int x, y = 0;
    int e = 2 * dy - dx;
    for (x = 0; x <= dx; x++)
    {
        Plot(x1 + x, y1 + y, c);
        if (e >= 0)
        {
            y++;
            e -= 2 * dx;
        }
        e += 2 * dy;
    }
}

void PlotCirclePoints(int x0, int y0, int x, int y, char c)
{
    Plot(x0 + x, y0 + y, c);
    Plot(x0 - x, y0 + y, c);
    Plot(x0 + x, y0 - y, c);
    Plot(x0 - x, y0 - y, c);
    Plot(x0 + y, y0 + x, c);
    Plot(x0 - y, y0 + x, c);
    Plot(x0 + y, y0 - x, c);
    Plot(x0 - y, y0 - x, c);
}
void PlotOvalPoints(int x0, int y0, int x, int y, char c)
{
    Plot(x0 + x, y0 + y, c);
    Plot(x0 - x, y0 + y, c);
    Plot(x0 + x, y0 - y, c);
    Plot(x0 - x, y0 - y, c);
}
void SlowDrawCircle(int x0, int y0, int r, char c)
{
    for (int y = y0; y <= y0 + r; y++)
    {
        int y_relative = y - y0;
        double x_offset = sqrt((double)r * r - (double)y_relative * y_relative);
        int x_relative = (int)round(x_offset);
        if (y_relative > x_relative)
            break;
        PlotCirclePoints(x0, y0, x_relative, y_relative, c);
    }
}
void FastDrawCircle(int x0, int y0, int r, int c)
{
    int x_offset = 0; // 円の最上点 (0, r) からスキャンを開始
    int y_offset = r;
    int decision = 1 - r; // 決定パラメータ (整数)
    PlotCirclePoints(x0, y0, x_offset, y_offset, c);
    while (x_offset < y_offset)
    {
        x_offset++; // x は常にインクリメント
        if (decision < 0)
        {
            decision += 2 * x_offset + 1; // f(x, y+1) update
        }
        else
        {
            y_offset--;
            decision += 2 * (x_offset - y_offset) + 1; // f(x-1, y+1) update
        }
        PlotCirclePoints(x0, y0, x_offset, y_offset, c);
    }
}
void SlowDrawOval(int x0, int y0, int rx, int ry, char c)
{
    double x_limit = (double)rx * rx;
    double y_limit = (double)ry * ry;
    for (int x_offset = 0; x_offset <= rx; x_offset++)
    {
        double y_offset = (double)ry * sqrt(1.0 - (x_offset * x_offset / x_limit));
        PlotOvalPoints(x0, y0, x_offset, (int)round(y_offset), c);
    }
    for (int y_offset = 0; y_offset <= ry; y_offset++)
    {
        double x_offset = (double)rx * sqrt(1.0 - (y_offset * y_offset / y_limit));
        PlotOvalPoints(x0, y0, (int)round(x_offset), y_offset, c);
    }
}
void FastDrawOval(int x0, int y0, int rx, int ry, char c)
{
    long rx2 = (long)rx * rx;
    long ry2 = (long)ry * ry;
    long decision = (long)round(ry2 - rx2 * ry + 0.25 * rx2);
    int x_offset = 0;
    int y_offset = ry;
    while (2 * ry2 * x_offset < 2 * rx2 * y_offset)
    {
        PlotOvalPoints(x0, y0, x_offset, y_offset, c);
        x_offset++;
        if (decision < 0)
        {
            decision += 2 * ry2 * x_offset + ry2;
        }
        else
        {
            y_offset--;
            decision += 2 * ry2 * x_offset + ry2 - 2 * rx2 * y_offset;
        }
    }
    decision = (long)round(ry2 * (x_offset + 0.5) * (x_offset + 0.5) +
                           rx2 * (y_offset - 1) * (y_offset - 1) -
                           rx2 * ry2);
    while (y_offset >= 0)
    {
        PlotOvalPoints(x0, y0, x_offset, y_offset, c);
        y_offset--; // y is always decremented in this region
        if (decision > 0)
        {
            decision += -2 * rx2 * y_offset + rx2;
        }
        else
        {
            x_offset++;
            decision += 2 * ry2 * x_offset - 2 * rx2 * y_offset + rx2;
        }
    }
}
double Timer(void)
{
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC_RAW, &ts);
    return ts.tv_sec + ts.tv_nsec * 1.0e-9;
}

#define Graph(mode) \
    {               \
        win = mode; \
    }
#define ON stdscr
#define OFF NULL

// ---------------- CSV Logging function ----------------
void LogToCSV(const char *method, double elapsed, int n, int dx, int dy)
{
    FILE *fp = fopen("timelog.csv", "a");
    if (!fp)
        return;

    // Get current timestamp
    time_t now = time(NULL);
    struct tm *tm_info = localtime(&now);
    char timestr[64];
    strftime(timestr, sizeof(timestr), "%Y-%m-%d %H:%M:%S", tm_info);

    // Append CSV row
    fprintf(fp, "%s,%d,%d,%d,%s,%.9f\n", timestr, n, dx, dy, method, elapsed);
    fclose(fp);
}
// -------------------------------------------------------

// Macro for timing and logging
#define TT(y, name, drawfunc, n)              \
    {                                         \
        Graph(ON);                            \
        drawfunc;                             \
        Graph(OFF);                           \
        for (int w = 0; w < 16; ++w)          \
            drawfunc;                         \
        double t0 = Timer();                  \
        for (int i = 0; i < n; i++)           \
            drawfunc;                         \
        double t = Timer() - t0;              \
        mvprintw(y, 0, "%s:\t%f s", name, t); \
        refresh();                            \
        LogToCSV(name, t, n, dx, dy);         \
    }
//==============================================================

//============================ main =============================
int main(int argc, char **argv)
{
    int dx = 40, dy = 20;
    int n = 100000;
    int key;
    int rx = 1;
    int ry = 1;
    if (argc > 2)
    {
        dx = atoi(argv[1]);
        dy = atoi(argv[2]);
        argc -= 2;
    }
    if (argc == 2)
        n = atoi(argv[1]);

    setlocale(LC_ALL, "");
    initscr();
    curs_set(0);
    noecho();
    keypad(stdscr, true);

    // Write CSV header if not present
    FILE *fp = fopen("timelog.csv", "r");
    if (!fp)
    {
        fp = fopen("timelog.csv", "w");
        if (fp)
        {
            fprintf(fp, "timestamp,n,dx,dy,method,time_sec\n");
            fclose(fp);
        }
    }
    else
        fclose(fp);

    while (1)
    {
        erase();
        mvprintw(0, 0, "n=%d\tdx=%d\tdy=%d\trx=%d\try=%d", n, dx, dy, rx, ry);
        // TT(3, "Slow1", SlowDrawLine1(20, 3, dx, dy, '#'), n);
        // TT(6, "Slow2", SlowDrawLine2(20, 6, dx, dy, '#'), n);
        // TT(9, "DDA1", FastDrawLineDDA1(20, 9, dx, dy, '#'), n);
        // TT(12, "DDA2", FastDrawLineDDA2(20, 12, dx, dy, '#'), n);
        // TT(15, "DDA3", FastDrawLineDDA3(20, 15, dx, dy, '#'), n);
        // TT(18, "DDA4", FastDrawLineDDA4(20, 18, dx, dy, '#'), n);
        // TT(21, "BS", FastDrawLineBA(20, 21, dx, dy, '#'), n);

        TT(10, "Slow Circle", SlowDrawCircle(dx, dy, rx, 'o'), n);
        TT(13, "Fast Circle", FastDrawCircle(dx + (2 * rx) + 5, dy, rx, 'o'), n);
        TT(16, "Slow Oval", SlowDrawOval(dx + (4 * rx) + 10, dy, rx, ry, 'o'), n);
        TT(18, "Fast Oval", FastDrawOval(dx + (6 * rx) + 15, dy, rx, ry, 'o'), n);

        refresh();

        key = getch();
        if (key == 'q')
            break;
        switch (key)
        {
        case 'w':
            rx += 1;
            break;
        case 's':
            rx -= 1;
            break;
        case 'a':
            ry -= 1;
            break;
        case 'd':
            ry += 1;
            break;
        case '+':
            n *= 10;
            break;
        case '-':
            n /= 10;
            break;
        case 'h':
        case KEY_LEFT:
            dx -= 1;
            break;
        case 'j':
        case KEY_DOWN:
            dy += 1;
            break;
        case 'k':
        case KEY_UP:
            dy -= 1;
            break;
        case 'l':
        case KEY_RIGHT:
            dx += 1;
            break;
        }
    }
    endwin();
    return 0;
}