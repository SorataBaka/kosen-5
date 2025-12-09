import argparse
import cv2 as cv
import numpy as np
import os

parser = argparse.ArgumentParser(description="Threshold generators.")
parser.add_argument("image_path", help="Path to the input image.")
parser.add_argument(
    "--min_output", type=int, default=0, help="Minimum output pixel value."
)
parser.add_argument(
    "--max_output", type=int, default=255, help="Maximum output pixel value."
)
parser.add_argument(
    "--out", help="Specifies if output should be created", action="store_true"
)
args = parser.parse_args()

min_output = args.min_output
max_output = args.max_output
img = cv.imread(args.image_path, cv.IMREAD_GRAYSCALE)

img = img.astype(float)
original_img = img.copy()

height, width = img.shape
min_pixel = img.min()
max_pixel = img.max()

print(f"Min Output: {min_output}, Max Output: {max_output}")
print(f"Min Pixel Value: {min_pixel}, Max Pixel Value: {max_pixel}")
print(f"Image Width: {width}, Image Height: {height}")

img = (
    (img - min_pixel) * (max_output - min_output) / (max_pixel - min_pixel)
) + min_output

# stitch img and original_img horizontally

stacked = np.hstack((original_img.astype(np.uint8), img.astype(np.uint8)))

cv.imshow("Original Image", stacked)
cv.waitKey()
cv.destroyAllWindows()

if args.out:
    out_path = f"modified_{os.path.basename(args.image_path)}"
    cv.imwrite(out_path, img.astype(np.uint8))
    print(f"Output image saved to {out_path}")
