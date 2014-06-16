/* 
 * File:   output.cpp
 * Author: tobi
 * 
 * Created on 11. Juni 2014, 15:50
 */

#include "output.h"

output::output() {
   
}

output::output(const output& orig) {
}

output::~output() {
}

int output::getDirection(){
    return direction;
}

char output::getValue() {
    return value;
}

void setValue(char value) {
    this->value = value;
}

void setDirection(int direction) {
    this->direction = direction;
}

