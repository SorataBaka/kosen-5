import argparse
import cv2 as cv
import numpy as np

parser = argparse.ArgumentParser(description="Threshold generators.")
parser.add_argument("image_path", help="Path to the input image.")
parser.add_argument(
    "--direction",
    help="Direction of co-occurance",
    choices=["dx", "dy"],
    default="dx",
)
args = parser.parse_args()

img = cv.imread(args.image_path, cv.IMREAD_GRAYSCALE)


def horizontal_occurance(image):
    quantized = (image // 32).astype(np.uint8)
    occurance_matrix = np.zeros((8, 8), dtype=np.int32)
    rows, cols = image.shape

    for y in range(rows):
        for x in range(cols - 1):
            i = quantized[y, x]
            j = quantized[y, x + 1]
            occurance_matrix[i, j] += 1
    occurance_matrix = occurance_matrix + occurance_matrix.T
    return occurance_matrix


def vertical_occurance(image):
    quantized = (image // 32).astype(np.uint8)
    occurance_matrix = np.zeros((8, 8), dtype=np.int32)
    rows, cols = image.shape

    for y in range(rows - 1):
        for x in range(cols):
            i = quantized[y, x]
            j = quantized[y + 1, x]
            occurance_matrix[i, j] += 1
    occurance_matrix = occurance_matrix + occurance_matrix.T
    return occurance_matrix


if args.direction == "dx":
    print("Horizontal Co-occurance Matrix:")
    print(horizontal_occurance(img))
else:
    print("Vertical Co-occurance Matrix:")
    print(vertical_occurance(img))
