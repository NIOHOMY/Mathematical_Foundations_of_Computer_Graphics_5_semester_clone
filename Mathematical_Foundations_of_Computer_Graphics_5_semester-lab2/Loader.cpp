#pragma once
#include "Loader.h"

Loader::Loader(const std::string& path) :
    m_path(path)
{
    isLoad();
}

Loader::~Loader()
{
}

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
    return false;
}
