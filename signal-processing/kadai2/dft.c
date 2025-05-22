// 離散フーリエ変換  // Discrete Fourier transform
// Ver.2023.12.15
// コンパイル：$ cc dft.c -std=c99 -lpcm -lm -o dft
// 実行方法：$ ./dft [入力ファイル.wav [標本数 [始点]]]  -->  Execution method: $ ./dft [input file.wav [sample size [start point]]] 

#include <stdio.h>
#include <stdlib.h>
#define	__USE_POSIX199309	// clock_gettime()
#include <time.h>
#include <complex.h>
#include "pcm/pcm.h"
#include "cx.h"

#define	debug(...)	fprintf(stderr, __VA_ARGS__)
#define	fatal(s, ...)	{ debug(__VA_ARGS__); exit(s); }

// グラフ用データ出力関数  --> Graph data output function 
void Plot(const char *file, const Cx *v, int N, double d, double (*func)(Cx v))
{
	FILE	*fp = fopen(file, "w");
	if (!fp) fatal(1, "%s オープン失敗\n", file);

	for (int i = 0; i < N; i++) {
		fprintf(fp, "%e\t%e\n", i*d, func(v[i]));
	}
	debug("出力ファイル = %s\n", file);
	fclose(fp);
}

// 時間測定関数  --> Time measurement function
double Timer()
{
	struct timespec	ts;		// 時刻データの構造体  --> time data structure

	clock_gettime(CLOCK_REALTIME, &ts);	// 現在時刻を取得 --> Get Current time
			// ts.tv_sec：	時刻の整数成分（s；秒）--> Integer component of time (s; seconds)
			// ts.tv_nsec：	時刻の小数成分（ns；ナノ秒）--> Fractional component of time (ns; nanoseconds)

	return (ts.tv_sec + ts.tv_nsec*1.0e-9);	// 1 ns = 1.0x10^-9 s
}

void DFT(const Cx *x, Cx *X, int N)
{
	// 各自で定義せよ  --> Define yourself
}

void IDFT(const Cx *X, Cx *x, int N)
{
	// 各自で定義せよ  --> Define yourself
}

int main(int argc, char *argv[])
{
	char	*wav = "-";	// 入力WAVファイル名  --> input WAV file name
	int	N = 480;	// 分析対象区間の標本数  --> Number of samples in the analysis interval
	int	n0 = 0;		// 分析対象区間の始点   ---> start point of the analysis interval
	if (argc > 1) wav = argv[1];
	if (argc > 2) N = atoi(argv[2]);
	if (argc > 3) n0 = atoi(argv[3]);

	Wav	*p = pcmLoad(wav);
	if (p == NULL) return (1);
	debug("■ 入力データ\n");
	pcmInfo(stderr, p);

	debug("■ 分析条件\n");
	debug("開始番号 = %d，\t開始時刻 = %f [s]\n", n0, (double)n0/p->fmt.fs);
	debug("標本数 = %d，\t窓幅 = %f [s]\n", N, (double)N/p->fmt.fs);
	debug("基本周波数 = %f [Hz]\n", p->fmt.fs/(double)N);
	debug("\n");

	Cx	x[N], X[N];		// 波形とスペクトルのバッファ  --> Waveform and spectrum buffer
	double	dt = 1.0/p->fmt.fs;	// Δt = 1/f_s
	double	df = p->fmt.fs/N;	// Δf = f_s//N
	double	*v = &(p->val[0][n0]);		// 分析対象の標本値列の先頭アドレス
	for (int n = 0; n < N; n++) x[n] = v[n];	// 分析対象をバッファへコピー
	pcmFin(p);
	debug("■ 入力波形\n");
	Plot("wf.txt", x, N, dt, creal);
	debug("\n");

/*
	double	t0 = Timer();
	DFT(x, X, N);
	debug("■ DFT\n処理時間 = %f [s]\n", Timer() - t0);
	Plot("dft.txt", X, N, df, cabs);
	debug("\n");

	t0 = Timer();
	IDFT(X, x, N);
	debug("■ IDFT\n処理時間 = %f [s]\n", Timer() - t0);
	Plot("idft.txt", x, N, dt, creal);
	debug("\n");
*/
	return (0);
}

