#pragma once

#include <d3d12.h>
#include <dxgi1_6.h>
#include <d3dcompiler.h>
#include <DirectXMath.h>
#include <windows.h>
#include <wrl/client.h>
#include <stdexcept>

using Microsoft::WRL::ComPtr;

class TriangleRenderer {
public:
    TriangleRenderer(HINSTANCE hInstance);
    ~TriangleRenderer();

    int Run();

private:
    bool Initialize();
    void Update();
    void Render();
    void CreatePipeline();
    void CreateVertexBuffer();
    void WaitForPreviousFrame();

    static const UINT FrameCount = 2;

    HINSTANCE m_hInstance;
    HWND m_hwnd;
    UINT m_width;
    UINT m_height;

    ComPtr<IDXGIFactory4> m_dxgiFactory;
    ComPtr<ID3D12Device> m_device;
    ComPtr<ID3D12CommandQueue> m_commandQueue;
    ComPtr<IDXGISwapChain3> m_swapChain;
    ComPtr<ID3D12DescriptorHeap> m_rtvHeap;
    ComPtr<ID3D12Resource> m_renderTargets[FrameCount];
    ComPtr<ID3D12CommandAllocator> m_commandAllocators[FrameCount];
    ComPtr<ID3D12GraphicsCommandList> m_commandList;
    ComPtr<ID3D12PipelineState> m_pipelineState;
    ComPtr<ID3D12Resource> m_vertexBuffer;
    D3D12_VERTEX_BUFFER_VIEW m_vertexBufferView;

    UINT m_frameIndex;
    HANDLE m_fenceEvent;
    ComPtr<ID3D12Fence> m_fence;
    UINT64 m_fenceValue;

    LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
};

