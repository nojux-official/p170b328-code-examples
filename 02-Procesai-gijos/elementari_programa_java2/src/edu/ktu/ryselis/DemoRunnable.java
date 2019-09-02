package edu.ktu.ryselis;

public class DemoRunnable implements Runnable {
    private String name;

    DemoRunnable(String name){
        this.name = name;
    }

    @Override
    public void run() {
        System.out.println(this.name + ": one");
        System.out.println(this.name + ": two");
        System.out.println(this.name + ": three");
    }
}
