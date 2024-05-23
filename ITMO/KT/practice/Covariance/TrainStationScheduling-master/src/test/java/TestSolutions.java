import org.junit.Assert;
import org.junit.Ignore;
import org.junit.Test;
import ru.covariance.jbintern.*;

import java.util.ArrayList;
import java.util.Comparator;
import java.util.List;
import java.util.Random;
import java.util.stream.Collectors;
import java.util.stream.IntStream;

public class TestSolutions {
    private final static double DOUBLE_EPS = 1e-7;

    // This validator works only if train IDs in trains list are corresponding to their indexes
    private void validateSolution(List<Train> trains, Solution solution) {
        // ru.covariance.jbintern.Solution trains is a sorted by time of arrival list of trains that we must unload in solution
        List<Train> solutionTrains = solution.getTrainIDs().stream()
                .mapToInt(index -> index)
                .mapToObj(trains::get)
                .sorted(Comparator.comparingDouble(Train::getArrival))
                .collect(Collectors.toList());
        // This assertion checks absence of intersections between unloads
        IntStream.range(1, solutionTrains.size())
                .forEachOrdered(i -> Assert.assertTrue(
                        solutionTrains.get(i).getArrival()
                                >= solutionTrains.get(i - 1).getUnloadingEnd()
                        )
                );
        // This assertion checks equality of solution sum and counted sum
        Assert.assertEquals(solutionTrains.stream().mapToDouble(Train::getPayment).sum(),
                solution.getSum(),
                DOUBLE_EPS
        );
    }

    private void testsFromList(List<List<Train>> testCases, List<Double> answers) {
        Solver naive = new NaiveSolver(), optimized = new OptimizedSolver();
        for (int i = 0; i < testCases.size(); i++) {
            Solution naiveSolution = naive.solve(new ArrayList<>(testCases.get(i)));
            Solution optimizedSolution = optimized.solve(new ArrayList<>(testCases.get(i)));
            validateSolution(testCases.get(i), naiveSolution);
            validateSolution(testCases.get(i), optimizedSolution);
            Assert.assertEquals(naiveSolution.getSum(), answers.get(i), DOUBLE_EPS);
            Assert.assertEquals(optimizedSolution.getSum(), answers.get(i), DOUBLE_EPS);
        }
    }

    @Test
    public void testsFromStatements() {
        testsFromList(
                List.of(
                        List.of(
                                new Train(0, 1, 3, 10),
                                new Train(1, 0, 3, 9),
                                new Train(2, 0, 2, 5)
                        ),
                        List.of(
                                new Train(0, 0, 2, 2),
                                new Train(1, 1, 4, 4),
                                new Train(2, 2, 3, 3)
                        )
                ),
                List.of(
                        10.,
                        5.
                )
        );
    }

    @Test
    public void manualTest() {
        testsFromList(
                List.of(
                        // Empty test
                        List.of(),
                        // All can be taken (small test)
                        IntStream.range(0, 1_000).mapToObj(i -> new Train(i, i, 1, 1)).collect(Collectors.toList()),
                        // All can be taken (big test)
                        IntStream.range(0, 1_00_000).mapToObj(i -> new Train(i, i, 1, 1)).collect(Collectors.toList())
                ),
                List.of(
                        0.,
                        1_000.,
                        1_00_000.
                )
        );
    }

    @Test
    public void randomSmallTests() {
        Random rand = new Random();
        Solver naive = new NaiveSolver(), optimized = new OptimizedSolver();
        for (int i = 0; i < 1_000; i++) {
            List<Train> test = TestGenerator.generateTest(i + 1, rand);
            Solution naiveSolution = naive.solve(new ArrayList<>(test));
            Solution optimizedSolution = optimized.solve(new ArrayList<>(test));
            validateSolution(test, naiveSolution);
            validateSolution(test, optimizedSolution);
            Assert.assertEquals(naiveSolution.getSum(), optimizedSolution.getSum(), DOUBLE_EPS);
        }
    }

    @Test
    public void randomBigTests() {
        Random rand = new Random();
        Solver optimized = new OptimizedSolver();
        for (int i = 5_00_000; i < 1_000_000; i += 1000) {
            List<Train> test = TestGenerator.generateTest(i, rand);
            Solution optimizedSolution = optimized.solve(new ArrayList<>(test));
            validateSolution(test, optimizedSolution);
        }
    }
}
