package edu.ktu.ryselis;

class Locker {
    private boolean[] flag = {false, false};
    private int turn;

    void setFlag(int i) {
        flag[i] = true;
    }

    void resetFlag(int i) {
        flag[i] = false;
    }

    int getTurn() {
        return turn;
    }

    void setTurn(int turn) {
        this.turn = turn;
    }

    boolean flagIsSet(int i) {
        return flag[i];
    }
}
