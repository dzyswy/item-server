file(GLOB_RECURSE test_srcs "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")


#INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/../../3rdparty/jsoncpp/include)

if (UNIX)
	set(LIBS ${LIBS} pthread)
endif ()


SET(LIBS ${LIBS} item_server)

foreach(SOURCE_FILE ${test_srcs})
  # get file name
  get_filename_component(TEST_NAME ${SOURCE_FILE} NAME_WE)
    
  add_executable(${TEST_NAME} ${SOURCE_FILE})
  target_link_libraries(${TEST_NAME} ${LIBS})


  # install
  install(TARGETS ${TEST_NAME} DESTINATION bin)


endforeach()
