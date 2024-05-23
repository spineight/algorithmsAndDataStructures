package ru.covariance.jbintern;

import java.util.ArrayList;
import java.util.Collections;
import java.util.Comparator;
import java.util.List;

/**
 * Naive implementation of Solver interface, that provides solution for given problem
 * in a O(n^2) of time and O(n) of memory
 */
public class NaiveSolver implements Solver {
    /**
     * Solves the problem for given schedule.
     * @param schedule {List<Train>} Schedule of trains
     * @return Solution for the given schedule
     */
    @Override
    public Solution solve(List<Train> schedule) {
        schedule.sort(Comparator.comparingDouble(Train::getArrival));
        int n = schedule.size();
        double[] dp = new double[n + 1];
        dp[0] = 0.;
        for (int i = 1; i <= n; i++) {
            int index = 0;
            for (int j = 1; j < i; j++) {
                if (schedule.get(j - 1).getUnloadingEnd() <= schedule.get(i - 1).getArrival()
                        && dp[j] > dp[index]) {
                    index = j;
                }
            }
            dp[i] = dp[index] + schedule.get(i - 1).getPayment();
        }

        int index = 0;
        for (int i = 0; i <= n; i++) {
            if (dp[i] > dp[index]) {
                index = i;
            }
        }
        List<Integer> res = new ArrayList<>();
        int current = index;
        while (current != 0) {
            int maxIndex = 0;
            for (int j = 1; j < current; j++) {
                if (schedule.get(j - 1).getUnloadingEnd() <= schedule.get(current - 1).getArrival()
                        && dp[j] > dp[maxIndex]) {
                    maxIndex = j;
                }
            }
            res.add(schedule.get(current - 1).getID());
            current = maxIndex;
        }
        Collections.sort(res);
        return new Solution(dp[index], res);
    }
}
