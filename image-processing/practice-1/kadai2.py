import cv2 as cv
import numpy as np
import argparse
import sys

def restricted_float(x):
    x = float(x)
    if x < 0.0 or x > 1.0:
        raise argparse.ArgumentTypeError("Threshold must be between 0 and 1.")
    return x

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

def binary_inverted_threshold(image, threshold):
  h, w = image.shape
  new_image = np.zeros((h, w), image.dtype)
  
  for y in range(h):
    for x in range(w):
      current_value = image[y][x]
      
      # Apply thresholding
      if current_value > threshold:
        new_image[y][x] = 0
      else:
        new_image[y][x] = 255
  return new_image

def truncate_threshold(image, threshold):
  h, w = image.shape
  new_image = np.zeros((h, w), image.dtype)
  
  for y in range(h):
    for x in range(w):
      current_value = image[y][x]
      
      # Apply thresholding
      if current_value > threshold:
        new_image[y][x] = threshold
      else:
        new_image[y][x] = current_value
  return new_image

def to_zero_threshold(image, threshold):
  h, w = image.shape
  new_image = np.zeros((h, w), image.dtype)
  
  for y in range(h):
    for x in range(w):
      current_value = image[y][x]
      
      # Apply thresholding
      if current_value > threshold:
        new_image[y][x] = current_value
      else:
        new_image[y][x] = 0
  return new_image

def to_zero_inverted_threshold(image, threshold):
  h, w = image.shape
  new_image = np.zeros((h, w), image.dtype)
  
  for y in range(h):
    for x in range(w):
      current_value = image[y][x]
      
      # Apply thresholding
      if current_value > threshold:
        new_image[y][x] = 0
      else:
        new_image[y][x] = current_value
  return new_image

parser = argparse.ArgumentParser(description="Threshold generators.")
parser.add_argument("image_path", help="Path to the input image.")
parser.add_argument("--algorithm", help="Select thresholding algorithm to use.", choices=["BINARY", "BINARY_INVERTED", "TRUNCATE", "TO_ZERO", "TO_ZERO_INVERTED"], required=True)
parser.add_argument("--threshold", help="The threshold for the algorithm", type=restricted_float ,required=True)
parser.add_argument("--out", help="Specifies if output should be created", action="store_true")
args = parser.parse_args()

img = cv.imread(args.image_path, cv.IMREAD_GRAYSCALE)
algorithm = args.algorithm
threshold = int(round(args.threshold * 255))

print(f"Running THRESHOLD_{args.algorithm} against {args.image_path} with threshold {threshold} ({args.threshold})")

new_image = None
match algorithm:
  case "BINARY":
    new_image = binary_threshold(img, threshold)
  case "BINARY_INVERTED":
    new_image = binary_inverted_threshold(img, threshold)
  case "TRUNCATE":
    new_image = truncate_threshold(img, threshold)
  case "TO_ZERO":
    new_image = to_zero_threshold(img, threshold)
  case "TO_ZERO_INVERTED":
    new_image = to_zero_inverted_threshold(img, threshold)
  case _:
    print("Unknown command.. aborting")
    sys.exit(1)

cv.imshow(f"Output of {algorithm}", new_image)
cv.waitKey()
cv.destroyAllWindows()

cv.imwrite(f"{algorithm.lower()}_{args.image_path}", new_image)

