import javax.swing.*;
import java.awt.*;
import java.util.ArrayList;
import java.util.List;


public class Mandelbrot_set {
    public static void main(String[] args) {

        List<ComplexNumber> mySet = mandelSet();
        for(ComplexNumber z : mySet){
            System.out.println(z);
        }

        JFrame frame = new JFrame("Mandelbrot Set");
        MyJPanel myJPanel = new MyJPanel();

        frame.add(myJPanel);

        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.setPreferredSize(new Dimension(800, 800));
        frame.setResizable(true);
        frame.pack();
        frame.setLocationRelativeTo(null);
        frame.setVisible(true);

    }
    public static ComplexNumber addComplexNumbers(ComplexNumber z1, ComplexNumber z2){

        double real = z1.getReal() + z2.getReal();
        double imaginary = z1.getImaginary() + z2.getImaginary();
        ComplexNumber z3 = new ComplexNumber(real, imaginary);
        return z3;
    }
    public static ComplexNumber subComplexNumbers(ComplexNumber z1, ComplexNumber z2){

        double real = z1.getReal() - z2.getReal();
        double imaginary = z1.getImaginary() - z2.getImaginary();
        ComplexNumber z3 = new ComplexNumber(real, imaginary);
        return z3;
    }
    public static ComplexNumber mulComplexNumbers(ComplexNumber z1, ComplexNumber z2){

        double real = (z1.getReal() * z2.getReal()) - (z1.getImaginary() * z2.getImaginary());
        double imaginary = (z1.getReal() * z2.getImaginary()) + (z1.getImaginary() * z2.getReal());
        ComplexNumber z3 = new ComplexNumber(real ,imaginary);
        return z3;
    }

    public static ComplexNumber squareComplexNumbers(ComplexNumber z){

        return mulComplexNumbers(z,z);
    }

    public static double squareRootComplexNumbers(ComplexNumber z){

        double value = (z.getReal() * z.getReal()) + (z.getImaginary() * z.getImaginary());
        return Math.sqrt(value);
    }


    public static List<ComplexNumber> mandelSet(){

        List<ComplexNumber> mandelSet = new ArrayList<ComplexNumber>();
        double realMin = -2;
        double realMax = 1;
        double imaginaryMin = -1.5;
        double imaginaryMax = 1.5;
        int maxIter = 200;
        double step = 0.05;

        for(double real = realMin; real <= realMax; real+=step){
            for(double imaginary = imaginaryMin; imaginary <= imaginaryMax; imaginary += step){
                ComplexNumber c = new ComplexNumber(real, imaginary);
                if(isInMandelSet(c, maxIter)){
                    mandelSet.add(c);
                }
            }
        }
        return mandelSet;
    }

    public static boolean isInMandelSet(ComplexNumber c, int maxIter){

        ComplexNumber z0 = new ComplexNumber(0,0);
        List<ComplexNumber> myMangelSet = new ArrayList<ComplexNumber>();
        myMangelSet.add(z0);

        for(int i = 1; i < maxIter; ++i){
            ComplexNumber nextIteCompelxNumber = addComplexNumbers(squareComplexNumbers(myMangelSet.get(i - 1)), c);
            myMangelSet.add(i, nextIteCompelxNumber);
            if(squareRootComplexNumbers(myMangelSet.get(i)) > 2){
                return false;
            }
        }
        return true;
    }

    public static int calcualteIterationsToLeftTheBound(ComplexNumber c, int maxIter){

        ComplexNumber z0 = new ComplexNumber(0,0);
        List<ComplexNumber> myMangelSet = new ArrayList<ComplexNumber>();
        myMangelSet.add(z0);
        int counter = 0;

        for(int i = 1; i < maxIter; ++i){
            ComplexNumber nextIteCompelxNumber = addComplexNumbers(squareComplexNumbers(myMangelSet.get(i - 1)), c);
            myMangelSet.add(i, nextIteCompelxNumber);
            if(squareRootComplexNumbers(myMangelSet.get(i)) > 2){
                return counter;
            }
            else{
                ++counter;
            }
        }
        return counter;
    }
}

class MyJPanel extends JPanel{

    @Override
    public void paintComponent(Graphics g) {
        super.paintComponent(g);

        double realMin = -2;
        double realMax = 1;
        double imaginaryMin = -1.5;
        double imaginaryMax = 1.5;
        int maxIter = 200;

        for(int x = 0; x < getWidth(); ++x){
            for(int y = 0; y < getHeight(); ++y){
                double real = realMin + x * (realMax - realMin) / getWidth();
                double imaginary = imaginaryMin + y * (imaginaryMax - imaginaryMin) / getHeight();
                ComplexNumber c = new ComplexNumber(real, imaginary);
                int numberIterations = Mandelbrot_set.calcualteIterationsToLeftTheBound(c, maxIter);

                float hue = numberIterations / (float) maxIter;
                boolean inSet = numberIterations < maxIter;
                if(numberIterations == maxIter){
                    g.setColor(Color.BLACK);

                }
                else{
                    g.setColor(Color.getHSBColor(hue, 1f, 1f));

                }
                g.fillRect(x,y,1,1);

            }
        }
    }
}

class ComplexNumber{

    private double real;
    private double imaginary;

    public ComplexNumber(double real, double imaginary){
        this.real = real;
        this.imaginary = imaginary;
    }

    @Override
    public String toString(){
        return real + " " + imaginary + "i";
    }

    void setAUndB(double real, double imaginary){
        this.real = real;
        this.imaginary = imaginary;
    }

    public double getReal(){
        return real;
    }

    public double getImaginary(){
        return imaginary;
    }
}

