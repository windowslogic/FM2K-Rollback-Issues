// This example draws a rectangle in DirectDraw 7 in a command prompt.
// THIS CODE DOES NOT COMPILE, IT IS FOR DEMONSTRATION PURPOSES ONLY.

#include <windows.h>
#include <ddraw.h>

LPDIRECTDRAW7 lpDD;
LPDIRECTDRAWSURFACE7 lpDDSPrimary;
LPDIRECTDRAWSURFACE7 lpDDSBack;

// Initialises DirectDraw and GDI.
void InitDirectDraw(HWND hwnd) {
    DirectDrawCreateEx(NULL, (void**)&lpDD, IID_IDirectDraw7, NULL);
    lpDD->SetCooperativeLevel(hwnd, DDSCL_FULLSCREEN | DDSCL_EXCLUSIVE);
    lpDD->SetDisplayMode(800, 600, 32);

    DDSURFACEDESC2 ddsd;
    ZeroMemory(&ddsd, sizeof(ddsd));
    ddsd.dwSize = sizeof(ddsd);
    ddsd.dwFlags = DDSD_CAPS;
    ddsd.ddsCaps.dwCaps = DDSCAPS_PRIMARYSURFACE;

    lpDD->CreateSurface(&ddsd, &lpDDSPrimary, NULL);

    ddsd.dwFlags = DDSD_CAPS | DDSD_BACKBUFFERCOUNT;
    ddsd.ddsCaps.dwCaps = DDSCAPS_FLIP | DDSCAPS_COMPLEX | DDSCAPS_BACKBUFFER;
    ddsd.dwBackBufferCount = 1;

    lpDD->CreateSurface(&ddsd, &lpDDSBack, NULL);
}

// Clears buffer.
// Renders a red rectangle on the screen.
// Finally, flips back to the primary surface.
void Render() {
    DDBLTFX ddbltfx;
    ZeroMemory(&ddbltfx, sizeof(ddbltfx));
    ddbltfx.dwSize = sizeof(ddbltfx);
    ddbltfx.dwFillColor = 0x000000; // Black
    lpDDSBack->Blt(NULL, NULL, NULL, DDBLT_COLOR | DDBLT_WAIT, &ddbltfx);
    RECT rect = { 100, 100, 300, 250 };
    HDC hdc;
    lpDDSBack->GetDC(&hdc);
    HBRUSH brush = CreateSolidBrush(RGB(255, 0, 0)); // Red
    FillRect(hdc, &rect, brush);
    lpDDSBack->ReleaseDC(hdc);
    DeleteObject(brush);
    lpDD->FlipToGDISurface();
}

// Releases all objects in memory.
void Cleanup() {
    if (lpDDSBack) lpDDSBack->Release();
    if (lpDDSPrimary) lpDDSPrimary->Release();
    if (lpDD) lpDD->Release();
}

// This code below uses the console window to draw a DirectDraw surface.
// It creates a loop at 60 FPS.
// Finally, runs the cleanup void.
int main() {
    HWND hwnd = GetConsoleWindow();
    InitDirectDraw(hwnd);

    bool running = true;
    while (running) {
        Render();
        Sleep(16);
    }

    Cleanup();
    return 0;
}
