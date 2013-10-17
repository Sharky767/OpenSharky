#include <windows.h>
#include <vector>
#include "GLBase.h"

std::vector<GLBase*> g_base_list;

GLBase::GLBase(const GString& strWndName, int x, int y, 
    int width, int height)
  : m_strWndName(strWndName),
    m_strClassName(GText("GLBase_Class32")),
    m_x(x), m_y(y), m_width(width), m_height(height)
{
  if(x < 0)
    m_x = (::GetSystemMetrics(SM_CXSCREEN) / 2) - (m_width / 2);
  if(y < 0)
    m_y = (::GetSystemMetrics(SM_CYSCREEN) / 2) - (m_height / 2);

}

int GLBase::Run()
{
  WNDCLASSEX wcx;
  
  wcx.cbSize        = sizeof(WNDCLASSEX);
  wcx.style         = CS_HREDRAW | CS_VREDRAW;
  wcx.cbClsExtra    = 0;
  wcx.cbWndExtra    = 0;
  wcx.hCursor       = ::LoadCursor(NULL, IDC_ARROW);
  wcx.hIcon         = ::LoadIcon(NULL, IDI_APPLICATION);
  wcx.hIconSm       = ::LoadIcon(NULL, IDI_APPLICATION);
  wcx.hInstance     = (HINSTANCE)::GetModuleHandle(NULL);
  wcx.hbrBackground = (HBRUSH)(COLOR_BTNFACE+1);
  wcx.lpfnWndProc   = GLBase::_proc;
  wcx.lpszMenuName  = NULL;
  wcx.lpszClassName = m_strClassName.c_str();
  
  if(!RegisterClassEx(&wcx)) {
    ::MessageBox(NULL, GQuote("GLBase Class Registration Failed!"),
        GQuote("Error!"), MB_ICONEXCLAMATION | MB_OK);
    return -1;
  }
  
  m_hWnd = CreateWindowEx(0, m_strClassName.c_str(),
      m_strWndName.c_str(), WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN,
      m_x, m_y, m_width, m_height, HWND_DESKTOP, NULL, 
      (HINSTANCE)::GetModuleHandle(NULL), NULL);

  if(!m_hWnd) {
    ::MessageBox(NULL, GQuote("GLBase Class Window Creation Failed!"),
      GQuote("Error!"), MB_ICONEXCLAMATION | MB_OK);
    return -1;
  }

  ::ShowWindow(m_hWnd, SW_SHOW);
  ::UpdateWindow(m_hWnd);

  g_base_list.push_back(this);

  return MessagePump();
}

int GLBase::OnClose(WPARAM wParam, LPARAM lParam)
{
  ::DestroyWindow(m_hWnd);
  return 0;
}

int GLBase::OnDestroy(WPARAM wParam, LPARAM lParam)
{
  ::PostQuitMessage(0);
  return 0;
}

int GLBase::MessagePump()
{
  MSG msg;
  while(::GetMessage(&msg, NULL, 0, 0) > 0) {
    ::TranslateMessage(&msg);
    ::DispatchMessage(&msg);
  }
  return msg.wParam;
}

LRESULT CALLBACK GLBase::_proc(HWND hWnd, 
    UINT uMsg, WPARAM wParam, LPARAM lParam)
{
  for(auto g : g_base_list) {
    if(g->m_hWnd == hWnd)
    {
      switch(uMsg){
        case WM_CLOSE:
          return g->OnClose(wParam, lParam);
        case WM_DESTROY:
          return g->OnDestroy(wParam, lParam);
      }
    }
  }
  return ::DefWindowProc(hWnd, uMsg, wParam, lParam);
}

GLBase::~GLBase()
{
  std::vector<GLBase*>::iterator it;
  for(it = g_base_list.begin();
      it != g_base_list.end();
      ++it) {
    if(*it == this) {
      g_base_list.erase(it);
      break;
    }
  }
}

