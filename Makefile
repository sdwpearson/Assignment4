CXX=g++
CXXFLAGS=-std=c++11 -g -O3 -march=native
CXXTESTFLAGS=-std=c++11 -g 
CXXFLAGS=-std=c++11 -g -O2 -march=native -ftree-vectorize -Wall

LDFLAGS=-g
LDLIBS=
LDBOOST = -lboost_unit_test_framework

all: antsontable-orig antsontable

clean: clean-orig clean-new

distclean: clean clean-more

.PHONY: all clean distclean clean-orig clean-new clean-more run-orig run integratedtest help

antsontable-orig.o: antsontable-orig.cc
	${CXX} ${CXXFLAGS} -c -o $@ $^

antsontable-orig: antsontable-orig.o
	${CXX} ${LDFLAGS} -o $@ $^ ${LDLIBS}

run-orig: antsontable-orig
	./antsontable-orig > run-orig

clean-orig:
	\rm -f antsontable-orig.o


output.o: output.cc output.h
	${CXX} ${CXXFLAGS} -c -o $@ $<

timestep.o: timestep.cc timestep.h
	${CXX} ${CXXFLAGS} -c -o $@ $<

report.o: report.cc report.h
	${CXX} ${CXXFLAGS} -c -o $@ $<

initialization.o: initialization.cc initialization.h
	${CXX} ${CXXFLAGS} -c -o $@ $<

randompartition.o: randompartition.cc randompartition.h
	${CXX} ${CXXFLAGS} -c -o $@ $<

antsontable.o: antsontable.cc initialization.h report.h timestep.h output.h
	${CXX} ${CXXFLAGS} -c -o $@ $<

antsontable: antsontable.o initialization.o randompartition.o report.o timestep.o output.o
	${CXX} ${LDFLAGS} -o $@ $^ ${LDLIBS}

run: antsontable
	./antsontable > run

clean-new:
	\rm -f antsontable.o initialization.o randompartition.o report.o timestep.o output.o

clean-more:
	\rm -f antsontable antsontable-orig run run-orig

integratedtest: run run-orig
	diff run run-orig

initializationtest.o: initialization.o
	${CXX} ${CXXTESTFLAGS} -c initialization_bt.cc

initializationtest: initializationtest.o
	${CXX} ${CXXTESTFLAGS} -o initialization_bt initialization_bt.o initialization.o ${LDBOOST}
	./initialization_bt --log_level=all

randompartitiontest.o: randompartition.o
	${CXX} ${CXXTESTFLAGS} -c randompartition_bt.cc

randompartitiontest: randompartitiontest.o
	${CXX} ${CXXTESTFLAGS} -o randompartition_bt randompartition_bt.o randompartition.o ${LDBOOST}
	./randompartition_bt --log_level=all

help:
	@echo Type:
	@echo " 'make'                		to compile the antsontable and antsontable-orig applications;"
	@echo " 'make run'            		to run antsontable;"
	@echo " 'make run-orig'       		to run antsontable-orig;"
	@echo " 'make integratedtest' 		to compare outputs of antsontable and antsontable-orig."
	@echo " 'make initializationtest' 	to verify that arrays are uniformly initialized properly."
	@echo " 'make randompartitiontest' 	to verify that the rand_partition function partitions the correct total number."
	@echo " 'make clean'          		to remove all object files (triggers a full recompile on next 'make')"
	@echo " 'make distclean'      		to remove all object files, executables and test outputs"






