find_package(VTK REQUIRED COMPONENTS CommonDataModel FiltersCore RenderingCore)

add_library(Visualization
    Visualization.cpp
)

target_include_directories(Visualization
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_compile_features(Visualization PUBLIC cxx_std_20)

target_link_libraries(Visualization
    PUBLIC
        VTK::CommonDataModel
        VTK::FiltersCore
        VTK::RenderingCore
)
