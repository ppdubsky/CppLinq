add_unit_test(
    NAME
        Concatenate
    SOURCES
        ${PROJECT_SOURCE_DIR}/Tests/Concatenate/Concatenate_two_sequences.cpp
        ${PROJECT_SOURCE_DIR}/Tests/Concatenate/Enumerator_is_inaccessible_after_it_is_finished.cpp
)