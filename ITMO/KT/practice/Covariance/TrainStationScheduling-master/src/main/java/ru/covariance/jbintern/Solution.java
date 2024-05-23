package ru.covariance.jbintern;

import java.util.List;
import java.util.Objects;
import java.util.stream.Collectors;

/**
 * Class that stores information about solution
 */
public class Solution {
    private final double sum;
    private final List<Integer> trainIDs;

    /**
     * Constructs new Solution from given sum of payments and list of train IDs
     * @param sum sum of payments for unloading of trains in this solution
     * @param trainIDs list of train IDs that must be unloaded in solution
     */
    public Solution(double sum, List<Integer> trainIDs) {
        this.sum = sum;
        this.trainIDs = trainIDs;
    }

    /**
     * Gets a sum of payment amount of this solution
     * @return sum of payment amount of this solution
     */
    public double getSum() {
        return sum;
    }

    /**
     * Gets a list of trains to be unloaded in this solution
     * @return list of trains to be unloaded in this solution
     */
    public List<Integer> getTrainIDs() {
        return trainIDs;
    }

    @Override
    public boolean equals(Object obj) {
        if (obj instanceof Solution) {
            Solution solution = (Solution) obj;
            return this.sum == solution.sum && trainIDs.equals(solution.trainIDs);
        }
        return false;
    }

    @Override
    public int hashCode() {
        return 31 * Objects.hashCode(sum) + Objects.hashCode(trainIDs);
    }

    @Override
    public String toString() {
        return trainIDs.stream()
                .map(String::valueOf)
                .collect(Collectors.joining(" ",
                        Double.toString(sum) + '\n' + trainIDs.size() + '\n',
                        "")
                );
    }
}
