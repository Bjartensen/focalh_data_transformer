# * See https://root.cern/manual/integrate_root_into_my_cmake_project/ for more info
cmake_minimum_required(VERSION 3.12)
set(CMAKE_CXX_STANDARD 17)
project(focalh_data_transformer)

find_package(ROOT REQUIRED COMPONENTS 
  Core 
	Tree
  RIO
  Thread
)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

add_library(focalh_data_transformer SHARED 
  include/focal_sim_reader.h
  src/focal_sim_reader.cxx
  include/superimpose_events.h
  src/superimpose_events.cxx
  )

target_link_libraries(focalh_data_transformer PUBLIC 
  ROOT::Core
  ROOT::Tree
  ROOT::RIO
  ROOT::Thread
)

# * Change script name here to run different scripts
add_executable(test_script                  ./scripts/test_script.cxx)
add_executable(sim2gen                  ./scripts/sim2gen.cxx)
add_executable(merge                  ./scripts/merge.cxx)
add_executable(triangular_merge                  ./scripts/triangular_merge.cxx)
add_executable(random_merge                  ./scripts/random_merge.cxx)

target_link_libraries(test_script                     focalh_data_transformer)
target_link_libraries(sim2gen                     focalh_data_transformer)
target_link_libraries(merge                     focalh_data_transformer)
target_link_libraries(triangular_merge                     focalh_data_transformer)
target_link_libraries(random_merge                     focalh_data_transformer)

