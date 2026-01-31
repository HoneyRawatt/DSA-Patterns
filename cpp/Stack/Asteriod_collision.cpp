#include <iostream>
#include <vector>
using namespace std;

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
    arr -> vector of integers representing asteroids

RETURNS:
    vector<int> -> final asteroid configuration
=====================================================
*/
vector<int> asteroidCollision(vector<int>& arr){
    vector<int> st;  // Using vector as a stack to store surviving asteroids

    // Traverse each asteroid
    for(int a : arr){

        // Case 1: Right-moving asteroid
        // No collision possible now, so push it
        if(a > 0) {
            st.push_back(a);
        }
        else {
            // Case 2: Left-moving asteroid
            // Possible collision with right-moving asteroids in stack

            // Remove all smaller right-moving asteroids
            while(!st.empty() && st.back() > 0 && st.back() < -a)
                st.pop_back();  // smaller asteroid explodes

            // If equal size collision, both explode
            if(!st.empty() && st.back() == -a)
                st.pop_back();

            // If stack is empty OR top is left-moving,
            // then no collision occurs
            else if(st.empty() || st.back() < 0)
                st.push_back(a);
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
- Stack (vector) can store up to n asteroids.
=====================================================
*/

int main() {
    // Sample test cases
    vector<int> asteroids1 = {5, 10, -5};
    vector<int> asteroids2 = {8, -8};
    vector<int> asteroids3 = {10, 2, -5, -15, 20};

    vector<int> result1 = asteroidCollision(asteroids1);
    vector<int> result2 = asteroidCollision(asteroids2);
    vector<int> result3 = asteroidCollision(asteroids3);

    cout << "Result 1: ";
    for(int a : result1) cout << a << " ";
    cout << endl;

    cout << "Result 2: ";
    for(int a : result2) cout << a << " ";
    cout << endl;

    cout << "Result 3: ";
    for(int a : result3) cout << a << " ";
    cout << endl;

    return 0;
}
