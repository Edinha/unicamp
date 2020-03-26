from image import Image
import numpy

class Resolution(Image):

    def resolution_cut_half(self):
        img = self.get()
        img = img[::2]
        img = img.T[::2].T

        self.set(img)

if __name__ == "__main__":
    import sys
    r = Resolution(sys.argv[1])
    (w, h) = r.get().shape
    i = w // 2
    while i >= 8:
        r.resolution_cut_half()
        r.save_to_file("output-{}.png".format(i))
        i = i // 2