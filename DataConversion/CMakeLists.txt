find_package(VTK REQUIRED COMPONENTS CommonDataModel)

add_library(DataConversion
    DataConversion.cpp
)

target_include_directories(DataConversion
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_compile_features(DataConversion PUBLIC cxx_std_20)

target_link_libraries(DataConversion
    PUBLIC
        VTK::CommonDataModel
)
