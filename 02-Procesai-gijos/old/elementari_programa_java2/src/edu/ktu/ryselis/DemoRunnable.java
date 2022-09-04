package edu.ktu.ryselis;

public class DemoRunnable implements Runnable {
    private final String name;

    DemoRunnable(String name){
        this.name = name;
    }

    @Override
    public void run() {
        System.out.println(name + ": one");
        System.out.println(name + ": two");
        System.out.println(name + ": three");
    }
}
