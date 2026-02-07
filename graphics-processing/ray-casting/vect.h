// 3Dベクトル演算 API Ver.2026.01.07

#ifndef VECT_H
#define VECT_H
#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>

typedef struct { double x, y, z; } Vect;

extern Vect vInit(double x, double y, double z);	// 初期化
#define vZero()	vInit(0.0, 0.0, 0.0)			// ゼロベクトル
extern Vect vCirc(Vect v, int n);	// 成分の循環
extern Vect vAdd(Vect a, Vect b);	// 和 a + b
extern Vect vSub(Vect a, Vect b);	// 差 a - b
extern Vect vScale(Vect v, double s);	// 拡大（スカラ倍） v s
extern Vect vShrink(Vect v, double s);	// 縮小（スカラ分割） v/s
#define vRev(v)	vScale(v, -1.0)		// 反転 -v
extern double vDot(Vect a, Vect b);	// 内積 a . b
extern Vect vCross(Vect a, Vect b);	// 外積 a X b
extern Vect vMul(Vect a, Vect b);	// 成分毎の積 a b
extern Vect vDiv(Vect a, Vect b);	// 成分毎の商 a/b
extern double vLen2(Vect v);		// 長さの自乗 |v|^2
extern double vLen(Vect v);		// 長さ |v|
extern Vect vUnit(Vect v);		// 正規化
extern double vDif(Vect a, Vect b);	// 距離 |a - b|
extern Vect vLerp(Vect a, Vect b, double t);	// 線形補間
extern Vect vSlerp(Vect a, Vect b, double t);	// 球面線形補間
extern Vect vMax(Vect a, Vect b);	// 最大値
extern Vect vMin(Vect a, Vect b);	// 最小値
extern void vPrint(FILE *fp, Vect v);	// 成分表示

#ifdef __cplusplus
}
#endif
#endif

