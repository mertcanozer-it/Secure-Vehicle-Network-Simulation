#include "Vehicle.h"
#include <unordered_map>

int main() {
    std::unordered_map<int, int> trusted_keys_1 = {{2, 3}};
    std::unordered_map<int, int> trusted_keys_2 = {{1, 2}};
    Vehicle vehicle1(1, 2, trusted_keys_1);
    Vehicle vehicle2(2, 3, trusted_keys_2);

    vehicle1.send(vehicle2, "Hello from vehicle 1!");
    vehicle2.send(vehicle1, "Hello from vehicle 2!");

    std::unordered_map<int, int> trusted_keys_3 = {};
    Vehicle vehicle3(3, 5, trusted_keys_3);

    vehicle3.send(vehicle1, "Hello from vehicle 3!");
    vehicle3.send(vehicle2, "Hello from vehicle 3!");

    return 0;
}
