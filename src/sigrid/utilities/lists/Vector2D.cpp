#include "sigrid/utilities/lists/Vector2D.h"
#include "sigrid/utilities/lists/Vector2D_contentTypes.h"
// Any type used must be added in the Vector2D_contentTypes.h file
// Reasoning being that I want this code in a cpp file
// If this should work with any class, then it is possible by
// renaming this file's extension to tpp and
// including this file at the end of Vector.h
// Both includes above can then be removed from this file

#include <iostream>

template <typename T> 
void sigrid_list::Vector2D<T>::addColumn(){
    m_vector.push_back(std::vector<T>{});
}

template <typename T> 
bool sigrid_list::Vector2D<T>::push_back(const int& x, const T& value){

    if(x >= m_vector.size()){
        std::cerr << "Vector2D: Column " << x << " does not exist."
            << " Failed to push_back value" << std::endl;
        return false;
    }
    m_vector.at(x).push_back(value);

    return true;
}

template <typename T> 
bool sigrid_list::Vector2D<T>::insert(const sigrid_coord::Coord& position, const T& value){

    if(position.x < 0){

        std::cerr << "Vector2D: x position " << position.x << " is too low."
            << " Type: " << typeid(*this).name()
            << " Failed to insert at " << position.getNotation() << std::endl;
        return false;
    }
    if(position.y < 0){

        std::cerr << "Vector2D: y position " << position.y << " is too low."
            << " Type: " << typeid(*this).name()
            << " Failed to insert at " << position.getNotation() << std::endl;
        return false;
    }

    if(position.x >= m_vector.size()){

        std::cerr << "Vector2D: x position " << position.x << " is too high."
            << " Type: " << typeid(*this).name()
            << " Failed to insert at " << position.getNotation() << std::endl;
        return false;
    }

    if(position.y >= m_vector.at(position.x).size()){

        std::cerr << "Vector2D: y position " << position.y << " is too high."
            << " Type: " << typeid(*this).name()
            << " Failed to insert at " << position.getNotation() << std::endl;
        return false;
    }

    m_vector.at(position.x).insert(m_vector.at(position.x).begin() + position.y, value);
    return true;
}

template <typename T> 
bool sigrid_list::Vector2D<T>::erase(const sigrid_coord::Coord& position){

    if(position.x < 0){

        std::cerr << "Vector2D: x position " << position.x << " is too low."
            << " Type: " << typeid(*this).name()
            << " Failed to erase at " << position.getNotation() << std::endl;
        return false;
    }
    if(position.y < 0){

        std::cerr << "Vector2D: y position " << position.y << " is too low."
            << " Type: " << typeid(*this).name()
            << " Failed to erase at " << position.getNotation() << std::endl;
        return false;
    }

    if(position.x >= m_vector.size()){

        std::cerr << "Vector2D: x position " << position.x << " is too high."
            << " Type: " << typeid(*this).name()
            << " Failed to erase at " << position.getNotation() << std::endl;
        return false;
    }

    if(position.y >= m_vector.at(position.x).size()){

        std::cerr << "Vector2D: y position " << position.y << " is too high."
            << " Type: " << typeid(*this).name()
            << " Failed to erase at " << position.getNotation() << std::endl;
        return false;
    }

    m_vector.at(position.x).erase(m_vector.at(position.x).begin() + position.y);
    return true;
}

template <typename T> 
void sigrid_list::Vector2D<T>::clear(){
    m_vector.clear();
}

template<typename T>
std::optional<std::reference_wrapper<T>> sigrid_list::Vector2D<T>::at(const sigrid_coord::Coord& position){

    if(position.x < 0){

        std::cerr << "Vector2D: x position " << position.x << " is too low."
            << " Type: " << typeid(*this).name()
            << " Failed to get value at " << position.getNotation() << std::endl;
        return std::nullopt;
    }

    if(position.y < 0){

        std::cerr << "Vector2D: y position " << position.y << " is too low."
            << " Type: " << typeid(*this).name()
            << " Failed to get value at " << position.getNotation() << std::endl;
        return std::nullopt;
    }

    if(position.x >= m_vector.size()){

        std::cerr << "Vector2D: x position " << position.x << " is too high."
            << " Type: " << typeid(*this).name()
            << " Failed to get value at " << position.getNotation() << std::endl;
        return std::nullopt;
    }

    if(position.y >= m_vector.at(position.x).size()){

        std::cerr << "Vector2D: y position " << position.y << " is too high."
            << " Type: " << typeid(*this).name()
            << " Failed to get value at " << position.getNotation() << std::endl;
        return std::nullopt;
    }

    return m_vector.at(position.x).at(position.y);
}

template<typename T>
const std::optional<std::reference_wrapper<const T>> sigrid_list::Vector2D<T>::at(const sigrid_coord::Coord& position) const{
    
    if(position.x < 0){

        std::cerr << "Vector2D: x position " << position.x << " is too low."
            << " Type: " << typeid(*this).name()
            << " Failed to get const value at " << position.getNotation() << std::endl;
        return std::nullopt;
    }

    if(position.y < 0){

        std::cerr << "Vector2D: y position " << position.y << " is too low."
            << " Type: " << typeid(*this).name()
            << " Failed to get const value at " << position.getNotation() << std::endl;
        return std::nullopt;
    }

    if(position.x >= m_vector.size()){

        std::cerr << "Vector2D: x position " << position.x << " is too high."
            << " Type: " << typeid(*this).name()
            << " Failed to get const value at " << position.getNotation() << std::endl;
        return std::nullopt;
    }

    if(position.y >= m_vector.at(position.x).size()){

        std::cerr << "Vector2D: y position " << position.y << " is too high."
            << " Type: " << typeid(*this).name()
            << " Failed to get const value at " << position.getNotation() << std::endl;
        return std::nullopt;
    }

    return m_vector.at(position.x).at(position.y);
}

template<typename T>
int sigrid_list::Vector2D<T>::numColumns() const{
    return m_vector.size();
}

template<typename T>
int sigrid_list::Vector2D<T>::numRows(const int& x) const{
    
    if(x > m_vector.size()){
        std::cerr << "Vector2D: column " << x << " does not exist"
            << " Type: " << typeid(*this).name()
            << " returning 0 rows" << std::endl;
        return 0;
    }

    return m_vector.at(x).size();
}