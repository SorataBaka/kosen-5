import argparse
import cv2 as cv
import numpy as np
import os

parser = argparse.ArgumentParser(description="Threshold generators.")
parser.add_argument("image_path", help="Path to the input image.")
# sobel, prewitt, laplacian, sharpness
parser.add_argument(
    "--filter_type",
    help="Type of filter to apply",
    choices=["sobel", "prewitt", "laplacian", "sharpness"],
    default="sobel",
)
parser.add_argument(
    "--direction",
    help="Direction of the filter",
    choices=["x", "y"],
    default="x",
)
parser.add_argument(
    "--laplacian_type",
    type=int,
    help="Type of laplacian filter (4 or 8)",
    choices=[4, 8],
    default=4,
)
parser.add_argument(
    "--out", help="Specifies if output should be created", action="store_true"
)
args = parser.parse_args()

img = cv.imread(args.image_path, cv.IMREAD_GRAYSCALE).astype(float)
original_img = img.copy()

img_padded = np.pad(img, pad_width=1, mode="constant", constant_values=0)


def sobel_filter(image, direction):
    h, w = image.shape
    if direction != "x" and direction != "y":
        raise ValueError("Direction must be 'x' or 'y'")
    sobel_array = (
        [[-1, 0, 1], [-2, 0, 2], [-1, 0, 1]]
        if direction == "x"
        else [[-1, -2, -1], [0, 0, 0], [1, 2, 1]]
    )

    empty_array = np.zeros((h - 2, w - 2))
    for y in range(1, h - 2):
        for x in range(1, w - 2):
            selected_region = image[y : y + 3, x : x + 3]
            empty_array[y, x] = np.sum(sobel_array * selected_region)
            empty_array[y, x] = np.clip(empty_array[y, x], 0, 255)
    return empty_array


def prewitt_filter(image, direction):
    h, w = image.shape
    if direction != "x" and direction != "y":
        raise ValueError("Direction must be 'x' or 'y'")
    prewitt_array = (
        [[-1, 0, 1], [-1, 0, 1], [-1, 0, 1]]
        if direction == "x"
        else [[-1, -1, -1], [0, 0, 0], [1, 1, 1]]
    )
    empty_array = np.zeros((h - 2, w - 2))
    for y in range(1, h - 2):
        for x in range(1, w - 2):
            selected_region = image[y : y + 3, x : x + 3]
            empty_array[y, x] = np.sum(prewitt_array * selected_region)
            empty_array[y, x] = np.clip(empty_array[y, x], 0, 255)
    return empty_array


def laplacian_filter(image, type):
    if type != 4 and type != 8:
        raise ValueError("Laplacian filter type must be 4 or 8")
    laplacian_array = (
        [[0, 1, 0], [1, -4, 1], [0, 1, 0]]
        if type == 4
        else [[1, 1, 1], [1, -8, 1], [1, 1, 1]]
    )
    h, w = image.shape
    empty_array = np.zeros((h - 2, w - 2))
    for y in range(1, h - 2):
        for x in range(1, w - 2):
            selected_region = image[y : y + 3, x : x + 3]
            empty_array[y, x] = np.sum(laplacian_array * selected_region)
            empty_array[y, x] = np.clip(empty_array[y, x], 0, 255)
    return empty_array


def sharpening(image):
    sharpening_array = [[-1, -1, -1], [-1, 9, -1], [-1, -1, -1]]
    h, w = image.shape
    empty_array = np.zeros((h - 2, w - 2))
    for y in range(1, h - 2):
        for x in range(1, w - 2):
            selected_region = image[y : y + 3, x : x + 3]
            empty_array[y, x] = np.sum(sharpening_array * selected_region)
            empty_array[y, x] = np.clip(empty_array[y, x], 0, 255)
    return empty_array


# first pad the image so that out of bounds pixels can still be calculated
img = np.pad(img, pad_width=1, mode="constant", constant_values=0)
filtered_img = None
if args.filter_type == "sobel":
    filtered_img = sobel_filter(img, args.direction)
elif args.filter_type == "prewitt":
    direction = "x" if args.direction == "horizontal" else "y"
    filtered_img = prewitt_filter(img, args.direction)
elif args.filter_type == "laplacian":
    filtered_img = laplacian_filter(img, args.laplacian_type)
elif args.filter_type == "sharpness":
    filtered_img = sharpening(img)

if filtered_img is None:
    raise ValueError("Filtered image is None. Check filter type and parameters.")

stacked = np.hstack((original_img.astype(np.uint8), filtered_img.astype(np.uint8)))

print("Applying filter:", args.filter_type)
print(
    "With settings - Direction:", args.direction, "Laplacian type:", args.laplacian_type
)

cv.imshow("Results", stacked)
cv.waitKey()
cv.destroyAllWindows()

if args.out:
    out_path = f"{args.filter_type}_filtered_{os.path.basename(args.image_path)}"
    cv.imwrite(out_path, filtered_img.astype(np.uint8))
    print(f"Output image saved to {out_path}")
