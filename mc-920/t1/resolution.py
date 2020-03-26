from image import Image
import numpy

class Resolution(Image):

    def resolution_cut_half(self, step):
        img = self.get()

        for i in range(1, step):
            img[i::step] = img[::step]

        img = img.T

        for i in range(1, step):
            img[i::step] = img[::step]

        self.set(img.T)

if __name__ == "__main__":
    import sys
    r = Resolution(sys.argv[1])
    (w, h) = r.get().shape
    i = w // 2
    while i >= 8:
        res = w // i
        r.resolution_cut_half(res)
        r.save_to_file("output-{}.png".format(i))
        i = i // 2