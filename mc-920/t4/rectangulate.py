from image import Image
import numpy
from connected import ComponentLimiter

class FilterBaseLimits(Image):
    def filter_apply(self, limits, filter_function):
        img = self.get()

        new_limits = []
        for l in limits:
            tl, tr, bl, br = l

            s = img[tl[0]:bl[0],tl[1]:tr[1]]
            w, h = s.shape
            size = w * h
            black_pixels = numpy.count_nonzero(s == 0)

            if w * h > 0:
                q0 = black_pixels / size

            if filter_function(q0, 0, size):
                new_limits.append(l)

        return new_limits


class FilterTextLimits(FilterBaseLimits):
    def filter_text(self, limits):
        return self.filter_apply(limits, self.is_text)

    def is_text(self, black_pixel_ratio, _, __):
        return black_pixel_ratio > 0.19 and black_pixel_ratio < 0.4

class FilterWordsLimits(Image):
    def filter_words(self, limits):
        return self.filter_apply(limits, self.is_word)

    def is_word(self, black_pixel_ratio, _, size):
        return black_pixel_ratio > 0.05 and black_pixel_ratio < 0.7 and size < 10000


class MarkRectangles(Image):
    def mark(self, limits):
        img = self.get()
        for l in limits:
            tl, tr, bl, br = l

            for i in range(tl[1], tr[1]):
                img[tl[0] - 1, i] = 1
                img[tl[0], i] = 1

            for i in range(tl[0], bl[0]):
                img[i, tl[1] - 1] = 1
                img[i, tl[1]] = 1

            for i in range(bl[1], br[1]):
                img[bl[0] - 1, i] = 1
                img[bl[0], i] = 1

            for i in range(tr[0], br[0]):
                img[i, tr[1] - 1] = 1
                img[i, tr[1]] = 1

        self.set(img)

class MarkLinesRectangles(FilterTextLimits, MarkRectangles):
    def mark_lines(self, limits):
        limits = self.filter_text(limits)
        self.mark(limits)

if __name__ == "__main__":
    import sys
    i = ComponentLimiter(sys.argv[1])
    i.binary_set()
    i.set(i.get() * 255)
    all_l = i.get_limits()

    i = MarkLinesRectangles(sys.argv[2])
    i.mark_lines(all_l)
    i.save_to_file("rectangules.pbm")
