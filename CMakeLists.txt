cmake_minimum_required(VERSION 3.14)
project(GNQTS_SelectStock)

set(CMAKE_CXX_STANDARD 14)

add_executable(GNQTS_SelectStock main.cpp Logger.h Model.cpp Model.h Stock.h Particle.h QTS.cpp QTS.h)