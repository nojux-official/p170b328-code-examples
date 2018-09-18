package edu.ktu.ryselis;

class SimpleBoundedCounter {
    private final long MIN = 0;
    private final long MAX = 50;
    private long count = MIN;

    synchronized void increase() throws InterruptedException {
        awaitUnderMax();
        setCount(count + 1);
    }

    synchronized void decrease() throws InterruptedException {
        awaitOverMin();
        setCount(count - 1);
    }

    private void setCount(long newValue){
        count = newValue;
        notifyAll();
    }

    private void awaitUnderMax() throws InterruptedException {
        while (count == MAX) {
            wait();
        }
    }

    private void awaitOverMin() throws InterruptedException {
        while (count == MIN) {
            wait();
        }
    }

    long getCount(){
        return count;
    }
}
