#ifndef ENTITIES_API_HPP
#define ENTITIES_API_HPP

#ifdef Entities_EXPORTS
#define EntitiesAPI __declspec(dllexport)
#else 
#define EntitiesAPI __declspec(dllimport)
#endif

#endif
