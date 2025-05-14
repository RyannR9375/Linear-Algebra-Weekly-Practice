#include <iostream>
#include <cmath>
#include <cstdlib>
#include <utility>
#include <vector>
#include <random>

struct Vector3 {
    Vector3(float x, float y, float z) {  this->x = x; this->y = y; this->z = z; }
    Vector3() = default;
    float x{}, y{}, z{};

    Vector3 operator-(Vector3& from) {
        return {this->x - from.x, this->y - from.y, this->z - from.z};
    }

    Vector3 operator+(Vector3& from) {
        return {this->x + from.x, this->y + from.y, this->z + from.z};
    }
};

float Dot(Vector3 a, Vector3 b);
float Magnitude(Vector3 a);
Vector3 Normalize(Vector3 a);
void RandomizeEnemyPositions(std::vector<Vector3>& positions);
void SortEnemyRelativeTo(Vector3 playerLocation, Vector3 playerDir, std::vector<Vector3>& allPositions, std::vector<Vector3>& inFront, std::vector<Vector3>& behind, std::vector<Vector3>& perpendicular);
void Print(std::vector<Vector3> enemiesBehind);

inline std::mt19937& generator() {
    // the generator will only be seeded once (per thread) since it's static
    static thread_local std::mt19937 gen(std::random_device{}());
    return gen;
}


int main() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(1, 10);

    const int NUM_OF_ENEMIES = 100;

    Vector3 playerLocation  = Vector3(0, 0, 0);
    Vector3 playerDirection = Vector3(1, 0, 0);

    std::vector<Vector3> enemyPositions(NUM_OF_ENEMIES);
    RandomizeEnemyPositions(enemyPositions);

    std::vector<Vector3> enemiesBehind;
    std::vector<Vector3> enemiesInFront;
    std::vector<Vector3> enemiesPerpendicular;

    SortEnemyRelativeTo(playerLocation,
        playerDirection, enemyPositions, enemiesInFront, enemiesBehind, enemiesPerpendicular);

    printf("Player's location: (%f, %f, %f), Player's forward: (%f, %f, %f)\n",
        playerLocation.x, playerLocation.y, playerLocation.z,
        playerDirection.x, playerDirection.y, playerDirection.z);

    std::cout << "Enemies Behind: " << enemiesBehind.size() << '\n';
    std::cout << "Enemies In Front: " << enemiesInFront.size() << '\n';
    std::cout << "Enemies Perpendicular: " << enemiesPerpendicular.size() << '\n';

    std::string input{};
    printf("enter '1' if you would like to see a printed list of all the enemy positions generated: ");
    std::cin >> input;

    if (input == "1") {
        std::cout << "Enemies Behind: " << enemiesBehind.size() << '\n';
        Print(enemiesBehind);
        std::cout << "Enemies In Front: " << enemiesInFront.size() << '\n';
        Print(enemiesInFront);
        std::cout << "Enemies Perpendicular: " << enemiesPerpendicular.size() << '\n';
        Print(enemiesPerpendicular);
    }
    else exit(0);

    return 0;
}

float Dot(const Vector3 a, const Vector3 b){ return (a.x * b.x) + (a.y * b.y) + (a.z * b.z); }
float Magnitude(const Vector3 a){ return (sqrtf(Dot(a, a))); }
Vector3 Normalize(const Vector3  a) { return {a.x/Magnitude(a), a.y/Magnitude(a),a.z/Magnitude(a)}; }

void RandomizeEnemyPositions(std::vector<Vector3> &positions) {
    int MAX = 100;
    int MIN = -100;
    int range = MAX - MIN + 1;

    std::uniform_int_distribution<> distrib(MIN, MAX);
    for(auto& enemyPosition : positions) {
        //enemyPosition.x = rand() % range + MIN;
        enemyPosition.x = distrib(generator());
        //enemyPosition.y = rand() % 100;
        enemyPosition.z = distrib(generator());
    }
}

void SortEnemyRelativeTo(Vector3 playerLocation, Vector3 playerDir,
    std::vector<Vector3>& allPositions,
    std::vector<Vector3>& inFront, std::vector<Vector3>& behind, std::vector<Vector3>& perpendicular) {

    for (auto& position : allPositions) {
        //step 1 subtract player location from the enemy location
        playerDir = Normalize(playerDir);
        Vector3 toTarget = playerLocation - position;
        float dotProduct = Dot(playerDir, toTarget);

        if (dotProduct > 0) {
            inFront.push_back(position);
        }else if (dotProduct < 0) {
            behind.push_back(position);
        }else {
            perpendicular.push_back(position);
        }
    }
}

void Print(const std::vector<Vector3> positions) {
    for (auto position : positions) {
        std::cout << '(' << position.x << ',' << position.y << ',' << position.z << ")\n";
    }
}

