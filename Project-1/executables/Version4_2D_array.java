package executables;

import java.util.Scanner;
import java.util.Random;
import java.io.File;
import java.io.FileNotFoundException;

class Matrix {
    private float[][] data;
    private int rows, cols;

    // Initialize matrix
    public Matrix(int rows, int cols) {
        this.rows = rows;
        this.cols = cols;
        this.data = new float[rows][cols];
    }

    // Method to input matrix data manually
    public void inputMatrix(Scanner sc) {
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                System.out.print("Element [" + (i + 1) + "][" + (j + 1) + "]: ");
                data[i][j] = sc.nextFloat();
            }
        }
    }

    // Method to generate matrix randomly
    public void randomMatrix() {
        Random rand = new Random();
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                data[i][j] = rand.nextFloat() * 100;
            }
        }
    }

    // Method to read matrix data from a file
    public void readFromFile(String filename) throws FileNotFoundException {
        Scanner fileScanner = new Scanner(new File(filename));
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                if (fileScanner.hasNextFloat()) {
                    data[i][j] = fileScanner.nextFloat();
                }
            }
        }
        fileScanner.close();
    }

    // Method to add two matrices
    public Matrix add(Matrix other) throws IllegalArgumentException {
        if (this.rows != other.rows || this.cols != other.cols) {
            throw new IllegalArgumentException("Matrix dimensions must match for addition.");
        }
        Matrix result = new Matrix(rows, cols);
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                result.data[i][j] = this.data[i][j] + other.data[i][j];
            }
        }
        return result;
    }

    // Method to subtract two matrices
    public Matrix subtract(Matrix other) throws IllegalArgumentException {
        if (this.rows != other.rows || this.cols != other.cols) {
            throw new IllegalArgumentException("Matrix dimensions must match for subtraction.");
        }
        Matrix result = new Matrix(rows, cols);
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                result.data[i][j] = this.data[i][j] - other.data[i][j];
            }
        }
        return result;
    }

    // Method to multiply two matrices
    public Matrix multiply(Matrix other) throws IllegalArgumentException {
        if (this.cols != other.rows) {
            throw new IllegalArgumentException("Matrix 1 columns must equal Matrix 2 rows for multiplication.");
        }
        Matrix result = new Matrix(this.rows, other.cols);
        for (int i = 0; i < this.rows; i++) {
            for (int j = 0; j < other.cols; j++) {
                result.data[i][j] = 0;
                for (int k = 0; k < this.cols; k++) {
                    result.data[i][j] += this.data[i][k] * other.data[k][j];
                }
            }
        }
        return result;
    }

    // Method to display matrix
    public void printMatrix() {
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                System.out.printf("%.2f ", data[i][j]);
            }
            System.out.println();
        }
    }

    // Method to multiply matrices X times and show average time taken
    public static void multiplyMatricesMultipleTimes(Matrix mat1, Matrix mat2, int repetitions) {
        long totalTime = 0;
        for (int i = 0; i < repetitions; i++) {
            long startTime = System.nanoTime();
            mat1.multiply(mat2);
            long endTime = System.nanoTime();
            totalTime += (endTime - startTime);
        }

        long averageTime = totalTime / repetitions;
        System.out.println("Average time for " + repetitions + " multiplications: (Version 4)" + averageTime + " nanoseconds");
    }
}

public class Version4_2D_array {

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        Matrix mat1 = null, mat2 = null;
        int choice;
        int rows1, cols1, rows2, cols2;

        while (true) {
            displayMenu();
            choice = sc.nextInt();

            switch (choice) {
                case 1: // Input matrices manually
                    System.out.print("Enter rows and columns for Matrix 1: ");
                    rows1 = sc.nextInt();
                    cols1 = sc.nextInt();
                    mat1 = new Matrix(rows1, cols1);
                    System.out.println("Enter elements for Matrix 1:");
                    mat1.inputMatrix(sc);

                    System.out.print("Enter rows and columns for Matrix 2: ");
                    rows2 = sc.nextInt();
                    cols2 = sc.nextInt();
                    mat2 = new Matrix(rows2, cols2);
                    System.out.println("Enter elements for Matrix 2:");
                    mat2.inputMatrix(sc);
                    break;

                case 2: // Generate matrices randomly
                    System.out.print("Enter rows and columns for Matrix 1: ");
                    rows1 = sc.nextInt();
                    cols1 = sc.nextInt();
                    mat1 = new Matrix(rows1, cols1);
                    mat1.randomMatrix();

                    System.out.print("Enter rows and columns for Matrix 2: ");
                    rows2 = sc.nextInt();
                    cols2 = sc.nextInt();
                    mat2 = new Matrix(rows2, cols2);
                    mat2.randomMatrix();
                    break;

                case 3: // Read matrices from file
                    System.out.print("Enter rows and columns for Matrix 1: ");
                    rows1 = sc.nextInt();
                    cols1 = sc.nextInt();
                    mat1 = new Matrix(rows1, cols1);
                    System.out.print("Enter filename for Matrix 1: ");
                    String file1 = sc.next();
                    try {
                        mat1.readFromFile(file1);
                    } catch (FileNotFoundException e) {
                        System.out.println("Error: File not found.");
                        break;
                    }

                    System.out.print("Enter rows and columns for Matrix 2: ");
                    rows2 = sc.nextInt();
                    cols2 = sc.nextInt();
                    mat2 = new Matrix(rows2, cols2);
                    System.out.print("Enter filename for Matrix 2: ");
                    String file2 = sc.next();
                    try {
                        mat2.readFromFile(file2);
                    } catch (FileNotFoundException e) {
                        System.out.println("Error: File not found.");
                        break;
                    }
                    break;

                case 4: // Add matrices
                    try {
                        Matrix resultAdd = mat1.add(mat2);
                        System.out.println("Result of Matrix 1 + Matrix 2:");
                        resultAdd.printMatrix();
                    } catch (IllegalArgumentException e) {
                        System.out.println(e.getMessage());
                    }
                    break;

                case 5: // Subtract matrices
                    try {
                        Matrix resultSub = mat1.subtract(mat2);
                        System.out.println("Result of Matrix 1 - Matrix 2:");
                        resultSub.printMatrix();
                    } catch (IllegalArgumentException e) {
                        System.out.println(e.getMessage());
                    }
                    break;

                case 6: // Multiply matrices
                    try {
                        long startTime = System.nanoTime();
                        Matrix resultMul = mat1.multiply(mat2);
                        long endTime = System.nanoTime();
                        long duration = endTime - startTime;
                
                        System.out.println("Result of Matrix 1 * Matrix 2:");
                        resultMul.printMatrix();
                        System.out.println("Time taken for multiplication (Version 4): " + duration + " nanoseconds");
                    } catch (IllegalArgumentException e) {
                        System.out.println(e.getMessage());
                    }
                    break;
                
                case 7: // View both matrices
                    System.out.println("Matrix 1:");
                    mat1.printMatrix();
                    System.out.println("Matrix 2:");
                    mat2.printMatrix();
                    break;

                case 8: // Multiply matrices X times and show average time
                    if (mat1 != null && mat2 != null) {
                        System.out.print("Enter number of repetitions: ");
                        int repetitions = sc.nextInt();
                        Matrix.multiplyMatricesMultipleTimes(mat1, mat2, repetitions);
                    } else {
                        System.out.println("Matrices are not initialized.");
                    }
                    break;

                case 9: // Exit
                    System.out.println("Exiting...");
                    sc.close();
                    return;

                default:
                    System.out.println("Invalid option.");
                    break;
            }
        }
    }

    // Function to display the menu
    private static void displayMenu() {
        System.out.println("\nMenu:");
        System.out.println("1. Input matrices manually");
        System.out.println("2. Generate matrices randomly");
        System.out.println("3. Read matrices from file");
        System.out.println("4. Add matrices");
        System.out.println("5. Subtract matrices");
        System.out.println("6. Multiply matrices");
        System.out.println("7. View both matrices");
        System.out.println("8. Multiply matrices X times and show average time");
        System.out.println("9. Exit");
        System.out.print("Choose an option: ");
    }
}
