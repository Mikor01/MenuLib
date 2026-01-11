add_library(menulib
    menulib/MenuPage.cpp
    menulib/MenuOption.cpp
    menulib/MenuNavigator.cpp
    menulib/MenuToggle.cpp
    menulib/MenuSlider.cpp
)

target_include_directories(menulib PUBLIC
    ${CMAKE_SOURCE_DIR}/include
)

add_executable(MenuApp main.cpp)

target_link_libraries(MenuApp PRIVATE menulib)
