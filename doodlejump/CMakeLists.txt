cmake_minimum_required(VERSION 3.10)

set(CMAKE_AUTOMOC ON)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_compile_options(/Zc:__cplusplus)

project(doodlejump)

include_directories("D:\\Qt\\6.8.2\\msvc2022_64\\include\\QtWidgets"
                    "D:\\Qt\\6.8.2\\msvc2022_64\\include\\QtCore"
                    "D:\\Qt\\6.8.2\\msvc2022_64\\include\\QtGui"
                    "D:\\Qt\\6.8.2\\msvc2022_64\\include")

link_directories("D:\\Qt\\6.8.2\\msvc2022_64\\lib")

set(Qt6Widgets_DIR "D:\\Qt\\6.8.2\\msvc2022_64\\lib\\cmake\\Qt6Widgets")
find_package(Qt6Widgets REQUIRED)
set(Qt6Core_DIR "D:\\Qt\\6.8.2\\msvc2022_64\\lib\\cmake\\Qt6Core")
find_package(Qt6Core REQUIRED)
set(Qt6Gui_DIR "D:\\Qt\\6.8.2\\msvc2022_64\\lib\\cmake\\Qt6Gui")
find_package(Qt6Gui REQUIRED)

add_executable(doodlejump main.cpp MainWindow.cpp MainHero.cpp MenuState.cpp ActingState.cpp Platform.cpp DefaultPlatform.cpp MovingPlatform.cpp BreakingPlatform.cpp
    ButtonForMenu.cpp GameOverDecorations.cpp MoveSprite.cpp OptionsState.cpp)

target_link_libraries(doodlejump PRIVATE Qt6Widgets Qt6Core Qt6Gui)