/* 
 * File:   output.h
 * Author: tobi
 *
 * Created on 11. Juni 2014, 15:50
 */

#include <string>
#pragma once

class output {
public:
    output();
    output(const output& orig);
    virtual ~output();
    
    int getDirection();
    char getValue();
    void setValue(char value);
    void setDirection(int direction);
    
    
private:
    char value;
    int direction;
};

