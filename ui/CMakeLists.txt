CMAKE_MINIMUM_REQUIRED(VERSION 3.16)
PROJECT(projet1 C)

SET(CMAKE_C_STANDARD 99)

file(GLOB CSS_FILE "./*.css")
file(COPY ${CSS_FILE} DESTINATION ${CMAKE_CURRENT_BINARY_DIR})