CXX = g++
CXXFLAGS = -g -std=c++11 -lgmpxx -lgmp
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
    ContextList.o \
    Frame.o \
    NumericOp.o \
    SimpleOp.o \
    OpSeq.o \
    PoweredOp.o \
    SuperpositionIter.o \
    SingleOpRule.o \
    OpRule.o \
    SelfKet.o \
    FnOp.o \
    BracketOp.o \
    Sigmoids.o \
    FnMap.o \
    main.o \
    ) # Prepends the BUILDDIR to the OBJS

all: directories $(OUTDIR)/main

$(OUTDIR)/main: $(OBJS)
	@echo "LD $@"
	@$(CXX) $(CXXFLAGS) -o $@ $^ $(INCS)

$(BUILDDIR)/%.o: $(SRCDIR)/%.cpp
	@echo "CXX $<"
	@$(CXX) $(CXXFLAGS) -c $< -o $@ $(INCS)


.PHONY: directories clean

directories: $(OUTDIR)/ $(BUILDDIR)/

%/:
	@echo "MKDIR $<"
	@mkdir -p $@

clean:
	@echo "RMDIR ${BUILDDIR} ${OUTDIR}"
	@rm $(BUILDDIR)/* $(OUTDIR)/* 2> /dev/null

