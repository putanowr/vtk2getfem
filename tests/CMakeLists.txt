cmake_minimum_required(VERSION 3.4)

add_test(NAME InfoTest
	COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/infoTest.sh $<TARGET_FILE:vtk2getfem> ${CMAKE_CURRENT_SOURCE_DIR})
