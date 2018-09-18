package edu.ktu.ryselis;

import java.util.Arrays;

class Locker {
    private volatile boolean[] choosing;
    private volatile int[] ticket;

    Locker(int threadCount) {
        choosing = new boolean[threadCount];
        ticket = new int[threadCount];
        for (int i = 0; i < threadCount; i++){
            choosing[i] = false;
            ticket[i] = 0;
        }
    }

    void setChoosing(int k) {
        choosing[k] = true;
    }

    void unsetChoosing(int k) {
        choosing[k] = false;
    }

    void setTicket(int k) {
        ticket[k] =  Arrays.stream(ticket).max().getAsInt() + 1;
    }

    void unsetTicket(int k){
        ticket[k] = 0;
    }

    void wait(int k){
        for (int i = 0; i < choosing.length; i++) {
            if (i == k) {
                continue;
            }
            while (choosing[i]) ;
            while (ticket[i] != 0 && ( ticket[k] > ticket[i]  ||
                    (ticket[k] == ticket[i] && k > i))) {}
        }
    }


}
