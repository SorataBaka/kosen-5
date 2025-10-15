import cv2
import numpy as np
import sys

if len(sys.argv) < 2:
  print("Usage: python3 script.py <image_path>")
  sys.exit(1)
  
image_path = sys.argv[1]
print(f"Reading image {image_path}")

img = cv2.imread(image_path, cv2.IMREAD_GRAYSCALE)
hist = np.zeros(256, int)

h, w = img.shape

for y in range(h):
  for x in range(w):
    hist[img[y][x]] += 1
    
histImage = np.zeros((h, w, 3), dtype=np.uint8)
hist = hist.astype(np.float32)
cv2.normalize(hist, hist, alpha=0, beta=h, norm_type=cv2.NORM_MINMAX)

bin_w = int(round(w/256))
for i in range(1, 256):
  cv2.line(histImage, ( bin_w*(i-1), h - int(round(hist[i-1])) ),
            ( bin_w*(i), h - int(round(hist[i]))),
            (255, 255, 255), thickness=2)

cv2.imshow("Original", img)
cv2.imshow("Histogram", histImage)
cv2.waitKey(0)
cv2.destroyAllWindows()

cv2.imwrite(f"histogram_{image_path}", histImage)