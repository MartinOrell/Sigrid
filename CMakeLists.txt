cmake_minimum_required(VERSION 3.28)
project(MyEditTool LANGUAGES CXX)

set(SRC_FILES
    src/main.cpp
    src/MainWindow/MainWindow.cpp
    src/MainWindow/MainWindowConfigContainer.cpp
    src/Menu/Menu.cpp
    src/Menu/MenuItem.cpp
    src/WorkWindow/WorkWindow.cpp
    src/ToolWindow/ToolWindow.cpp
    src/ToolWindow/ToolItem.cpp
    src/Board/Board.cpp src/Piece/Piece.cpp
    src/Board/GraphicBoard.cpp
    src/Board/LogicBoard.cpp
    src/Board/Coord.cpp
    src/Piece/LogicPiece.cpp
    src/Piece/GraphicPiece.cpp
    src/Piece/PieceIdentifier.cpp
    src/Piece/PieceManager.cpp
    src/Tool/Tool.cpp
    src/Tool/ToolManager.cpp
    src/ToolPicker/GraphicToolPicker.cpp
    src/ToolPicker/ToolPickerWindow.cpp
    src/Arrow/Arrow.cpp
    src/Arrow/LogicArrow.cpp
    src/Arrow/GraphicArrow.cpp
    src/Color/ColorManager.cpp
)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 3.0.1
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM)
FetchContent_MakeAvailable(SFML)

add_executable(main ${SRC_FILES})
target_compile_features(main PRIVATE cxx_std_17)
target_link_libraries(main PRIVATE SFML::Graphics)