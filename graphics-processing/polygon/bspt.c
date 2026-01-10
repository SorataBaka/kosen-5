/* ポリゴンモデルのサンプル
 * 座標系：右手系．右が +x，上が +y，手前が +z．
 */

#include "polygon.h"

void shader(Polygon *p)		// ポリゴン毎のシェーディング
{
	double s;

//	s = -Dot(&p->view, &p->normal); // 可視性（−視線・法線）
	s = p->normal.vector[2];	// （法線ベクトルの z 成分）
	if (s <= 0.0) {		// 裏向きの面
		p->shade = 0.2;		// 暗めに
//		p->visible = 1;		// 表示する
		p->visible = 0;		// 表示しない（後面除去）
	} else {		// 表向きの面
		p->shade = s*0.6 + 0.4;	// 傾きに応じて明るめに
		p->visible = 1;		// 表示する
	}
}

int main()
{
	NewColors(2);			// 色の個数
	SetColor(0, 1.0, 0.5, 0.5);	// 色番号, R, G, B
	SetColor(1, 0.5, 1.0, 0.5);

	NewVertexes(5);			// 頂点の個数
	SetVertex(0, -2.0,  0.0,  0.0);	// 頂点番号, x, y, z
	SetVertex(1,  2.0,  2.0,  0.0);
	SetVertex(2,  2.0, -2.0,  0.0);
	SetVertex(3,  0.0,  0.0,  1.0);
	SetVertex(4,  0.0,  0.0, -1.0);

	NewPolygons(6);			// ポリゴンの個数
	SetPolygon3(0,  0, 3, 1,  0);	// 面番号, 頂点番号x3, 色番号
	SetPolygon3(1,  0, 1, 4,  0);
	SetPolygon3(2,  0, 4, 2,  0);
	SetPolygon3(3,  0, 2, 3,  0);
	SetPolygon3(4,  1, 3, 4,  0);
	SetPolygon3(5,  2, 4, 3,  0);

	SetBsptRoot(0);		// ルートポリゴンの面番号
	SetBspt(0, -1, 1);	// 面番号，前方の面，後方の面
	SetBspt(1, -1, 2);
	SetBspt(2, -1, 3);
	SetBspt(3, -1, 4);
	SetBspt(4,  5, -1);
	SetBspt(5, -1, -1);

	UseDepthBuffer(0);	// デプスバッファ法を使わない
/*
*/
	UseBspt(1);		// BSP-Tree法を使う
	UseShader(shader);
	Preview("BSP-Tree");	// 表示
/*
	UseBspt(0);		// BSP-Tree法を使わない
	UseShader(shader);
	Preview("No BSP-Tree");	// 表示
*/
	return (0);
}

