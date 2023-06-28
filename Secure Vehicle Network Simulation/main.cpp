#include <iostream>
#include <string>
#include <unordered_map>

class Vehicle {
public:
    Vehicle(int id, int key, const std::unordered_map<int, int>& trusted_keys)
        : id(id), key(key), trusted_keys(trusted_keys), sequence_number(0) {}

    void send(Vehicle& other, const std::string& message) {
        int signature = sign(message, sequence_number);
        other.receive(id, message, signature, sequence_number);
        sequence_number++;
    }

    void receive(int sender_id, const std::string& message, int signature, int sequence_number) {
        auto it = trusted_keys.find(sender_id);
        if (it != trusted_keys.end()) {
            if (sequence_number <= last_sequence_numbers[sender_id]) {
                std::cout << "Vehicle " << id << " disregarded replayed message from " << sender_id << std::endl;
                return;
            }
            last_sequence_numbers[sender_id] = sequence_number;
            if (verify(message, signature, sequence_number, it->second)) {
                std::cout << "Vehicle " << id << " received: " << message << std::endl;
            } else {
                std::cout << "Vehicle " << id << " received forged message from " << sender_id << std::endl;
            }
        } else {
            std::cout << "Vehicle " << id << " received unauthorized message from " << sender_id << std::endl;
        }
    }

private:
    int id;
    int key;
    std::unordered_map<int, int> trusted_keys;
    std::unordered_map<int, int> last_sequence_numbers;
    int sequence_number;

    int sign(const std::string& message, int sequence_number) {
        int sum = 0;
        for (char c : message) {
            sum += c;
        }
        return (sum + sequence_number) * key;
    }

    bool verify(const std::string& message, int signature, int sequence_number, int sender_key) {
        int sum = 0;
        for (char c : message) {
            sum += c;
        }
        return signature == (sum + sequence_number) * sender_key;
    }
};

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
