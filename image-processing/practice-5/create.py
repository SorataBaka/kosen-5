import cv2
import numpy as np

# 1. Create a 21x21 BGR image (3 channels)
size = 21
img = np.zeros((size, size, 3), dtype=np.uint8)

# 2. Fill with a checkerboard
for y in range(size):
    for x in range(size):
        if (x + y) % 2 == 0:
            img[y, x] = [255, 255, 255] # White
        else:
            img[y, x] = [0, 0, 0]       # Black

# 3. Highlight the "Edge Case" (Last row and column) in Red
# This helps you see if your padding/slicing logic processes these pixels
img[-1, :, :] = [0, 0, 255] # Red bottom row
img[:, -1, :] = [0, 0, 255] # Red right column

# 4. Save original
cv2.imwrite("test_edge_case.png", img)

# 5. Upscale for your report (so the teacher can see the red lines)
upscaled = cv2.resize(img, (420, 420), interpolation=cv2.INTER_NEAREST)
cv2.imwrite("test_edge_case_view.png", upscaled)