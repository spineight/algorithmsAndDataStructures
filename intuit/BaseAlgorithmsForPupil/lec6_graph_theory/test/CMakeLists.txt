include(GoogleTest)
include(packageAddTestAndPractice)

packageAddTestAndPractice(
        INTUIT::baseAlgorithmsForPupil::lec6_graph_theory::lib
        INTUIT::baseAlgorithmsForPupil::lec6_graph_theory::practice
        lec6_testMST_Kruskal
        testMST_Kruskal.cpp
)

packageAddTestAndPractice(
        INTUIT::baseAlgorithmsForPupil::lec6_graph_theory::lib
        INTUIT::baseAlgorithmsForPupil::lec6_graph_theory::practice
        lec6_testMST_Prim
        testMST_Prim.cpp
)

packageAddTestAndPractice(
        INTUIT::baseAlgorithmsForPupil::lec6_graph_theory::lib
        INTUIT::baseAlgorithmsForPupil::lec6_graph_theory::practice
        lec6_testEulerCycle
        testEulerCycle.cpp
)

