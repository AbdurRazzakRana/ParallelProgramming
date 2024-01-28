import java.io.File;
import java.io.FileNotFoundException;
import java.util.*;
import java.util.concurrent.*;

public class EvaluatePerformanceJavaThreads implements Runnable {
    private static int ARRAY_LENGTH = 1000000;
    private static int MAX_THREADS=10;
    private static final int MAX_RANGE = 5;
    private static final Random random = new Random();
    private static int count = 0;
    private static Object lock=new Object();
    private static int[] array;
    private static Thread[] t;

    public static void main(String[] args) {
        if (args.length != 0){
            // fetching the argument values for thread number and array size
            MAX_THREADS = Integer.parseInt(args[0]);
            ARRAY_LENGTH = Integer.parseInt(args[1]);
        }
        // start counting time
        long startTime = System.currentTimeMillis();

        // initializing variables
        array = new int[ARRAY_LENGTH];
        t = new Thread[MAX_THREADS];

        int i=0;
        int actualCount=0;
        try {
            // accessing the input file to read the values
            File file = new File("input.txt");
            Scanner scanner = new Scanner(file);

            // Read input from the file using the Scanner
            while (scanner.hasNextInt()) {
                int number = scanner.nextInt();
                if(number == 3) actualCount++;
                array[i] = number;
                i++;
            }

            // Close the Scanner
            scanner.close();
        } catch (FileNotFoundException e) {
            // Handle the case where the file is not found
            e.printStackTrace();
        }

        // creating the threads
        EvaluatePerformanceJavaThreads[] counters = new EvaluatePerformanceJavaThreads[MAX_THREADS];
        int lengthPerThread = ARRAY_LENGTH / MAX_THREADS;
        for (i = 0; i < counters.length; i++) {
            counters[i] = new EvaluatePerformanceJavaThreads(i * lengthPerThread,
                    lengthPerThread);
        }
        // run the threads
        for (i = 0; i < counters.length; i++) {
            t[i] = new Thread(counters[i]);
            t[i].start();
        }
        // wait for all child threads to finish and join
        for (i = 0; i < counters.length; i++) {
            try {
                t[i].join();
            } catch (InterruptedException e) {
                /* do nothing */ }
        }
        int notTakenCareIndex;
        int localCount = 0;
        if (ARRAY_LENGTH % MAX_THREADS != 0){
            notTakenCareIndex = (ARRAY_LENGTH / MAX_THREADS) * MAX_THREADS;
            while(notTakenCareIndex < ARRAY_LENGTH) {
                if(array[notTakenCareIndex] == 3){
                    localCount++;
                }
                notTakenCareIndex++;
            }
            count += localCount;
        }

        // end time and calculating the runtime
        long endTime = System.currentTimeMillis();
        System.out.println("Number of threes in Serial Count: "+actualCount);
        System.out.println("Number of threes in Java Threads: "+count);
        System.out.println("Parallel counting time: "+ String.valueOf(endTime-startTime)+" ms");
    }

    private int startlndex;
    private int elements;
    private int myCount=0;

    public EvaluatePerformanceJavaThreads(int start, int elem) {
        startlndex=start;
        elements=elem;
    }
    //Overload of run method in the Thread class
    public void run() {
        //count the number of threes
        for(int i=0; i<elements; i++) {
            if(array[startlndex+i]==3) {
                myCount++;
            }
        }
        //implementing cricital code section with synchronization
        synchronized(lock) {
            count+=myCount;
        }
    }
}