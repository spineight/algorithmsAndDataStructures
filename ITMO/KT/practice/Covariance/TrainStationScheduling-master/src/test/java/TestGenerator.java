import ru.covariance.jbintern.Train;

import java.util.List;
import java.util.Random;
import java.util.stream.Collectors;
import java.util.stream.IntStream;

public class TestGenerator {
    public static Train generateTrain(int ID, Random rand) {
        return new Train(ID,
                rand.nextDouble() * rand.nextInt(100),
                (rand.nextDouble() + 1e-7) * (1 + rand.nextInt(100)),
                Math.abs(rand.nextDouble() * rand.nextInt(10)) + 1.
        );
    }

    public static List<Train> generateTest(int length, Random rand) {
        return IntStream.range(0, length).mapToObj(i -> generateTrain(i, rand)).collect(Collectors.toList());
    }
}
