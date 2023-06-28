#ifndef VEHICLE_H
#define VEHICLE_H

#include <string>
#include <unordered_map>

class Vehicle {
public:
    Vehicle(int id, int key, const std::unordered_map<int, int>& trusted_keys);

    void send(Vehicle& other, const std::string& message);

    void receive(int sender_id, const std::string& message, int signature, int sequence_number);

private:
    int id;
    int key;
    std::unordered_map<int, int> trusted_keys;
    std::unordered_map<int, int> last_sequence_numbers;
    int sequence_number;

    int sign(const std::string& message, int sequence_number);

    bool verify(const std::string& message, int signature, int sequence_number, int sender_key);
};

#endif // VEHICLE_H
