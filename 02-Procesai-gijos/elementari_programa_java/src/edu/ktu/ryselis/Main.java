package edu.ktu.ryselis;

public class Main {

    public static void main(String[] args) {
        DemoThread thread1 = new DemoThread("Pirma");
        DemoThread thread2 = new DemoThread("Antra");
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
