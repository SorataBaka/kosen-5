import argparse
import cv2 as cv
import numpy as np
import os

parser = argparse.ArgumentParser(description="Threshold generators.")
parser.add_argument("image_path", help="Path to the input image.")
parser.add_argument(
    "--out", help="Specifies if output should be created", action="store_true"
)
args = parser.parse_args()
img = cv.imread(args.image_path, cv.IMREAD_GRAYSCALE).astype(float)
original_img = img.copy()

f = np.fft.fft2(img)
spec = 20 * np.log(np.abs(f))

if args.out:
    out_path = f"2_fft_no_shift_{os.path.basename(args.image_path)}"
    cv.imwrite(out_path, spec.astype(np.uint8))
    print(f"Output image saved to {out_path}")
