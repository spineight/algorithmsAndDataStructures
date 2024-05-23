package perfomance;

import ru.covariance.jbintern.NaiveSolver;
import ru.covariance.jbintern.OptimizedSolver;
import ru.covariance.jbintern.Solution;
import ru.covariance.jbintern.Train;

import java.util.stream.Collectors;
import java.util.stream.IntStream;

public class PerformanceTest {
    public static void main(String[] args) {
        int length = Integer.parseInt(args[0]);
        Solution s = ((args[1].charAt(0) == 'n') ? new NaiveSolver() : new OptimizedSolver())
                .solve(
                        // List is ordered backwards in order to test sorting time
                        IntStream.range(0, length)
                                .mapToObj(i -> new Train(length - i - 1, length - i - 1, 1, 1))
                                .collect(Collectors.toList())
                );
        if (s.getSum() != length) {
            // This if is here to make sure that JVM does not skip
            // calculation of solution because variable s is not
            // used anywhere further in code
            System.out.println('a');
        }
    }
}
