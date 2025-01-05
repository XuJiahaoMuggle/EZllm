cmake_minimum_required(VERSION 3.16)
project(ezllm LANGUAGES C CXX CUDA)
set(CMAKE_CUDA_ARCHITECTURES 89)

# build our xym shared library
add_subdirectory(base)
add_subdirectory(device)
add_subdirectory(ir)
add_subdirectory(ops)
add_subdirectory(frame)
list(
  APPEND
  XYM_SRCS
  ${BASE_SCRS}
  ${DEVICE_SRCS}
  ${IR_SRCS}
  ${OPS_SRCS}
  ${FRAME_SRCS}
)
add_library(xym_infer SHARED ${XYM_SRCS})
set(CUDA_DIR /usr/local/cuda)
target_link_libraries(
  xym_infer PRIVATE
  cuda
  cudart
)

target_include_directories(
  xym_infer PRIVATE 
  ${CUDA_DIR}/include
  ${CMAKE_CURRENT_SOURCE_DIR}
)

# build samples
add_subdirectory(samples)
foreach(SAMPLE_SRC ${SAMPLE_SRCS})
  get_filename_component(SAMPLE_NAME ${SAMPLE_SRC} NAME_WE)
  add_executable(${SAMPLE_NAME} ${SAMPLE_SRC})
  target_include_directories(
    ${SAMPLE_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
  )
  target_link_libraries(
    ${SAMPLE_NAME} PRIVATE
    xym_infer
  )
endforeach()

# build tests
add_subdirectory(tests)
foreach(TEST_SRC ${TEST_SRCS})
  get_filename_component(TEST_NAME ${TEST_SRC} NAME_WE)
  message(STATUS ${TEST_NAME})
  add_executable(${TEST_NAME} ${TEST_SRC})
  target_include_directories(
    ${TEST_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
  )
  target_link_libraries(
    ${TEST_NAME} PRIVATE
    xym_infer
  )
endforeach()
