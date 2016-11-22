#
#  There exist several targets which are by default empty and which can be 
#  used for execution of your targets. These targets are usually executed 
#  before and after some main targets. They are: 
#
#     .build-pre:              called before 'build' target
#     .build-post:             called after 'build' target
#     .clean-pre:              called before 'clean' target
#     .clean-post:             called after 'clean' target
#     .clobber-pre:            called before 'clobber' target
#     .clobber-post:           called after 'clobber' target
#     .all-pre:                called before 'all' target
#     .all-post:               called after 'all' target
#     .help-pre:               called before 'help' target
#     .help-post:              called after 'help' target
#
#  Targets beginning with '.' are not intended to be called on their own.
#
#  Main targets can be executed directly, and they are:
#  
#     build                    build a specific configuration
#     clean                    remove built files from a configuration
#     clobber                  remove all built files
#     all                      build all configurations
#     help                     print help mesage
#  
#  Targets .build-impl, .clean-impl, .clobber-impl, .all-impl, and
#  .help-impl are implemented in nbproject/makefile-impl.mk.
#
#  Available make variables:
#
#     CND_BASEDIR                base directory for relative paths
#     CND_DISTDIR                default top distribution directory (build artifacts)
#     CND_BUILDDIR               default top build directory (object files, ...)
#     CONF                       name of current configuration
#     CND_PLATFORM_${CONF}       platform name (current configuration)
#     CND_ARTIFACT_DIR_${CONF}   directory of build artifact (current configuration)
#     CND_ARTIFACT_NAME_${CONF}  name of build artifact (current configuration)
#     CND_ARTIFACT_PATH_${CONF}  path to build artifact (current configuration)
#     CND_PACKAGE_DIR_${CONF}    directory of package (current configuration)
#     CND_PACKAGE_NAME_${CONF}   name of package (current configuration)
#     CND_PACKAGE_PATH_${CONF}   path to package (current configuration)
#
# NOCDDL


# Environment 
MKDIR=mkdir
CP=cp
CCADMIN=CCadmin


# build
build: .build-post

.build-pre:
# Add your pre 'build' code here...

.build-post: .build-impl
# Add your post 'build' code here...


# clean
clean: .clean-post

.clean-pre:
# Add your pre 'clean' code here...

.clean-post: .clean-impl
# Add your post 'clean' code here...


# clobber
clobber: .clobber-post

.clobber-pre:
# Add your pre 'clobber' code here...

.clobber-post: .clobber-impl
# Add your post 'clobber' code here...


# all
all: main.o LinkedList.o Hashtable.o Hamming.o CosineSim.o Euclidean.o DistanceMatrix.o randomfunc.o NeighbourSearch.o DataPoints.o Cluster.o K_medoids.o Park_Jun.o
	g++ -g main.o LinkedList.o Hashtable.o Hamming.o CosineSim.o Euclidean.o DistanceMatrix.o randomfunc.o NeighbourSearch.o DataPoints.o Cluster.o K_medoids.o Park_Jun.o -o medoids -lm

main.o: main.cpp DataPoints.h
	g++ -std=c++0x -c -g main.cpp

LinkedList.o:../proj1.3/LinkedList.cpp ../proj1.3/LinkedList.h
	g++ -std=c++0x -c -g ../proj1.3/LinkedList.cpp

Hashtable.o: ../proj1.3/Hashtable.cpp ../proj1.3/LinkedList.h ../proj1.3/Hashtable.h
	g++ -c -g ../proj1.3/Hashtable.cpp 

Hamming.o: ../proj1.3/Hamming.cpp ../proj1.3/Hamming.h
	g++ -c -g ../proj1.3/Hamming.cpp
	
CosineSim.o: ../proj1.3/CosineSim.cpp ../proj1.3/CosineSim.h ../proj1.3/randomfunc.h
	g++ -std=c++0x -c -g ../proj1.3/CosineSim.cpp
	
DistanceMatrix.o: ../proj1.3/DistanceMatrix.cpp ../proj1.3/DistanceMatrix.h
	g++ -std=c++0x -c -g ../proj1.3/DistanceMatrix.cpp 
	
Euclidean.o: ../proj1.3/Euclidean.cpp ../proj1.3/Euclidean.h
	g++ -std=c++0x -c -g ../proj1.3/Euclidean.cpp
	
randomfunc.o: ../proj1.3/randomfunc.cpp ../proj1.3/randomfunc.h
	g++ -c -g ../proj1.3/randomfunc.cpp
	
NeighbourSearch.o: ../proj1.3/NeighbourSearch.cpp ../proj1.3/NeighbourSearch.h ../proj1.3/Hashtable.h 
	g++ -c -g ../proj1.3/NeighbourSearch.cpp
	
DataPoints.o: DataPoints.cpp DataPoints.h 
	g++ -c -g DataPoints.cpp

Cluster.o: Cluster.cpp Cluster.h
	g++ -c -g Cluster.cpp
	
K_medoids.o: K_medoids.cpp K_medoids.h
	g++ -std=c++0x -c -g K_medoids.cpp

Park_Jun.o: Park_Jun.cpp Park_Jun.h
	g++ -std=c++0x -c -g Park_Jun.cpp
	
clean:
	rm -f *.o lsh


# build tests
build-tests: .build-tests-post

.build-tests-pre:
# Add your pre 'build-tests' code here...

.build-tests-post: .build-tests-impl
# Add your post 'build-tests' code here...


# run tests
test: .test-post

.test-pre: build-tests
# Add your pre 'test' code here...

.test-post: .test-impl
# Add your post 'test' code here...


# help
help: .help-post

.help-pre:
# Add your pre 'help' code here...

.help-post: .help-impl
# Add your post 'help' code here...



# include project implementation makefile
include nbproject/Makefile-impl.mk

# include project make variables
include nbproject/Makefile-variables.mk
