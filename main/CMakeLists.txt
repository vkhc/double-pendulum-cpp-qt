
set(SOURCES main.cpp
            mainwidget.cpp
            PWidget.cpp
            pendulum.cpp
            helpers.cpp
            )
if(WIN32)
    add_executable(${MAIN} WIN32 ${SOURCES}) # WIN32 prevents console opening
else()
    add_executable(${MAIN} ${SOURCES})
endif()

target_link_libraries(${MAIN} Qt6::Widgets
                              )
