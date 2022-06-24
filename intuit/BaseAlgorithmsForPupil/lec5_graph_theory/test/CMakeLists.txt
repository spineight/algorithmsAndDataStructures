include(GoogleTest)
include(packageAddTestAndPractice)

packageAddTestAndPractice(
        INTUIT::baseAlgorithmsForPupil::lec5_graph_theory::lib
        INTUIT::baseAlgorithmsForPupil::lec5_graph_theory::practice
        lec5_testTopologicalSort
        testTopologicalSort.cpp
)

packageAddTestAndPractice(
        INTUIT::baseAlgorithmsForPupil::lec5_graph_theory::lib
        INTUIT::baseAlgorithmsForPupil::lec5_graph_theory::practice
        lec5_testCycleDetection
        testCycleDetection.cpp
)

packageAddTestAndPractice(
        INTUIT::baseAlgorithmsForPupil::lec5_graph_theory::lib
        INTUIT::baseAlgorithmsForPupil::lec5_graph_theory::practice
        lec5_testShortestPathsBFS
        testShortestPathsBFS.cpp
)

packageAddTestAndPractice(
        INTUIT::baseAlgorithmsForPupil::lec5_graph_theory::lib
        INTUIT::baseAlgorithmsForPupil::lec5_graph_theory::practice
        lec5_testDijkstra
        testDijkstra.cpp
)
