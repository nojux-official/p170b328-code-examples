package edu.ktu.ryselis;

public class DemoThread extends Thread {
    private Data data;

    DemoThread(Data d){
        data = d;
    }

    @Override
    public void run() {
        for (int i = 0; i < 15; i++) {
            int counter = data.getCounter();
            counter++;
            data.setCounter(counter);
        }
    }
}
