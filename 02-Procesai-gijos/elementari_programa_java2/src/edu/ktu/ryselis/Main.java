package edu.ktu.ryselis;

public class Main {

    public static void main(String[] args) {
        Thread thread1 = new Thread(new DemoRunnable("Pirma"));
        Thread thread2 = new Thread(new DemoRunnable("Antra"));
        thread1.start();
        thread2.start();
        try {
            thread1.join();
            thread2.join();
        } catch (InterruptedException e) {
            System.out.println("Thread was interrupted");
        }
    }
}
