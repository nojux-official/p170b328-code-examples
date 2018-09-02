package edu.ktu.ryselis;

public class DemoRunnable implements Runnable {
    private String name;

    DemoRunnable(String name){
        this.name = name;
    }

    @Override
    public void run() {
        System.out.print(this.name + ": ");
        System.out.print("vienas ");
        System.out.print("du ");
        System.out.println("trys ");
    }
}
