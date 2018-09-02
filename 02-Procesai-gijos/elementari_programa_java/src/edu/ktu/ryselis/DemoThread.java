package edu.ktu.ryselis;

public class DemoThread extends Thread{
    DemoThread(String name){
        super(name);
    }

    @Override
    public void run() {
        System.out.print(this.getName() + ": ");
        System.out.print("vienas ");
        System.out.print("du ");
        System.out.println("trys ");
    }
}
