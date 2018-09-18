package edu.ktu.ryselis;

class LimitedBuffer {
    private int bufferSize;
    private int[] buffer;
    private int from;
    private int to;
    private int currentSize;

    LimitedBuffer(int bufferSize){
        this.bufferSize = bufferSize;
        buffer = new int[this.bufferSize];
        from = 0;
        to = 0;
        currentSize = 0;
    }

    synchronized void insert(int item){
        while (currentSize == bufferSize) {
            try {
                wait();
            } catch (InterruptedException e) {
                System.out.println("failed to insert");
            }
        }
        buffer[to] = item;
        to = (to + 1) % bufferSize;
        currentSize++;
        notifyAll();
    }

    synchronized int remove() {
        while (currentSize == 0) {
            try {
                wait();
            } catch (InterruptedException e) {
                System.out.println("failed to remove");
            }
        }
        int item = buffer[from];
        buffer[from] = Integer.MIN_VALUE;
        from = (from + 1) % bufferSize;
        currentSize--;
        notifyAll();
        return item;
    }
}
