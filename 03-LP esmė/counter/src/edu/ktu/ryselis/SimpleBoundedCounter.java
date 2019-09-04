package edu.ktu.ryselis;

class SimpleBoundedCounter {
    private final long MIN = 0;
    private final long MAX = 50;
    private long count = MIN;

    /**
     * Waits until count is less than MAX and increases it
     * @throws InterruptedException because call to wait() throws it
     */
    synchronized void increase() throws InterruptedException {
        while (count == MAX) {
            // if count is already MAX, thread should be blocked until count changes. We are going
            // to use notifyAll to wake all threads, so we don't know if our thread is woken first
            // or not. This means that the thread might be woken when count is MAX again, so we
            // put this call inside a while loop
            wait();
        }
        // count is guaranteed to be less than MAX here, so increase it
        setCount(count + 1);
    }

    /**
     * Waits until count is more than MIN and increases it. Works the same way as increase.
     * @throws InterruptedException because call to wait() throws it
     */
    synchronized void decrease() throws InterruptedException {
        while (count == MIN) {
            wait();
        }
        setCount(count - 1);
    }

    /**
     * Sets counter value
     * @param newValue a value to set
     */
    private void setCount(long newValue){
        count = newValue;
        // count value have changed - if there are threads that called wait(), they should wake up
        // because they may now continue
        notifyAll();
    }

    /**
     * Gets current value of count
     * @return current value of count
     */
    long getCount(){
        return count;
    }
}
