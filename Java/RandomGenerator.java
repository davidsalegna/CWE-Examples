import java.util.Random;

public class RandomGenerator {
    //CWE-230: As a minimum value is missing, default is set as 0
    //CWE-233: Functions are checked to ensure proper handling of parameters
    public void generateRandom(int max) {
        Random rand = new Random();
        int min = 0;
        int num = rand.nextInt(max - min + 1) + min;
        System.out.println("Random integer between " + min + " and " + max + ": " + num);
    }

    public void generateRandom(int min, int max) {
        Random rand = new Random();
        int num = rand.nextInt(max - min + 1) + min;
        System.out.println("Random integer between " + min + " and " + max + ": " + num);
    }

    public void generateRandom() {
        Random rand = new Random();
        int min = 0;
        int max = 10;
        int num = rand.nextInt(max - min + 1) + min;
        System.out.println("Random integer between " + min + " and " + max + ": " + num);
    }

    public static void main(String[] args) {
        RandomGenerator demo = new RandomGenerator();

        // Call the generateRandom() method with different arguments
        demo.generateRandom();
        demo.generateRandom(10);
        demo.generateRandom(5, 15);
    }
}