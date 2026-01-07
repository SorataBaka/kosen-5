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
fshift = np.fft.fftshift(f)
magnitude_spectrum = 20 * np.log(np.abs(fshift))

rows, cols = img.shape
crow, ccol = rows // 2, cols // 2
# Create a high-pass filter mask
fshift[crow - 30 : crow + 30, ccol - 30 : ccol + 30] = 0
f_ishift = np.fft.ifftshift(fshift)
img_back = np.fft.ifft2(f_ishift)
img_back = np.abs(img_back)

if args.out:
    out_path = f"3_high_pass_{os.path.basename(args.image_path)}"
    cv.imwrite(out_path, img_back.astype(np.uint8))
    print(f"Output image saved to {out_path}")
