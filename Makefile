HPVMC=0
SRC_DIR = src/
BUILD_DIR = obj_hpvm/$(TARGET)$(VERSION)
BUILD_DIR_PARENT = obj_hpvm
#DEBUG = 1

INCLUDES +=
LFLAGS += -lm -lrt

HPVM_SRC=main.c
ALL_SRCS:= $(foreach f, $(wildcard src/*.c), $(shell basename $(f)))
OTHER_SRCS:= $(filter-out $(HPVM_SRC),$(ALL_SRCS))

$(info $$OTHER_SRCS is [${OTHER_SRCS}])


APP_CFLAGS += $(INCLUDES) -ffast-math -O1 -fno-lax-vector-conversions -fno-vectorize -fno-slp-vectorize -finline -finline-functions -DHPVM
APP_CXXFLAGS += $(INCLUDES) -ffast-math -O1 -fno-lax-vector-conversions -fno-vectorize -fno-slp-vectorize -finline -finline-functions -DHPVM
APP_LDFLAGS= $(LFLAGS)

# These paths should be set to your local directories of CUDA and OpenCL
CUDA_PATH=/software/cuda-9.1
CUDA_LIB_PATH=$(CUDA_PATH)/lib64
OPENCL_PATH=$(CUDA_PATH)
OPENCL_LIB_PATH=$(OPENCL_PATH)/lib64

# These paths should be set to your HPVM build directory
LLVM_BUILD_DIR=$(HPVM_BUILD_DIR)

INCDIR += -I./include -I./soc_utils -I$(SCHED_LIB_DIR)/include -I$(TASK_LIB_DIR)/include -I/usr/include/python3.6m
CC = $(LLVM_BUILD_DIR)/bin/clang

CXX = $(LLVM_BUILD_DIR)/bin/clang++

LINKER = $(LLVM_BUILD_DIR)/bin/clang++
PLATFORM_LDFLAGS = -lm -lpthread -lrt -lOpenCL -L$(OPENCL_LIB_PATH)

LLVM_LIB_PATH = $(LLVM_BUILD_DIR)/lib
LLVM_BIN_PATH = $(LLVM_BUILD_DIR)/bin

OPT = $(LLVM_BIN_PATH)/opt
LLVM_LINK = $(LLVM_BIN_PATH)/llvm-link
LLVM_AS = $(LLVM_BIN_PATH)/llvm-as
LLVM_DIS = $(LLVM_BIN_PATH)/llvm-dis
LIT = $(LLVM_BIN_PATH)/llvm-lit
OCLBE = $(LLVM_BIN_PATH)/llvm-ocl

HPVM_RT_PATH = $(LLVM_BUILD_DIR)/tools/hpvm/projects/hpvm-rt
HPVM_RT_LIB = $(HPVM_RT_PATH)/hpvm-rt.bc

HPVM-CC=$(LLVM_BIN_PATH)/hpvm-cc
HCC=$(LLVM_BIN_PATH)/hcc

HCC-OPTS := -dot-dfg
HPVM-CGEN-PATH=$(LLVM_BUILD_DIR)/tools/hpvm/projects/hetero-c++/
HPVM-CGEN-DECLS-FILE=./soc_utils/HPVMCFunctionDeclarations.ll
HCC-OPTS := $(HCC-OPTS) -declsfile $(HPVM-CGEN-DECLS-FILE) -sanitise-funcs

TARGET ?= seq

GENHPVM_OPTFLAGS = -load HPVMGenHPVM.so -genhpvm -globaldce -hpvm-timers-gen
ifeq ($(TARGET),seq)
  DEVICE = CPU_TARGET
  DDEF = CPU
  HPVM_OPTSO = -load HPVMBuildDFG.so -load HPVMDFG2LLVM_CPU.so -load HPVMClearDFG.so -load HPVMDFGTransformPasses.so
  HPVM_OPTFLAGS = -sequentializeflatten -dfg2llvm-cpu -clearDFG -hpvm-timers-cpu
else ifeq ($(TARGET),fpga)
  BOARD ?= a10gx
  ifeq ($(BOARD),a10gx)
    VERSION := $(VERSION)_A10
  else
    ifeq ($(BOARD),s10_gh2e2_4Gx2)
      VERSION := $(VERSION)_DE10
    endif
  endif
  DEVICE = FPGA_TARGET
  DDEF = FPGA
else ifeq ($(TARGET),gpu)
  DEVICE = GPU_TARGET
  DDEF = GPU
  HPVM_OPTSO = -load HPVMBuildDFG.so -load HPVMLocalMem.so -load HPVMDFG2LLVM_GPU_OCL.so -load HPVMDFG2LLVM_CPU.so -load HPVMClearDFG.so
  HPVM_OPTFLAGS =  -localmem -dfg2llvm-gpu-ocl -dfg2llvm-cpu -clearDFG -hpvm-timers-cpu -hpvm-timers-ptx
endif

$(info $$DDEF is [${DDEF}])
$(info $$DEVICE is [${DEVICE}])
$(info $$TARGET is [${TARGET}])

PLATFORM_CFLAGS = -I$(OPENCL_PATH)/include/CL/ $(INCDIR) -DDEVICE=$(DEVICE) -D$(DDEF)
PLATFORM_CXXFLAGS = -I$(OPENCL_PATH)/include/CL/ $(INCDIR) -DDEVICE=$(DEVICE) -D$(DDEF) 
$(info $$PLATFORM_CXXFLAGS is [${PLATFORM_CXXFLAGS}])

ifeq ($(BASELINE),1)
	FPGA_OPTFLAGS += --baseline
	VERSION := $(VERSION)_BASELINE
endif

ifeq ($(NORESTRICT),1)
	FPGA_OPTFLAGS += --remove-restrict
	VERSION := $(VERSION)_NORESTRICT
endif

ifneq (,$(FPGAOPTS))
	HPVM_OPTSO += -load LLVMHPVMFPGATransformPasses.so
endif

ifneq (,$(findstring LU, $(FPGAOPTS)))
  VERSION := $(VERSION)_LU
	FPGA_OPTFLAGS += --unroll --uf=$(UF)
endif

ifneq (,$(findstring OU, $(FPGAOPTS)))
  VERSION := $(VERSION)_OU_$(UF)
	FPGA_OPTFLAGS += --outermostunroll --uf=$(UF)
endif

ifneq (,$(findstring BI, $(FPGAOPTS)))
  VERSION := $(VERSION)_BI
	FPGA_OPTFLAGS += --bufferin
endif

ifneq (,$(findstring PRIV, $(FPGAOPTS)))
  VERSION := $(VERSION)_P
	FPGA_OPTFLAGS += --argpriv
endif

ifneq (,$(findstring LF, $(FPGAOPTS)))
  VERSION := $(VERSION)_LF
	FPGA_OPTFLAGS += --fuse
endif

ifneq (,$(findstring NTLP, $(FPGAOPTS)))
  VERSION := $(VERSION)_NTLP
	FPGA_OPTFLAGS += --no-tlp
endif
ifneq (,$(findstring NF, $(FPGAOPTS)))
  VERSION := $(VERSION)_NF
	FPGA_OPTFLAGS += --nodefuse
endif

ifeq ($(VERSION),)
    VERSION := _Default
endif

ifneq ($(GRAPHOPTS),)
	VERSION := $(VERSION)_GOPT
	HPVM_OPTSO += -load HPVMDFGTransformPasses.so
endif

ifeq ($(POWER),1)
  DEVICE += -DREPORT_POWER
  ifeq ($(TARGET),gpu)
    DEVICE += -I/software/cuda-9.1/include
    PLATFORM_LDFLAGS += -lnvidia-ml
  endif
endif

ifdef EXTRACT
	HCC-OPTS := $(HCC-OPTS) -extract-only
endif

ifdef CONTROL
	HCC-OPTS := $(HCC-OPTS) -control-only
endif

ifeq ($(DEBUG),1)
	FPGA_OPTFLAGS += -debug --dbg
	GENHPVM_OPTFLAGS += -debug
	OCLBE_FLAGS += -debug
	HCC-OPTS := $(HCC-OPTS) --debug-only=HPVMCGen
endif

CURRENT_DIR := $(dir $(abspath $(lastword $(MAKEFILE_LIST))))

CFLAGS = $(APP_CFLAGS) $(PLATFORM_CFLAGS)
CXXFLAGS = $(APP_CXXFLAGS) $(PLATFORM_CXXFLAGS)
LDFLAGS= $(APP_LDFLAGS) $(PLATFORM_LDFLAGS)

COMP = $(CXX)
OMP_FLAGS = $(CFLAGS)

# Add BUILDDIR as a prefix to each element of $1
INBUILDDIR=$(addprefix $(BUILD_DIR)/,$(1))
INSRCDIR=$(addprefix $(SRC_DIR)/,$(1))

.PRECIOUS: $(BUILD_DIR)/%.ll $(BUILD_DIR)/%.bc

SRCDIR_LLVM=$(addsuffix .ll, $(foreach f, $(ALL_SRCS), $(BUILD_DIR)/$(basename $(f))))
$(info $$SRCDIR_LLVM is [${SRCDIR_LLVM}])

HPVM_OBJS=$(basename hpvm).ll

PRE_HCC = $(call INBUILDDIR,$(basename hpvm)-task.bc)
POST_HCC = $(call INBUILDDIR,$(basename hpvm).hpvm.bc)

OBJS = $(call INBUILDDIR,$(SRCDIR_OBJS))
HOST = $(call INBUILDDIR,$(basename $(HPVM_OBJS)).hpvm.host.ll)
KERNEL = $(call INBUILDDIR,$(basename $(HPVM_OBJS)).hpvm.kernels.ll)

ifeq ($(TARGET),gpu)
KERNEL_OCL = $(basename $(KERNEL)).cl
else ifeq ($(TARGET),fpga)
  KERNEL_OCL = $(basename $(KERNEL)).cl
  AOCX = $(basename $(KERNEL)).aocx
  ifeq ($(PROFILE),1)
    AOC_PROFILE = -profile
  endif
  ifeq ($(EMULATION),1)
	FPGA_OPTFLAGS += -emu
  else ifeq ($(RTL),1)
    undefine EXE
    undefine HOST_LINKED
    AOCX = $(basename $(KERNEL)).aocr
    FPGA_OPTFLAGS += -rtl
	VERSION := $(VERSION)_RTL
  endif
endif

EXE = ERAhpvm_$(TARGET)
HOST_LINKED = $(BUILD_DIR)/$(EXE).linked.ll
LLVM_LINKED_HCC_INPUT = $(BUILD_DIR)/hpvm_task.ll

# Targets
default: $(BUILD_DIR) $(EXE) $(KERNEL_OCL)
host: $(BUILD_DIR) $(EXE)
kernel: $(BUILD_DIR) $(KERNEL_OCL)
ll: $(BUILD_DIR) $(BUILD_DIR)/main.ll

ifeq ($(TARGET),gpu)
$(KERNEL_OCL): $(KERNEL)
	$(OCLBE) $(OCLBE_FLAGS) $< -o $@
endif

$(AOCX): FPGA_OPTFLAGS += -run-aoc
default: FPGA_OPTFLAGS += -run-aoc
clean :
	if [ -f $(EXE) ]; then rm $(EXE); fi
	if [ -f DataflowGraph.dot ]; then rm DataflowGraph.dot*; fi
	if [ -d $(BUILD_DIR_PARENT) ]; then rm -rf $(BUILD_DIR_PARENT); fi
	$(RM) *.dot
	$(RM) *.xml

$(EXE) : $(HOST_LINKED)
	$(info Building ${EXE} from ${HOST_LINKED})
	$(COMP) -O1 $(LDFLAGS) $< -o $@ -L/usr/lib/python3.6/config-3.6m-x86_64-linux-gnu -L/usr/lib -lpython3.6m -lpthread -ldl  -lutil -lm  -Xlinker -export-dynamic -Wl,-O1 -Wl,-Bsymbolic-functions

$(HOST_LINKED) : $(HOST) $(OBJS) $(HPVM_RT_LIB)
	$(LLVM_LINK) $^ -S -o $@

ifneq ($(HPVMC),1)
$(POST_HCC): $(LLVM_LINKED_HCC_INPUT)
	$(HCC) $(HCC-OPTS) -o $@ $<
else
$(POST_HCC): $(call INSRCDIR,$(HPVM_SRC))
	$(COMP) $(COMP_FLAGS) -emit-llvm -c -o $@ $<
endif

ifeq ($(TARGET), fpga)
$(HOST) $(KERNEL) $(KERNEL_OCL) $(AOCX): $(POST_HCC)
	$(OPT) -S -inline $< -o $(BUILD_DIR)/main.hpvm.ll
	$(LLVM_BUILD_DIR)/bin/hpvm2fpga -hm=$(HOST) -km=$(KERNEL) -clm=$(KERNEL_OCL) -cxm=$(AOCX) $(FPGA_OPTFLAGS) $(BUILD_DIR)/main.hpvm.ll
else
$(HOST) $(KERNEL): $(POST_HCC)
	$(OPT) -enable-new-pm=0 -inline $(GENHPVM_OPTFLAGS) $(HPVM_OPTSO) $(GRAPHOPTS) $(HPVM_OPTFLAGS) -S $< -o $(HOST)
endif

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(BUILD_DIR)/%.ll : $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -emit-llvm -S -o $@ $<

$(BUILD_DIR)/%.ll : $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -emit-llvm -S -o $@ $<

$(LLVM_LINKED_HCC_INPUT) : $(SRCDIR_LLVM)
	$(LLVM_LINK) $^ -S -o $@
