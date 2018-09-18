package edu.ktu.ryselis;

public class Decreaser implements Runnable {
    private SimpleBoundedCounter counter;

    Decreaser(SimpleBoundedCounter counter) {
        this.counter = counter;
    }

    @Override
    public void run() {
        for (int i = 0; i < 50; i++) {
            try {
                counter.decrease();
            } catch (InterruptedException e) {
                System.out.println("failed to increase");
            }
        }
    }
}
