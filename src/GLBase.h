#ifndef __GLBASE_H__
#define __GLBASE_H__

#include <windows.h>
#include <string>

#ifdef _UNICODE
  #define GString std::wstring
  #define GQuote(str) L##str
  #define GText(str) std::wstring(L##str)
#else
  #define GString std::string
  #define GQuote(str) str
  #define GText(str) std::string(str)
#endif

class GLBase {
  public:
    GLBase(const GString& strWndName = GText("GLBase Window"), 
        int x = -1, int y = -1, int width = 800, int height = 600);
    int Run();

    virtual int OnClose(WPARAM wParam, LPARAM lParam);
    virtual int OnDestroy(WPARAM wParam, LPARAM lParam);
    
    operator HWND() { return this->m_hWnd; }

    ~GLBase();
  private:
  protected:
    GString m_strWndName;
    GString m_strClassName; 
    int m_x;
    int m_y;
    int m_width;
    int m_height;
    HWND m_hWnd;
    virtual int MessagePump();
    static LRESULT CALLBACK _proc(HWND hWnd, 
        UINT uMsg, WPARAM wParam, LPARAM lParam);
};

#endif

