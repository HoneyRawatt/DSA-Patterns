package StackQ;

import java.util.ArrayList;
import java.util.Arrays;

public class AsteroidCollision {

    /*
    =====================================================
    PROBLEM STATEMENT:
    -----------------------------------------------------
    Given an array of integers representing asteroids in a row.

    - Absolute value  -> size of the asteroid
    - Sign:
        positive  -> moving to the right
        negative  -> moving to the left

    When two asteroids collide:
    - The smaller one explodes
    - If both are the same size, both explode
    - Asteroids moving in the same direction never collide

    Return the final state of asteroids after all collisions.
    =====================================================
    */

    /*
    =====================================================
    INTUITION:
    -----------------------------------------------------
    - Collisions only happen when:
        right-moving asteroid (+) meets a left-moving asteroid (-)

    - We simulate the process using a STACK:
        - Right-moving asteroids are pushed directly.
        - When a left-moving asteroid appears, it may collide
          with previously stored right-moving asteroids.

    - We keep removing smaller right-moving asteroids until:
        1) Stack becomes empty
        2) Top is a left-moving asteroid
        3) A bigger right-moving asteroid survives
    =====================================================
    */

    /*
    =====================================================
    FUNCTION: asteroidCollision
    -----------------------------------------------------
    Simulates all asteroid collisions using stack logic.

    PARAMETERS:
        arr -> array of integers representing asteroids

    RETURNS:
        ArrayList<Integer> -> final asteroid configuration
    =====================================================
    */
    public static ArrayList<Integer> asteroidCollision(int[] arr) {
        ArrayList<Integer> st = new ArrayList<>(); // Using ArrayList as a stack

        // Traverse each asteroid
        for (int a : arr) {

            // Case 1: Right-moving asteroid
            if (a > 0) {
                st.add(a); // push
            }
            else {
                // Case 2: Left-moving asteroid

                // Remove all smaller right-moving asteroids
                while (!st.isEmpty() &&
                       st.get(st.size() - 1) > 0 &&
                       st.get(st.size() - 1) < -a) {
                    st.remove(st.size() - 1); // pop
                }

                // If equal size collision, both explode
                if (!st.isEmpty() && st.get(st.size() - 1) == -a) {
                    st.remove(st.size() - 1);
                }
                // If stack is empty OR top is left-moving
                else if (st.isEmpty() || st.get(st.size() - 1) < 0) {
                    st.add(a);
                }
            }
        }
        return st;
    }

    /*
    =====================================================
    TIME COMPLEXITY:
    -----------------------------------------------------
    O(n)
    - Each asteroid is pushed and popped at most once.

    SPACE COMPLEXITY:
    -----------------------------------------------------
    O(n)
    - Stack (ArrayList) can store up to n asteroids.
    =====================================================
    */

    public static void main(String[] args) {
        int[] asteroids1 = {5, 10, -5};
        int[] asteroids2 = {8, -8};
        int[] asteroids3 = {10, 2, -5, -15, 20};

        System.out.println("Result 1: " + asteroidCollision(asteroids1));
        System.out.println("Result 2: " + asteroidCollision(asteroids2));
        System.out.println("Result 3: " + asteroidCollision(asteroids3));
    }
}
