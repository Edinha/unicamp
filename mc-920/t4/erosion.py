from image import Image
import numpy
from scipy.ndimage.morphology import binary_erosion

class Erosion(Image):

    def erode(self, structure):
        img = self.get()
        result = binary_erosion(img, structure=structure)
        self.set(result)
        self.astype(img.dtype)


if __name__ == "__main__":
    import sys
    i = Erosion(sys.argv[1])
    i.binary_set()
    structure = numpy.ones((int(sys.argv[2]), int(sys.argv[3])))
    i.erode(structure)
    i.binary_normalize()
    print("IMG: ", i.get().max(), i.get())
    i.save_to_file("erosion.pbm")
