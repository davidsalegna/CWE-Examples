import java.util.Random;

public class RandomGenerator {
    private int arraySize = 10;
    // CWE-582: This array is declared private, making its contents safe from being modified outside this class.
    // CWE-607: This array is a mutable object and is declared private, protecting its contents.
    private int[] numArray = new int[arraySize];

    // CWE-230: As a minimum value is missing, default is set as 0
    // CWE-233: Functions are checked to ensure proper handling of parameters
    public int generateRandom(int max) {
        Random rand = new Random();
        int min = 0;
        int num = rand.nextInt(max - min + 1) + min;
        System.out.println("Random integer between " + min + " and " + max + ": " + num);
        return num;
    }

    public int generateRandom(int min, int max) {
        Random rand = new Random();
        int num = rand.nextInt(max - min + 1) + min;
        System.out.println("Random integer between " + min + " and " + max + ": " + num);
        return num;
    }

    public int generateRandom() {
        Random rand = new Random();
        int min = 0;
        int max = 10;
        int num = rand.nextInt(max - min + 1) + min;
        System.out.println("Random integer between " + min + " and " + max + ": " + num);
        return num;
    }

    public int[] generateRandomArray()
    {
        // CWE-193: This loop is not off-by-one as the indexes of an array start at 0 and end one less than its size.
        for (int x = 0; x < arraySize; x++)
        {
            numArray[x] = generateRandom();
        }
        return numArray;
    }

    // CWE-583: finalize() is declared protected rather than public.
    // CWE-586: There is no explicit call to finalize() in the code.
    protected void finalize()
    {
        System.out.println("RandomGenerator's finalize() method was called.");
    }

    public static void main(String[] args) {
        int[] testArray = new int[10];
        int[] tempArray;
        RandomGenerator demo = new RandomGenerator();

        // Call the generateRandom() method with different arguments
        demo.generateRandom();
        demo.generateRandom(10);
        demo.generateRandom(5, 15);

        // Generate a random array of numbers, copy them to another array, and show the results.
        tempArray = demo.generateRandomArray();
        for (int a = 0; a < testArray.length && a < tempArray.length; a++)
        {
            testArray[a] = tempArray[a];
            System.out.println("Number at index " + a + ": " + testArray[a]);
        }
    }
}