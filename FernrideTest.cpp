// The task was that given the set of movements of a robot in terms of ^ UP, v DOWN, < LEFT, > RIGHT, we need to determine if the robot forms a rectangle or not.
// The robot forms a rectangle if it returns to the starting point (0, 0) and the number of horizontal and vertical moves cancel out each other.

#include <iostream>
#include <string>
#include <set>
#include <utility>

using namespace std;

bool solution(string &moves) {
    int x = 0, y = 0;
    int left_moves = 0, right_moves = 0, up_moves = 0, down_moves = 0;
    char last_direction = ' '; // Keeping track of the last direction
    int direction_changes = 0; // Counting direction changes

    // Track visited positions
    set<pair<int, int>> visited_positions;
    visited_positions.insert({x, y});

    for (char move : moves) {
        // Update position and count moves
        if (move == '^') {
            y++;  // Goes up
            up_moves++;
        } else if (move == 'v') {
            y--;  // Goes down
            down_moves++;
        } else if (move == '>') {
            x++;  // Goes right
            right_moves++;
        } else if (move == '<') {
            x--;  // Goes left
            left_moves++;
        }

        // check if this new position has been visited before
        if (visited_positions.count({x, y}) && !(x == 0 && y == 0)) {
            // if revisits a point (other than (0, 0)), it can't be a rectangle
            return false;
        }

        visited_positions.insert({x, y});

        // counting direction changes
        if (last_direction != ' ') {
            // change of direction is a turn
            if ((move == '^' || move == 'v') && (last_direction == '>' || last_direction == '<')) {
                direction_changes++;
            } else if ((move == '>' || move == '<') && (last_direction == '^' || last_direction == 'v')) {
                direction_changes++;
            }
        }

        // Update the last direction
        last_direction = move;
    }

    // conditions for forming a rectangle
    // - return to (0, 0)
    // - horizontal and vertical moves should cancel out
    // - at least 4 direction changes
    if (x == 0 && y == 0 && left_moves == right_moves && up_moves == down_moves && direction_changes <= 4) {
        return true;  // is a rectangle
    }

    return false; // not a rectangle
}

int main() {
    // Test cases
    string moves1 = "^^^<<<<vvv>>>>";
    cout << (solution(moves1) ? "true" : "false") << endl;  // Expected output: true

    string moves2 = "<vvv>>^^^<";
    cout << (solution(moves2) ? "true" : "false") << endl;  // Expected output: true

    string moves3 = "<^^^>v";
    cout << (solution(moves3) ? "true" : "false") << endl;  // Expected output: false

    string moves4 = "vv<<vv>>>>^^<^^<";  //Added new test case by me
    cout << (solution(moves4) ? "true" : "false") << endl;  // Expected output: false

    return 0;
}
