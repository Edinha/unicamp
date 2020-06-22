from image import Image
import numpy
from closing import Closing
from rectangulate import FilterTextLimits, MarkRectangles, ComponentLimiter

class WordLimiter(Closing, ComponentLimiter):
    def separate_lines_to_words(self, limits):
        img = self.get()

        for l in limits:
            tl, tr, bl, br = l
            text_line = img[tl[0]:bl[0],tl[1]:tr[1]]

            self.set(text_line)
            self.binary_set()
            self.close(numpy.ones((1, 15)))

            self.set(self.get() * 255)
            line_word_limits = self.get_limits()

            self.set(text_line)
            self.mark(line_word_limits)

            img[tl[0]:bl[0],tl[1]:tr[1]] = self.get()

        self.set(img)

class MarkWordsRectangules(WordLimiter, FilterTextLimits, MarkRectangles):

    def mark_words(self, limits):
        text_limits = self.filter_text(limits)
        self.separate_lines_to_words(text_limits)

if __name__ == "__main__":
    import sys
    i = ComponentLimiter(sys.argv[1])
    i.binary_set()
    i.set(i.get() * 255)
    all_l = i.get_limits()

    i = MarkWordsRectangules(sys.argv[2])
    i.mark_words(all_l)
    i.save_to_file("words.pbm")
