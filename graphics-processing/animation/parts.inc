/* 人形モデル パーツ定義ファイル */

#include "colors.inc"
#include "shapes.inc"
#include "textures.inc"
#include "glass.inc"

// 座標を右手系に変更するマクロ
#macro RightHandSystem()
up<0.0, 1.0, 0.0>
    right<-1.33, 0.0, 0.0>
        sky<0.0, 1.0, 0.0>
#end

// 標準の質感の設定
#default {
            finish{ambient 0.6 diffuse 0.4 reflection 0.0} pigment
{
  color Gray
}
}

// 関節
#declare JointL = object{Sphere scale 0.075 } // 大
#declare EndM = object{torus{0.025, 0.01 } rotate 90 * z }
#declare EndS = object{torus{0.0125, 0.0075 } rotate 90 * z }
#declare JointM = merge { // 中
object{Disk_X scale<0.035, 0.035, 0.035>} object{EndM translate 0.035 * x} object { EndM translate - 0.035 * x }
}
#declare JointS = merge { // 小
object{Disk_X scale<0.020, 0.020, 0.020>} object{EndS translate 0.020 * x} object { EndS translate - 0.020 * x }
}

// グラサン
#declare SunGlass = intersection {
difference
{
  object{Disk_Y scale<0.1 + 0.02, 0.025, 0.125 + 0.02>} object { Disk_Y scale<0.1 + 0.01, 1, 0.125 + 0.01> }
}
object{Sphere scale<0.05, 0.05, 0.15> translate<0.05, 0.025, 0.15>} material{M_Glass} finish { conserve_energy }
}

#declare SunGlasses = merge {
object{SunGlass} object { SunGlass scale - 1 * x }
}

// 頭
#declare Hemisphere = intersection {
object{Sphere} object { Cube translate 1 * y }
}

#declare Head = merge {
merge{
    object{SunGlasses translate - 0.0 * y} merge{
        object{Hemisphere scale<0.1, 0.125, 0.125>} object{Hemisphere scale<0.1, -0.175, 0.125>} rotate - 25 * x} translate<0, 0.15, 0.0>} object { JointL } // 首関節
}

// 胸
#declare ChestH = 0.15; // 高さ÷2
#declare ChestW = 0.2;  // 幅÷2
#declare Chest = object{Sphere scale < 0.2, 0.15, 0.125> }

// 胴
#declare WaistH = 0.2; // 幅÷2
#declare Waist = object{Sphere scale < 0.075, 0.2, 0.05> }

// 腰
#declare HipW = 0.1; // 幅÷2
#declare Hip = object{Sphere scale < 0.1, 0.1, 0.075> }

// 上腕
#declare ArmLen = 0.25; // 長さ
#declare Arm = merge {
object{JointL} // 肩関節
object
{
  Sphere scale<0.05, 0.125, 0.05> translate - 0.125 * y
}
}

// 前腕
#declare ForearmLen = 0.25; // 長さ
#declare Forearm = merge {
object{JointM} // 肘関節
object
{
  Sphere scale<0.05, 0.125, 0.05> translate - 0.125 * y
}
}

// 手
#declare Hand = merge {
object{JointS} // 手首関節
object{Sphere scale<0.04, 0.075, 0.03>
           translate -
       0.075 * y} // 掌
object
{
  Sphere scale<0.02, 0.035, 0.02>
          translate - 0.035 * y rotate 30 * z rotate - 30 * y translate<0.015, -0.02, 0.01>
} // 親指
}
#declare LeftHand = object{Hand }            // 左手
#declare RightHand = object{Hand scale - x } // 右手

// 大腿
#declare ThighLen = 0.4; // 長さ
#declare Thigh = merge {
object{JointL} // 股関節
object
{
  Sphere scale<0.075, 0.2, 0.075> translate - 0.2 * y
}
}

// 下腿
#declare LegLen = 0.3; // 長さ
#declare Leg = merge {
object{JointM} // 膝関節
object
{
  Sphere scale<0.05, 0.15, 0.05> translate - 0.15 * y
}
}

// 足
#declare Foot = merge {
object{JointM} // 足首関節
intersection
{
  object{Sphere scale<0.05, 0.1, 0.15>} object{Cube scale 1 translate 1 * y} translate<0.0, -0.1, 0.05>
}
}

// 座標軸
#declare Axes = merge {
object
{
  Cylinder_X scale 0.02 pigment { color Red }
} // x軸
object
{
  Cylinder_Y scale 0.02 pigment { color Green }
} // y軸
object
{
  Cylinder_Z scale 0.02 pigment { color Blue }
} // z軸
}

#declare Floor = object {
Disk_Y scale<10.0, 0.1, 10.0> translate - 0.1 * y pigment { color GreenYellow }
}

// 照明
light_source
{
<0, 10,  20> color White*1.5
	parallel point_at <0, 0, 0>
  //	area_light <4, 0, 0>, <0, 2.8, -2.8>, 3, 3
}
