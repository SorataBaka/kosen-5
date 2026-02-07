#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "img.h"

#define PUBLIC
#define PRIVATE	static

#define BUFLEN	256

PRIVATE void fatal(char *msg) { fprintf(stderr, "%s\n", msg); exit(1); }
PRIVATE void debug(char *msg) { fprintf(stderr, "%s\n", msg); }

PRIVATE int mkCmd(char *buf, int n, const char *cmd, const char *file)
{
	if (strlen(cmd)+strlen(file) > n) return (1);
	sprintf(buf, cmd, file);
	return (0);
}

PRIVATE int GetImgSize(const char *file, int *w, int *h)
{
	FILE *pp;
	char buf[BUFLEN];
	int  n;

	if (mkCmd(buf, BUFLEN, IDENTIFY_CMD, file)) fatal("GetImgSize(): filename too long.");
	if ((pp = popen(buf, "r")) == NULL) fatal("GetImgSize(): couldn't identify.");
	n = fscanf(pp, "%d %d", w, h);
	pclose(pp);
	if (n != 2) fatal("GetImgSize(): couldn't get image size.");
	return (0);
}

PRIVATE FILE *OpenImgFile(const char *file)
{
	char buf[BUFLEN];

	if (mkCmd(buf, BUFLEN, CONVERT_CMD, file)) fatal("OpenImgFIle(): filename too long.");
	return (popen(buf, "r"));
}

PRIVATE void CloseImgFile(FILE *fp)
{
	pclose(fp);
}

// 画像を生成
PUBLIC Img *NewImg(int n, int w, int h, int max)
{
	Img *img;

	img = (Img *)malloc(sizeof(Img));
	if (img == NULL) goto ERROR;

	img->n = n;
	img->w = w;
	img->h = h;
	img->max = max;

	img->pixel = (double *)calloc(w*h, sizeof(double)*n);
	if (img->pixel == NULL) goto ERROR;

	return (img);

ERROR:
	FreeImg(img);
	return (NULL);
}

// 画像を破棄
PUBLIC void FreeImg(Img *img)
{
	if (img != NULL) free(img->pixel);
	free(img);
}

// 画像をクリア
PUBLIC int ClearImg(Img *img, const double *val)
{
	int	x, y, c;
	double	*p;

	if (!img) return (1);
	p = img->pixel;
	for (y = 0; y < img->h; y++)
	for (x = 0; x < img->w; x++)
	for (c = 0; c < img->n; c++)
	{
		*p = val[c];
		p++;
	}
	return (0);
}

// not-tested: 任意形式をRGB形式へ変換し入力
PUBLIC Img *ReadImgRGB(const char *file)
{
	FILE	*fp;
	Img	*img;
	int	w, h;
	int	x, y, c;
	int	tmp;
	double	*p;

	GetImgSize(file, &w, &h);
	if ((img = NewImg(RGB, w, h, 255)) == NULL) goto ERROR;
	if ((fp = OpenImgFile(file)) == NULL) goto ERROR;

	p = img->pixel;
	for (y = 0; y < h; y++)
	for (x = 0; x < w; x++)
	for (c = 0; c < RGB; c++)
	{
		if ((tmp = fgetc(fp)) == EOF) goto ERROR;
		*p = (double)tmp;
		p++;
	}
	CloseImgFile(fp);
	return (img);

ERROR:
	CloseImgFile(fp);
	return (NULL);
}

// RGB成分をPPM形式として出力
PUBLIC int WriteImgRGB(FILE *fp, const Img *img)
{
	int	x, y, c;
	double	*p0;	// RGBD値へのポインタ
	double	*p;	// RGB各成分へのポインタ
	double	v, max;	// 出力画素値

	if (!img) return (1);
	if (img->n < RGB) return (1);

	fprintf(fp, "P6\n");
	fprintf(fp, "%d %d\n", img->w, img->h);
	fprintf(fp, "%d\n", img->max);
	p0 = img->pixel;
	max = (double)(img->max);
	for (y = 0; y < img->h; y++)
	for (x = 0; x < img->w; x++)
	{
		p = p0;
		for (c = 0; c < RGB; c++) {
			v = max*(*p);
			if (v < 0.0) v = 0.0;
			else if (v > max) v = max;
			fputc((int)(v + 0.5), fp);
			p++;
		}
		p0 += img->n;
	}
	return (0);
}

// D値の最小値を設定
PUBLIC int SetImgNear(Img *img, double near)
{
	if (!img) return (1);
	if (img->n < RGBD) return (1);
	img->near = near;
	return (0);
}

// D値の最大値を設定
PUBLIC int SetImgFar(Img *img, double far)
{
	if (!img) return (1);
	if (img->n < RGBD) return (1);
	img->far = far;
	return (0);
}

// D成分をPGM形式として出力
// near：画素値をゼロとする距離
// far：画素値をMAXVALとする距離
PUBLIC int WriteImgD(FILE *fp, const Img *img)
{
	int	x, y;
	double	*p;		// D値へのポインタ
	double	near, dif;	// D値の範囲
	double	v, max;		// 出力画素値

	if (!img) return (1);
	if (img->n < RGBD) return (1);

	fprintf(fp, "P5\n");
	fprintf(fp, "%d %d\n", img->w, img->h);
	fprintf(fp, "%d\n", img->max);
	p = img->pixel + RGB;
	max = (double)(img->max);
	near = img->near;
	dif = img->far - near;
	for (y = 0; y < img->h; y++)
	for (x = 0; x < img->w; x++)
	{
		v = max*(*p - near)/dif;
		if (v < 0.0) v = 0.0; else if (v > max) v = max;
		fputc((int)(v + 0.5), fp);
		p += img->n;
	}
	return (0);
}

PRIVATE int chkXY(const Img *img, int x, int y)
{
	if (x < 0) return (1);
	if (x >= img->w) return (1);
	if (y < 0) return (1);
	if (y >= img->h) return (1);
	return (0);
}

// RGB値をセット
PUBLIC int SetImgRGB(Img *img, int x, int y, const double *val)
{
	int	c;
	double	*p;

	if (!img) return (1);
	if (img->n < RGB) return (1);
	if (chkXY(img, x, y)) return (1);

	p = img->pixel + (y*(img->w) + x)*(img->n);
	for (c = 0; c < RGB; c++) {
		*p = *val;
		val++;
		p++;
	}
	return (0);
}

// RGB値をゲット
PUBLIC int GetImgRGB(const Img *img, int x, int y, double *val)
{
	int  c;
	double  *p;

	if (!img) return (1);
	if (img->n < RGB) return (1);
	if (chkXY(img, x, y)) return (1);

	p = img->pixel + (y*(img->w) + x)*(img->n);
	for (c = 0; c < RGB; c++) {
		*val = *p;
		val++;
		p++;
	}
	return (0);
}

// D値をセット
PUBLIC int SetImgD(Img *img, int x, int y, const double *d)
{
	double	*p;

	if (!img) return (1);
	if (img->n < RGB) return (1);
	if (chkXY(img, x, y)) return (1);

	p = img->pixel + (y*(img->w) + x)*(img->n) + RGB;
	*p = *d;
	return (0);
}

// D値をゲット
PUBLIC int GetImgD(const Img *img, int x, int y, double *d)
{
	double  *p;

	if (!img) return (1);
	if (img->n < RGB) return (1);
	if (chkXY(img, x, y)) return (1);

	p = img->pixel + (y*(img->w) + x)*(img->n) + RGB;
	*d = *p;
	return (0);
}

// RGB画像を表示
PUBLIC int ShowImgRGB(const Img *img, const char *title)
{
	FILE *pp;
	char buf[BUFLEN];

	if (mkCmd(buf, BUFLEN, DISPLAY_CMD, title)) return (1);
	if ((pp = popen(buf, "w")) == NULL) return (1);
	WriteImgRGB(pp, img);
	pclose(pp);
	return (0);
}

// D画像を表示
PUBLIC int ShowImgD(const Img *img, const char *title)
{
	FILE *pp;
	char buf[BUFLEN];

	if (mkCmd(buf, BUFLEN, DISPLAY_CMD, title)) return (1);
	if ((pp = popen(buf, "w")) == NULL) return (1);
	WriteImgD(pp, img);
	pclose(pp);
	return (0);
}

// RGB画像を保存
PUBLIC int SaveImgRGB(const Img *img, const char *file)
{
	FILE *fp;

	if ((fp = fopen(file, "w")) == NULL) return (1);
	WriteImgRGB(fp, img);
	fclose(fp);
	return (0);
}

// D画像を保存
PUBLIC int SaveImgD(const Img *img, const char *file)
{
	FILE *fp;

	if ((fp = fopen(file, "w")) == NULL) return (1);
	WriteImgD(fp, img);
	fclose(fp);
	return (0);
}
#ifdef __cplusplus
}
#endif

