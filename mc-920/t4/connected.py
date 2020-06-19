from image import Image
import numpy
from skimage import measure, filters
from scipy import ndimage
import matplotlib.pyplot as plt

class ConnectedComponents(Image):

    def find_connected(self):
        threshold = 50
        blur_radius = 1.0

        img = self.get()
        imgf = ndimage.gaussian_filter(img, blur_radius)
        labeled, nr_objects = ndimage.label(imgf > threshold)

        # print("Number of objects is {}".format(nr_objects))
        # print("MAX ELEMENT {}".format(labeled.max()))
        # print("IMG IS {}".format(labeled))
        # plt.imshow(labeled)
        # plt.show()

        self.set(labeled)

    def display_normalize(self):
        img = self.get()
        img *= 255 // img.max()
        self.set(img)
        self.astype(numpy.uint8)

if __name__ == "__main__":
    import sys
    i = ConnectedComponents(sys.argv[1])
    i.binary_set()
    i.set(i.get() * 255)
    i.find_connected()
    i.display_normalize()

    print("IMG: ", i.get().max(), i.get())
    i.save_to_file("connected.png")
