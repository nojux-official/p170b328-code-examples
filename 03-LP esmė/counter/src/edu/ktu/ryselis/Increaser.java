package edu.ktu.ryselis;

public class Increaser implements Runnable {
    private SimpleBoundedCounter counter;

    Increaser(SimpleBoundedCounter counter) {
        this.counter = counter;
    }

    /**
     * Calls counter.increase 50 times
     */
    @Override
    public void run() {
        for (var i = 0; i < 50; i++) {
            try {
                counter.increase();
            } catch (InterruptedException e) {
                System.out.println("failed to increase");
            }
        }
    }
}
