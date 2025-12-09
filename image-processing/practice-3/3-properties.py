import argparse
import cv2 as cv
import numpy as np

parser = argparse.ArgumentParser(description="Threshold generators.")
parser.add_argument("image_path", help="Path to the input image.")
args = parser.parse_args()

img = cv.imread(args.image_path, cv.IMREAD_GRAYSCALE).astype(float)


def average(image):
    return np.average(image)


def variance(image):
    return np.var(image)


def gravity(image):
    height, width = image.shape
    y_indices, x_indices = np.indices((height, width))
    m00 = np.sum(image)
    m10 = np.sum(x_indices * image)
    m01 = np.sum(y_indices * image)
    return (float(m10 / m00), float(m01 / m00))


print(f"mu = {average(img)}")
print(f"mu_2 = {variance(img)}")
print(f"(x_G, y_G) = {gravity(img)}")
