from image import Image
import numpy
from scipy import ndimage
import matplotlib.pyplot as plt

class ConnectedComponents(Image):

    def find_connected(self):
        threshold = 30
        blur_radius = 0.5

        img = self.get()
        imgf = ndimage.gaussian_filter(img, blur_radius)
        labeled, nr_objects = ndimage.label(imgf > threshold)

        # print("Number of objects is {}".format(nr_objects))
        # print("MAX ELEMENT {}".format(labeled.max()))
        # print("IMG IS {}".format(labeled))
        # plt.imshow(labeled)
        # plt.show()

        rows, cols = numpy.where(labeled == 48)
        # print("ITEM INDEX IS {} {}".format(rows, cols))
        # print("ITEM INDEX TES IS {}".format(labeled[rows[0], cols[0]]))
        # print("ITEM INDEX TES IS {} {}".format(rows, cols))

        return labeled

    def display_normalize(self):
        img = self.get()
        img *= 255 // img.max()
        self.set(img)
        self.astype(numpy.uint8)


class ComponentLimiter(ConnectedComponents):

    def get_limits(self):
        labeled = self.find_connected()
        all_limits = []

        if len(labeled) == 0:
            return all_limits

        for i in range(0, labeled.max()):
            rows, cols = numpy.where(labeled == i)
            rows = numpy.sort(rows)
            cols = numpy.sort(cols)

            limits = self.get_limit_tuples(rows, cols)
            all_limits.append(limits)

        return all_limits

    def get_limit_tuples(self, rows, cols):
        rl = len(rows) - 1
        cl = len(cols) - 1
        return (
            (rows[0],  cols[0]),
            (rows[0],  cols[cl]),
            (rows[rl], cols[0]),
            (rows[rl], cols[cl]),
        )

if __name__ == "__main__":
    import sys
    i = ConnectedComponents(sys.argv[1])
    i.binary_set()
    i.set(i.get() * 255)
    img = i.find_connected()
    i.set(img)
    i.display_normalize()

    print("IMG: ", i.get().max(), i.get())
    i.save_to_file("connected.png")
