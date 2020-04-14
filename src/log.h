#ifndef LIB_LOG_H
#define LIB_LOG_H

#include <string>
#include <boost/log/core.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/expressions.hpp>

void log_init(std::string name);

void log_mute();

void log_test();

#endif // LIB_LOG_H
