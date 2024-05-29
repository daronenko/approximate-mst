add_library(graph_objs OBJECT
        graph/repr/base.hpp
        graph/repr/base.cpp
        graph/repr/arc.hpp
        graph/repr/arc.cpp
        graph/dsu/dsu.hpp
        graph/dsu/dsu.cpp
)
target_include_directories(graph_objs PUBLIC ${PROJECT_SOURCE_DIR}/src)

add_executable(${PROJECT_NAME}
        math.hpp
        math.cpp
        point.hpp
        point.cpp
        main.cpp
)
target_link_libraries(${PROJECT_NAME} PRIVATE graph_objs)
