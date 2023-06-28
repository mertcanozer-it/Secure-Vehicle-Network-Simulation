#include "Vehicle.h"
#include <iostream>
#include <string>
#include <unordered_map>

Vehicle::Vehicle(int id, int key, const std::unordered_map<int, int>& trusted_keys)
    : id(id), key(key), trusted_keys(trusted_keys), sequence_number(0) {}

void Vehicle::send(Vehicle& other, const std::string& message) {
    int signature = sign(message, sequence_number);
    other.receive(id, message, signature, sequence_number);
    sequence_number++;
}

void Vehicle::receive(int sender_id, const std::string& message, int signature, int sequence_number) {
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

int Vehicle::sign(const std::string& message, int sequence_number) {
    int sum = 0;
    for (char c : message) {
            sum += c;
    }
    return (sum + sequence_number) * key;
}

bool Vehicle::verify(const std::string& message, int signature, int sequence_number, int sender_key) {
    int sum = 0;
    for (char c : message) {
        sum += c;
    }
    return signature == (sum + sequence_number) * sender_key;
}
