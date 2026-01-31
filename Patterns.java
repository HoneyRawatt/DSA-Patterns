import java.util.Scanner;

public class Patterns {

    static void pattern1(int n) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < i; j++) System.out.print("*");
            System.out.println();
        }
    }

    static void pattern2(int n) {
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= i; j++) System.out.print(j);
            System.out.println();
        }
    }

    static void pattern3(int n) {
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= i; j++) System.out.print(i);
            System.out.println();
        }
    }

    static void pattern4(int n) {
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n - i + 1; j++) System.out.print("*");
            System.out.println();
        }
    }

    static void pattern5(int n) {
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n - i + 1; j++) System.out.print(j);
            System.out.println();
        }
    }

    static void pattern6(int n) {
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n - i + 1; j++) System.out.print(i);
            System.out.println();
        }
    }

    static void pattern7(int n) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n - i - 1; j++) System.out.print(" ");
            for (int j = 0; j <= 2 * i; j++) System.out.print("*");
            for (int j = 0; j < n - i - 1; j++) System.out.print(" ");
            System.out.println();
        }
    }

    static void pattern8(int n) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < i; j++) System.out.print(" ");
            for (int j = 0; j < 2 * n - (2 * i + 1); j++) System.out.print("*");
            for (int j = 0; j < i; j++) System.out.print(" ");
            System.out.println();
        }
    }

    static void pattern9(int n) {
        pattern7(n);
        pattern8(n);
    }

    static void pattern10(int n) {
        for (int i = 1; i <= 2 * n - 1; i++) {
            int stars = (i > n) ? 2 * n - i : i;
            for (int j = 1; j <= stars; j++) System.out.print("*");
            System.out.println();
        }
    }

    static void pattern11(int n) {
        int start;
        for (int i = 0; i < n; i++) {
            start = (i % 2 == 0) ? 1 : 0;
            for (int j = 0; j <= i; j++) {
                System.out.print(start);
                start = 1 - start;
            }
            System.out.println();
        }
    }

    static void pattern12(int n) {
        int space = 2 * (n - 1);
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= i; j++) System.out.print(j);
            for (int j = 1; j <= space; j++) System.out.print(" ");
            for (int j = i; j >= 1; j--) System.out.print(j);
            System.out.println();
            space -= 2;
        }
    }

    static void pattern13(int n) {
        int num = 1;
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= i; j++) System.out.print(num++);
            System.out.println();
        }
    }

    static void pattern14(int n) {
        for (int i = 0; i < n; i++) {
            for (char c = 'A'; c <= 'A' + i; c++) System.out.print(c);
            System.out.println();
        }
    }

    static void pattern15(int n) {
        for (int i = 0; i < n; i++) {
            for (char c = 'A'; c <= 'A' + (n - i - 1); c++) System.out.print(c);
            System.out.println();
        }
    }

    static void pattern16(int n) {
        for (int i = 0; i < n; i++) {
            char c = (char) ('A' + i);
            for (int j = 0; j <= i; j++) System.out.print(c);
            System.out.println();
        }
    }

    static void pattern17(int n) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n - i - 1; j++) System.out.print(" ");
            char ch = 'A';
            int bp = (2 * i + 1) / 2;
            for (int j = 1; j <= 2 * i + 1; j++) {
                System.out.print(ch);
                if (j <= bp) ch++;
                else ch--;
            }
            for (int j = 0; j < n - i - 1; j++) System.out.print(" ");
            System.out.println();
        }
    }

    static void pattern18(int n) {
        for (int i = 0; i < n; i++) {
            char ch = (char) ('A' + (n - i));
            for (int j = 0; j <= i; j++) {
                System.out.print(ch);
                ch++;
            }
            System.out.println();
        }
    }

    static void pattern19(int n) {
        int insideSpace = 0;
        for (int i = 0; i < n; i++) {
            for (int j = 1; j <= n - i; j++) System.out.print("*");
            for (int j = 1; j <= insideSpace; j++) System.out.print(" ");
            for (int j = 1; j <= n - i; j++) System.out.print("*");
            System.out.println();
            insideSpace += 2;
        }

        insideSpace = 2 * n - 2;
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= i; j++) System.out.print("*");
            for (int j = 1; j <= insideSpace; j++) System.out.print(" ");
            for (int j = 1; j <= i; j++) System.out.print("*");
            insideSpace -= 2;
            System.out.println();
        }
    }

    static void pattern20(int n) {
        int space = 2 * n - 2;
        for (int i = 1; i <= 2 * n - 1; i++) {
            int stars = (i > n) ? 2 * n - i : i;
            for (int j = 1; j <= stars; j++) System.out.print("*");
            for (int j = 1; j <= space; j++) System.out.print(" ");
            for (int j = 1; j <= stars; j++) System.out.print("*");
            System.out.println();
            if (i >= n) space += 2;
            else space -= 2;
        }
    }

    static void pattern21(int n) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (i == 0 || j == 0 || i == n - 1 || j == n - 1)
                    System.out.print("*");
                else
                    System.out.print(" ");
            }
            System.out.println();
        }
    }

    static void pattern22(int n) {
        for (int i = 0; i < 2 * n - 1; i++) {
            for (int j = 0; j < 2 * n - 1; j++) {
                int top = i;
                int left = j;
                int right = (2 * n - 2) - j;
                int down = (2 * n - 2) - i;
                int minDist = Math.min(Math.min(top, down), Math.min(left, right));
                System.out.print(n - minDist);
            }
            System.out.println();
        }
    }

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        System.out.print("Enter the value of n: ");
        int n = sc.nextInt();

        pattern1(n);
        pattern2(n);
        pattern3(n);
        pattern4(n);
        pattern5(n);
        pattern6(n);
        pattern7(n);
        pattern8(n);
        pattern9(n);
        pattern10(n);
        pattern11(n);
        pattern12(n);
        pattern13(n);
        pattern14(n);
        pattern15(n);
        pattern16(n);
        pattern17(n);
        pattern18(n);
        pattern19(n);
        pattern20(n);
        pattern21(n);
        pattern22(n);

        sc.close();
    }
}
