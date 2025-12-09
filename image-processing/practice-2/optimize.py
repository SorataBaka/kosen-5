import numpy as np
import cv2 as cv
import argparse
import os


def binary_threshold(image, threshold):
    h, w = image.shape
    new_image = np.zeros((h, w), image.dtype)

    for y in range(h):
        for x in range(w):
            current_value = image[y][x]

            # Apply thresholding
            if current_value > threshold:
                new_image[y][x] = 255
            else:
                new_image[y][x] = 0
    return new_image


def variance_ratio(image, start=1, stop=255):
    # for every threshold i, split the image into 2 classes
    h, w = image.shape
    best_ratio = 0
    best_t = 0
    for i in range(start, stop):
        class0 = []
        class1 = []
        global_list = []
        for y in range(h):
            for x in range(w):
                global_list.append(image[y][x])
                if image[y][x] <= i:
                    class0.append(image[y][x])
                if image[y][x] > i:
                    class1.append(image[y][x])
        if len(class0) == 0 or len(class1) == 0:
            continue
        class0_mean = np.mean(class0)
        class1_mean = np.mean(class1)
        global_mean = np.mean(global_list)

        prob0 = len(class0) / len(global_list)
        prob1 = len(class1) / len(global_list)

        var_between = (
            prob0 * (class0_mean - global_mean) ** 2
            + prob1 * (class1_mean - global_mean) ** 2
        )

        if var_between > best_ratio:
            best_ratio = var_between
            best_t = i

    return best_ratio, best_t


def kmeans_threshold(image, center0=0.0, center1=255.0, epsilon=0.5, max_iter=100):
    h, w = image.shape
    for _ in range(max_iter):
        cluster0 = []
        cluster1 = []
        for y in range(h):
            for x in range(w):
                pixel_value = image[y][x]
                classification = np.abs(pixel_value - center0) < np.abs(
                    pixel_value - center1
                )
                if classification:
                    cluster0.append(pixel_value)
                else:
                    cluster1.append(pixel_value)
        if len(cluster0) == 0 or len(cluster1) == 0:
            continue
        new_center0 = np.mean(cluster0)
        new_center1 = np.mean(cluster1)
        if (
            abs(new_center0 - center0) < epsilon
            and abs(new_center1 - center1) < epsilon
        ):
            center0 = new_center0
            center1 = new_center1
            break
        center0 = new_center0
        center1 = new_center1

    threshold = (center0 + center1) / 2
    return threshold, center0, center1


parser = argparse.ArgumentParser(description="Threshold generators.")
parser.add_argument("image_path", help="Path to the input image.")
parser.add_argument(
    "--algorithm",
    help="Select threshold optimizing algorithm to use.",
    choices=["dispersion", "kmeans"],
    required=True,
)
args = parser.parse_args()

img = cv.imread(args.image_path, cv.IMREAD_GRAYSCALE)

new_image = None
if args.algorithm == "dispersion":
    print("Running Dispersion Ratio")
    best_ratio, best_t = variance_ratio(img)
    print(f"Obtained T={best_t}")
    new_image = binary_threshold(img, best_t)
elif args.algorithm == "kmeans":
    print("Running KMeans")
    threshold, center1, center2 = kmeans_threshold(img)
    print(f"Obtained v1={center1} v2={center2}")
    new_image = binary_threshold(img, threshold)

if new_image is None:
    raise ValueError("new_image is NoneType")

filename = os.path.basename(args.image_path)
cv.imwrite(f"out_{args.algorithm}_{filename.lower()}", new_image)
cv.imshow("Output: ", new_image)
cv.waitKey()
cv.destroyAllWindows()
