package edu.ktu.ryselis;

public class DemoThread extends Thread{
    DemoThread(String name){
        super(name);
    }

    /**
     * Writes some simple output to console
     */
    @Override
    public void run() {
        System.out.println(getName() + ": one");
        System.out.println(getName() + ": two");
        System.out.println(getName() + ": three");
    }
}
