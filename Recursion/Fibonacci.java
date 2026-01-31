package Recursion;
import java.util.Scanner;

public class Fibonacci{

    static int fibo(int n) {
        if (n <= 1) return n;
        return fibo(n - 2) + fibo(n - 1);
    }

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int n = sc.nextInt();
        System.out.print(fibo(n));
        sc.close();
    }
}
