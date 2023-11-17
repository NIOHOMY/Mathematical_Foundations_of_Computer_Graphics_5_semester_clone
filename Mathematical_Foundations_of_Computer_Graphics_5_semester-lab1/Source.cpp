#include <Windows.h>
#include <windowsx.h>
#include "AffineTransform.h"
#include "Loader.h"
#include "Render2D.h"

WNDCLASS createWindowClass(HBRUSH bgColor, HCURSOR cursor, HINSTANCE hInstance, HICON icon, LPCWSTR windowName, WNDPROC windowProcedure);
LRESULT CALLBACK windowProcedure(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp);


int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{
	WNDCLASS mainWindow = createWindowClass((HBRUSH)COLOR_WINDOW, LoadCursor(NULL, IDC_ARROW), hInstance, LoadIcon(NULL, IDI_QUESTION), L"MainWndClass", windowProcedure);

	if (!RegisterClassW(&mainWindow))
		return -1;

    CreateWindow(L"MainWndClass", L"MainWindow", WS_OVERLAPPEDWINDOW | WS_VISIBLE, 100, 100, 800, 800, NULL, NULL, hInstance, NULL);

	MSG message = { 0 };
    while (GetMessage(&message, NULL, 0, 0)) {
		TranslateMessage(&message);
		DispatchMessage(&message);
	}

	return 0;
}

WNDCLASS createWindowClass(HBRUSH bgColor, HCURSOR cursor, HINSTANCE hInstance, HICON icon, LPCWSTR windowName, WNDPROC windowProcedure)
{
	WNDCLASS wc = { 0 };

	wc.hCursor = cursor;
	wc.hIcon = icon;
	wc.hInstance = hInstance;
	wc.lpszClassName = windowName;
	wc.hbrBackground = bgColor;
	wc.lpfnWndProc = windowProcedure;

	return wc;
}

LRESULT CALLBACK windowProcedure(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp)
{
    static HDC hdc = NULL; 
    static Render2D render;
    static std::vector<Model2D*> figures;
    static int currentIndex = 0;
    switch (msg)
    {
        case WM_CREATE:
        {
            std::vector<std::string> fileNames = { 
                /*
                */ 
                "triangle.txt", 
                "square.txt",
                "turtle.txt",
                "dove.txt",
                "moth.txt",
            }; 
            
            hdc = GetDC(hWnd);
            for (const std::string& fileName : fileNames)
            {
                Loader loader(fileName);
                std::vector<Vector2D> vertices = loader.vertices();
                std::vector<int> indices = loader.indices();
                figures.push_back(new Model2D(vertices, indices));
            }

            for (Model2D* _model : figures)
            {
                render.addObject(_model);
            }
            break;
        }
        case WM_DESTROY:
            PostQuitMessage(0);
            break;
        case WM_PAINT:
        {
            PAINTSTRUCT ps;
            hdc = BeginPaint(hWnd, &ps);
            render.draw(hdc);
            EndPaint(hWnd, &ps);
            break;
        }
        case VK_LEFT:
            currentIndex--;
            if (currentIndex < 0) {
                currentIndex = figures.size() - 1;
            }
            break;
        case VK_RIGHT:
            currentIndex++;
            if (currentIndex >= figures.size()) {
                currentIndex = 0;
            }
            break;
        case WM_KEYDOWN:
        {
            switch (wp)
            {
            case VK_LEFT:
                currentIndex--;
                if (currentIndex < 0) {
                    currentIndex = figures.size() - 1;
                }
                break;
            case VK_RIGHT:
                currentIndex++;
                if (currentIndex >= figures.size()) {
                    currentIndex = 0;
                }
                break;
            default:
                break;
            }
            Model2D* model = render.getObject(currentIndex);
            
            Vector2D O = model->getOXOYVector();

            double step = 20;
            double alpha = 10;
            double scale = 1.5;

            switch (wp)
            {
                case 'W':
                    model->applyTransformation(Translation(0, -step));
                    break;
                case 'A':
                    model->applyTransformation(Translation(-step, 0));
            
                    break;
                case 'S':
                    model->applyTransformation(Translation(0, step));
            
                    break;
                case 'D':
                    model->applyTransformation(Translation(step, 0));
                    break;
                case 'Z':
                {
                    model->applyTransformation(Scaling((1/scale), (1/scale)) * Translation(O.x(), O.y()));
                    model->applyTransformation(Translation(-O.x(), -O.y()));
                    break;
                }
                case 'X':
                {   
                    model->applyTransformation(Scaling(scale, scale) * Translation(O.x(), O.y()));
                    model->applyTransformation(Translation(-O.x(), -O.y()));
                    break;
                }
                case 'R':
                {
                    model->applyTransformation(ReflectionX()* Translation(O.x(), O.y()));
                    model->applyTransformation(Translation(-O.x(), -O.y()));
                    break;
                }
                case 'F':
                {
                    model->applyTransformation(ReflectionY() * Translation(O.x(), O.y()));
                    model->applyTransformation(Translation(-O.x(), -O.y()));
                    break;
                }
                case 'Q':
                {
                    model->applyTransformation(Rotation(-alpha)* Translation(O.x(), O.y()));
                    model->applyTransformation(Translation(-O.x(), -O.y()));
                    break;
                }
                case 'E':
                {
                    model->applyTransformation(Rotation(alpha)* Translation(O.x(), O.y()));
                    model->applyTransformation(Translation(-O.x(), -O.y()));
                    break;
                }
                break;
            }

            InvalidateRect(hWnd, NULL, TRUE);
            break;
        }
        default:
        {
            if (hWnd == NULL) { // Проверяем значение hWnd перед вызовом DefWindowProc
                OutputDebugStringA("Error: invalid HDC.\n");
            }
            else {
                return DefWindowProc(hWnd, msg, wp, lp);
            }
        }
    }

    return 0;
}

