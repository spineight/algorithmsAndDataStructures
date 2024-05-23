package ru.covariance.jbintern;

/**
 * Class that stores immutable information about train
 */
public class Train {
    private final int ID;
    private final double arrival;
    private final double unloading;
    private final double payment;

    /**
     * Constructs a train with a given ID, arrival time, unloading time and a payment amount
     * @param ID ID of a train
     * @param arrival Arrival time of a train
     * @param unloading Unloading time of a train
     * @param payment Payment amount for unloading of train
     */
    public Train(int ID, double arrival, double unloading, double payment) {
        this.ID = ID;
        this.arrival = arrival;
        this.unloading = unloading;
        this.payment = payment;
    }

    /**
     * Gets an ID of train
     * @return ID of a train
     */
    public int getID() {
        return ID;
    }

    /**
     * Gets an arrival time of a train
     * @return Arrival time of a train
     */
    public double getArrival() {
        return arrival;
    }

    /**
     * Gets an unloading end time of a train
     * @return Unloading end time of a train
     */
    public double getUnloadingEnd() {
        return arrival + unloading;
    }

    /**
     * Gets a payment amount of a train
     * @return Payment amount of a train
     */
    public double getPayment() {
        return payment;
    }

    /**
     * Returns new Train, constructed from the given string input
     * @param input String representation of a train
     * @return New train constructed from given string
     * @throws ClassFormatError if string is not formatted as a string Train representation
     * @throws NumberFormatException if any of numbers in string representation
     * does not match corresponding number pattern
     */
    public static Train parseTrain(String input) throws ClassFormatError, NumberFormatException {
        String[] splitInput = input.split(" ");
        if (splitInput.length != 4) {
            throw new ClassFormatError("Cannot parse train: " + input);
        }
        return new Train(Integer.parseInt(splitInput[0]),
                Double.parseDouble(splitInput[1]),
                Double.parseDouble(splitInput[2]),
                Double.parseDouble(splitInput[3]));
    }

    @Override
    public String toString() {
        return ID + " " + arrival + " " + unloading + " " + payment;
    }
}
