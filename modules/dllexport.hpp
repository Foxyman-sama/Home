#ifndef DLLEXPORT_HPP
#define DLLEXPORT_HPP

#define classexport(class_name) class __declspec(dllexport) class_name;
#define tclassexport(class_name) template classexport(class_name);

#endif
