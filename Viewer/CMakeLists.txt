cmake_minimum_required (VERSION 2.8)
project(viewer)

set(SOURCES 
    "../gui/aanimobject.cpp"
    "../code/gamesound.cpp"
    "../code/logisticscomponent.cpp"
    "../code/logisticsdata.cpp"
    "../code/logisticsmech.cpp"
    "../code/logisticsmissioninfo.cpp"
    "../code/logisticspilot.cpp"
    "../code/logisticsvariant.cpp"
    "../code/mechlopedia.cpp"
    "../code/mission2.cpp"
    "../code/prefs.cpp"
    "../code/radio.cpp"
    "../code/simplecamera.cpp"
    "../code/simplecomponentlistbox.cpp"
    #    "../strings.res.cpp"
    "View.cpp"
    )

add_definitions(-DVIEWER=1)
#add_definitions(-D_ARMOR)
#add_definitions(-D_DEBUG)

include_directories("./window" ${COMMON_INCLUDE_DIRS} "../mclib" "../gui" "../code" "../netlib")

add_executable(viewer ${SOURCES})
target_link_libraries(viewer mclib gosfx mlr stuff gui gameos windows z SDL2::SDL2 ${SDL_LIBS} GLEW SDL2_mixer ${ADDITIONAL_LIBS} OpenGL)

