from image import Image
import numpy
from scipy.ndimage.morphology import binary_erosion

class Erosion(Image):

    def erode(self, kernel):
        img = self.get()
        result = binary_erosion(img)
        self.set(result)
        self.astype(img.dtype)

    def normalize(self):
        img = self.get()
        img = (img + 1) % 2
        img *= 255
        self.set(img)

if __name__ == "__main__":
    import sys
    i = Erosion(sys.argv[1])
    i.binary_set()
    i.erode([])
    i.normalize()
    print("IMG: ", i.get().max(), i.get())
    i.save_to_file("output.pbm")
