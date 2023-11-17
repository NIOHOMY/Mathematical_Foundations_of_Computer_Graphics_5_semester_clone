#pragma once
#include <fstream>
#include <sstream>
#include "Loader.h"

Loader::Loader(const std::string& path) : m_path(path)
{
    // Проверяем загрузку данных из файла.
    if (!isLoad()) {
        throw std::runtime_error("Error loading data from file!");
    }
}

Loader::~Loader()
{}

std::vector<Vector2D> Loader::vertices() const
{
    return m_vertices;
}

std::vector<int> Loader::indices() const
{
    return m_indices;
}

bool Loader::isLoad()
{
    std::ifstream file(m_path);
    if (!file.is_open()) {
        return false;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string command;
        iss >> command;

        if (command == "v") {
            double x, y;
            iss >> x >> y;
            m_vertices.push_back(Vector2D(x, y));
        }
        else if (command == "f") {
            int idx;
            while (iss >> idx) {
                m_indices.push_back(idx);
            }
        }
    }

    // Закрываем файл.
    file.close();

    return true;
}
