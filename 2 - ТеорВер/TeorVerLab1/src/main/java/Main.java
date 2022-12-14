import java.io.FileNotFoundException;
import java.io.FileReader;
import java.util.Scanner;

public class Main {
    public static void main(String[] args) throws FileNotFoundException {
        FileReader fileReader = new FileReader("src/main/resources/input");
        Scanner scanner = new Scanner(fileReader);
        int n = 20;
        double[] elements = new double[n];

        for (int i = 0; i < n; i++)
            elements[i] = scanner.nextDouble();

        Functions functions = new Functions(elements);
        functions.getVarValues();
        functions.minMaxValues();
        functions.selectionSize();
        functions.disperancyCalculation();

        functions.calculateEmpiricFunction();
        functions.drawEmpiricFunction();

        functions.drawFrequencyPolygon();

        functions.drawHistogram(elements.length);

        functions.printVectors();
    }
}