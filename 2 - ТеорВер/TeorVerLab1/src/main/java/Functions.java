import java.util.*;

public class Functions {
    double[] values;
    Vector<Double> x_i = new Vector<>();
    Vector<Integer> n_i = new Vector<>();
    Vector<Double> p_i = new Vector<>();

    public Functions(double[] values) {
        this.values = values;
    }

    public void getVarValues() {
        Arrays.sort(this.values);
        System.out.println(">>> Вариационный ряд <<<\n" + Arrays.toString(values) + "\n");
    }

    public void minMaxValues() {
        System.out.println(">>> Экстремальные значения <<<\nMIN = " + values[0] + "\nMAX = " + values[values.length - 1] + "\n");
    }

    public void selectionSize() {
        System.out.println(">>> Размах выборки <<<\n" + (values[values.length - 1] - values[0]) + "\n");
    }

    public void disperancyCalculation() {
        Arrays.stream(values).distinct().forEach(x -> {
            int count = 0;
            x_i.add(x);
            for (double element : values)
                if (element == x) {
                    count++;
                }

            n_i.add(count);
            p_i.add(((double) count / (double) values.length));
        });

        double expectedValue = 0;
        for (int i = 0; i < x_i.size(); i++)
            expectedValue += x_i.get(i) * p_i.get(i);

        System.out.printf(">>> Оценка математического ожидания <<<\n%.2f\n\n", expectedValue);

        double disperancy = 0;
        for (int i = 0; i < x_i.size(); i++)
            disperancy += Math.pow((x_i.get(i) - expectedValue), 2) * n_i.get(i);

        disperancy *= 1.0 / values.length;

        System.out.printf(">>> Дисперсия <<<\n%.2f\n\n", disperancy);
        System.out.printf(">>> Cреднеквадратическое отклонение <<<\n%.2f\n\n", Math.sqrt(disperancy));
    }

    public double getH() {
        return (values[values.length - 1] - values[0]) / (1 + ((Math.log(values.length) / Math.log(2))));
    }

    public int getM() {
        return (int) Math.ceil(1 + (Math.log(values.length) / Math.log(2)));
    }

    public void calculateEmpiricFunction() {
        double h = p_i.get(0);

        System.out.println("\t\t\t>>> Функция <<<");
        System.out.printf("\t\t\tx\t<=\t%.2f\t->\t%.2f\n", x_i.get(0), 0.0);
        for (int i = 0; i < x_i.size() - 1; i++) {
            System.out.printf("%.2f\t<\tx\t<=\t%.2f\t->\t%.2f\n", x_i.get(i), x_i.get(i + 1), h);
            h += p_i.get(i + 1);
        }
        System.out.printf("%.2f\t<\tx\t\t\t\t->\t%.2f\n", x_i.get(x_i.size() - 1), h);
    }

    public void drawEmpiricFunction() {
        DrawChart drawChart = new DrawChart("x", "f(X)", "Эмпирическая функция");

        double h = p_i.get(0);
        drawChart.addChart("x <= " + x_i.get(0), x_i.get(0) - 0.5, x_i.get(0), 0);
        for (int i = 0; i < x_i.size() - 1; i++) {
            drawChart.addChart(x_i.get(i) + " < x <= " + x_i.get(i + 1), x_i.get(i), x_i.get(i + 1), h);
            h += p_i.get(i + 1);
        }
        drawChart.addChart(x_i.get(x_i.size() - 1) + " < x", x_i.get(x_i.size() - 1), x_i.get(x_i.size() - 1) + 1, h);
        drawChart.plot("EmpiricFunc");
    }

    public void drawFrequencyPolygon() {
        DrawChart frequencyPolygon = new DrawChart("x", "p_i", "Полигон частот");

        double x_start = values[0] - getH() / 2;
        for (int i = 0; i < getM(); i++) {
            int count = 0;
            for (double value : values)
                if (value >= x_start && value < (x_start + getH()))
                    count++;

            frequencyPolygon.PolygonalChart(x_start + getH() / 2, (double) count / (double) values.length);
            System.out.println("[ " + x_start + " : " + (x_start+getH()) + " ) -> " + (double) count / (double) values.length);

            x_start += getH();
        }
        frequencyPolygon.plotPolygon("FrequencyPolygon");
    }

    public void drawHistogram(int size) {
        DrawChart Histogram = new DrawChart("x", "p_i / h", "Гистограмма частот");
        double x_start = values[0] - getH() / 2;
        for (int i = 0; i < getM(); i++) {
            int s = 0;
            for (double value : values)
                if (value >= x_start && value < (x_start + getH())) {
                    s++;
                }

            Histogram.addHistogram(x_start + " : " + x_start + getH(), x_start, x_start + getH(),
                    ((double) s / (double) size) / getH());
            x_start += getH();
        }
        Histogram.plot("Histogram");
    }

    public void printVectors() {
        for (int i = 0; i < x_i.size(); i++) {
            System.out.println(x_i.get(i) + " " + n_i.get(i) + " " + p_i.get(i));
        }
    }
}