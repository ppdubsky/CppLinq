add_unit_test(
    NAME
        IntersectBy
    SOURCES
        ${PROJECT_SOURCE_DIR}/Tests/IntersectBy/Enumerator_is_inaccessible_after_it_is_finished.cpp
        ${PROJECT_SOURCE_DIR}/Tests/IntersectBy/Enumerator_is_inaccessible_after_it_is_finished_using_comparer.cpp
        ${PROJECT_SOURCE_DIR}/Tests/IntersectBy/Produce_set_intersection_of_two_sequences_by_key.cpp
        ${PROJECT_SOURCE_DIR}/Tests/IntersectBy/Produce_set_intersection_of_two_sequences_by_key_using_comparer.cpp
        ${PROJECT_SOURCE_DIR}/Tests/IntersectBy/Stubs/Customer.cpp
        ${PROJECT_SOURCE_DIR}/Tests/IntersectBy/Stubs/Customer.hpp
)