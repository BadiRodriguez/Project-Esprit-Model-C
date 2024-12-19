//
// Created by Badi on 11/12/2024.
//

#include "Testing.h"

int Testing::testing_1(){

    int value_a = 10;
    int value_b = 20;
    unsigned int value_c = 0;

    std::cout << value_a + value_b << std::endl;
    std::cout << value_c - 1 << std::endl;

    return 0;

}

int Testing::testing_2() {

    int value_x = 10;
    int value_y = 20;

    int* val_x_direction = &value_x;
    int* val_y_direction = &value_y;

    std::cout << "x = " << value_x << std::endl;
    std::cout << "y = " << value_y << std::endl;

    std::cout << "x (mem. location) = " << val_x_direction << std::endl;
    std::cout << "y (mem. location) = " << val_y_direction << std::endl;

    std::cout << "value of x (dereferenced) = " << *val_x_direction << std::endl;
    std::cout << "value of y (dereferenced) = " << *val_y_direction << std::endl;

    return 0;
}

int Testing::testing_3() {

    int MAX_COUNT = 10;
    int target_value = 3;
    std::string array[MAX_COUNT];

    array[0] = "Bean";
    array[1] = "Soy";
    array[2] = "Oil";
    array[3] = "Rice";

    for (int i = 0; i < MAX_COUNT; i++) {
        std::cout << "Element No. " << i << ": " << array[i] << std::endl;
    }

    std::cout << array << std::endl;
    std::cout << "Change element No. 2" << std::endl;

    for (int i = 0; i < MAX_COUNT; i++) {
        if (i == 2) {
            array[i] = "Chicken";
        }
        std::cout << "Element No. " << i << ": " << array[i] << std::endl;
    }

    std::cout << "The element in segment No. " << target_value << " is " << array[target_value].size() << " characters long." << std::endl;

    return 0;
}
