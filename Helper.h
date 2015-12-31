/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Helper.h
 * Author: brian
 *
 * Created on December 26, 2015, 7:27 PM
 */

#ifndef HELPER_H
#define HELPER_H

#include <iostream>

using namespace std;

/**
 * Log an SDL error with some error message to the output stream of our choice
 * @param os The output stream to write the message to
 * @param msg The error message to write, format will be msg error: SDL_GetError()
 */
void logSDLError(std::ostream &os, const std::string &msg);


#endif /* HELPER_H */

