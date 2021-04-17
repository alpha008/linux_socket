SHARE=--share
CC=gcc
AR=ar -cr
CO=$(AR)
######### 标准Makefile Lv1 ########  
EXTENSION=c
CC=gcc
LIB=libstatic_test.a
SUBDIR=./source
OBJ = obj
DEP = dep
LIBDIR = libstatic
#CXXFLAGS:编译选项, LDFLAGS:链接选项  
CXXFLAGS += -I ./include
#LDFLAGS +=
CXX_SOURCES =$(foreach dir,$(SUBDIR), $(wildcard $(dir)/*$(EXTENSION)))
CXX_OBJECTS=$(patsubst  %.$(EXTENSION), ${OBJ}/%.o, $(notdir $(CXX_SOURCES)))
DEP_FILES  =$(patsubst  %.$(EXTENSION), ${DEP}/%.d, $(notdir $(CXX_SOURCES)))
$(LIB): $(CXX_OBJECTS)
	@mkdir -p $(LIBDIR)
	$(CO) ./libstatic/$@ $^
${OBJ}/%.o: ${SUBDIR}/%.$(EXTENSION)
	@mkdir -p $(OBJ)
	$(CC)  -c $(CXXFLAGS)  $<  -o  $@
${DEP}/%.d: ${SUBDIR}/%.$(EXTENSION)
	@mkdir -p $(DEP)
	$(CC) $(CXXFLAGS) -MM $< | sed -e 1's,^,$(OBJ)/,' > $@
-include ${DEP_FILES}
clean:
	rm  -rf  $(LIB) 
	rm  -rf  $(OBJ)
	rm  -rf  $(DEP)
	rm  -rf  $(LIBDIR)