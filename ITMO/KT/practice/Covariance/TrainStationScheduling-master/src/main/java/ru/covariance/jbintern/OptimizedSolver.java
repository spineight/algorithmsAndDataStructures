package ru.covariance.jbintern;

import java.util.ArrayList;
import java.util.Collections;
import java.util.List;

/**
 * Naive implementation of Solver interface, that provides solution for given problem
 * in a O(n*log(n)) of time and O(n) of memory
 */
public class OptimizedSolver implements Solver {
    private static class Event implements Comparable<Event> {
        public final double time;
        public final boolean isArrival;
        public final int train;

        public Event(final double time, final boolean isArrival, final int train) {
            this.time = time;
            this.isArrival = isArrival;
            this.train = train;
        }

        @Override
        public int compareTo(Event event) {
            return (this.time == event.time) ? (this.isArrival ? 1 : -1)
                    : ((this.time < event.time) ? -1 : 1);
        }

        @Override
        public String toString() {
            return time + " " + isArrival + " " + train;
        }
    }

    /**
     * Solves the problem for given schedule.
     * @param schedule {List<Train>} Schedule of trains
     * @return Solution for the given schedule
     */
    @Override
    public Solution solve(List<Train> schedule) {
        int n = schedule.size();
        if (n == 0) {
            return new Solution(0., List.of());
        }
        List<Event> events = new ArrayList<>();
        for (int i = 0; i < n; i++) {
            events.add(new Event(schedule.get(i).getArrival(), true, i));
            events.add(new Event(schedule.get(i).getUnloadingEnd(), false, i));
        }
        Collections.sort(events);


        double[] dp = new double[2 * n];
        int[] arrival = new int[n];
        for (int i = 0; i < 2 * n; i++) {
            if (events.get(i).isArrival) {
                dp[i] = (i == 0) ? 0 : dp[i - 1];
                arrival[events.get(i).train] = i;
            } else {
                dp[i] = Math.max(
                        dp[i - 1],
                        dp[arrival[events.get(i).train]]
                                + schedule.get(events.get(i).train).getPayment()
                );
            }
        }

        List<Integer> res = new ArrayList<>();
        int current = 2 * n - 1;
        while (current != 0) {
            if (!events.get(current).isArrival
                    && dp[arrival[events.get(current).train]]
                    + schedule.get(events.get(current).train).getPayment() > dp[current - 1]) {
                res.add(schedule.get(events.get(current).train).getID());
                current = arrival[events.get(current).train];
            } else {
                current--;
            }
        }
        Collections.sort(res);
        return new Solution(dp[2 * n - 1], res);
    }
}
