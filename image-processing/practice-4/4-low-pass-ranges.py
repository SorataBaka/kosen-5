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

rows, cols = img.shape
crow, ccol = rows // 2, cols // 2

images = []
spectrums = []
F = np.fft.fftshift(np.fft.fft2(img))  # original spectrum

for i in range(10, 60, 10):
    mask = np.zeros((rows, cols), np.uint8)
    mask[crow - i : crow + i, ccol - i : ccol + i] = 1

    fshift = F * mask
    magnitude_spectrum = 20 * np.log(np.abs(fshift) + 1)
    img_back = np.fft.ifft2(np.fft.ifftshift(fshift))
    img_back = np.abs(img_back)

    spectrums.append(magnitude_spectrum)
    images.append(img_back)

# normalize each image to uint8
out_imgs = []

for im in images:
    im = im / im.max() * 255
    out_imgs.append(im.astype(np.uint8))

out_spectrums = []
for spec in spectrums:
    spec = spec / spec.max() * 255
    out_spectrums.append(spec.astype(np.uint8))


# concatenate horizontally
final_imgs = np.hstack(out_imgs)
final_spectrums = np.hstack(out_spectrums)
final = np.vstack([final_imgs, final_spectrums])

if args.out:
    out_path = f"4_low_pass_range_{os.path.basename(args.image_path)}"
    cv.imwrite(out_path, final)
    print(f"Output image saved to {out_path}")
