from image import Image
import numpy
from connected import ConnectedComponents

class ComponentLimiter(ConnectedComponents):

    def get_limits(self):
        labeled = self.find_connected()

        all_limits = []
        for i in range(0, labeled.max()):
            rows, cols = numpy.where(labeled == i)
            rows = numpy.sort(rows)
            cols = numpy.sort(cols)

            if not (len(rows) == 0 or len(cols) == 0):
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

class FilterTextLimits(Image):
    def filter_text(self, limits):
        img = self.get()

        new_limits = []
        for l in limits:
            tl, tr, bl, br = l

            s = img[tl[0]:bl[0],tl[1]:tr[1]]
            w, h = s.shape
            black_pixels = numpy.count_nonzero(s == 0)

            if w * h > 0:
                q0 = black_pixels / (w * h)

            if self.is_text(q0, 0):
                new_limits.append(l)

        return new_limits

    def is_text(self, black_pixel_ratio, _):
        return black_pixel_ratio > 0.19 and black_pixel_ratio < 0.4

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
