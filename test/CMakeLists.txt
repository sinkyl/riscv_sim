FILE(GLOB SOURCES ./*.c ../src/*.c)

ADD_SUBDIRECTORY(unity)
ADD_EXECUTABLE(test ${SOURCES} projet1.c projet1.h test_processeur.c)
TARGET_LINK_LIBRARIES(test unity)