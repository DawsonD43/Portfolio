/*
 * Dawson Dauphinais
 * CS425 Operating Systems
 * Date Last Modified: 08/28/2020
 *
 * The purpose of this program is to implement the collatz conjecture using multiple threads to make it faster.
 */

class CollatzFinal {
    public static void main(final String[] args) {
        int finalLongestLength = 0;
        long finalLargestVal = 0;
        int[] prev = new int[1000000];
        Object[] locks = new Object[1000000];
        for(int i = 0; i < locks.length; i++){
            locks[i] = new Object();
        }
        int size = 4;
        int h = 250000;
        int l = 1;
        final MyThread[] threads = new MyThread[size];
        for (int i = 0; i < size; i++) {
            threads[i] = new MyThread(l, h, prev, locks);
            threads[i].start();
            l += 250000;
            h += 250000;
        }
        try {
            for (int i = 0; i < size; i++) {
                threads[i].join();
                if (threads[i].longestLength > finalLongestLength) {
                    finalLongestLength = threads[i].longestLength;
                    finalLargestVal = threads[i].highestVal;
                }
            }
        } catch (final InterruptedException e) {
        }
        System.out.println("Longest Sequence : " + finalLongestLength);
        System.out.println("The Largest Sequence Is: " + finalLongestLength + " Found at the Number: " + finalLargestVal); // find and print the largest value
    }
}

class MyThread extends Thread {
    int low;
    int high;
    int[] prev;
    Object[] locks;
    long highestVal;
    long collatzNum;
    int longestLength = 0;
    int temp;
    int count;

    public MyThread(int l, int h, int[] p, Object[] o) {
        low = l;
        high = h;
        prev = p;
        locks = o;
    }

    @Override
    public synchronized void run() {
        for (int currentNum = low; currentNum < high; currentNum++) {
            // keeping track of the new length
            // and compare it to the previous length
            collatzNum = currentNum;
            count = 0;
            while (collatzNum > 1) {
                // check if prev array has n val
                // add val from prev array and exit loop
                // save current num and step count
                if (collatzNum < prev.length && prev[(int) collatzNum] != 0) { // Ben Basten helped me with these three
                    // lines
                    count += prev[(int) collatzNum];
                    collatzNum = 1;
                } else if (collatzNum % 2 == 0) {
                    collatzNum = collatzNum / 2;
                    count++;
                } else {
                    collatzNum = (3 * collatzNum) + 1;
                    count++;
                }

            }
            temp = (int) collatzNum;
            synchronized (locks[currentNum]) {
                prev[currentNum] = count;
            }
            if (count > longestLength) {
                longestLength = count;
                highestVal = currentNum;
            }
        }
    }
}