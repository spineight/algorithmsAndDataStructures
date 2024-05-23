package ru.covariance.jbintern;

import java.util.List;

/**
 * An object that provides solution for scheduling problem specified in README
 */
public interface Solver {
    /**
     * Solves the problem for given schedule.
     * @param schedule {List<Train>} Schedule of trains
     * @return Solution for the given schedule
     */
    Solution solve(List<Train> schedule);
}
