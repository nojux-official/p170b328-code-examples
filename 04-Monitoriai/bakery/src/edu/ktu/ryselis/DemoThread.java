package edu.ktu.ryselis;

public class DemoThread extends Thread {
    private Data data;
    private int id;
    private Locker locker;

    DemoThread(Data d, int id, Locker locker){
        this.data = d;
        this.id = id;
        this.locker = locker;
    }

    @Override
    public void run() {
        for (int i = 0; i < 15; i++) {
            locker.setChoosing(id);
            locker.setTicket(id);
            locker.unsetChoosing(id);
            locker.wait(id);
            int counter = data.getCounter();
            counter++;
            data.setCounter(counter);
            locker.unsetTicket(id);
        }
    }
}
