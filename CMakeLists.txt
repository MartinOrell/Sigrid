cmake_minimum_required(VERSION 3.28)
project(sigrid LANGUAGES CXX)

set(SRC_FILES
    src/sigrid/main.cpp
    src/sigrid/SigridRenderTexture/SigridRenderTexture.cpp
    src/sigrid/utilities/lists/Vector.cpp
    src/sigrid/utilities/lists/Vector2D.cpp
    src/sigrid/utilities/lists/Map.cpp
    src/sigrid/utilities/lists/OrderedMap.cpp
    src/sigrid/utilities/lists/VectorWithDisplayGrid.cpp
    src/sigrid/utilities/lists/AutoInsertMappedGrid.cpp
    src/sigrid/utilities/lists/listLoaders/LoadStrings.cpp
    src/sigrid/utilities/lists/listSavers/ListSaver.cpp
    src/sigrid/utilities/lists/listSavers/IntListSaver.cpp
    src/sigrid/utilities/lists/listSavers/StringListSaver.cpp
    src/sigrid/utilities/String/String.cpp
    src/sigrid/utilities/InputStream/InputStream.cpp
    src/sigrid/utilities/FileSystem/FileSystem.cpp
    src/sigrid/Input/Mouse/Mouse.cpp
    src/sigrid/Input/InputHandler.cpp
    src/sigrid/Config/MainConfigContainer.cpp
    src/sigrid/Window/WindowContainer.cpp
    src/sigrid/Window/MainWindow/MainWindow.cpp
    src/sigrid/Menu/MenuContainer.cpp
    src/sigrid/Menu/HeaderContainer.cpp
    src/sigrid/Menu/MenuItemContainer.cpp
    src/sigrid/Menu/Menu.cpp
    src/sigrid/Menu/MenuItem.cpp
    src/sigrid/Window/WorkWindow/WorkWindowContainer.cpp
    src/sigrid/Window/WorkWindow/WorkWindow.cpp
    src/sigrid/Window/WorkWindow/PdfHandler.cpp
    src/sigrid/Window/ToolWindow/ToolWindowContainer.cpp
    src/sigrid/Window/ToolWindow/ToolWindow.cpp
    src/sigrid/Board/BoardContainer.cpp
    src/sigrid/Board/BoardStateContainer.cpp
    src/sigrid/Board/BoardDesignContainer.cpp
    src/sigrid/Board/BoardLabelContainer.cpp
    src/sigrid/Board/BoardLabelLocationContainer.cpp
    src/sigrid/Board/Board.cpp
    src/sigrid/Board/GraphicBoard.cpp
    src/sigrid/Board/BoardState.cpp
    src/sigrid/Board/BoardLabels.cpp
    src/sigrid/Board/SideLabels.cpp
    src/sigrid/utilities/Coord/Coord.cpp
    src/sigrid/utilities/Coord/CoordPair.cpp
    src/sigrid/utilities/Layout/LayoutGrid.cpp
    src/sigrid/Font/FontManager.cpp
    src/sigrid/Entity/Piece/PieceContainer.cpp
    src/sigrid/Entity/Piece/PieceDataContainer.cpp
    src/sigrid/Entity/Piece/PieceColor.cpp
    src/sigrid/Entity/Piece/LogicPiece.cpp
    src/sigrid/Entity/Piece/GraphicPiece.cpp
    src/sigrid/Entity/Piece/PieceIdentifier.cpp
    src/sigrid/Entity/Piece/PieceManager.cpp
    src/sigrid/Tool/ToolContainer.cpp
    src/sigrid/Tool/Tool.cpp
    src/sigrid/ToolPicker/ToolPickerContainer.cpp
    src/sigrid/ToolPicker/ToolBlockContainer.cpp
    src/sigrid/ToolPicker/ToolPickerWindow.cpp
    src/sigrid/Color/ColorContainer.cpp
    src/sigrid/Color/ColorManager.cpp
    src/sigrid/Action/Action.cpp
    src/sigrid/Entity/Tile/TileContainer.cpp
    src/sigrid/Entity/Tile/LogicTile.cpp
    src/sigrid/Entity/Tile/GraphicTile.cpp
    src/sigrid/Entity/Tile/LogicTiles.cpp
    src/sigrid/Entity/Tile/GraphicTiles.cpp
    src/sigrid/Entity/Icon/IconDataContainer.cpp
    src/sigrid/Entity/Icon/LogicIcon.cpp
    src/sigrid/Entity/Icon/Icon.cpp
    src/sigrid/Entity/Icon/IconManager.cpp
    src/sigrid/Entity/Shape/Circle/CircleContainer.cpp
    src/sigrid/Entity/Shape/Circle/CircleDataContainer.cpp
    src/sigrid/Entity/Shape/Circle/LogicCircle.cpp
    src/sigrid/Entity/Shape/Circle/GraphicCircle.cpp
    src/sigrid/Entity/Shape/Arrow/ArrowContainer.cpp
    src/sigrid/Entity/Shape/Arrow/ArrowDataContainer.cpp
    src/sigrid/Entity/Shape/Arrow/LogicArrow.cpp
    src/sigrid/Entity/Shape/Arrow/GraphicArrow.cpp
    src/sigrid/Entity/Shape/Arrow/LogicArrows.cpp
    src/sigrid/Entity/Shape/Arrow/GraphicArrows.cpp
    src/sigrid/Entity/Shape/RectangleBorder/RectangleBorderContainer.cpp
    src/sigrid/Entity/Shape/RectangleBorder/RectangleBorder.cpp
    src/sigrid/Entity/LogicEntities.cpp
    src/sigrid/Entity/GraphicEntities.cpp
    src/sigrid/Entity/TurnToken/TurnTokenContainer.cpp
    src/sigrid/Entity/TurnToken/TurnToken.cpp
    src/sigrid/Pdf/Pdf.cpp
    src/sigrid/Pdf/Object.cpp
    src/sigrid/Pdf/Catalog.cpp
    src/sigrid/Pdf/Pages.cpp
    src/sigrid/Pdf/Page.cpp
    src/sigrid/Pdf/ProcedureSet.cpp
    src/sigrid/Pdf/MediaBox.cpp
    src/sigrid/Pdf/PageResources.cpp
    src/sigrid/Pdf/ExternalObject.cpp
    src/sigrid/Pdf/ExternalObjects.cpp
    src/sigrid/Pdf/ContentStream.cpp
    src/sigrid/Pdf/ContentStreams.cpp
)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include(FetchContent)
FetchContent_Declare(nfd
    GIT_REPOSITORY https://github.com/btzy/nativefiledialog-extended
    GIT_SHALLOW ON)
FetchContent_MakeAvailable(nfd)

FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 3.0.1
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM)
FetchContent_MakeAvailable(SFML)

add_executable(main ${SRC_FILES})
target_include_directories(main PRIVATE src)
set_target_properties(main PROPERTIES OUTPUT_NAME "sigrid")
target_compile_features(main PRIVATE cxx_std_17)

target_link_libraries(main PRIVATE nfd)
target_link_libraries(main PRIVATE SFML::Graphics)