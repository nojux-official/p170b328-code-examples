package edu.ktu.ryselis;

public class Decreaser implements Runnable {
    private SimpleBoundedCounter counter;

    Decreaser(SimpleBoundedCounter counter) {
        this.counter = counter;
    }

    /**
     * Calls counter.decrease 50 times
     */
    @Override
    public void run() {
        for (var i = 0; i < 50; i++) {
            try {
                counter.decrease();
            } catch (InterruptedException e) {
                System.out.println("failed to increase");
            }
        }
    }
}
