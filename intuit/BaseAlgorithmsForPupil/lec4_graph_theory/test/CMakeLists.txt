include(GoogleTest)
include(packageAddTestAndPractice)

packageAddTestAndPractice(
        INTUIT::baseAlgorithmsForPupil::lec4_graph_theory::lib
        INTUIT::baseAlgorithmsForPupil::lec4_graph_theory::practice
        lec4_testAdjacencyLists
        testAdjacencyLists.cpp
)

packageAddTestAndPractice(
        INTUIT::baseAlgorithmsForPupil::lec4_graph_theory::lib
        INTUIT::baseAlgorithmsForPupil::lec4_graph_theory::practice
        lec4_testDFS
        testDFS.cpp
)

packageAddTestAndPractice(
        INTUIT::baseAlgorithmsForPupil::lec4_graph_theory::lib
        INTUIT::baseAlgorithmsForPupil::lec4_graph_theory::practice
        lec4_testConnectedComponents
        testConnectedComponents.cpp
)

packageAddTestAndPractice(
        INTUIT::baseAlgorithmsForPupil::lec4_graph_theory::lib
        INTUIT::baseAlgorithmsForPupil::lec4_graph_theory::practice
        lec4_testTopSortNSquared
        testTopSortNSquared.cpp
)

