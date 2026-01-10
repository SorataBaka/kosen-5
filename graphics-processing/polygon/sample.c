/*
 * ポリゴンモデルのサンプル
 * 座標系：右手系．右が +x，上が +y，手前が +z．
 * コンパイル：cc sample.c -lpolygon -L. -o sample
 * キー操作：[↑], [↓], [←], [→], [Space]，[B]，[R]，[Q]
 */

#include "polygon.h"

// ポリゴン毎のシェーディング（陰影付け）関数
// （この関数は，どこからも呼び出されていないように見えるが，
// main() からではなく，Preview() 内から呼び出される．
// ちなみに，キー入力等も Preview() 内で処理される．）
void shader(Polygon *p)
{
	double s;

//	s = -Dot(&p->view, &p->normal);	// 可視性（−視線・法線）
	s = p->normal.vector[2];	// （法線ベクトルの z 成分）
	if (s < 0.0) {		// 裏向きの面
		p->shade = 0.2;		// 暗めに
		p->visible = 1;		// 表示する
//		p->visible = 0;		// 表示しない（後面除去法で隠面消去）
	} else {		// 表向きの面
		p->shade = s*0.6 + 0.4;	// 傾きに応じて明るめに
		p->visible = 1;		// 表示する
	}
}

// メイン関数
int main()
{
// モデリング
	// 色の設定
	NewColors(2);			// 色の個数
	SetColor(0, 1.0, 0.5, 0.5);	// 色番号, R, G, B
	SetColor(1, 0.5, 1.0, 0.5);

	// 頂点データの設定
	NewVertexes(4);			// 頂点の個数
	SetVertex(0, -1.0, -1.0,  1.0);	// 頂点番号, x, y, z
	SetVertex(1,  1.0, -1.0, -1.0);
	SetVertex(2,  1.0,  1.0,  1.0);
	SetVertex(3, -1.0,  1.0, -1.0);

	// 面データの設定
	// 頂点番号の順序は，「その面を表側から見て」反時計回り
	// （「視点から見て」...ではない!!）
	NewPolygons(2);			// 面（三角形ポリゴン）の個数
	SetPolygon3(0,  0, 1, 2,  0);	// 面番号, 頂点番号x3, 色番号
	SetPolygon3(1,  2, 3, 0,  1);

// レンダリング
	UseDepthBuffer(1);		// デプスバッファ法で隠面消去する
//	UseDepthBuffer(0);		// デプスバッファ法で隠面消去しない
	UseShader(shader);
	Preview("Polygon");		// 表示開始
	return (0);
}

