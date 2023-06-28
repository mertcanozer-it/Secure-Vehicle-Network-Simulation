#include <iostream>
#include <string>
#include <unordered_set>

class Vehicle {
public:
    Vehicle(int id, const std::unordered_set<int>& trusted_ids)
        : id(id), trusted_ids(trusted_ids) {}

    void send(Vehicle& other, const std::string& message) {
        other.receive(id, message);
    }

    void receive(int sender_id, const std::string& message) {
        if (trusted_ids.find(sender_id) != trusted_ids.end()) {
            std::cout << "Vehicle " << id << " received: " << message << std::endl;
        } else {
            std::cout << "Vehicle " << id << " received unauthorized message from " << sender_id << std::endl;
        }
    }

private:
    int id;
    std::unordered_set<int> trusted_ids;
};

int main() {
    std::unordered_set<int> trusted_ids_1 = {2};
    std::unordered_set<int> trusted_ids_2 = {1};
    Vehicle vehicle1(1, trusted_ids_1);
    Vehicle vehicle2(2, trusted_ids_2);

    vehicle1.send(vehicle2, "Hello from vehicle 1!");
    vehicle2.send(vehicle1, "Hello from vehicle 2!");

    return 0;
}
