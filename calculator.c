#ifndef UNICODE
#define UNICODE
#endif

#include <windows.h>
#include <stdlib.h>
#include <wchar.h>

#include <stdio.h>

struct StateInfo
{
    wchar_t *quitMessage;
};

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE deprecatedHINSTANCE,
    PSTR lpCmdLine, int nCmdShow)
{
    //Register the window class
    const wchar_t CLASS_NAME[] = L"Sample Window Class";

    WNDCLASS wc = { 0 };

    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;

    RegisterClass(&wc);

    struct StateInfo *pState = malloc(sizeof(struct StateInfo));

    wchar_t quitMessage[] = L"It works!";

    pState->quitMessage = malloc(sizeof(quitMessage));

    wcscpy(pState->quitMessage, quitMessage);

    //sStateInfo.quitMessage = malloc(sizeof(L"Goodbye"));

    wprintf(L"%ls", pState->quitMessage);

    

    if(pState == NULL){
        free(pState->quitMessage);
        free(pState);
        return 14;
    }

    

    // Create the window

    HWND hwnd = CreateWindowEx(
        0,                              // Optional window styles.
        CLASS_NAME,                     // Window class
        L"Learn to Program Windows",    // Window text
        WS_OVERLAPPEDWINDOW,            // Window style

        // Size and position
        CW_USEDEFAULT,                  // x
        CW_USEDEFAULT,                  // y
        CW_USEDEFAULT,                  // Width
        CW_USEDEFAULT,                  // Height

        NULL,                           // Parent window
        NULL,                           // Menu
        hInstance,                      // Instance handle
        pState                          // Additional application data
    );

    if(hwnd == NULL){
        free(pState->quitMessage);
        free(pState);
        return 27;
    }

    ShowWindow(hwnd, nCmdShow);

    // Run the message loop

    MSG msg = { 0 };
    while(GetMessage(&msg, NULL, 0, 0) > 0){
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    free(pState->quitMessage);
    free(pState);
    return 0;
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;

    case WM_CLOSE:
        struct StateInfo *pStateInfo = (struct StateInfo*)GetWindowLongPtr(hwnd, GWLP_USERDATA);

        if (MessageBox(hwnd, pStateInfo->quitMessage, L"My application", MB_OKCANCEL) == IDOK)
        {
            DestroyWindow(hwnd);
        }
        // Else: User canceled. Do nothing.

        
        return 0;

    case WM_CREATE:
        CREATESTRUCT *pCreate = (CREATESTRUCT*)(lParam);
        struct StateInfo *pState = (struct StateInfo*)(pCreate->lpCreateParams);

        SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR)pState);

        return 0;

    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hwnd, &ps);

            // All painting occurs here, between BeginPaint and EndPaint

            FillRect(hdc, &ps.rcPaint, (HBRUSH) (COLOR_HOTLIGHT+1));

            EndPaint(hwnd, &ps);
        }
        return 0;

    default:
        // Implement error message?
        break;
    }

    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}