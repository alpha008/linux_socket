STALIB=../staticlib
DYNAMICLIB=../dynamic
######### 标准Makefile Lv1 ########  
EXTENSION=c
CC=gcc
LIB=libstatic_test.a
SUBDIR=./source
OBJ = obj
DEP = dep
TARGET = app
#CXXFLAGS:编译选项, LDFLAGS:链接选项  
CXXFLAGS +=-I./include \
	-I../staticlib/include\
	-I../dynamic/include
LFLAG=-L../staticlib/libstatic\
	   -L../dynamic/libdynamic
LIBS=-lstatic_test -ldynamic
CFLAGE=-Wall 
#LDFLAGS +=
CXX_SOURCES =$(foreach dir,$(SUBDIR), $(wildcard $(dir)/*$(EXTENSION)))
CXX_OBJECTS=$(patsubst  %.$(EXTENSION), ${OBJ}/%.o, $(notdir $(CXX_SOURCES)))
DEP_FILES  =$(patsubst  %.$(EXTENSION), ${DEP}/%.d, $(notdir $(CXX_SOURCES)))
$(TARGET): $(CXX_OBJECTS)
	make -C $(STALIB)
	make -C $(DYNAMICLIB)
	$(CC) $^  $(CFLAGE) -o $@ $(LFLAG) $(LIBS)
${OBJ}/%.o: ${SUBDIR}/%.$(EXTENSION)
	@mkdir -p $(OBJ)
	$(CC)  -c $(CXXFLAGS)  $<  -o  $@
${DEP}/%.d: ${SUBDIR}/%.$(EXTENSION)
	@mkdir -p $(DEP)
	$(CC) $(CXXFLAGS) -MM $< | sed -e 1's,^,$(OBJ)/,' > $@
-include ${DEP_FILES}
clean:
	rm -rf $(OBJ)
	rm -rf $(DEP)
	rm -rf $(TARGET)
	rm -rf ../dynamic/libdynamic
	rm -rf ../staticlib/libstatic
