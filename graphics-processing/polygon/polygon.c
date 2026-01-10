// libpolygon Ver.20141219
// by yanagawa@kushiro-ct.ac.jp
//
// added:
//   SetPolygon4() - 四角形ポリゴンの作成
//   SetPolygon3() - 三角形ポリゴンの作成（旧SetPolygon() と同）

#include "polygon.h"
#ifdef MACOSX
#include <OpenGL/gl.h>
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define PRIVATE	static
#define PUBLIC

PRIVATE Vector  *color = NULL;		// 色
PRIVATE int     n_color = 0;		// 色の個数

PRIVATE Vector  *vertex = NULL;		// 頂点の位置ベクトル
PRIVATE int     n_vertex = 0;		// 頂点の個数

PRIVATE Polygon *polygon = NULL;	// ポリゴン
PRIVATE Vector  *normal = NULL;		// ポリゴンの法線ベクトル
PRIVATE int     n_polygon = 0;		// ポリゴンの個数

PRIVATE int     ready = 0;
PRIVATE int     mode = 0;	// 表示方法：0=サーフェス，1=ワイヤーフレーム
PRIVATE int	use_bspt = 0;	// BSP-tree フラグ
PRIVATE int	bspt_root = 0;
PRIVATE int	use_dbuf = 0;

PRIVATE double  rotx;	// x軸中心の回転角度
PRIVATE double  roty;	// y軸中心の回転角度
PRIVATE double  dist;	// z方向の位置

PRIVATE void Reset()
{
	rotx = 0.0;
	roty = 0.0;
	dist = -10.0;
}

PUBLIC void Fatal(char *msg) { fprintf(stderr, "%s\n", msg); exit(1); }
PUBLIC void Debug(char *msg) { fprintf(stderr, "%s\n", msg); }

PRIVATE void DefaultShader(Polygon *p)
{
// to-do
}

void (*shaderfunc)(Polygon *p) = DefaultShader;

PUBLIC void UseShader(void (*func)(Polygon *p))
{
	shaderfunc = func;
}

PRIVATE Vector *NewVectors(int n)
{
	return ((Vector *)malloc(sizeof(Vector)*n));
}

PUBLIC void UseDepthBuffer(int sw)
{
	use_dbuf = sw;
}

PUBLIC int NewColors(int n)
{
	n_color = n;
	color = NewVectors(n);
	if (color == NULL) return (1);
	return (0);
}

PUBLIC int NewVertexes(int n)
{
	n_vertex = n;
	vertex = NewVectors(n);
	if (vertex == NULL) return (1);
	return (0);
}

PUBLIC int NewPolygons(int n)
{
	n_polygon = n;
	polygon = (Polygon *)malloc(sizeof(Polygon)*n);
	if (polygon == NULL) return (1);
	normal = (Vector *)malloc(sizeof(Vector)*n);
	if (normal == NULL) { free(polygon); return (1); }
	return (0);
}

PRIVATE void SetVector(double *v, double x, double y, double z, double w)
{
	v[0] = x; v[1] = y; v[2] = z; v[3] = w;
}

PUBLIC void SetColor(int i, double r, double g, double b)
{
	SetVector(color[i].vector, r, g, b, 1.0);
}

PUBLIC void SetVertex(int i, double x, double y, double z)
{
	SetVector(vertex[i].vector, x, y, z, 1.0);
}

PUBLIC double Norm(Vector *v)
{
	static int i;
	static double d, n;

	n = 0.0;
	for (i = 0; i < 3; i++) {
		d = v->vector[i];
		n += d*d;
	}
	return (sqrt(n));
}

PRIVATE void Normalize(Vector *v)
{
	static int i;
	static double n;

	n = Norm(v);
	for (i = 0; i < 3; i++) {
		v->vector[i] /= n;
	}
	v->vector[3] = 1.0;
}

PRIVATE void Add(Vector *v, Vector *v1, Vector *v2)
{
	static int i;
	for (i = 0; i < 3; i++) {
		v->vector[i] = v1->vector[i] + v2->vector[i];
	}
	v->vector[3] = 1.0;
}

PRIVATE void Sub(Vector *v, Vector *v1, Vector *v2)
{
	static int i;
	for (i = 0; i < 3; i++) {
		v->vector[i] = v1->vector[i] - v2->vector[i];
	}
	v->vector[3] = 1.0;
}

PUBLIC double Dot(Vector *v1, Vector *v2)
{
	static int i;
	double z=0.0;

	for (i = 0; i < 3; i++) {
		z += v1->vector[i] * v2->vector[i];
	}
	return (z);
}

PRIVATE void Cross(Vector *v, Vector *v1, Vector *v2)
{
	static int i, j, k;

	for (i = 0; i < 3; i++) {
		j = (i+1)%3;
		k = (i+2)%3;
		v->vector[i] = v1->vector[j]*v2->vector[k]
			- v1->vector[k]*v2->vector[j];
	}
	v->vector[3] = 1.0;
}

PRIVATE void CalcNormal(Polygon *p, Vector *n)
{
	static Vector v1, v2;

	Sub(&v1, &vertex[p->vertex[1]], &vertex[p->vertex[0]]);
	Sub(&v2, &vertex[p->vertex[2]], &vertex[p->vertex[0]]);
	Cross(n, &v1, &v2);
	Normalize(n);
	// 注：四角形ポリゴンの頂点[3] は不使用．
}

PUBLIC void SetPolygon4(int i, int v0, int v1, int v2, int v3, int c)
{
	static Polygon *p;

	p = &polygon[i];
	p->vertex[0] = v0;
	p->vertex[1] = v1;
	p->vertex[2] = v2;
	p->vertex[3] = v3;
	p->n_vertex = 4;
	p->color = c;

	CalcNormal(p, &normal[i]);
	p->shade = 1.0;
	p->visible = 1;
}

//PUBLIC void SetPolygon(int i, int v0, int v1, int v2, int c)
PUBLIC void SetPolygon3(int i, int v0, int v1, int v2, int c)
{
	static Polygon *p;

	p = &polygon[i];
	p->vertex[0] = v0;
	p->vertex[1] = v1;
	p->vertex[2] = v2;
	p->n_vertex = 3;
	p->color = c;

	CalcNormal(p, &normal[i]);
	p->shade = 1.0;
	p->visible = 1;
}

PUBLIC void SetBsptRoot(int i) { bspt_root = i; }

PUBLIC void SetBspt(int i, int fore, int back)
{
	static Polygon *p;

	p = &polygon[i];
	p->bspt_fore = fore;
	p->bspt_back = back;
}

PUBLIC void UseBspt(int s) { use_bspt = s; }

PRIVATE void UpdateNormal(Polygon *p, Vector *n, double *mat)
{
	static int  i, j;

	for (i = 0; i < 3; i++) {
		p->normal.vector[i] = 0.0;
		for (j = 0; j < 3; j++) {
			p->normal.vector[i] += n->vector[j]*mat[j*4+i];
		}
	}
	p->normal.vector[3] = 1.0;


	for (i = 0; i < 4; i++) {
		p->view.vector[i] = 0.0;
		for (j = 0; j < 4; j++) {
			p->view.vector[i] += vertex[p->vertex[0]].vector[j]*mat[j*4+i];
		}
	}
	Normalize(&p->view);

//	p->normal.vector[3] = -Dot(&p->view, &p->normal); // 可視性（迷い中）
}

PRIVATE void ShadeColor(Polygon *p)
{
	static int  i;
	static double shade[4];

	for (i = 0; i < 3; i++) {
		shade[i] = color[p->color].vector[i]*p->shade;
	}
	shade[3] = 1.0;

	glColor4dv(shade);
}

PRIVATE void DrawPolygon(Polygon *p)
{
	static int i;
	static int n;

	if (!p->visible) return;

	glBegin(GL_POLYGON);
	ShadeColor(p);
	n = p->n_vertex;
	for (i = 0; i < n; i++) {
		glVertex4dv(vertex[p->vertex[i]].vector);
	}
	glEnd();
}

PRIVATE void DrawPolygons()
{
	static int  i;
	static double mat[16];
	static Polygon *p;
	static Vector *n;

	glGetDoublev(GL_MODELVIEW_MATRIX, mat);

	glPushMatrix();
	p = polygon;
	n = normal;
	for (i = 0; i < n_polygon; i++) {
		UpdateNormal(p, n, mat);
		shaderfunc(p);
		DrawPolygon(p);
		p++;
		n++;
	}
	glPopMatrix();
}

PRIVATE void TraverseBspt(int i)
{
	Polygon *p;

	if (i < 0) return;
	if (i >= n_polygon) return;

	p = &polygon[i];
//	if (p->normal.vector[2] > 0.0) {	// 表向きの面
//	if (p->normal.vector[3] > 0.0) {	// 表向きの面
	if (Dot(&p->view, &p->normal) < 0.0) {	// （迷い中）
		TraverseBspt(p->bspt_back);		// 後方を描く
		DrawPolygon(p);				// この面を描く
		TraverseBspt(p->bspt_fore);		// 前方を描く
	} else {				// 裏向きの面
		TraverseBspt(p->bspt_fore);		// 前方を描く
		DrawPolygon(p);				// この面を描く
		TraverseBspt(p->bspt_back);		// 後方を描く
	}
}

PRIVATE void BsptDrawPolygons()
{
	static int  i;
	static double mat[16];
	static Polygon *p;
	static Vector *n;

	glGetDoublev(GL_MODELVIEW_MATRIX, mat);

	glPushMatrix();
	p = polygon;
	n = normal;
	for (i = 0; i < n_polygon; i++) {
		UpdateNormal(p, n, mat);
		shaderfunc(p);
		p++;
		n++;
	}
	TraverseBspt(bspt_root);
	glPopMatrix();
}

PRIVATE void Display()
{
//	static float lightpos[] = { 1.0, 1.0, 1.0, 0.0 };

	switch (mode) {
	case 0: glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); break;
	case 1: glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); break;
	default: break;
	}

	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
//	glLightfv(GL_LIGHT0, GL_POSITION, lightpos);
	gluLookAt(0.0, 0.0, 0.0,   0.0, 0.0, -1.0,   0.0, 1.0, 0.0);

	glTranslated(0.0, 0.0, dist);
	glRotated(rotx, 1.0, 0.0, 0.0);
	glRotated(roty, 0.0, 1.0, 0.0);

	if (use_bspt) {
		BsptDrawPolygons();
	} else {
		DrawPolygons();
	}

	glutSwapBuffers();
}

PRIVATE void Keybd(unsigned char key, int x, int y)
{
	if (ready) return;

	switch (key) {
	case 'q': exit(1); break;		// 終了

	case 'r': Reset(); break;		// リセット

	case ' ': dist += 1.0; break;		// 前後移動
	case 'b': dist -= 1.0; break;

	case 's': mode = (mode+1)%2; break;	// 表示方法変更
	default: break;
	}
	ready = 1;
}

PRIVATE void Keypad(int key, int x, int y)
{
	if (ready) return;

	switch (key) {
	case GLUT_KEY_LEFT:  roty -= 10.0; break;	// 左右回転
	case GLUT_KEY_RIGHT: roty += 10.0; break;
	case GLUT_KEY_UP:    rotx -= 10.0; break;	// 上下回転
	case GLUT_KEY_DOWN:  rotx += 10.0; break;
	default: break;
	}
	ready = 1;
}

PRIVATE void Timer(int val)
{
	ready = 0;
	glutTimerFunc(INTVAL, Timer, val);
	glutPostRedisplay();
}

PRIVATE void Reshape(int w, int h)
{
	double aspect = (double)w/(double)h;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(30.0, aspect, 0.1, 100.0);
	glViewport(0, 0, w, h);
	glutPostRedisplay();
}

// PRIVATE void Idle() { glutPostRedisplay(); }

PUBLIC void Preview(char *title)
{
	int dummy=0;

	Reset();

	glutInit(&dummy, NULL);
	glutInitWindowSize(WIDTH, HEIGHT);
	glutInitDisplayMode(GLUT_RGBA|GLUT_DEPTH|GLUT_DOUBLE);
	glutCreateWindow(title);

	glutDisplayFunc(Display);
	glutReshapeFunc(Reshape);
	glutKeyboardFunc(Keybd);
	glutSpecialFunc(Keypad);
	glutTimerFunc(INTVAL, Timer, 0);
//	glutIdleFunc(Idle);

/*
　隠面処理とシェーディングについては，OpenGL の機能を利用せずとも，
　自前で実装し，main( ) および shader( ) で制御できるようにした．

	// OpenGL の機能を利用する場合...
	glEnable(GL_CULL_FACE);		// 後面除去法
	glCullFace(GL_BACK);
	glEnable(GL_LIGHTING);		// 照明
	glEnable(GL_LIGHT0);
*/

	if (use_dbuf) {			// デプスバッファ法
		glEnable(GL_DEPTH_TEST);
	} else {
		glDisable(GL_DEPTH_TEST);
	}

	glEnable(GL_NORMALIZE);
	glClearColor(0.5, 1.0, 1.0, 1.0);

	ready = 0;
	glutMainLoop();
}

