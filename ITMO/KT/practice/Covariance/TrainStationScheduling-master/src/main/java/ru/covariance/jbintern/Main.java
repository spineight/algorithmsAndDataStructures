package ru.covariance.jbintern;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.List;

public class Main {
    public static void main(String[] args) {
        try (BufferedReader reader = new BufferedReader(new InputStreamReader(System.in))) {
            int n = Integer.parseInt(reader.readLine());
            List<Train> trains = new ArrayList<>();
            for (int i = 0; i < n; i++) {
                trains.add(Train.parseTrain(reader.readLine()));
            }
            Solution solution = new OptimizedSolver().solve(trains);
            System.out.println(solution);
        } catch (IOException e) {
            System.out.println("IOException occurred while reading input data.");
        }
    }
}
