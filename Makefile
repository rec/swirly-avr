PREPROCESS=gcc -E -C -x c -iquote ./src
# -E : Stop after preprocessing.
# -C : Don't discard comments.
# -x c : Treat the file as C code.
# -iquote ./src : Use ./src for the non-system include path.

TARGETS=sketches/morse/morse.h

all: $(TARGETS)

clean:
	rm $(TARGETS)

%.h: %.h.in
	$(PREPROCESS) $< -o $@

