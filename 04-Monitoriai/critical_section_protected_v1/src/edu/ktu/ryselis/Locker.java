package edu.ktu.ryselis;

class Locker {
    private int lockedBy = -1;

    void lock(int threadId) {
        lockedBy = threadId;
    }

    void unlock() {
        lockedBy = -1;
    }

    boolean isLocked() {
        return lockedBy > -1;
    }
}
