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
        System.out.println(this.getName() + ": one");
        System.out.println(this.getName() + ": two");
        System.out.println(this.getName() + ": three");
    }
}
