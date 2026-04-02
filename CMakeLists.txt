cmake_minimum_required(VERSION 3.28)
project(MyEditTool LANGUAGES CXX)

set(SRC_FILES
    src/main.cpp
    src/Window/MainWindow/MainWindow.cpp
    src/Window/MainWindow/MainWindowConfigContainer.cpp
    src/Menu/Menu.cpp
    src/Menu/MenuItem.cpp
    src/Window/WorkWindow/WorkWindow.cpp
    src/Window/ToolWindow/ToolWindow.cpp
    src/Window/ToolWindow/ToolItem.cpp
    src/Board/BoardDataContainer.cpp
    src/Board/Board.cpp
    src/Board/GraphicBoard.cpp
    src/Board/LogicBoard.cpp
    src/Coord/Coord.cpp
    src/Coord/CoordPair.cpp
    src/Font/FontManager.cpp
    src/Entity/Piece/LogicPiece.cpp
    src/Entity/Piece/GraphicPiece.cpp
    src/Entity/Piece/PieceIdentifier.cpp
    src/Entity/Piece/PieceManager.cpp
    src/Tool/Tool.cpp
    src/Tool/ToolManager.cpp
    src/ToolPicker/GraphicToolPicker.cpp
    src/ToolPicker/ToolPickerWindow.cpp
    src/Color/ColorManager.cpp
    src/Action/Action.cpp
    src/Entity/Tile/LogicTile.cpp
    src/Entity/Tile/GraphicTile.cpp
    src/Entity/Tile/LogicTiles.cpp
    src/Entity/Tile/GraphicTiles.cpp
    src/Entity/Shape/Circle/LogicCircle.cpp
    src/Entity/Shape/Circle/GraphicCircle.cpp
    src/Entity/Shape/Arrow/LogicArrow.cpp
    src/Entity/Shape/Arrow/GraphicArrow.cpp
    src/Entity/Shape/Arrow/LogicArrows.cpp
    src/Entity/Shape/Arrow/GraphicArrows.cpp
    src/Entity/Shape/RectangleBorder/RectangleBorder.cpp
    src/Entity/LogicEntities.cpp
    src/Entity/GraphicEntities.cpp
    src/Entity/TurnToken/TurnToken.cpp
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