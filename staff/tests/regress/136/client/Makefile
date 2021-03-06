include ../../../../Makefile.env

INTERFACES := Test136.h Test136Types.h
TARGET = staff_test_regress_$(notdir $(patsubst %/,%,$(dir $(CURDIR))))

CXXFLAGS += -c -I$(DEPLOYDIR)$(INCDIR)
LDFLAGS += -lstaffutils -lstaffcommon -lstaffclient -L$(DEPLOYDIR)$(LIBDIR)

CODEGEN_INTERFACES := $(patsubst %.h,$(SRCDIR)%.h,$(INTERFACES))
CODEGEN_HEADERS := $(patsubst %.h,%Proxy.h,$(CODEGEN_INTERFACES))
CODEGEN_SOURCES := $(patsubst %.h,%Proxy.cpp,$(CODEGEN_INTERFACES))
CODEGEN_FILES := $(CODEGEN_HEADERS) $(CODEGEN_SOURCES)

NON_CODEGEN_SOURCES := $(filter-out $(CODEGEN_SOURCES),$(wildcard $(SRCDIR)*.cpp))
SOURCES := $(CODEGEN_SOURCES) $(NON_CODEGEN_SOURCES)
OBJECTS := $(patsubst $(SRCDIR)%.cpp,$(OBJDIR)%.o,$(SOURCES))

.NOTPARALLEL: $(CODEGEN_FILES)

# == make ===========================================
make:;

make_test: checkdeploy "$(OBJDIR)" "$(OUTDIR)" $(OUTDIR)$(TARGET)

# link
$(OUTDIR)$(TARGET): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $(OUTDIR)$(TARGET) $(LDFLAGS)

# compile
$(OBJDIR)%.o: $(SRCDIR)%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(NON_CODEGEN_SOURCES): $(CODEGEN_SOURCES)

$(SRCDIR)%Proxy.h $(SRCDIR)%Proxy.cpp:: $(SRCDIR)%.h
	$(STAFF_HOME)/bin/staff_codegen -e -tclient -c$(SRCDIR) $(INTERFACES)

# == clean ==========================================
clean:
	rm -f $(OUTDIR)$(TARGET) $(OBJECTS) $(CODEGEN_FILES)
	test ! -d $(OBJDIR) || rmdir -p $(OBJDIR)
	test ! -d $(OUTDIR) || rmdir -p $(OUTDIR)

# == mkdir ==========================================
"%/":
	@[ -z "$@" -o -d "$@" ] || mkdir -p $@ && chmod g+w $@

# == test ===========================================
test: make_test

checkdeploy:
	@test -d $(DEPLOYDIR) || (echo "Please compile staff first."; false)
