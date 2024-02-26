#include "pch.h"
#include <Windows.h> // Inclure l'en-tête Windows.h pour les fonctions Windows
#include <tchar.h>   // Inclure l'en-tête tchar.h pour les types TCHAR

#define WIN32_LEAN_AND_MEAN   

#define MAX_NAME_STRING 100 // Définir une taille maximale pour les chaînes de caractères

TCHAR WindowClass[MAX_NAME_STRING]; // Utiliser TCHAR au lieu de WCHAR pour la compatibilité Unicode
TCHAR WindowTitle[MAX_NAME_STRING];

int WindowWidth;
int WindowHeight;

LRESULT CALLBACK WindowProcess(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam); // Ajouter un défaut pour les autres messages
    }
    return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    /*Initialize Global Variables*/
    _tcscpy_s(WindowClass, MAX_NAME_STRING, _T("3D Engine")); // Utiliser _tcscpy_s pour la compatibilité Unicode
    _tcscpy_s(WindowTitle, MAX_NAME_STRING, _T("Window 3D"));

    WindowWidth = 1020;
    WindowHeight = 720;

    /*Create Windows Class*/
    WNDCLASSEX wcex = { sizeof(WNDCLASSEX) }; // Initialiser la taille avec sizeof
    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WindowProcess;
    wcex.hInstance = hInstance;
    wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszClassName = WindowClass;

    if (!RegisterClassEx(&wcex)) // Vérifier si l'enregistrement de la classe a réussi
    {
        MessageBox(NULL, _T("RegisterClassEx Failed"), _T("Error"), MB_ICONERROR | MB_OK);
        return 1;
    }

    /*Create and Display Windows */
    HWND hWnd = CreateWindow(WindowClass, WindowTitle, WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, 0, WindowWidth, WindowHeight, NULL, NULL, hInstance, NULL);
    if (!hWnd)
    {
        MessageBox(NULL, _T("CreateWindow Failed"), _T("Error"), MB_ICONERROR | MB_OK);
        return 1;
    }

    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    /* Listen for messages */
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) // Utiliser GetMessage pour récupérer les messages
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return (int)msg.wParam;
}
