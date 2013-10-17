#include "GLBase.h"

class MyGLWindow : public GLBase
{
  public:
    MyGLWindow()
      : GLBase(GQuote("This is my GL Window!"),
          -1, -1, 800, 600)
    {}
    
    virtual int OnClose(WPARAM wParam, LPARAM lParam)
    {
      int ans = ::MessageBox(*this, GQuote("Are you sure you want to exit?"),
          GQuote("Exit???"), MB_YESNO);

      if(ans == IDYES)
        ::DestroyWindow(*this);

      return 0;
    }

    ~MyGLWindow() {}
  private:
  protected:
};

int WINAPI WinMain(
    HINSTANCE hInstance,
    HINSTANCE hPrevInstance,
    LPSTR lpCmdLine,
    int nCmdShow
    )
{
  MyGLWindow g;
  return g.Run();
}

