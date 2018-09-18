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
        int turnNumber = 1 - id;
        for (int i = 0; i < 15; i++) {
            locker.setFlag(id);
            locker.setTurn(turnNumber);
            while (locker.flagIsSet(turnNumber) && locker.getTurn() == turnNumber) {}
            int counter = data.getCounter();
            counter++;
            data.setCounter(counter);
            locker.resetFlag(id);
        }
    }
}
