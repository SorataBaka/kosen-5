/* 人形モデル シーンファイル */

#include "parts.inc"

/* 人形モデル
 * 各パーツは階層的に接続される．

         +-- 胴       +-- 胸
         |            |
         |            +-- 頭     +-- 上腕   +-- 手
         |            |          |          |
  全身 --+-- 上半身 --+-- 左腕 --+-- 肘下 --+-- 前腕
         |            |
         |            +-- 右腕 ...
         |            
         |            +-- 腰     +-- 腿     +-- 足
         |            |          |          |
         +-- 下半身 --+-- 左脚 --+-- 膝下 --+-- 脛
                      |
                      +-- 右脚 ...
 
 * 胴の中央が基準点 <0, 0, 0>．
 * 距離の単位はメートル程度，角度の単位は度．
 */
merge {
  object { Waist }

  /* --- Upper Body --- */
  merge {
    object { Chest }

    object {
      Head    
      rotate <10, 0, -20> 
      translate ChestH*y  
    }

    /* CHARACTER'S LEFT ARM: The one reaching high/back */
    merge {
      object { Arm }
      merge {
        object { Forearm }
        object { LeftHand translate -ForearmLen*y rotate <0, -90, 0> }
        rotate <0, 0, 0> 
        translate -ArmLen*y
      }
      rotate <0, 0, 110> // Raised high on the character's left
      translate ChestW*x
    }
    merge {
      object { Arm }
      merge {
        object { Forearm }
        object { RightHand translate -ForearmLen*y rotate <0, 90, 0>}
        rotate <-150, -20, 20> // Sharp elbow bend
        translate -ArmLen*y
      }
      rotate <-40, 20, -90> // Positioned in front of the torso
      translate -ChestW*x
    }

    rotate <0, 0, 20> // Torso tilt
    translate WaistH*y  
  }

  merge {
    object { Hip }
    merge {
      object { Thigh }
      merge {
        object { Leg }
        merge { object { Foot } rotate <20, 0, 0> translate -(LegLen*y) }
        rotate <0, 0, 20> 
        translate -ThighLen*y
      }
      rotate <0, 0, 0> 
      translate HipW*x
    }
    merge {
      object { Thigh }
      merge {
        object { Leg }
        merge { object { Foot } rotate <30, 0, 30> translate -(LegLen*y) }
        rotate <0, 0, 20> 
        translate -ThighLen*y
      }
      rotate <0, 0, 0> 
      translate -HipW*x
    }
    rotate <0, 0, -20> 
    translate -WaistH*y
  }

  /* Final Global Orientation */
  rotate <0, 0, 0> // Turn character slightly toward camera
  translate <0, 1.1, 0> // Lowered height for deep crouch
  pigment { color Gray80 }
}

object { Floor }		// 床
background { color LightBlue }	// 背景

camera {			// カメラ
	RightHandSystem()
	angle 30
	location <2.0, 5.0, 0.0>
	look_at <0.0, 1.0, 0.0>
}
 