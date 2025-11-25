#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "motor.hpp"

void setup();

int QR_search();

std::vector<std::string> splitString(const std::string &str,
                                     char delimiter = ',');

void processarComandos(const std::vector<std::string> &comandos);
#endif // !CAMERA_HPP
