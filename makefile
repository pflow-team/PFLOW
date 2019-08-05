# For debugging
# override CFLAGS += -Iinclude -DPFLOW_DISPLAY_RESULTS -DDEBUGPS
CFLAGS += -Iinclude #-DPFLOW_DISPLAY_RESULTS
FFLAGS           =
CPPFLAGS         =
FPPFLAGS         =

OS := $(shell uname)
ifeq ($(OS),Darwin)
  OTHER_LIB =
  LIB_EXT = dylib
  LDFLAGS = -dynamiclib
else
  OTHER_LIB = -lrt
  LIB_EXT = so
  LDFLAGS = -shared
endif

ALL:

include $(PETSC_DIR)/lib/petsc/conf/variables
include $(PETSC_DIR)/lib/petsc/conf/rules

PFLOW_SRC_OBJECTS = src/ps/ps.o src/utils/comm.o src/pflow/pflow.o

PFLOW_APP1_OBJECTS = applications/pflow-main.o
OBJECTS_PFLOW1 = $(PFLOW_APP1_OBJECTS)
PFLOW: $(OBJECTS_PFLOW1) libpflow chkopts
	 -$(CLINKER) -o PFLOW $(OBJECTS_PFLOW1) $(PETSC_SNES_LIB) -L${PFLOW_DIR}/lib -lpflow
	$(RM) $(OBJECTS_PFLOW1)

PFLOW_APP_OBJECTS = applications/pflow-main3.o
OBJECTS_PFLOW = $(PFLOW_APP_OBJECTS)
PFLOW3: $(OBJECTS_PFLOW) libpflow chkopts
	 -$(CLINKER) -o PFLOW3 $(OBJECTS_PFLOW) $(PETSC_SNES_LIB) -L${PFLOW_DIR}/lib -lpflow
	$(RM) $(OBJECTS_PFLOW)

libpflow:$(PFLOW_SRC_OBJECTS) chkopts
	 -$(CLINKER) $(LDFLAGS) -o libpflow.$(LIB_EXT) $(PFLOW_SRC_OBJECTS) $(PETSC_SNES_LIB)
	${MV} libpflow.${LIB_EXT} lib/

cleanobj:
	rm -f $(OBJECTS_PFLOW) $(OBJECTS_PFLOW3) ${PFLOW_SRC_OBJECTS}
