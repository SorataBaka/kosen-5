// libpolygon Ver.20141219
// by yanagawa@kushiro-ct.ac.jp

#ifndef POLYGON_H
#define POLYGON_H

#define INTVAL	30
#define WIDTH	640
#define HEIGHT	480

typedef struct {
	double vector[4];	// x,y,z,w  or  r,g,b,a
} Vector;		// 4D同次座標ベクトル

typedef struct {
//	int	vertex[3];	// 頂点番号リスト（旧ver.では三角形だけ）
	int	vertex[4];	// 頂点番号リスト（本ver.では四角形も使える）
	int	n_vertex;	// 頂点の個数（must be 3 or 4）
	int	color;		// 色番号

	Vector	normal;		// 変換後の法線
	Vector	view;		// 視線ベクトル
	double	shade;		// 照度
	int	visible;		// 可視性

	int	bspt_fore;	// 前方の面番号
	int	bspt_back;	// 後方の面番号
} Polygon;		// ポリゴン

//extern void shader(Polygon *p);
extern void UseShader(void (*func)(Polygon *p));

extern void Fatal(char *msg);
extern void Debug(char *msg);

extern double Norm(Vector *v);
extern double Dot(Vector *v1, Vector *v2);

extern void UseDepthBuffer(int sw);

extern int NewColors(int n);
extern int NewVertexes(int n);
extern int NewPolygons(int n);

extern void SetColor(int i, double r, double g, double b);
extern void SetVertex(int i, double x, double y, double z);

extern void SetPolygon4(int i, int v0, int v1, int v2, int v3, int c);
extern void SetPolygon3(int i, int v0, int v1, int v2, int c);
#define SetPolygon	SetPolygon3

extern void SetBsptRoot(int i);
extern void SetBspt(int i, int fore, int back);
extern void UseBspt(int s);

extern void Preview(char *title);

#endif

