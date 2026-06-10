cmake_minimum_required(VERSION 3.28)
project(MyEditTool LANGUAGES CXX)

set(SRC_FILES
    src/main.cpp
    src/Input/Mouse/Mouse.cpp
    src/Input/InputHandler.cpp
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
    src/Board/BoardLabels.cpp
    src/Coord/Coord.cpp
    src/Coord/CoordPair.cpp
    src/Layout/LayoutGrid.cpp
    src/Font/FontManager.cpp
    src/Entity/Piece/LogicPiece.cpp
    src/Entity/Piece/GraphicPiece.cpp
    src/Entity/Piece/PieceIdentifier.cpp
    src/Entity/Piece/PieceManager.cpp
    src/Tool/Tool.cpp
    src/ToolPicker/ToolPickerWindow.cpp
    src/Color/ColorManager.cpp
    src/Action/Action.cpp
    src/Entity/Tile/LogicTile.cpp
    src/Entity/Tile/GraphicTile.cpp
    src/Entity/Tile/LogicTiles.cpp
    src/Entity/Tile/GraphicTiles.cpp
    src/Entity/Icon/LogicIcon.cpp
    src/Entity/Icon/Icon.cpp
    src/Entity/Icon/IconManager.cpp
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
    src/Pdf/Pdf.cpp
    src/Pdf/Object.cpp
    src/Pdf/Catalog.cpp
    src/Pdf/Pages.cpp
    src/Pdf/Page.cpp
    src/Pdf/ProcedureSet.cpp
    src/Pdf/MediaBox.cpp
    src/Pdf/PageResources.cpp
    src/Pdf/ExternalObject.cpp
    src/Pdf/ExternalObjects.cpp
    src/Pdf/ContentStream.cpp
    src/Pdf/ContentStreams.cpp
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
set_target_properties(main PROPERTIES OUTPUT_NAME "sigrid")
target_compile_features(main PRIVATE cxx_std_17)
target_link_libraries(main PRIVATE SFML::Graphics)