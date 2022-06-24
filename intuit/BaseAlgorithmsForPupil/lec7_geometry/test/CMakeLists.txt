include(GoogleTest)
include(packageAddTestAndPractice)

packageAddTestAndPractice(
        INTUIT::baseAlgorithmsForPupil::lec7_geometry::lib
        INTUIT::baseAlgorithmsForPupil::lec7_geometry::practice
        lec7_testVector
        testVector2D.cpp
)

packageAddTestAndPractice(
        INTUIT::baseAlgorithmsForPupil::lec7_geometry::lib
        INTUIT::baseAlgorithmsForPupil::lec7_geometry::practice
        lec7_testLine
        testLine.cpp
)

packageAddTestAndPractice(
        INTUIT::baseAlgorithmsForPupil::lec7_geometry::lib
        INTUIT::baseAlgorithmsForPupil::lec7_geometry::practice
        lec7_testRay
        testRay.cpp
)

packageAddTestAndPractice(
        INTUIT::baseAlgorithmsForPupil::lec7_geometry::lib
        INTUIT::baseAlgorithmsForPupil::lec7_geometry::practice
        lec7_testSegment
        testSegment.cpp
)

