add_unit_test(
    NAME
        SelectMany
    SOURCES
        ${PROJECT_SOURCE_DIR}/Tests/SelectMany/Enumerator_is_inaccessible_after_it_is_finished.cpp
        ${PROJECT_SOURCE_DIR}/Tests/SelectMany/Stubs/Order.hpp
        ${PROJECT_SOURCE_DIR}/Tests/SelectMany/Transform_each_element_and_flatten_resulting_sequence.cpp
)