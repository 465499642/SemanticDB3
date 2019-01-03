CXX = g++
CXXFLAGS = -g -std=c++11
INCS = -Iinclude/
BUILDDIR = build
OUTDIR = bin
SRCDIR = src
OBJS = $(addprefix ${BUILDDIR}/, \
    KetMap.o \
    Ket.o \
    Superposition.o \
    Functions.o \
    Sequence.o \
    NewContext.o \
    main.o \
    ) # Prepends the BUILDDIR to the OBJS

all: directories $(OUTDIR)/main

$(OUTDIR)/main: $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(INCS)

$(BUILDDIR)/%.o: $(SRCDIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@ $(INCS)


.PHONY: directories clean

directories: $(OUTDIR)/ $(BUILDDIR)/

%/:
	mkdir -p $@

clean:
	rm $(BUILDDIR)/* $(OUTDIR)/*

