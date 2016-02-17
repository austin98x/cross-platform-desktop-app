cmake_minimum_required(VERSION 2.8.0)

include(cmake/x_precheck.cmake)

project(App)

include(cmake/x.cmake)

x_add_subdirectory(cmake/testcase)

x_add_subdirectory(3rdparty)
x_add_subdirectory(bfc)
x_add_subdirectory(uilayer)
x_add_subdirectory(core)
x_add_subdirectory(datalayer)

x_final_deal()
