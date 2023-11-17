#pragma once
#include "Model2D.h"
#include <windef.h>
#include <wingdi.h>
#include <windowsx.h>

Model2D::Model2D(const std::vector<Vector2D>& vertices, const std::vector<int> indices)
    : m_vertices(vertices), m_indices(indices), m_modelMatrix(vertices.size(), 3)
{
    // Заполнение матрицы m_modelMatrix с использованием векторов x и y
    for (int i = 0; i < m_vertices.size(); i++) {
        m_modelMatrix(i+1, 1) = m_vertices[i].x();
        m_modelMatrix(i+1, 2) = m_vertices[i].y();
        m_modelMatrix(i+1, 3) = 1.0;
    }
}
void Model2D::applyTransformation(Matrix<> transformationMatrix)
{
    // Умножаем текущую матрицу модели на матрицу преобразования
    //Matrix<>transformationMatrix = _transformationMatrix;
    for (size_t i = 0; i < m_vertices.size(); i++)
    {
        Matrix<>modelMatrix(3, 1);
        modelMatrix(1, 1) = m_modelMatrix(i+1, 1);
        modelMatrix(2, 1) = m_modelMatrix(i+1, 2);
        modelMatrix(3, 1) = 1.0;

        modelMatrix = modelMatrix*transformationMatrix;

        m_modelMatrix(i + 1, 1) = modelMatrix(1,1);
        m_modelMatrix(i + 1, 2) = modelMatrix(2,1);
    }

    // Применяем преобразование ко всем вершинам модели
    for (int i = 0; i < m_vertices.size(); i++) {
        m_vertices[i].setX(m_modelMatrix(i + 1, 1));
        m_vertices[i].setY(m_modelMatrix(i + 1, 2));
    }
}

Vector2D Model2D::getOXOYVector()
{
    return Vector2D(-m_vertices[0].x(), -m_vertices[0].y());
}



void Model2D::draw(const HDC& hdc)
{
    // новые вершины
    std::vector<Vector2D> transformedVertices(m_vertices.size());
    if (m_vertices.size() != 0)// Индекс выходит за пределы вектора, обработка ошибки
    {
        /*
        for (int i = 0; i < m_vertices.size(); i++) {
            Matrix<> point(3, 1);
            point(1, 1) = m_vertices[i].x();
            point(2, 1) = m_vertices[i].y();
            point(3, 1) = 1;
            Matrix<> transformedPoint = m_modelMatrix * point;
            transformedVertices[i] = Vector2D(transformedPoint(1, 1), transformedPoint(2, 1));
        }

        // Отрисовать модель на экране
        HPEN hPen = CreatePen(PS_DOT, 1, RGB(255, 0, 0));
        HGDIOBJ hOldPen = SelectObject(hdc, hPen);
        for (int i = 0; i < m_indices.size()-1; i++) {
            MoveToEx(hdc, transformedVertices[m_indices[i]].x(), transformedVertices[m_indices[i]].y(), nullptr);
            LineTo(hdc, transformedVertices[m_indices[i + 1]].x(), transformedVertices[m_indices[i + 1]].y());
        }
        SelectObject(hdc, hOldPen);
        DeleteObject(hPen);
        */
        for (int i = 0; i < m_vertices.size(); i++) {
            transformedVertices[i].setX(m_modelMatrix(i + 1, 1));
            transformedVertices[i].setY(m_modelMatrix(i + 1, 2));
        }
        // Отрисовать модель на экране
        HPEN hPen = CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
        HGDIOBJ hOldPen = SelectObject(hdc, hPen);
        for (int i = 0; i < m_indices.size() - 1; i++) {
            MoveToEx(hdc, transformedVertices[m_indices[i]].x(), transformedVertices[m_indices[i]].y(), nullptr);
            LineTo(hdc, transformedVertices[m_indices[i + 1]].x(), transformedVertices[m_indices[i + 1]].y());
        }
        SelectObject(hdc, hOldPen);
        DeleteObject(hPen);

    }
}

