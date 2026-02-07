// 画像処理 API Ver.2022.01.07
// 要 ImageMagick

#ifndef IMG_H
#define IMG_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>

// 画像データの構造体
typedef struct {
	int	n;	// チャネル数（例：3 or 4）
	int	w, h;	// サイズ（幅，高さ）
	int	max;	// 出力画素値の最大値
	double	*pixel;	// 画素値配列
	double	near, far;	// D値の最小値，最大値
} Img;

// 画像のチャネル数
#define RGB	3	// カラー画像の場合
#define RGBD	4	// カラー画像＋深度画像の場合

// ImageMagick によるお手軽な任意形式画像の入力
#define IDENTIFY_CMD	"identify -format '%%w %%h' %s"
#define CONVERT_CMD	"convert %s -depth 8 rgba:-"
#define DISPLAY_CMD	"display -title '%s' -"

extern Img *NewImg(int n, int w, int h, int max);	// 画像を生成
extern void FreeImg(Img *img);				// 画像を破棄
extern int ClearImg(Img *img, const double *val);	// 画像をクリア

extern Img *ReadImg(const char *file);		// 任意形式画像を入力
extern int WriteImgRGB(FILE *fp, const Img *img);	// RGB画像をPPM形式として出力

extern int SetImgNear(Img *img, double near);	// D値の最小値を設定
extern int SetImgFar(Img *img, double far);	// D値の最大値を設定
extern int WriteImgD(FILE *fp, const Img *img);	// D画像をPGM形式として出力

extern int SetImgRGB(Img *img, int x, int y, const double *rgb);	// RGB値をセット
extern int GetImgRGB(const Img *img, int x, int y, double *rgb);	// RGB値をゲット
extern int SetImgD(Img *img, int x, int y, const double *d);	// D値をセット
extern int GetImgD(const Img *img, int x, int y, double *d);	// D値をゲット

extern int ShowImgRGB(const Img *img, const char *title);	// RGB画像を表示
extern int ShowImgD(const Img *img, const char *title);		// D画像を表示

extern int SaveImgRGB(const Img *img, const char *file);	// RGB画像を保存
extern int SaveImgD(const Img *img, const char *file);		// D画像を保存
#ifdef __cplusplus
}
#endif

#endif

