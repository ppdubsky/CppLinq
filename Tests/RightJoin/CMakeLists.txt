add_unit_test(
    NAME
        RightJoin
    SOURCES
        ${PROJECT_SOURCE_DIR}/Tests/RightJoin/Enumerator_is_inaccessible_after_it_is_finished.cpp
        ${PROJECT_SOURCE_DIR}/Tests/RightJoin/Enumerator_is_inaccessible_after_it_is_finished_using_comparer.cpp
        ${PROJECT_SOURCE_DIR}/Tests/RightJoin/Right_join_two_sequences.cpp
        ${PROJECT_SOURCE_DIR}/Tests/RightJoin/Right_join_two_sequences_using_comparer.cpp
        ${PROJECT_SOURCE_DIR}/Tests/RightJoin/Stubs/Person.cpp
        ${PROJECT_SOURCE_DIR}/Tests/RightJoin/Stubs/Person.hpp
        ${PROJECT_SOURCE_DIR}/Tests/RightJoin/Stubs/Pet.cpp
        ${PROJECT_SOURCE_DIR}/Tests/RightJoin/Stubs/Pet.hpp
)