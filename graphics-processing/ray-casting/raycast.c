/*
 * レイキャスティング法によるレンダリング
 * Ver.2021.01.11
 *
 * 簡単化などのための仮定：
 * ・座標系（x, y, z）＝（右，上，手前）
 *     - スクリーンは xy 平面上（z = 0）
 *     - 視点は +z 軸上
 * ・3D 的なスクリーンのサイズ＝出力画像のサイズ
 * ・3D 的な原点 ＝ スクリーンの中心
 * ・方向ベクトルを常に正規化しておく
 * ・フレームバッファとデプスバッファをRGBD画像として一体化
 *
 * 動作環境：画像表示ShowImgRGB()ではImageMagickが必要．
 *   Linux以外では画像保存SaveImgRGB()を推奨．
 */
#include "img.h"
#include "vect.h"
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

typedef struct
{
	double diff[RGB]; // 拡散反射率のRGB値	k_d
	double spec[RGB]; // 鏡面反射率のRGB値	k_s
	int high;					// ハイライトパラメータ	n，α
} Material;

// Sphere（球体）型構造体
typedef struct
{
	Vect pos;		// 24 bytes
	double rad; // 8 bytes
	int mid;		// 4 bytes
	int pad;		// 4 bytes (PADDING to make total size 40 bytes)
} Sphere;

/* 球体へのレイキャスティング
 * 入力：球体 *s，視点 eye，視線 ray
 * return：視点-球体表面の距離（視線の到達時間）
 */
#define MAX_SPHERES 150

// Helper: Random double between min and max
double randomVal(double min, double max)
{
	return min + (max - min) * ((double)rand() / (double)RAND_MAX);
}

void generateRandomSpheres(Sphere spheres[], int *nsph)
{
	*nsph = 0;
	int max_attempts = 10000;
	int attempts = 0;

	while (*nsph < MAX_SPHERES && attempts < max_attempts)
	{
		Sphere candidate;

		candidate.pos.x = randomVal(-400.0, 400.0);
		candidate.pos.y = randomVal(-300.0, 300.0);
		candidate.pos.z = randomVal(-200.0, 200.0);
		candidate.rad = randomVal(10.0, 50.0);
		candidate.mid = (int)randomVal(0, 8);
		if (candidate.mid > 7)
			candidate.mid = 7;
		// ----------------------------------------

		int overlap = 0;
		for (int i = 0; i < *nsph; i++)
		{
			Sphere other = spheres[i];
			double dx = candidate.pos.x - other.pos.x;
			double dy = candidate.pos.y - other.pos.y;
			double dz = candidate.pos.z - other.pos.z;
			double distSq = dx * dx + dy * dy + dz * dz;
			double minDist = candidate.rad + other.rad;

			if (distSq < (minDist * minDist))
			{
				overlap = 1;
				break;
			}
		}

		if (overlap == 0)
		{
			spheres[*nsph] = candidate;
			(*nsph)++;
			attempts = 0;
		}
		else
		{
			attempts++;
		}
	}
}
double RayCast(Sphere *s, Vect eye, Vect ray)
{
	double a, b, c; // 二次方程式 a t^2 + b t + c = 0 の係数
	double d;				// 二次方程式の判別式
	double t;				// 二次方程式の解

	a = vLen2(ray); // or  a = 1.0;

	b = 2.0 * vDot(ray, vSub(eye, s->pos));
	if (b >= 0.0)
		return (-1.0); // 球体が視線の逆方向→妥当な解なし

	c = vLen2(vSub(eye, s->pos)) - (s->rad) * (s->rad);
	if (c < 0.0)
		return (-1.0); // 視点が球内→妥当な解なし

	d = b * b - 4.0 * a * c;
	if (d < 0.0)
		return (-1.0); // 交点なし→解なし

	t = (b + sqrt(d)) / (-2.0 * a); // ２つの解のうち小さい方
	return (t);
}

int main(int argc, char **argv)
{
	// -------- ここから ------ 初期値を適宜変更可 ------ ここから --------
	// 材料
	Material matl[] = {
			// 拡散反射率，鏡面反射率，ハイライト
			{{0.40, 0.25, 0.10}, {0.80, 0.50, 0.20}, 4}, // [0]:金
			{{0.45, 0.46, 0.49}, {0.90, 0.91, 0.98}, 4}, // [1]:銀
			{{0.36, 0.23, 0.10}, {0.72, 0.45, 0.20}, 4}, // [2]:銅
			{{1.0, 0.0, 0.0}, {1.0, 1.0, 1.0}, 20},			 // [3]:赤プラ
			{{0.0, 1.0, 0.0}, {1.0, 1.0, 1.0}, 20},			 // [4]:緑プラ
			{{0.0, 0.0, 1.0}, {1.0, 1.0, 1.0}, 20},			 // [5]:青プラ
			{{0.5, 0.5, 0.5}, {0.5, 0.5, 0.5}, 1},			 // [6]:舗装
			{{0.0, 0.0, 0.0}, {1.0, 1.0, 1.0}, 100},		 // [7]: 完全鏡面 (Perfect Mirror)
	};

	// 球体
	Sphere sph[MAX_SPHERES];
	int nsph = 0;
	srand((unsigned int)time(NULL));
	generateRandomSpheres(sph, &nsph);

	// 背景
	double bg[RGBD] = {0.25, 0.5, 0.75, 1.0e+10}; // RGBD値

	// 照明光・環境光
	Vect light = {1.0, 0.5, 1.0};			 // 照明の位置ベクトル	Ｌ
	double inc[RGB] = {1.0, 1.0, 1.0}; // 照明光強度のRGB値	I_i
	double amb[RGB] = {0.5, 0.5, 0.5}; // 環境光強度のRGB値	I_a

	// カメラ・画像
	int w = 1920, h = 1080; // スクリーン（画像）のサイズ
	int ez = 800;						// 視点のz座標
													// -------- ここまで -------------------------------- ここまで --------

	// 画像関連の変数
	Img *img; // 画像
	int x, y; // 画素のスクリーン座標
	Vect pix; // 画素の位置ベクトル

	// レイキャスティング，デプスバッファリング関連の変数
	Vect eye;			// 視点の位置ベクトル		Ｐ_1
	Vect ray;			// 視線の方向ベクトル		Ｄ
	double dist;	// 視点-物体間の距離（時間）	t
	double depth; // 深度値（distの最小値）	t
	int i, c;			// 物体番号，RGBチャネル番号

	// シェーディング関連の変数
	Sphere *s;			 // 可視物体へのポインタ
	Material *m;		 // 可視物体の材料へのポインタ
	Vect lookat;		 // 注視点の位置ベクトル	Ｐ
	Vect normal;		 // 法線ベクトル		Ｎ
	Vect reflect;		 // 整反射の方向ベクトル	Ｒ
	Vect view;			 // 視点の方向ベクトル	Ｖ
	double cosd;		 // 拡散反射の角度因子	cosθ
	double coss;		 // 鏡面反射の角度因子	cosφ
	double cosh;		 // ハイライトの因子	cos^n φ
	double val[RGB]; // 反射光強度のRGB値（0.0〜1.0）	I

	// RGBD画像の初期化
	img = NewImg(RGBD, w, h, 255); // メモリ領域を確保
	if (!img)
		return (1);			 // 確保失敗→ 終了
	ClearImg(img, bg); // 背景を設定

	// 各種ベクトルの初期化
	eye = vInit(0.0, 0.0, ez); // 視点の位置ベクトル	Ｐ_1
	light = vUnit(light);			 // 照明の方向ベクトル	Ｌ

	// レンダリング
	for (y = 0; y < h; y++)
		for (x = 0; x < w; x++)
		{ // ラスタスキャン
			// 各種ベクトルの初期化
			pix = vInit(x - w / 2.0, h / 2.0 - y, 0.0); // 画素の位置ベクトル
			ray = vUnit(vSub(pix, eye));								// 視線ベクトル   Ｄ

			double total_col[RGB] = {0.0, 0.0, 0.0};
			double weight[RGB] = {1.0, 1.0, 1.0};
			Vect current_eye = eye;
			Vect current_ray = ray;
			int bounce;
			for (bounce = 0; bounce < 3; bounce++)
			{
				s = NULL;
				depth = 1.0e+10; // Reset depth for local search
				for (i = 0; i < nsph; i++)
				{
					// レイキャスティング (Use current_eye/current_ray)
					dist = RayCast(&sph[i], current_eye, current_ray);
					if (dist <= 0.0)
						continue; // 交差なし
					if (dist >= depth)
						continue;
					depth = dist; // 深度の更新
					s = &sph[i];	// 可視物体の更新
				}
				if (!s)
				{
					for (c = 0; c < RGB; c++)
						total_col[c] += bg[c] * weight[c];
					break; // Stop bouncing
				}
				if (bounce == 0)
				{
					double old_depth;
					GetImgD(img, x, y, &old_depth);
					if (depth < old_depth)
					{
						SetImgD(img, x, y, &depth);
					}
				}

				lookat = vAdd(current_eye, vScale(current_ray, depth)); // 注視点
				normal = vUnit(vSub(lookat, s->pos));										// 法線
				m = &matl[s->mid];																			// 材料
				// 拡散反射成分のシェーディング
				cosd = vDot(light, normal);
				if (cosd < 0.0)
					cosd = 0.0;

				// 鏡面反射成分のシェーディング
				coss = 0.0;
				view = vScale(current_ray, -1.0);
				reflect = vSub(vScale(normal, 2.0 * vDot(normal, light)), light);
				coss = vDot(view, reflect);
				if (coss < 0.0)
					coss = 0.0;
				cosh = pow(coss, (double)(m->high));

				// シャドーイング
				int shadow = 0;
				Vect origin = vAdd(lookat, vScale(normal, 1.0e-3));
				for (int k = 0; k < nsph; k++)
				{
					if (&sph[k] == s)
						continue; // Don't self-shadow
					double t_shadow = RayCast(&sph[k], origin, light);
					if (t_shadow > 0.0)
					{
						shadow = 1;
						break;
					}
				}
				for (c = 0; c < RGB; c++)
				{
					val[c] = (m->diff[c]) * amb[c];
					if (!shadow)
					{
						val[c] += (m->diff[c]) * inc[c] * cosd + (m->spec[c]) * inc[c] * cosh;
					}
					total_col[c] += val[c] * weight[c];
				}
				if (s->mid == 7)
				{
					double d_dot_n = vDot(current_ray, normal);
					current_ray = vSub(current_ray, vScale(normal, 2.0 * d_dot_n));
					current_ray = vUnit(current_ray);

					// 2. Update Eye (Move to surface)
					current_eye = vAdd(lookat, vScale(normal, 1.0e-3));

					// 3. Update Weight (Mirror absorbs slight light)
					for (c = 0; c < RGB; c++)
						weight[c] *= 0.95;
				}
				else
				{
					break;
				}
			}
			SetImgRGB(img, x, y, total_col); // Update with total accumulated color
		}

	// RGB画像の出力
	// ShowImgRGB(img, "RayCasting [RGB]");	// RGB画像を表示
	SaveImgRGB(img, "color.ppm"); // RGB画像を保存

	// D画像の出力
	SetImgNear(img, ez - 100.0); // 画素値がゼロとなるD値を設定
	SetImgFar(img, ez + 100.0);	 // 　〃　　最大　　〃
	// ShowImgD(img, "RayCasting [D]"); // D画像を表示
	SaveImgD(img, "depth.ppm"); // D画像を保存
	FreeImg(img);								// RGBD画像のメモリ領域を解放
	return (0);
}
