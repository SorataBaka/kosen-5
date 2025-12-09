import argparse
import cv2 as cv

parser = argparse.ArgumentParser(description="Threshold generators.")
parser.add_argument("image_path", help="Path to the input image.")
# sobel, prewitt, laplacian, sharpness
parser.add_argument(
    "--filter_type",
    help="Type of filter to apply",
    choices=["sobel", "prewitt", "laplacian"],
    default="sobel",
)
parser.add_argument(
    "--out", help="Specifies if output should be created", action="store_true"
)
args = parser.parse_args()

img = cv.imread(args.image_path, cv.IMREAD_GRAYSCALE).astype(float)
original_img = img.copy()


cv.imshow("Original Image", img)
cv.waitKey()
cv.destroyAllWindows()
